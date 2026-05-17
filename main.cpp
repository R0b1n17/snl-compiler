#include <iostream>
#include <stdio.h>
#include <string>

#include "codegen.h"
#include "globals.h"
#include "semantic.h"
#include "y.tab.h"

extern int yyparse();
extern int yylex();
extern FILE* yyin;
extern int lineno;
extern TreeNode* root;

using namespace std;

static string opToString(int op) {
    switch (op) {
        case PLUS: return "+";
        case MINUS: return "-";
        case TIMES: return "*";
        case OVER: return "/";
        case LT: return "<";
        case LE: return "<=";
        case GT: return ">";
        case GE: return ">=";
        case EQ: return "=";
        case NE: return "<>";
        case AND: return "AND";
        case OR: return "OR";
        case NOT: return "NOT";
        case DOT: return ".";
        case LMIDPAREN: return "[]";
        default: return "?";
    }
}

static string tokenToString(int token) {
    switch (token) {
        case PROGRAM: return "PROGRAM";
        case PROCEDURE: return "PROCEDURE";
        case TYPE: return "TYPE";
        case VAR: return "VAR";
        case IF: return "IF";
        case THEN: return "THEN";
        case ELSE: return "ELSE";
        case FI: return "FI";
        case WHILE: return "WHILE";
        case DO: return "DO";
        case ENDWH: return "ENDWH";
        case BEGIN_SYM: return "BEGIN";
        case END: return "END";
        case READ: return "READ";
        case WRITE: return "WRITE";
        case ARRAY: return "ARRAY";
        case OF: return "OF";
        case RECORD: return "RECORD";
        case RETURN: return "RETURN";
        case CALL: return "CALL";
        case INTEGER_T: return "INTEGER";
        case CHAR_T: return "CHAR";
        case ASSIGN: return ":=";
        case EQ: return "=";
        case LT: return "<";
        case LE: return "<=";
        case GT: return ">";
        case GE: return ">=";
        case NE: return "<>";
        case PLUS: return "+";
        case MINUS: return "-";
        case TIMES: return "*";
        case OVER: return "/";
        case AND: return "AND";
        case OR: return "OR";
        case NOT: return "NOT";
        case LPAREN: return "(";
        case RPAREN: return ")";
        case LMIDPAREN: return "[";
        case RMIDPAREN: return "]";
        case DOT: return ".";
        case COLON: return ":";
        case SEMI: return ";";
        case COMMA: return ",";
        case RANGE: return "..";
        case ID: return "ID";
        case NUM: return "NUM";
        case CHARC: return "CHARC";
        case ERROR: return "ERROR";
        case 0: return "EOF";
        default: return "UNKNOWN";
    }
}

static int dumpTokens() {
    int token = 0;
    while ((token = yylex()) != 0) {
        cout << "[Line " << lineno << "] " << tokenToString(token);
        if (token == ID) {
            cout << "\t" << yylval.name;
        } else if (token == NUM || token == CHARC) {
            cout << "\t" << yylval.val;
        }
        cout << endl;
        if (token == ERROR) {
            return 1;
        }
    }
    cout << "[Line " << lineno << "] EOF" << endl;
    return 0;
}

void printTree(TreeNode* t, int indent) {
    while (t != nullptr) {
        for (int i = 0; i < indent; i++) cout << "  ";

        switch (t->nodekind) {
            case ProgramK:
                cout << "[Program]" << endl;
                break;
            case RoutineK:
                if (t->kind.routine == RoutineHeadK) {
                    cout << "[RoutineHead] " << t->attr.name << endl;
                } else {
                    cout << "[RoutineBody]" << endl;
                }
                break;
            case DeclareK:
                if (t->kind.dec == VarDecK) cout << "[VarDecl]" << endl;
                else if (t->kind.dec == TypeDecK) cout << "[TypeDecl] " << t->attr.name << endl;
                else if (t->kind.dec == ProcDecK) cout << "[ProcDecl] " << t->attr.name << endl;
                else if (t->kind.dec == FieldDecK) cout << "[FieldDecl]" << endl;
                break;
            case TypeK:
                if (t->kind.type == BaseTypeK) cout << "[Type] " << t->attr.name << endl;
                else if (t->kind.type == AliasTypeK) cout << "[TypeAlias] " << t->attr.name << endl;
                else if (t->kind.type == ArrayTypeK) cout << "[ArrayType] [" << t->attr.low << ".." << t->attr.high << "]" << endl;
                else if (t->kind.type == RecordTypeK) cout << "[RecordType]" << endl;
                break;
            case ParamK:
                cout << "[Param] " << (t->kind.param == VarParamK ? "VAR" : "VALUE") << endl;
                break;
            case StmtK:
                if (t->kind.stmt == AssignK) cout << "[Stmt] Assign" << endl;
                else if (t->kind.stmt == IfK) cout << "[Stmt] IF" << endl;
                else if (t->kind.stmt == WhileK) cout << "[Stmt] WHILE" << endl;
                else if (t->kind.stmt == ReadK) cout << "[Stmt] READ" << endl;
                else if (t->kind.stmt == WriteK) cout << "[Stmt] WRITE" << endl;
                else if (t->kind.stmt == CallK) cout << "[Stmt] CALL " << t->attr.name << endl;
                else if (t->kind.stmt == ReturnK) cout << "[Stmt] RETURN" << endl;
                break;
            case ExpK:
                if (t->kind.exp == OpK) cout << "[Op] " << opToString(t->attr.op) << endl;
                else if (t->kind.exp == UnaryOpK) cout << "[Unary] " << opToString(t->attr.op) << endl;
                else if (t->kind.exp == ConstK) cout << "[Const] " << t->attr.val << endl;
                else if (t->kind.exp == IdK) cout << "[Id] " << t->attr.name << endl;
                break;
            default:
                cout << "[Unknown]" << endl;
                break;
        }

        printTree(t->firstChild, indent + 2);

        t = t->sibling;
    }
}

int main(int argc, char* argv[]) {
    bool tokenDumpMode = false;
    const char* inputPath = nullptr;

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--tokens" || arg == "-t") {
            tokenDumpMode = true;
        } else if (inputPath == nullptr) {
            inputPath = argv[i];
        }
    }

    if (inputPath != nullptr) {
        yyin = fopen(inputPath, "r");
        if (!yyin) {
            cout << "File not found!" << endl;
            return 1;
        }
    }

    if (tokenDumpMode) {
        if (yyin == nullptr) {
            cout << "Usage: parser.exe [--tokens|-t] <input.snl>" << endl;
            return 1;
        }
        return dumpTokens();
    }

    if (yyparse() == 0) {
        cout << "--- Parse Success! ---" << endl;
        if (root == nullptr) {
            cout << "Warning: Root is NULL." << endl;
        } else {
            cout << "--- AST Structure ---" << endl;
            printTree(root, 0);

            SemanticResult semantic = analyzeSemantics(root);
            if (semantic.errorCount == 0) {
                cout << "--- Semantic Check Passed ---" << endl;

                CodegenResult codegen = generateMips32(root, "out.s");
                if (codegen.success) {
                    cout << "--- Codegen Success ---" << endl;
                    cout << "MIPS asm generated: " << codegen.outputAsmPath << endl;
                    cout << "Run with Mars example:" << endl;
                    cout << "java -jar \"Mars for Compile 2022.jar\" nc " << codegen.outputAsmPath << endl;
                } else {
                    cout << "--- Codegen Failed: " << codegen.errorCount << " error(s) ---" << endl;
                }
            } else {
                cout << "--- Semantic Check Failed: " << semantic.errorCount << " error(s) ---" << endl;
            }
            if (semantic.warningCount > 0) {
                cout << "--- Semantic Warning(s): " << semantic.warningCount << " ---" << endl;
            }
        }
    } else {
        cout << "--- Parse Failed ---" << endl;
    }

    return 0;
}
