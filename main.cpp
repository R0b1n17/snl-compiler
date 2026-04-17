#include <iostream>
#include <stdio.h>
#include "globals.h"
#include "y.tab.h"

extern int yyparse();
extern FILE* yyin;
extern TreeNode* root; // 确保这里是 extern

using namespace std;

void printTree(TreeNode* t, int indent) {
    if (t == nullptr) return; // 递归出口

    while (t != nullptr) {
        for (int i = 0; i < indent; i++) cout << "  ";

        // --- 完善打印逻辑 ---
        if (t->nodekind == ProgramK) cout << "[Program Root]" << endl;
        else if (t->nodekind == RoutineK) cout << "[Routine Head]: " << t->attr.name << endl;
        else if (t->nodekind == DeclareK) cout << "[Declaration Part]" << endl;
        else if (t->nodekind == StmtK) {
            if (t->kind.stmt == AssignK) cout << "[Stmt]: Assign to " << t->attr.name << endl;
            else if (t->kind.stmt == IfK) cout << "[Stmt]: IF" << endl;
            else if (t->kind.stmt == WhileK) cout << "[Stmt]: WHILE" << endl;
            else if (t->kind.stmt == WriteK) cout << "[Stmt]: WRITE" << endl;
            else if (t->kind.stmt == ReadK) cout << "[Stmt]: READ " << t->attr.name << endl;
        }
        else if (t->nodekind == ExpK) {
            if (t->kind.exp == OpK) {
                string op;
                switch(t->attr.op) {
                    case PLUS: op = "+"; break; case MINUS: op = "-"; break;
                    case TIMES: op = "*"; break; case OVER: op = "/"; break;
                    case LT: op = "<"; break; case EQ: op = "="; break;
                    default: op = "?";
                }
                cout << "[Op]: " << op << endl;
            }
            else if (t->kind.exp == ConstK) cout << "[Const]: " << t->attr.val << endl;
            else if (t->kind.exp == IdK) cout << "[Id]: " << t->attr.name << endl;
        }

        // 递归打印子节点（SNL 语法树最多有 3 个孩子）
        for (int i = 0; i < 3; i++) {
            if (t->child[i] != nullptr) {
                printTree(t->child[i], indent + 4);
            }
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