#include "semantic.h"
#include "y.tab.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

enum class TypeKindEx {
    Unknown,
    Integer,
    Char,
    Boolean,
    Array,
    Record,
};

struct TypeInfo {
    TypeKindEx kind;
    int low;
    int high;
    TypeInfo* elementType;
    std::unordered_map<std::string, TypeInfo*> recordFields;

    TypeInfo()
        : kind(TypeKindEx::Unknown), low(0), high(0), elementType(nullptr) {}
};

enum class SymbolKind {
    Variable,
    Procedure,
    Parameter,
};

struct ParamInfo {
    std::string name;
    TypeInfo* type;
    bool isVarParam;
};

struct SymbolInfo {
    SymbolKind kind;
    TypeInfo* type;
    std::vector<ParamInfo> params;
};

class SemanticAnalyzer {
public:
    SemanticAnalyzer()
        : errors_(0) {
        integerType_ = createType(TypeKindEx::Integer);
        charType_ = createType(TypeKindEx::Char);
        booleanType_ = createType(TypeKindEx::Boolean);
    }

    SemanticResult analyze(TreeNode* root) {
        if (root == nullptr) {
            return {0};
        }

        enterScope();
        defineType("INTEGER", integerType_, 0);
        defineType("CHAR", charType_, 0);

        if (root->nodekind == ProgramK) {
            TreeNode* cur = (root->firstChild == nullptr) ? nullptr : root->firstChild->sibling;
            analyzeDeclAndBodyList(cur);
        }

        leaveScope();
        return {errors_};
    }

private:
    std::vector<std::unordered_map<std::string, SymbolInfo>> symbolScopes_;
    std::vector<std::unordered_map<std::string, TypeInfo*>> typeScopes_;
    std::vector<TypeInfo*> ownedTypes_;
    int errors_;

    TypeInfo* integerType_;
    TypeInfo* charType_;
    TypeInfo* booleanType_;

    void reportError(int line, const std::string& message) {
        std::cerr << "Semantic error at line " << line << ": " << message << std::endl;
        errors_++;
    }

    void enterScope() {
        symbolScopes_.push_back({});
        typeScopes_.push_back({});
    }

    void leaveScope() {
        if (!symbolScopes_.empty()) symbolScopes_.pop_back();
        if (!typeScopes_.empty()) typeScopes_.pop_back();
    }

    TypeInfo* createType(TypeKindEx kind) {
        TypeInfo* t = new TypeInfo();
        t->kind = kind;
        ownedTypes_.push_back(t);
        return t;
    }

    bool defineType(const std::string& name, TypeInfo* type, int line) {
        auto& scope = typeScopes_.back();
        if (scope.find(name) != scope.end()) {
            reportError(line, "type '" + name + "' is redefined in the same scope");
            return false;
        }
        scope[name] = type;
        return true;
    }

    TypeInfo* findType(const std::string& name) {
        for (int i = static_cast<int>(typeScopes_.size()) - 1; i >= 0; --i) {
            auto it = typeScopes_[i].find(name);
            if (it != typeScopes_[i].end()) {
                return it->second;
            }
        }
        return nullptr;
    }

    bool defineSymbol(const std::string& name, const SymbolInfo& symbol, int line) {
        auto& scope = symbolScopes_.back();
        if (scope.find(name) != scope.end()) {
            reportError(line, "identifier '" + name + "' is redefined in the same scope");
            return false;
        }
        scope[name] = symbol;
        return true;
    }

    SymbolInfo* findSymbol(const std::string& name) {
        for (int i = static_cast<int>(symbolScopes_.size()) - 1; i >= 0; --i) {
            auto it = symbolScopes_[i].find(name);
            if (it != symbolScopes_[i].end()) {
                return &it->second;
            }
        }
        return nullptr;
    }

    TreeNode* getNthChild(TreeNode* node, int n) {
        if (node == nullptr) return nullptr;
        TreeNode* c = node->firstChild;
        for (int i = 0; c != nullptr && i < n; ++i) {
            c = c->sibling;
        }
        return c;
    }

    void analyzeDeclList(TreeNode* decl) {
        for (TreeNode* cur = decl; cur != nullptr; cur = cur->sibling) {
            if (cur->nodekind != DeclareK) continue;

            switch (cur->kind.dec) {
                case TypeDecK:
                    analyzeTypeDecl(cur);
                    break;
                case VarDecK:
                    analyzeVarDecl(cur, SymbolKind::Variable);
                    break;
                case ProcDecK:
                    analyzeProcDecl(cur);
                    break;
                case FieldDecK:
                    break;
            }
        }
    }

    void analyzeDeclAndBodyList(TreeNode* firstNode) {
        for (TreeNode* cur = firstNode; cur != nullptr; cur = cur->sibling) {
            if (cur->nodekind == DeclareK) {
                switch (cur->kind.dec) {
                    case TypeDecK:
                        analyzeTypeDecl(cur);
                        break;
                    case VarDecK:
                        analyzeVarDecl(cur, SymbolKind::Variable);
                        break;
                    case ProcDecK:
                        analyzeProcDecl(cur);
                        break;
                    case FieldDecK:
                        break;
                }
                continue;
            }

            if (cur->nodekind == RoutineK && cur->kind.routine == RoutineBodyK) {
                analyzeRoutineBody(cur);
                break;
            }
        }
    }

    TypeInfo* resolveTypeNode(TreeNode* typeNode) {
        if (typeNode == nullptr || typeNode->nodekind != TypeK) {
            return createType(TypeKindEx::Unknown);
        }

        if (typeNode->kind.type == BaseTypeK) {
            if (typeNode->attr.name == "INTEGER") return integerType_;
            if (typeNode->attr.name == "CHAR") return charType_;
            reportError(typeNode->lineno, "unknown base type '" + typeNode->attr.name + "'");
            return createType(TypeKindEx::Unknown);
        }

        if (typeNode->kind.type == AliasTypeK) {
            TypeInfo* alias = findType(typeNode->attr.name);
            if (alias == nullptr) {
                reportError(typeNode->lineno, "undefined type alias '" + typeNode->attr.name + "'");
                return createType(TypeKindEx::Unknown);
            }
            return alias;
        }

        if (typeNode->kind.type == ArrayTypeK) {
            TypeInfo* arr = createType(TypeKindEx::Array);
            arr->low = typeNode->attr.low;
            arr->high = typeNode->attr.high;
            arr->elementType = resolveTypeNode(typeNode->firstChild);
            if (arr->low > arr->high) {
                reportError(typeNode->lineno, "array lower bound is greater than upper bound");
            }
            return arr;
        }

        if (typeNode->kind.type == RecordTypeK) {
            TypeInfo* rec = createType(TypeKindEx::Record);
            TreeNode* fieldDecl = typeNode->firstChild;
            for (TreeNode* f = fieldDecl; f != nullptr; f = f->sibling) {
                if (f->nodekind != DeclareK || f->kind.dec != FieldDecK) continue;
                TreeNode* ids = getNthChild(f, 0);
                TreeNode* fTypeNode = getNthChild(f, 1);
                TypeInfo* ft = resolveTypeNode(fTypeNode);
                for (TreeNode* id = ids; id != nullptr; id = id->sibling) {
                    if (id->nodekind != ExpK || id->kind.exp != IdK) continue;
                    if (rec->recordFields.find(id->attr.name) != rec->recordFields.end()) {
                        reportError(id->lineno, "field '" + id->attr.name + "' is duplicated in record type");
                    } else {
                        rec->recordFields[id->attr.name] = ft;
                    }
                }
            }
            return rec;
        }

        return createType(TypeKindEx::Unknown);
    }

    void analyzeTypeDecl(TreeNode* node) {
        TypeInfo* t = resolveTypeNode(node->firstChild);
        defineType(node->attr.name, t, node->lineno);
    }

    void analyzeVarDecl(TreeNode* node, SymbolKind kind) {
        TreeNode* ids = getNthChild(node, 0);
        TreeNode* typeNode = getNthChild(node, 1);
        TypeInfo* t = resolveTypeNode(typeNode);

        for (TreeNode* id = ids; id != nullptr; id = id->sibling) {
            if (id->nodekind != ExpK || id->kind.exp != IdK) continue;
            SymbolInfo sym;
            sym.kind = kind;
            sym.type = t;
            defineSymbol(id->attr.name, sym, id->lineno);
        }
    }

    std::vector<ParamInfo> parseParamList(TreeNode* paramListNode) {
        std::vector<ParamInfo> params;
        for (TreeNode* p = paramListNode; p != nullptr; p = p->sibling) {
            if (p->nodekind != ParamK) continue;
            bool isVar = (p->kind.param == VarParamK);
            TreeNode* ids = getNthChild(p, 0);
            TreeNode* typeNode = getNthChild(p, 1);
            TypeInfo* pt = resolveTypeNode(typeNode);
            for (TreeNode* id = ids; id != nullptr; id = id->sibling) {
                if (id->nodekind != ExpK || id->kind.exp != IdK) continue;
                params.push_back({id->attr.name, pt, isVar});
            }
        }
        return params;
    }

    void analyzeProcDecl(TreeNode* node) {
        TreeNode* head = getNthChild(node, 0);
        TreeNode* body = getNthChild(node, 1);

        TreeNode* paramList = nullptr;
        if (head != nullptr && head->nodekind == RoutineK) {
            paramList = head->firstChild;
        }

        SymbolInfo proc;
        proc.kind = SymbolKind::Procedure;
        proc.type = nullptr;
        proc.params = parseParamList(paramList);
        defineSymbol(node->attr.name, proc, node->lineno);

        enterScope();

        for (const auto& p : proc.params) {
            SymbolInfo paramSym;
            paramSym.kind = SymbolKind::Parameter;
            paramSym.type = p.type;
            defineSymbol(p.name, paramSym, node->lineno);
        }

        TreeNode* bodyFirst = nullptr;
        if (body != nullptr && body->nodekind == RoutineK) {
            bodyFirst = body->firstChild;
        }
        analyzeDeclAndBodyList(bodyFirst);

        leaveScope();
    }

    bool isNumeric(TypeInfo* t) {
        return t != nullptr && t->kind == TypeKindEx::Integer;
    }

    bool isBoolean(TypeInfo* t) {
        return t != nullptr && t->kind == TypeKindEx::Boolean;
    }

    bool sameType(TypeInfo* a, TypeInfo* b) {
        if (a == b) return true;
        if (a == nullptr || b == nullptr) return false;
        if (a->kind != b->kind) return false;

        if (a->kind == TypeKindEx::Array) {
            return a->low == b->low && a->high == b->high && sameType(a->elementType, b->elementType);
        }

        if (a->kind == TypeKindEx::Record) {
            if (a->recordFields.size() != b->recordFields.size()) return false;
            for (const auto& kv : a->recordFields) {
                auto it = b->recordFields.find(kv.first);
                if (it == b->recordFields.end()) return false;
                if (!sameType(kv.second, it->second)) return false;
            }
            return true;
        }

        return true;
    }

    TypeInfo* analyzeVariable(TreeNode* varNode) {
        if (varNode == nullptr || varNode->nodekind != ExpK) {
            return createType(TypeKindEx::Unknown);
        }

        if (varNode->kind.exp == IdK) {
            SymbolInfo* sym = findSymbol(varNode->attr.name);
            if (sym == nullptr) {
                reportError(varNode->lineno, "undefined identifier '" + varNode->attr.name + "'");
                return createType(TypeKindEx::Unknown);
            }
            if (sym->kind == SymbolKind::Procedure) {
                reportError(varNode->lineno, "procedure name '" + varNode->attr.name + "' cannot be used as a variable");
                return createType(TypeKindEx::Unknown);
            }
            return sym->type;
        }

        if (varNode->kind.exp == OpK && varNode->attr.op == LMIDPAREN) {
            TreeNode* base = getNthChild(varNode, 0);
            TreeNode* idx = getNthChild(varNode, 1);
            TypeInfo* baseType = analyzeVariable(base);
            TypeInfo* idxType = analyzeExp(idx);
            if (!isNumeric(idxType)) {
                reportError(varNode->lineno, "array index must be INTEGER");
            }
            if (baseType == nullptr || baseType->kind != TypeKindEx::Array) {
                reportError(varNode->lineno, "indexed object is not an array");
                return createType(TypeKindEx::Unknown);
            }
            return baseType->elementType;
        }

        if (varNode->kind.exp == OpK && varNode->attr.op == DOT) {
            TreeNode* base = getNthChild(varNode, 0);
            TreeNode* fieldId = getNthChild(varNode, 1);
            TypeInfo* baseType = analyzeVariable(base);
            if (baseType == nullptr || baseType->kind != TypeKindEx::Record) {
                reportError(varNode->lineno, "field selection target is not a record");
                return createType(TypeKindEx::Unknown);
            }
            if (fieldId == nullptr || fieldId->nodekind != ExpK || fieldId->kind.exp != IdK) {
                return createType(TypeKindEx::Unknown);
            }
            auto it = baseType->recordFields.find(fieldId->attr.name);
            if (it == baseType->recordFields.end()) {
                reportError(fieldId->lineno, "field '" + fieldId->attr.name + "' not found in record");
                return createType(TypeKindEx::Unknown);
            }
            return it->second;
        }

        return createType(TypeKindEx::Unknown);
    }

    TypeInfo* analyzeExp(TreeNode* exp) {
        if (exp == nullptr) return createType(TypeKindEx::Unknown);
        if (exp->nodekind != ExpK) return createType(TypeKindEx::Unknown);

        if (exp->kind.exp == ConstK) {
            if (exp->type == Char) return charType_;
            return integerType_;
        }

        if (exp->kind.exp == IdK) {
            return analyzeVariable(exp);
        }

        if (exp->kind.exp == UnaryOpK) {
            TypeInfo* operand = analyzeExp(exp->firstChild);
            if (exp->attr.op == NOT) {
                if (!isBoolean(operand)) {
                    reportError(exp->lineno, "NOT operand must be BOOLEAN");
                }
                return booleanType_;
            }
            if (!isNumeric(operand)) {
                reportError(exp->lineno, "unary +/- operand must be INTEGER");
            }
            return integerType_;
        }

        if (exp->kind.exp == OpK) {
            if (exp->attr.op == DOT || exp->attr.op == LMIDPAREN) {
                return analyzeVariable(exp);
            }

            TypeInfo* lhs = analyzeExp(getNthChild(exp, 0));
            TypeInfo* rhs = analyzeExp(getNthChild(exp, 1));

            switch (exp->attr.op) {
                case PLUS:
                case MINUS:
                case TIMES:
                case OVER:
                    if (!isNumeric(lhs) || !isNumeric(rhs)) {
                        reportError(exp->lineno, "arithmetic operands must be INTEGER");
                    }
                    return integerType_;
                case AND:
                case OR:
                    if (!isBoolean(lhs) || !isBoolean(rhs)) {
                        reportError(exp->lineno, "logical operands must be BOOLEAN");
                    }
                    return booleanType_;
                case LT:
                case LE:
                case GT:
                case GE:
                case EQ:
                case NE:
                    if (!sameType(lhs, rhs)) {
                        reportError(exp->lineno, "comparison operands have incompatible types");
                    }
                    return booleanType_;
                default:
                    return createType(TypeKindEx::Unknown);
            }
        }

        return createType(TypeKindEx::Unknown);
    }

    void analyzeCall(TreeNode* stmt) {
        SymbolInfo* sym = findSymbol(stmt->attr.name);
        if (sym == nullptr) {
            reportError(stmt->lineno, "undefined procedure '" + stmt->attr.name + "'");
            return;
        }
        if (sym->kind != SymbolKind::Procedure) {
            reportError(stmt->lineno, "identifier '" + stmt->attr.name + "' is not a procedure");
            return;
        }

        std::vector<TreeNode*> actualArgs;
        for (TreeNode* a = stmt->firstChild; a != nullptr; a = a->sibling) {
            actualArgs.push_back(a);
        }

        if (actualArgs.size() != sym->params.size()) {
            reportError(stmt->lineno, "procedure '" + stmt->attr.name + "' argument count mismatch");
            for (TreeNode* arg : actualArgs) analyzeExp(arg);
            return;
        }

        for (size_t i = 0; i < actualArgs.size(); ++i) {
            TypeInfo* actualType = analyzeExp(actualArgs[i]);
            TypeInfo* formalType = sym->params[i].type;
            if (!sameType(actualType, formalType)) {
                reportError(actualArgs[i]->lineno, "argument type mismatch in call to '" + stmt->attr.name + "'");
            }
            if (sym->params[i].isVarParam) {
                TreeNode* arg = actualArgs[i];
                bool isLValue = (arg->nodekind == ExpK) &&
                                (arg->kind.exp == IdK ||
                                 (arg->kind.exp == OpK && (arg->attr.op == DOT || arg->attr.op == LMIDPAREN)));
                if (!isLValue) {
                    reportError(arg->lineno, "VAR parameter requires a variable argument");
                }
            }
        }
    }

    void analyzeStmt(TreeNode* stmt) {
        if (stmt == nullptr || stmt->nodekind != StmtK) return;

        switch (stmt->kind.stmt) {
            case AssignK: {
                TreeNode* lhsNode = getNthChild(stmt, 0);
                TreeNode* rhsNode = getNthChild(stmt, 1);
                TypeInfo* lhsType = analyzeVariable(lhsNode);
                TypeInfo* rhsType = analyzeExp(rhsNode);
                if (!sameType(lhsType, rhsType)) {
                    reportError(stmt->lineno, "assignment type mismatch");
                }
                break;
            }
            case IfK: {
                TreeNode* cond = getNthChild(stmt, 0);
                TypeInfo* condType = analyzeExp(cond);
                if (!isBoolean(condType)) {
                    reportError(stmt->lineno, "IF condition must be BOOLEAN");
                }
                analyzeStmtList(getNthChild(stmt, 1));
                analyzeStmtList(getNthChild(stmt, 2));
                break;
            }
            case WhileK: {
                TreeNode* cond = getNthChild(stmt, 0);
                TypeInfo* condType = analyzeExp(cond);
                if (!isBoolean(condType)) {
                    reportError(stmt->lineno, "WHILE condition must be BOOLEAN");
                }
                analyzeStmtList(getNthChild(stmt, 1));
                break;
            }
            case ReadK: {
                TreeNode* var = getNthChild(stmt, 0);
                TypeInfo* t = analyzeVariable(var);
                if (t == nullptr || (t->kind != TypeKindEx::Integer && t->kind != TypeKindEx::Char)) {
                    reportError(stmt->lineno, "READ target must be INTEGER or CHAR variable");
                }
                break;
            }
            case WriteK: {
                TreeNode* e = getNthChild(stmt, 0);
                analyzeExp(e);
                break;
            }
            case CallK:
                analyzeCall(stmt);
                break;
            case ReturnK:
                break;
        }
    }

    void analyzeStmtList(TreeNode* stmList) {
        for (TreeNode* s = stmList; s != nullptr; s = s->sibling) {
            analyzeStmt(s);
        }
    }

    void analyzeRoutineBody(TreeNode* routineBody) {
        if (routineBody == nullptr) return;
        if (routineBody->nodekind != RoutineK || routineBody->kind.routine != RoutineBodyK) return;
        analyzeStmtList(routineBody->firstChild);
    }
};

SemanticResult analyzeSemantics(TreeNode* root) {
    SemanticAnalyzer analyzer;
    return analyzer.analyze(root);
}
