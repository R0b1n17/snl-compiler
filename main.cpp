#include <iostream>
#include <stdio.h>
#include <string>

#include "globals.h"
#include "semantic.h"
#include "y.tab.h"

extern int yyparse();
extern FILE* yyin;
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
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            cout << "File not found!" << endl;
            return 1;
        }
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
            } else {
                cout << "--- Semantic Check Failed: " << semantic.errorCount << " error(s) ---" << endl;
            }
        }
    } else {
        cout << "--- Parse Failed ---" << endl;
    }

    return 0;
}
