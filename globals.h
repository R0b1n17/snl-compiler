#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <iostream>
#include <string>
#include <vector>

typedef enum { ProgramK, RoutineK, DeclareK, TypeK, StmtK, ExpK } NodeKind;
typedef enum { VarDecK, ProcDecK, ParamDecK, TypeDecK } DecKind;
typedef enum { BaseTypeK, ArrayTypeK, RecordTypeK, AliasTypeK } TypeKind;
typedef enum { IfK, WhileK, ForK, AssignK, ReadK, WriteK, CallK, ReturnK } StmtKind;
typedef enum { OpK, ConstK, IdK, ArrayMemberK, FieldMemberK } ExpKind;
typedef enum { Void, Integer, Boolean, Char } ExpType;

struct TreeNode {
    TreeNode* child;
    TreeNode* sibling;
    int lineno;
    NodeKind nodekind;
    
    union { DecKind dec; TypeKind typekind; StmtKind stmt; ExpKind exp; } kind;

    struct {
        int op;
        int val;
        int arrayLow;
        int arrayHigh;
        std::string name;
    } attr;

    ExpType type;

    TreeNode() {
        child = nullptr;
        sibling = nullptr;
        lineno = 0;
        attr.name = "";
        attr.val = 0;
        attr.op = 0;
        attr.arrayLow = 0;
        attr.arrayHigh = 0;
        type = Void;
    }

    void addChild(TreeNode* node) {
        if (node == nullptr) return;
        if (child == nullptr) {
            child = node;
            return;
        }
        TreeNode* tail = child;
        while (tail->sibling != nullptr) {
            tail = tail->sibling;
        }
        tail->sibling = node;
    }
};

#endif
