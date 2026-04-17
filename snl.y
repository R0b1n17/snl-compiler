%{
#include "globals.h"
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

extern int yylex();
extern int lineno;
void yyerror(const char *s);

TreeNode * root = nullptr;
%}

%union {
    int val;
    char * name;
    TreeNode * node;
}

/* --- Token 声明 --- */
%token PROGRAM PROCEDURE TYPE VAR IF THEN ELSE FI WHILE DO ENDWH 
%token BEGIN_SYM END READ WRITE ARRAY OF RECORD RETURN 
%token INTEGER_T CHAR_T
%token ASSIGN EQ LT PLUS MINUS TIMES OVER 
%token LPAREN RPAREN LMIDPAREN RMIDPAREN 
%token DOT COLON SEMI COMMA RANGE ERROR
%token <name> ID CHARC
%token <val> NUM

/* --- 非终结符类型声明 --- */
%type <node> program programHead declarePart varDecList varIdList 
%type <node> programBody stmList stm assignStm ifStm whileStm readStm writeStm returnStm 
%type <node> exp simple_exp term factor

%%

/* 1. 程序结构 */
program     : programHead declarePart programBody DOT
              {
                  $$ = new TreeNode();
                  $$->nodekind = ProgramK;
                  $$->child[0] = $1; 
                  $$->child[1] = $2; 
                  $$->child[2] = $3; 
                  root = $$;
              }
            ;

programHead : PROGRAM ID SEMI
              {
                  $$ = new TreeNode();
                  $$->nodekind = RoutineK;
                  $$->attr.name = $2;
              }
            ;

declarePart : VAR varDecList { $$ = $2; }
            | /* empty */ { $$ = nullptr; }
            ;

varDecList  : INTEGER_T varIdList SEMI
              {
                  $$ = new TreeNode();
                  $$->nodekind = DeclareK;
                  $$->kind.dec = IntegerK;
                  $$->child[0] = $2; // 这里挂载的是变量链表的头
              }
            ;

/* --- 重点修改：支持 x, y, z 这种多变量形式 --- */
varIdList   : ID
              {
                  $$ = new TreeNode();
                  $$->attr.name = $1;
                  /* 只有一个变量，没有兄弟节点 */
              }
            | ID COMMA varIdList
              {
                  $$ = new TreeNode();
                  $$->attr.name = $1;
                  $$->sibling = $3; // 通过 sibling 把后面的变量链表接上来
              }
            ;

programBody : BEGIN_SYM stmList END { $$ = $2; }
            ;

/* 2. 语句部分 */
stmList     : stm { $$ = $1; }
            | stm SEMI stmList { $1->sibling = $3; $$ = $1; }
            | stm SEMI { $$ = $1; } 
            ;

stm         : assignStm { $$ = $1; }
            | ifStm     { $$ = $1; }
            | whileStm  { $$ = $1; }
            | readStm   { $$ = $1; }
            | writeStm  { $$ = $1; }
            | returnStm { $$ = $1; }
            ;

assignStm   : ID ASSIGN exp
              {
                  $$ = new TreeNode();
                  $$->nodekind = StmtK; $$->kind.stmt = AssignK;
                  $$->attr.name = $1; $$->child[0] = $3;
                  $$->lineno = lineno;
              }
            ;
        
ifStm       : IF exp THEN stmList ELSE stmList FI
              {
                  $$ = new TreeNode();
                  $$->nodekind = StmtK; $$->kind.stmt = IfK;
                  $$->child[0] = $2; 
                  $$->child[1] = $4; 
                  $$->child[2] = $6; 
                  $$->lineno = lineno;
              }
            | IF exp THEN stmList FI
              {
                  $$ = new TreeNode();
                  $$->nodekind = StmtK; $$->kind.stmt = IfK;
                  $$->child[0] = $2;
                  $$->child[1] = $4;
                  $$->lineno = lineno;
              }
            ;

whileStm    : WHILE exp DO stmList ENDWH
              {
                  $$ = new TreeNode();
                  $$->nodekind = StmtK; $$->kind.stmt = WhileK;
                  $$->child[0] = $2; 
                  $$->child[1] = $4; 
                  $$->lineno = lineno;
              }
            ;

readStm     : READ LPAREN ID RPAREN
              {
                  $$ = new TreeNode();
                  $$->nodekind = StmtK; $$->kind.stmt = ReadK;
                  $$->attr.name = $3;
                  $$->lineno = lineno;
              }
            ;

writeStm    : WRITE LPAREN exp RPAREN
              {
                  $$ = new TreeNode();
                  $$->nodekind = StmtK; $$->kind.stmt = WriteK;
                  $$->child[0] = $3;
                  $$->lineno = lineno;
              }
            ;

returnStm   : RETURN
              {
                  $$ = new TreeNode();
                  $$->nodekind = StmtK; $$->kind.stmt = ReturnK;
                  $$->lineno = lineno;
              }
            ;
        
/* 3. 表达式层级 */
exp         : simple_exp { $$ = $1; }
            | simple_exp LT simple_exp 
              { 
                  $$ = new TreeNode(); $$->nodekind = ExpK; $$->kind.exp = OpK;
                  $$->attr.op = LT; $$->child[0] = $1; $$->child[1] = $3;
                  $$->lineno = lineno;
              }
            | simple_exp EQ simple_exp 
              { 
                  $$ = new TreeNode(); $$->nodekind = ExpK; $$->kind.exp = OpK;
                  $$->attr.op = EQ; $$->child[0] = $1; $$->child[1] = $3;
                  $$->lineno = lineno;
              }
            ;

simple_exp  : term { $$ = $1; }
            | simple_exp PLUS term 
              { 
                  $$ = new TreeNode(); $$->nodekind = ExpK; $$->kind.exp = OpK;
                  $$->attr.op = PLUS; $$->child[0] = $1; $$->child[1] = $3;
                  $$->lineno = lineno;
              }
            | simple_exp MINUS term 
              { 
                  $$ = new TreeNode(); $$->nodekind = ExpK; $$->kind.exp = OpK;
                  $$->attr.op = MINUS; $$->child[0] = $1; $$->child[1] = $3;
                  $$->lineno = lineno;
              }
            ;

term        : factor { $$ = $1; }
            | term TIMES factor 
              { 
                  $$ = new TreeNode(); $$->nodekind = ExpK; $$->kind.exp = OpK;
                  $$->attr.op = TIMES; $$->child[0] = $1; $$->child[1] = $3;
                  $$->lineno = lineno;
              }
            | term OVER factor 
              { 
                  $$ = new TreeNode(); $$->nodekind = ExpK; $$->kind.exp = OpK;
                  $$->attr.op = OVER; $$->child[0] = $1; $$->child[1] = $3;
                  $$->lineno = lineno;
              }
            ;

factor      : NUM 
              { 
                  $$ = new TreeNode(); $$->nodekind = ExpK; $$->kind.exp = ConstK;
                  $$->attr.val = $1; $$->lineno = lineno;
              }
            | ID 
              { 
                  $$ = new TreeNode(); $$->nodekind = ExpK; $$->kind.exp = IdK;
                  $$->attr.name = $1; $$->lineno = lineno;
              }
            | LPAREN exp RPAREN 
              { $$ = $2; }
            ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", lineno, s);
}
