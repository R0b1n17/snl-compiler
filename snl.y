%{
#include "globals.h"
#include <iostream>
#include <stdio.h>

using namespace std;

extern int yylex();
extern int lineno;
void yyerror(const char *s);

TreeNode * root = nullptr;

static TreeNode* newNode(NodeKind kind) {
    TreeNode* t = new TreeNode();
    t->nodekind = kind;
    t->lineno = lineno;
    return t;
}

static TreeNode* appendSibling(TreeNode* head, TreeNode* tail) {
    if (head == nullptr) return tail;
    TreeNode* p = head;
    while (p->sibling != nullptr) p = p->sibling;
    p->sibling = tail;
    return head;
}

static TreeNode* makeOpNode(int op, TreeNode* left, TreeNode* right) {
    TreeNode* t = newNode(ExpK);
    t->kind.exp = OpK;
    t->attr.op = op;
    t->addChild(left);
    t->addChild(right);
    return t;
}

static TreeNode* makeUnaryNode(int op, TreeNode* operand) {
    TreeNode* t = newNode(ExpK);
    t->kind.exp = OpK;
    t->attr.op = op;
    t->addChild(operand);
    return t;
}
%}

%union {
    int val;
    char * name;
    TreeNode * node;
}

%token PROGRAM PROCEDURE TYPE VAR IF THEN ELSE FI WHILE DO ENDWH
%token BEGIN_SYM END READ WRITE CALL ARRAY OF RECORD RETURN
%token INTEGER_T CHAR_T
%token ASSIGN EQ LT LE GT GE NEQ PLUS MINUS TIMES OVER
%token AND OR NOT
%token LPAREN RPAREN LMIDPAREN RMIDPAREN
%token DOT COLON SEMI COMMA RANGE ERROR
%token <name> ID CHARC
%token <val> NUM

%type <node> program programHead declarePart declareItem typeDecList typeDec
%type <node> varDecList varDec idList procDec paramList paramDec
%type <node> typeSpec standardType arrayType recordType fieldDecList fieldDec
%type <node> programBody stmList stm assignStm ifStm whileStm readStm writeStm callStm returnStm
%type <node> actParamList variable exp andExp relExp simpleExp term unaryExp factor

%%

program      : programHead declarePart programBody DOT
               {
                   $$ = newNode(ProgramK);
                   $$->addChild($1);
                   $$->addChild($2);
                   $$->addChild($3);
                   root = $$;
               }
             | programHead error DOT
               {
                   yyerror("syntax error in program");
                   $$ = newNode(ProgramK);
                   $$->addChild($1);
                   root = $$;
                   yyerrok;
               }
             ;

programHead  : PROGRAM ID SEMI
               {
                   $$ = newNode(RoutineK);
                   $$->attr.name = $2;
               }
             ;

declarePart  : declareItem declarePart     { $$ = appendSibling($1, $2); }
             | /* empty */                 { $$ = nullptr; }
             ;

declareItem  : TYPE typeDecList            { $$ = $2; }
             | VAR varDecList              { $$ = $2; }
             | procDec                     { $$ = $1; }
             ;

typeDecList  : typeDec                 { $$ = $1; }
             | typeDec typeDecList      { $1->sibling = $2; $$ = $1; }
             ;

typeDec      : ID EQ typeSpec SEMI
               {
                   $$ = newNode(DeclareK);
                   $$->kind.dec = TypeDecK;
                   $$->attr.name = $1;
                   $$->addChild($3);
               }
             ;

varDecList   : varDec                 { $$ = $1; }
             | varDec varDecList      { $1->sibling = $2; $$ = $1; }
             ;

varDec       : idList COLON typeSpec SEMI
               {
                   $$ = newNode(DeclareK);
                   $$->kind.dec = VarDecK;
                   $$->addChild($1);
                   $$->addChild($3);
               }
             ;

idList       : ID
               {
                   $$ = newNode(ExpK);
                   $$->kind.exp = IdK;
                   $$->attr.name = $1;
               }
             | ID COMMA idList
               {
                   $$ = newNode(ExpK);
                   $$->kind.exp = IdK;
                   $$->attr.name = $1;
                   $$->sibling = $3;
               }
             ;

procDec      : PROCEDURE ID LPAREN paramList RPAREN SEMI declarePart programBody SEMI
               {
                   $$ = newNode(DeclareK);
                   $$->kind.dec = ProcDecK;
                   $$->attr.name = $2;
                   $$->addChild($4);
                   $$->addChild($7);
                   $$->addChild($8);
               }
             | PROCEDURE ID SEMI declarePart programBody SEMI
               {
                   $$ = newNode(DeclareK);
                   $$->kind.dec = ProcDecK;
                   $$->attr.name = $2;
                   $$->addChild($4);
                   $$->addChild($5);
               }
             ;

paramList    : paramDec                  { $$ = $1; }
             | paramDec SEMI paramList   { $1->sibling = $3; $$ = $1; }
             | /* empty */               { $$ = nullptr; }
             ;

paramDec     : idList COLON typeSpec
               {
                   $$ = newNode(DeclareK);
                   $$->kind.dec = ParamDecK;
                   $$->addChild($1);
                   $$->addChild($3);
               }
             ;

typeSpec     : standardType              { $$ = $1; }
             | arrayType                 { $$ = $1; }
             | recordType                { $$ = $1; }
             | ID
               {
                   $$ = newNode(TypeK);
                   $$->kind.typekind = AliasTypeK;
                   $$->attr.name = $1;
               }
             ;

standardType : INTEGER_T
               {
                   $$ = newNode(TypeK);
                   $$->kind.typekind = BaseTypeK;
                   $$->attr.name = "INTEGER";
                   $$->type = Integer;
               }
             | CHAR_T
               {
                   $$ = newNode(TypeK);
                   $$->kind.typekind = BaseTypeK;
                   $$->attr.name = "CHAR";
                   $$->type = Char;
               }
             ;

arrayType    : ARRAY LMIDPAREN NUM RANGE NUM RMIDPAREN OF typeSpec
               {
                   $$ = newNode(TypeK);
                   $$->kind.typekind = ArrayTypeK;
                   $$->attr.arrayLow = $3;
                   $$->attr.arrayHigh = $5;
                   $$->addChild($8);
               }
             ;

recordType   : RECORD fieldDecList END
               {
                   $$ = newNode(TypeK);
                   $$->kind.typekind = RecordTypeK;
                   $$->addChild($2);
               }
             ;

fieldDecList : fieldDec                 { $$ = $1; }
             | fieldDec SEMI fieldDecList { $1->sibling = $3; $$ = $1; }
             | fieldDec SEMI            { $$ = $1; }
             ;

fieldDec     : idList COLON typeSpec
               {
                   $$ = newNode(DeclareK);
                   $$->kind.dec = VarDecK;
                   $$->addChild($1);
                   $$->addChild($3);
               }
             ;

programBody  : BEGIN_SYM stmList END    { $$ = $2; }
             ;

stmList      : stm                      { $$ = $1; }
             | stm SEMI stmList
               {
                   if ($1 == nullptr) $$ = $3;
                   else { $1->sibling = $3; $$ = $1; }
               }
             | stm SEMI                 { $$ = $1; }
             | error SEMI stmList
               {
                   yyerror("invalid statement, skipping to ';'");
                   yyerrok;
                   $$ = $3;
               }
             | error SEMI
               {
                   yyerror("invalid statement, skipping to ';'");
                   yyerrok;
                   $$ = nullptr;
               }
             ;

stm          : assignStm                { $$ = $1; }
             | ifStm                    { $$ = $1; }
             | whileStm                 { $$ = $1; }
             | readStm                  { $$ = $1; }
             | writeStm                 { $$ = $1; }
             | callStm                  { $$ = $1; }
             | returnStm                { $$ = $1; }
             ;

assignStm    : variable ASSIGN exp
               {
                   $$ = newNode(StmtK);
                   $$->kind.stmt = AssignK;
                   $$->addChild($1);
                   $$->addChild($3);
               }
             ;

ifStm        : IF exp THEN stmList ELSE stmList FI
               {
                   $$ = newNode(StmtK);
                   $$->kind.stmt = IfK;
                   $$->addChild($2);
                   $$->addChild($4);
                   $$->addChild($6);
               }
             | IF exp THEN stmList FI
               {
                   $$ = newNode(StmtK);
                   $$->kind.stmt = IfK;
                   $$->addChild($2);
                   $$->addChild($4);
               }
             ;

whileStm     : WHILE exp DO stmList ENDWH
               {
                   $$ = newNode(StmtK);
                   $$->kind.stmt = WhileK;
                   $$->addChild($2);
                   $$->addChild($4);
               }
             ;

readStm      : READ LPAREN variable RPAREN
               {
                   $$ = newNode(StmtK);
                   $$->kind.stmt = ReadK;
                   $$->addChild($3);
               }
             ;

writeStm     : WRITE LPAREN exp RPAREN
               {
                   $$ = newNode(StmtK);
                   $$->kind.stmt = WriteK;
                   $$->addChild($3);
               }
             ;

callStm      : CALL ID
               {
                   $$ = newNode(StmtK);
                   $$->kind.stmt = CallK;
                   $$->attr.name = $2;
               }
             | CALL ID LPAREN actParamList RPAREN
               {
                   $$ = newNode(StmtK);
                   $$->kind.stmt = CallK;
                   $$->attr.name = $2;
                   $$->addChild($4);
               }
             ;

actParamList : exp                       { $$ = $1; }
             | exp COMMA actParamList    { $1->sibling = $3; $$ = $1; }
             | /* empty */               { $$ = nullptr; }
             ;

returnStm    : RETURN
               {
                   $$ = newNode(StmtK);
                   $$->kind.stmt = ReturnK;
               }
             ;

exp          : exp OR andExp             { $$ = makeOpNode(OR, $1, $3); }
             | andExp                    { $$ = $1; }
             ;

andExp       : andExp AND relExp         { $$ = makeOpNode(AND, $1, $3); }
             | relExp                    { $$ = $1; }
             ;

relExp       : simpleExp                 { $$ = $1; }
             | simpleExp LT simpleExp    { $$ = makeOpNode(LT, $1, $3); }
             | simpleExp LE simpleExp    { $$ = makeOpNode(LE, $1, $3); }
             | simpleExp GT simpleExp    { $$ = makeOpNode(GT, $1, $3); }
             | simpleExp GE simpleExp    { $$ = makeOpNode(GE, $1, $3); }
             | simpleExp EQ simpleExp    { $$ = makeOpNode(EQ, $1, $3); }
             | simpleExp NEQ simpleExp   { $$ = makeOpNode(NEQ, $1, $3); }
             ;

simpleExp    : simpleExp PLUS term       { $$ = makeOpNode(PLUS, $1, $3); }
             | simpleExp MINUS term      { $$ = makeOpNode(MINUS, $1, $3); }
             | term                      { $$ = $1; }
             ;

term         : term TIMES unaryExp       { $$ = makeOpNode(TIMES, $1, $3); }
             | term OVER unaryExp        { $$ = makeOpNode(OVER, $1, $3); }
             | unaryExp                  { $$ = $1; }
             ;

unaryExp     : MINUS unaryExp            { $$ = makeUnaryNode(MINUS, $2); }
             | PLUS unaryExp             { $$ = makeUnaryNode(PLUS, $2); }
             | NOT unaryExp              { $$ = makeUnaryNode(NOT, $2); }
             | factor                    { $$ = $1; }
             ;

factor       : NUM
               {
                   $$ = newNode(ExpK);
                   $$->kind.exp = ConstK;
                   $$->attr.val = $1;
                   $$->type = Integer;
               }
             | CHARC
               {
                   $$ = newNode(ExpK);
                   $$->kind.exp = ConstK;
                   $$->attr.name = $1;
                   $$->type = Char;
               }
             | variable
               {
                   $$ = $1;
               }
             | LPAREN exp RPAREN
               {
                   $$ = $2;
               }
             ;

variable     : ID
               {
                   $$ = newNode(ExpK);
                   $$->kind.exp = IdK;
                   $$->attr.name = $1;
               }
             | variable LMIDPAREN exp RMIDPAREN
               {
                   $$ = newNode(ExpK);
                   $$->kind.exp = ArrayMemberK;
                   $$->addChild($1);
                   $$->addChild($3);
               }
             | variable DOT ID
               {
                   $$ = newNode(ExpK);
                   $$->kind.exp = FieldMemberK;
                   $$->attr.name = $3;
                   $$->addChild($1);
               }
             ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", lineno, s);
}
