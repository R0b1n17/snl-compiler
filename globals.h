#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <iostream>
#include <string>
#include <vector>

#define MAXCHILDREN 3

typedef enum { ProgramK, RoutineK, DeclareK, StmtK, ExpK } NodeKind;
typedef enum { IntegerK, CharK, ArrayK, RecordK } DecKind;
typedef enum { IfK, WhileK, AssignK, ReadK, WriteK, CallK, ReturnK } StmtKind;
typedef enum { OpK, ConstK, IdK } ExpKind;
typedef enum { Void, Integer, Boolean, Char } ExpType;

struct TreeNode {
    TreeNode* child[MAXCHILDREN];
    TreeNode* sibling;
    int lineno;
    NodeKind nodekind;
    
    union { DecKind dec; StmtKind stmt; ExpKind exp; } kind;

    struct {
        int op;
        int val;
        std::string name;
    } attr;

    ExpType type;

    TreeNode() {
        for (int i = 0; i < MAXCHILDREN; i++) child[i] = nullptr;
        sibling = nullptr;
        lineno = 0;
        attr.name = "";
        attr.val = 0;
        attr.op = 0;
    }
};

#endif