#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <cstdio>
#include <string>

/* 使用 firstChild/sibling 作为主结构；child[] 仅保留兼容旧代码 */
#define MAXCHILDREN 8

typedef enum { ProgramK, RoutineK, DeclareK, TypeK, ParamK, StmtK, ExpK } NodeKind;
typedef enum { VarDecK, TypeDecK, ProcDecK, FieldDecK } DecKind;
typedef enum { RoutineHeadK, RoutineBodyK } RoutineKind;
typedef enum { ValueParamK, VarParamK } ParamKind;
typedef enum { BaseTypeK, ArrayTypeK, RecordTypeK, AliasTypeK } TypeKind;
typedef enum { IfK, WhileK, AssignK, ReadK, WriteK, CallK, ReturnK } StmtKind;
typedef enum { OpK, ConstK, IdK, UnaryOpK } ExpKind;
typedef enum { Void, Integer, Boolean, Char } ExpType;

struct TreeNode {
    TreeNode* child[MAXCHILDREN];
    TreeNode* firstChild;
    TreeNode* lastChild;
    TreeNode* sibling;
    int lineno;
    NodeKind nodekind;

    union {
        DecKind dec;
        RoutineKind routine;
        ParamKind param;
        TypeKind type;
        StmtKind stmt;
        ExpKind exp;
    } kind;

    struct {
        int op;
        int val;
        int low;
        int high;
        std::string name;
    } attr;

    ExpType type;

    TreeNode()
        : firstChild(nullptr), lastChild(nullptr), sibling(nullptr), lineno(0), nodekind(ProgramK), type(Void) {
        for (int i = 0; i < MAXCHILDREN; i++) child[i] = nullptr;
        attr.op = 0;
        attr.val = 0;
        attr.low = 0;
        attr.high = 0;
        attr.name = "";
    }

    void addChild(TreeNode* c) {
        if (c == nullptr) return;
        TreeNode* tail = c;
        while (tail->sibling != nullptr) tail = tail->sibling;
        if (firstChild == nullptr) {
            firstChild = c;
            lastChild = tail;
        } else {
            lastChild->sibling = c;
            lastChild = tail;
        }
        bool inserted = false;
        for (int i = 0; i < MAXCHILDREN; i++) {
            if (child[i] == nullptr) {
                child[i] = c;
                inserted = true;
                break;
            }
        }
        if (!inserted) {
            fprintf(stderr, "Warning: child[] compatibility array full at line %d\n", lineno);
        }
    }
};

#endif
