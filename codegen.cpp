#include "codegen.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "y.tab.h"

enum class TypeKindCg {
    Unknown,
    Integer,
    Char,
    Array,
    Record,
};

struct TypeDesc {
    TypeKindCg kind;
    int low;
    int high;
    TypeDesc* elementType;
    std::vector<std::pair<std::string, TypeDesc*>> fields;
    std::unordered_map<std::string, int> fieldOffset;

    TypeDesc() : kind(TypeKindCg::Unknown), low(0), high(0), elementType(nullptr) {}
};

enum class StorageClass {
    Global,
    Local,
    ParamValue,
    ParamRef,
};

struct VarInfo {
    std::string name;
    StorageClass storage;
    std::string label;
    int offset;
    TypeDesc* type;
};

struct ParamSpec {
    std::string name;
    TypeDesc* type;
    bool isVar;
};

struct ProcInfo {
    std::string name;
    std::string label;
    std::vector<ParamSpec> params;
    TreeNode* procDeclNode;
};

struct AddrResult {
    bool ok;
    std::string addrReg;
    TypeDesc* valueType;
};

class MipsGenerator {
public:
    explicit MipsGenerator(const std::string& outputPath)
        : outputPath_(outputPath),
          errorCount_(0),
          labelSeq_(0),
          tempTop_(0),
          currentReturnLabel_(),
          integerType_(nullptr),
          charType_(nullptr),
          unknownType_(nullptr) {
        tempRegs_ = {"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"};
        integerType_ = makeType(TypeKindCg::Integer);
        charType_ = makeType(TypeKindCg::Char);
        unknownType_ = makeType(TypeKindCg::Unknown);
    }

    CodegenResult run(TreeNode* root) {
        if (root == nullptr || root->nodekind != ProgramK) {
            reportError(0, "invalid AST root for code generation");
            return {false, errorCount_, outputPath_};
        }

        TreeNode* top = (root->firstChild == nullptr) ? nullptr : root->firstChild->sibling;
        collectTypeDecls(top);
        collectGlobalVars(top);
        collectProcedures(top);

        emitData("newline_str: .asciiz \"\\n\"");
        emitData(".align 2");
        for (const auto& kv : globalVars_) {
            int bytes = typeSize(kv.second.type);
            if (bytes <= 0) bytes = 4;
            emitData(kv.second.label + ": .space " + std::to_string(bytes));
        }

        emitTextRaw("main:");
        currentLocals_.clear();
        currentReturnLabel_.clear();
        emitStmtList(findProgramBodyStmtList(root));
        emitText("li $v0, 10");
        emitText("syscall");

        for (const auto& kv : procTable_) {
            emitProcedure(kv.second);
        }

        bool ok = writeAsmFile();
        return {ok && errorCount_ == 0, errorCount_, outputPath_};
    }

private:
    std::string outputPath_;
    int errorCount_;
    int labelSeq_;

    std::vector<std::string> dataLines_;
    std::vector<std::string> textLines_;

    std::vector<std::unique_ptr<TypeDesc>> ownedTypes_;
    std::unordered_map<std::string, TypeDesc*> typeAlias_;
    std::unordered_map<std::string, VarInfo> globalVars_;
    std::unordered_map<std::string, ProcInfo> procTable_;
    std::unordered_map<std::string, VarInfo> currentLocals_;

    std::vector<std::string> tempRegs_;
    int tempTop_;
    std::string currentReturnLabel_;

    TypeDesc* integerType_;
    TypeDesc* charType_;
    TypeDesc* unknownType_;

    void reportError(int line, const std::string& msg) {
        std::cerr << "Codegen error";
        if (line > 0) std::cerr << " at line " << line;
        std::cerr << ": " << msg << std::endl;
        errorCount_++;
    }

    void emitData(const std::string& s) { dataLines_.push_back(s); }

    void emitText(const std::string& s) { textLines_.push_back("    " + s); }

    void emitTextRaw(const std::string& s) { textLines_.push_back(s); }

    std::string newLabel(const std::string& prefix) {
        return prefix + "_" + std::to_string(labelSeq_++);
    }

    std::string allocTemp(int line) {
        if (tempTop_ >= static_cast<int>(tempRegs_.size())) {
            reportError(line, "temporary register pool exhausted");
            return "$t0";
        }
        return tempRegs_[tempTop_++];
    }

    void freeTemp() {
        if (tempTop_ > 0) tempTop_--;
    }

    TypeDesc* makeType(TypeKindCg kind) {
        ownedTypes_.push_back(std::unique_ptr<TypeDesc>(new TypeDesc()));
        ownedTypes_.back()->kind = kind;
        return ownedTypes_.back().get();
    }

    TreeNode* getNthChild(TreeNode* node, int n) {
        if (node == nullptr) return nullptr;
        TreeNode* c = node->firstChild;
        for (int i = 0; c != nullptr && i < n; ++i) c = c->sibling;
        return c;
    }

    TreeNode* unwrapStmtBlock(TreeNode* maybeBlock) {
        if (maybeBlock != nullptr && maybeBlock->nodekind == RoutineK && maybeBlock->kind.routine == RoutineBodyK) {
            return maybeBlock->firstChild;
        }
        return maybeBlock;
    }

    TreeNode* getIdListHead(TreeNode* declOrParam) {
        if (declOrParam == nullptr) return nullptr;
        TreeNode* c = declOrParam->firstChild;
        if (c != nullptr && c->nodekind == ExpK && c->kind.exp == IdK) return c;
        return nullptr;
    }

    TreeNode* findTypeChild(TreeNode* declOrParam) {
        if (declOrParam == nullptr) return nullptr;
        for (TreeNode* c = declOrParam->firstChild; c != nullptr; c = c->sibling) {
            if (c->nodekind == TypeK) return c;
        }
        return nullptr;
    }

    TreeNode* findProgramBodyStmtList(TreeNode* root) {
        TreeNode* cur = root == nullptr ? nullptr : root->firstChild;
        while (cur != nullptr) {
            if (cur->nodekind == RoutineK && cur->kind.routine == RoutineBodyK) {
                return cur->firstChild;
            }
            cur = cur->sibling;
        }
        return nullptr;
    }

    void collectTypeDecls(TreeNode* firstDeclOrBody) {
        typeAlias_["INTEGER"] = integerType_;
        typeAlias_["CHAR"] = charType_;

        for (TreeNode* cur = firstDeclOrBody; cur != nullptr; cur = cur->sibling) {
            if (cur->nodekind != DeclareK) continue;
            if (cur->kind.dec != TypeDecK) continue;
            TreeNode* spec = cur->firstChild;
            typeAlias_[cur->attr.name] = resolveType(spec);
        }
    }

    void collectGlobalVars(TreeNode* firstDeclOrBody) {
        for (TreeNode* cur = firstDeclOrBody; cur != nullptr; cur = cur->sibling) {
            if (cur->nodekind != DeclareK) continue;
            if (cur->kind.dec != VarDecK) continue;

            TreeNode* ids = getIdListHead(cur);
            TreeNode* typeNode = findTypeChild(cur);
            TypeDesc* t = resolveType(typeNode);

            for (TreeNode* id = ids; id != nullptr; id = id->sibling) {
                if (id->nodekind == ExpK && id->kind.exp == IdK) {
                    if (globalVars_.find(id->attr.name) == globalVars_.end()) {
                        globalVars_[id->attr.name] = {id->attr.name, StorageClass::Global, "g_" + id->attr.name, 0, t};
                    }
                }
            }
        }
    }

    void collectProcedures(TreeNode* firstDeclOrBody) {
        for (TreeNode* cur = firstDeclOrBody; cur != nullptr; cur = cur->sibling) {
            if (cur->nodekind != DeclareK || cur->kind.dec != ProcDecK) continue;

            ProcInfo p;
            p.name = cur->attr.name;
            p.label = "proc_" + cur->attr.name;
            p.procDeclNode = cur;

            TreeNode* head = getNthChild(cur, 0);
            TreeNode* params = (head == nullptr) ? nullptr : head->firstChild;
            for (TreeNode* paramDecl = params; paramDecl != nullptr; paramDecl = paramDecl->sibling) {
                if (paramDecl->nodekind != ParamK) continue;
                bool isVar = (paramDecl->kind.param == VarParamK);
                TreeNode* ids = getIdListHead(paramDecl);
                TypeDesc* t = resolveType(findTypeChild(paramDecl));
                for (TreeNode* id = ids; id != nullptr; id = id->sibling) {
                    if (id->nodekind == ExpK && id->kind.exp == IdK) {
                        p.params.push_back({id->attr.name, t, isVar});
                    }
                }
            }

            procTable_[p.name] = p;
        }
    }

    TypeDesc* resolveType(TreeNode* typeNode) {
        if (typeNode == nullptr || typeNode->nodekind != TypeK) return unknownType_;

        if (typeNode->kind.type == BaseTypeK) {
            if (typeNode->attr.name == "INTEGER") return integerType_;
            if (typeNode->attr.name == "CHAR") return charType_;
            return unknownType_;
        }

        if (typeNode->kind.type == AliasTypeK) {
            auto it = typeAlias_.find(typeNode->attr.name);
            if (it != typeAlias_.end()) return it->second;
            return unknownType_;
        }

        if (typeNode->kind.type == ArrayTypeK) {
            TypeDesc* t = makeType(TypeKindCg::Array);
            t->low = typeNode->attr.low;
            t->high = typeNode->attr.high;
            t->elementType = resolveType(typeNode->firstChild);
            return t;
        }

        if (typeNode->kind.type == RecordTypeK) {
            TypeDesc* t = makeType(TypeKindCg::Record);
            int offset = 0;
            for (TreeNode* fieldDecl = typeNode->firstChild; fieldDecl != nullptr; fieldDecl = fieldDecl->sibling) {
                if (fieldDecl->nodekind != DeclareK || fieldDecl->kind.dec != FieldDecK) continue;
                TreeNode* ids = getIdListHead(fieldDecl);
                TypeDesc* ft = resolveType(findTypeChild(fieldDecl));
                int fsize = typeSize(ft);
                if (fsize <= 0) fsize = 4;
                for (TreeNode* id = ids; id != nullptr; id = id->sibling) {
                    if (id->nodekind == ExpK && id->kind.exp == IdK) {
                        t->fields.push_back({id->attr.name, ft});
                        t->fieldOffset[id->attr.name] = offset;
                        offset += fsize;
                    }
                }
            }
            return t;
        }

        return unknownType_;
    }

    int typeSize(TypeDesc* t) {
        if (t == nullptr) return 4;
        if (t->kind == TypeKindCg::Integer || t->kind == TypeKindCg::Char || t->kind == TypeKindCg::Unknown) return 4;
        if (t->kind == TypeKindCg::Array) {
            int count = t->high - t->low + 1;
            if (count < 0) count = 0;
            return count * typeSize(t->elementType);
        }
        if (t->kind == TypeKindCg::Record) {
            int total = 0;
            for (const auto& f : t->fields) total += typeSize(f.second);
            return total;
        }
        return 4;
    }

    void emitStmtList(TreeNode* stmList) {
        for (TreeNode* s = stmList; s != nullptr; s = s->sibling) emitStmt(s);
    }

    const VarInfo* lookupVar(const std::string& name) const {
        auto itLocal = currentLocals_.find(name);
        if (itLocal != currentLocals_.end()) return &itLocal->second;
        auto itGlobal = globalVars_.find(name);
        if (itGlobal != globalVars_.end()) return &itGlobal->second;
        return nullptr;
    }

    void emitProcedure(const ProcInfo& p) {
        currentLocals_.clear();

        int paramOffset = 8;
        for (const auto& prm : p.params) {
            currentLocals_[prm.name] = {
                prm.name,
                prm.isVar ? StorageClass::ParamRef : StorageClass::ParamValue,
                "",
                paramOffset,
                prm.type,
            };
            paramOffset += 4;
        }

        TreeNode* body = getNthChild(p.procDeclNode, 1);
        TreeNode* declOrBody = (body == nullptr) ? nullptr : body->firstChild;

        int localBytes = 0;
        for (TreeNode* cur = declOrBody; cur != nullptr; cur = cur->sibling) {
            if (cur->nodekind == RoutineK && cur->kind.routine == RoutineBodyK) break;
            if (cur->nodekind != DeclareK || cur->kind.dec != VarDecK) continue;

            TreeNode* ids = getIdListHead(cur);
            TypeDesc* t = resolveType(findTypeChild(cur));
            int bytes = typeSize(t);
            if (bytes <= 0) bytes = 4;

            for (TreeNode* id = ids; id != nullptr; id = id->sibling) {
                if (id->nodekind != ExpK || id->kind.exp != IdK) continue;
                localBytes += bytes;
                currentLocals_[id->attr.name] = {
                    id->attr.name,
                    StorageClass::Local,
                    "",
                    -localBytes,
                    t,
                };
            }
        }

        TreeNode* stmtList = nullptr;
        for (TreeNode* cur = declOrBody; cur != nullptr; cur = cur->sibling) {
            if (cur->nodekind == RoutineK && cur->kind.routine == RoutineBodyK) {
                stmtList = cur->firstChild;
                break;
            }
        }

        currentReturnLabel_ = newLabel("ret_" + p.name);

        emitTextRaw(p.label + ":");
        emitText("addiu $sp, $sp, -8");
        emitText("sw $ra, 4($sp)");
        emitText("sw $fp, 0($sp)");
        emitText("move $fp, $sp");
        if (localBytes > 0) emitText("addiu $sp, $sp, -" + std::to_string(localBytes));

        emitStmtList(stmtList);

        emitTextRaw(currentReturnLabel_ + ":");
        emitText("move $sp, $fp");
        emitText("lw $fp, 0($sp)");
        emitText("lw $ra, 4($sp)");
        emitText("addiu $sp, $sp, 8");
        emitText("jr $ra");

        currentLocals_.clear();
        currentReturnLabel_.clear();
    }

    void emitStmt(TreeNode* s) {
        if (s == nullptr || s->nodekind != StmtK) return;

        switch (s->kind.stmt) {
            case AssignK: {
                TreeNode* lhs = getNthChild(s, 0);
                TreeNode* rhs = getNthChild(s, 1);
                AddrResult addr = emitLValueAddress(lhs);
                std::string r = emitExp(rhs);
                if (addr.ok) emitText("sw " + r + ", 0(" + addr.addrReg + ")");
                freeTemp();
                if (addr.ok) freeTemp();
                break;
            }
            case ReadK: {
                TreeNode* var = getNthChild(s, 0);
                AddrResult addr = emitLValueAddress(var);
                emitText("li $v0, 5");
                emitText("syscall");
                if (addr.ok) {
                    emitText("sw $v0, 0(" + addr.addrReg + ")");
                    freeTemp();
                }
                break;
            }
            case WriteK: {
                TreeNode* exp = getNthChild(s, 0);
                std::string r = emitExp(exp);
                emitText("move $a0, " + r);
                emitText("li $v0, 1");
                emitText("syscall");
                emitText("la $a0, newline_str");
                emitText("li $v0, 4");
                emitText("syscall");
                freeTemp();
                break;
            }
            case IfK: {
                TreeNode* cond = getNthChild(s, 0);
                TreeNode* thenList = unwrapStmtBlock(getNthChild(s, 1));
                TreeNode* elseList = unwrapStmtBlock(getNthChild(s, 2));
                std::string lElse = newLabel("if_else");
                std::string lEnd = newLabel("if_end");

                std::string rc = emitExp(cond);
                emitText("beq " + rc + ", $zero, " + lElse);
                freeTemp();

                emitStmtList(thenList);
                emitText("j " + lEnd);
                emitTextRaw(lElse + ":");
                emitStmtList(elseList);
                emitTextRaw(lEnd + ":");
                break;
            }
            case WhileK: {
                TreeNode* cond = getNthChild(s, 0);
                TreeNode* body = getNthChild(s, 1);
                std::string lStart = newLabel("while_begin");
                std::string lEnd = newLabel("while_end");

                emitTextRaw(lStart + ":");
                std::string rc = emitExp(cond);
                emitText("beq " + rc + ", $zero, " + lEnd);
                freeTemp();
                emitStmtList(body);
                emitText("j " + lStart);
                emitTextRaw(lEnd + ":");
                break;
            }
            case CallK:
                emitCall(s);
                break;
            case ReturnK:
                if (!currentReturnLabel_.empty()) emitText("j " + currentReturnLabel_);
                break;
        }
    }

    void emitCall(TreeNode* s) {
        auto it = procTable_.find(s->attr.name);
        if (it == procTable_.end()) {
            reportError(s->lineno, "unknown procedure '" + s->attr.name + "'");
            return;
        }

        const ProcInfo& p = it->second;
        std::vector<TreeNode*> args;
        for (TreeNode* a = s->firstChild; a != nullptr; a = a->sibling) args.push_back(a);

        if (args.size() != p.params.size()) {
            reportError(s->lineno, "procedure argument count mismatch for '" + s->attr.name + "'");
            return;
        }

        for (int i = static_cast<int>(args.size()) - 1; i >= 0; --i) {
            if (p.params[i].isVar) {
                AddrResult ar = emitLValueAddress(args[i]);
                if (!ar.ok) {
                    reportError(args[i]->lineno, "VAR argument must be an lvalue");
                    continue;
                }
                emitText("addiu $sp, $sp, -4");
                emitText("sw " + ar.addrReg + ", 0($sp)");
                freeTemp();
            } else {
                std::string rv = emitExp(args[i]);
                emitText("addiu $sp, $sp, -4");
                emitText("sw " + rv + ", 0($sp)");
                freeTemp();
            }
        }

        emitText("jal " + p.label);
        if (!args.empty()) emitText("addiu $sp, $sp, " + std::to_string(static_cast<int>(args.size()) * 4));
    }

    std::string emitExp(TreeNode* e) {
        if (e == nullptr || e->nodekind != ExpK) {
            reportError(0, "invalid expression node");
            return allocTemp(0);
        }

        if (e->kind.exp == ConstK) {
            std::string r = allocTemp(e->lineno);
            emitText("li " + r + ", " + std::to_string(e->attr.val));
            return r;
        }

        if (e->kind.exp == IdK) {
            AddrResult addr = emitLValueAddress(e);
            std::string r = addr.ok ? addr.addrReg : allocTemp(e->lineno);
            if (!addr.ok) emitText("move " + r + ", $zero");
            else emitText("lw " + r + ", 0(" + addr.addrReg + ")");
            return r;
        }

        if (e->kind.exp == UnaryOpK) {
            TreeNode* operand = e->firstChild;
            std::string ro = emitExp(operand);
            if (e->attr.op == MINUS) emitText("subu " + ro + ", $zero, " + ro);
            else if (e->attr.op == NOT) emitText("seq " + ro + ", " + ro + ", $zero");
            return ro;
        }

        if (e->kind.exp == OpK) {
            if (e->attr.op == DOT || e->attr.op == LMIDPAREN) {
                AddrResult addr = emitLValueAddress(e);
                std::string r = addr.ok ? addr.addrReg : allocTemp(e->lineno);
                if (!addr.ok) emitText("move " + r + ", $zero");
                else emitText("lw " + r + ", 0(" + addr.addrReg + ")");
                return r;
            }

            TreeNode* lhs = getNthChild(e, 0);
            TreeNode* rhs = getNthChild(e, 1);
            std::string rl = emitExp(lhs);
            std::string rr = emitExp(rhs);

            switch (e->attr.op) {
                case PLUS: emitText("addu " + rl + ", " + rl + ", " + rr); break;
                case MINUS: emitText("subu " + rl + ", " + rl + ", " + rr); break;
                case TIMES: emitText("mul " + rl + ", " + rl + ", " + rr); break;
                case OVER:
                    emitText("div " + rl + ", " + rr);
                    emitText("mflo " + rl);
                    break;
                case LT: emitText("slt " + rl + ", " + rl + ", " + rr); break;
                case GT: emitText("sgt " + rl + ", " + rl + ", " + rr); break;
                case LE: emitText("sle " + rl + ", " + rl + ", " + rr); break;
                case GE: emitText("sge " + rl + ", " + rl + ", " + rr); break;
                case EQ: emitText("seq " + rl + ", " + rl + ", " + rr); break;
                case NE: emitText("sne " + rl + ", " + rl + ", " + rr); break;
                case AND: emitText("and " + rl + ", " + rl + ", " + rr); break;
                case OR: emitText("or " + rl + ", " + rl + ", " + rr); break;
                default:
                    reportError(e->lineno, "unsupported operator in code generation");
                    break;
            }

            freeTemp();
            return rl;
        }

        reportError(e->lineno, "unknown expression kind");
        return allocTemp(e->lineno);
    }

    AddrResult emitLValueAddress(TreeNode* e) {
        if (e == nullptr || e->nodekind != ExpK) {
            reportError(0, "invalid lvalue node");
            return {false, "", unknownType_};
        }

        if (e->kind.exp == IdK) {
            const VarInfo* v = lookupVar(e->attr.name);
            if (v == nullptr) {
                reportError(e->lineno, "unknown variable '" + e->attr.name + "'");
                return {false, "", unknownType_};
            }

            std::string ra = allocTemp(e->lineno);
            if (v->storage == StorageClass::Global) {
                emitText("la " + ra + ", " + v->label);
            } else if (v->storage == StorageClass::Local || v->storage == StorageClass::ParamValue) {
                emitText("addiu " + ra + ", $fp, " + std::to_string(v->offset));
            } else {
                emitText("lw " + ra + ", " + std::to_string(v->offset) + "($fp)");
            }
            return {true, ra, v->type};
        }

        if (e->kind.exp == OpK && e->attr.op == LMIDPAREN) {
            TreeNode* base = getNthChild(e, 0);
            TreeNode* idx = getNthChild(e, 1);

            AddrResult b = emitLValueAddress(base);
            std::string ri = emitExp(idx);
            if (!b.ok) {
                freeTemp();
                return {false, "", unknownType_};
            }

            if (b.valueType == nullptr || b.valueType->kind != TypeKindCg::Array) {
                reportError(e->lineno, "indexed target is not an array");
                freeTemp();
                return {false, b.addrReg, unknownType_};
            }

            emitText("addiu " + ri + ", " + ri + ", " + std::to_string(-b.valueType->low));
            int elemSize = typeSize(b.valueType->elementType);
            if (elemSize <= 0) elemSize = 4;

            std::string rs = allocTemp(e->lineno);
            emitText("li " + rs + ", " + std::to_string(elemSize));
            emitText("mul " + ri + ", " + ri + ", " + rs);
            emitText("addu " + b.addrReg + ", " + b.addrReg + ", " + ri);

            freeTemp();
            freeTemp();

            return {true, b.addrReg, b.valueType->elementType};
        }

        if (e->kind.exp == OpK && e->attr.op == DOT) {
            TreeNode* base = getNthChild(e, 0);
            TreeNode* field = getNthChild(e, 1);
            AddrResult b = emitLValueAddress(base);
            if (!b.ok) return {false, "", unknownType_};

            if (b.valueType == nullptr || b.valueType->kind != TypeKindCg::Record) {
                reportError(e->lineno, "field target is not a record");
                return {false, b.addrReg, unknownType_};
            }

            if (field == nullptr || field->nodekind != ExpK || field->kind.exp != IdK) {
                reportError(e->lineno, "invalid field selector");
                return {false, b.addrReg, unknownType_};
            }

            auto itOff = b.valueType->fieldOffset.find(field->attr.name);
            if (itOff == b.valueType->fieldOffset.end()) {
                reportError(e->lineno, "unknown field '" + field->attr.name + "'");
                return {false, b.addrReg, unknownType_};
            }

            emitText("addiu " + b.addrReg + ", " + b.addrReg + ", " + std::to_string(itOff->second));

            TypeDesc* fieldType = unknownType_;
            for (const auto& f : b.valueType->fields) {
                if (f.first == field->attr.name) {
                    fieldType = f.second;
                    break;
                }
            }

            return {true, b.addrReg, fieldType};
        }

        reportError(e->lineno, "unsupported lvalue shape");
        return {false, "", unknownType_};
    }

    bool writeAsmFile() {
        std::ofstream out(outputPath_);
        if (!out.is_open()) {
            reportError(0, "cannot open output asm file: " + outputPath_);
            return false;
        }

        out << ".data\n";
        for (const auto& l : dataLines_) out << l << "\n";
        out << "\n.text\n";
        out << ".globl main\n";
        for (const auto& l : textLines_) out << l << "\n";

        return true;
    }
};

CodegenResult generateMips32(TreeNode* root, const std::string& outputAsmPath) {
    MipsGenerator g(outputAsmPath);
    return g.run(root);
}
