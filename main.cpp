#include <iostream>
#include <stdio.h>
#include "globals.h"
#include "y.tab.h"

extern int yyparse();
extern FILE* yyin;
extern TreeNode* root; // 确保这里是 extern

using namespace std;

static const char* opToString(int op) {
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
        case NEQ: return "<>";
        case AND: return "AND";
        case OR: return "OR";
        case NOT: return "NOT";
        default: return "?";
    }
}

void printTree(TreeNode* t, int indent) {
    if (t == nullptr) return; // 递归出口

    while (t != nullptr) {
        for (int i = 0; i < indent; i++) cout << "  ";

        // --- 完善打印逻辑 ---
        if (t->nodekind == ProgramK) cout << "[Program Root]" << endl;
        else if (t->nodekind == RoutineK) cout << "[Routine Head]: " << t->attr.name << endl;
        else if (t->nodekind == DeclareK) {
            if (t->kind.dec == VarDecK) cout << "[Declaration]: VAR" << endl;
            else if (t->kind.dec == TypeDecK) cout << "[Declaration]: TYPE " << t->attr.name << endl;
            else if (t->kind.dec == ProcDecK) cout << "[Declaration]: PROCEDURE " << t->attr.name << endl;
            else if (t->kind.dec == ParamDecK) cout << "[Declaration]: PARAM" << endl;
        }
        else if (t->nodekind == TypeK) {
            if (t->kind.typekind == BaseTypeK) cout << "[Type]: " << t->attr.name << endl;
            else if (t->kind.typekind == AliasTypeK) cout << "[Type Alias]: " << t->attr.name << endl;
            else if (t->kind.typekind == ArrayTypeK) {
                cout << "[Type]: ARRAY [" << t->attr.arrayLow << ".." << t->attr.arrayHigh << "]" << endl;
            } else if (t->kind.typekind == RecordTypeK) {
                cout << "[Type]: RECORD" << endl;
            }
        }
        else if (t->nodekind == StmtK) {
            if (t->kind.stmt == AssignK) cout << "[Stmt]: ASSIGN" << endl;
            else if (t->kind.stmt == IfK) cout << "[Stmt]: IF" << endl;
            else if (t->kind.stmt == WhileK) cout << "[Stmt]: WHILE" << endl;
            else if (t->kind.stmt == WriteK) cout << "[Stmt]: WRITE" << endl;
            else if (t->kind.stmt == ReadK) cout << "[Stmt]: READ" << endl;
            else if (t->kind.stmt == CallK) cout << "[Stmt]: CALL " << t->attr.name << endl;
            else if (t->kind.stmt == ReturnK) cout << "[Stmt]: RETURN" << endl;
        }
        else if (t->nodekind == ExpK) {
            if (t->kind.exp == OpK) {
                cout << "[Op]: " << opToString(t->attr.op) << endl;
            }
            else if (t->kind.exp == ConstK) {
                if (!t->attr.name.empty()) cout << "[Const]: " << t->attr.name << endl;
                else cout << "[Const]: " << t->attr.val << endl;
            }
            else if (t->kind.exp == IdK) cout << "[Id]: " << t->attr.name << endl;
            else if (t->kind.exp == ArrayMemberK) cout << "[Array Access]" << endl;
            else if (t->kind.exp == FieldMemberK) cout << "[Field Access]: ." << t->attr.name << endl;
        }

        // 递归打印子节点（使用链表存储）
        TreeNode* child = t->child;
        while (child != nullptr) {
            TreeNode* nextChild = child->sibling;
            child->sibling = nullptr;
            printTree(child, indent + 4);
            child->sibling = nextChild;
            child = nextChild;
        }

        // 顺着兄弟指针走（处理语句序列或变量列表）
        t = t->sibling;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) { cout << "File not found!" << endl; return 1; }
    }

    if (yyparse() == 0) {
        cout << "--- Parse Success! ---" << endl;
        if (root == nullptr) {
            cout << "Warning: Root is NULL. Did you assign 'root = $$' in snl.y?" << endl;
        } else {
            cout << "--- AST Structure ---" << endl;
            printTree(root, 0);
        }
    } else {
        cout << "--- Parse Failed ---" << endl;
    }
    return 0;
}
