%{
#include "globals.h"
#include <stdio.h>
#include <string>

extern int yylex();
extern int lineno;
void yyerror(const char *s);

TreeNode* root = nullptr;

static TreeNode* newNode(NodeKind kind) {
    TreeNode* t = new TreeNode();
    t->nodekind = kind;
    t->lineno = lineno;
    return t;
}

static TreeNode* appendSibling(TreeNode* a, TreeNode* b) {
    if (a == nullptr) return b;
    if (b == nullptr) return a;
    TreeNode* p = a;
    while (p->sibling != nullptr) p = p->sibling;
    p->sibling = b;
    return a;
}

static TreeNode* makeIdNode(char* name) {
    TreeNode* t = newNode(ExpK);
    t->kind.exp = IdK;
    t->attr.name = name;
    return t;
}

static TreeNode* makeConstNode(int val) {
    TreeNode* t = newNode(ExpK);
    t->kind.exp = ConstK;
    t->attr.val = val;
    return t;
}

static TreeNode* makeOpNode(int op, TreeNode* lhs, TreeNode* rhs) {
    TreeNode* t = newNode(ExpK);
    t->kind.exp = OpK;
    t->attr.op = op;
    t->addChild(lhs);
    t->addChild(rhs);
    return t;
}

static TreeNode* makeUnaryNode(int op, TreeNode* operand) {
    TreeNode* t = newNode(ExpK);
    t->kind.exp = UnaryOpK;
    t->attr.op = op;
    t->addChild(operand);
    return t;
}
%}

%union {
    int val;
    char* name;
    TreeNode* node;
}

%token PROGRAM PROCEDURE TYPE VAR IF THEN ELSE FI WHILE DO ENDWH
%token BEGIN_SYM END READ WRITE ARRAY OF RECORD RETURN CALL
%token INTEGER_T CHAR_T
%token ASSIGN EQ LT LE GT GE NE PLUS MINUS TIMES OVER AND OR NOT
%token LPAREN RPAREN LMIDPAREN RMIDPAREN
%token DOT COLON SEMI COMMA RANGE ERROR
%token <name> ID
%token <val> NUM CHARC

%type <node> program programHead declarePart declItem
%type <node> typeDecPart typeDecList typeDec typeSpec fieldDecList fieldDec
%type <node> varDecPart varDecList varDec idList
%type <node> procDec paramListOpt paramList paramDecl
%type <node> programBody stmListOpt stmList stm
%type <node> assignStm ifStm whileStm readStm writeStm returnStm callStm
%type <node> argListOpt argList variable
%type <node> exp orExp andExp relationExp arithExp term unaryExp factor

%right ASSIGN
%left OR
%left AND
%nonassoc LT LE GT GE EQ NE
%left PLUS MINUS
%left TIMES OVER
%right NOT UPLUS UMINUS

%%

program
    : programHead declarePart programBody DOT
      {
          $$ = newNode(ProgramK);
          $$->addChild($1);
          $$->addChild($2);
          $$->addChild($3);
          root = $$;
      }
    | error DOT
      {
          yyerror("syntax error in program");
          yyerrok;
          root = nullptr;
          $$ = nullptr;
      }
    ;

programHead
    : PROGRAM ID SEMI
      {
          $$ = newNode(RoutineK);
          $$->kind.routine = RoutineHeadK;
          $$->attr.name = $2;
      }
    ;

declarePart
    : /* empty */ { $$ = nullptr; }
    | declarePart declItem { $$ = appendSibling($1, $2); }
    ;

declItem
    : typeDecPart { $$ = $1; }
    | varDecPart  { $$ = $1; }
    | procDec     { $$ = $1; }
    ;

typeDecPart
    : TYPE typeDecList { $$ = $2; }
    ;

typeDecList
    : typeDec { $$ = $1; }
    | typeDecList typeDec { $$ = appendSibling($1, $2); }
    ;

typeDec
    : ID EQ typeSpec SEMI
      {
          $$ = newNode(DeclareK);
          $$->kind.dec = TypeDecK;
          $$->attr.name = $1;
          $$->addChild($3);
      }
    | error SEMI
      {
          yyerror("invalid type declaration");
          yyerrok;
          $$ = nullptr;
      }
    ;

varDecPart
    : VAR varDecList { $$ = $2; }
    ;

varDecList
    : varDec { $$ = $1; }
    | varDecList varDec { $$ = appendSibling($1, $2); }
    ;

varDec
    : idList COLON typeSpec SEMI
      {
          $$ = newNode(DeclareK);
          $$->kind.dec = VarDecK;
          $$->addChild($1);
          $$->addChild($3);
      }
    | error SEMI
      {
          yyerror("invalid variable declaration");
          yyerrok;
          $$ = nullptr;
      }
    ;

idList
    : ID { $$ = makeIdNode($1); }
    | idList COMMA ID { $$ = appendSibling($1, makeIdNode($3)); }
    ;

typeSpec
    : INTEGER_T
      {
          $$ = newNode(TypeK);
          $$->kind.type = BaseTypeK;
          $$->attr.name = "INTEGER";
      }
    | CHAR_T
      {
          $$ = newNode(TypeK);
          $$->kind.type = BaseTypeK;
          $$->attr.name = "CHAR";
      }
    | ID
      {
          $$ = newNode(TypeK);
          $$->kind.type = AliasTypeK;
          $$->attr.name = $1;
      }
    | ARRAY LMIDPAREN NUM RANGE NUM RMIDPAREN OF typeSpec
      {
          $$ = newNode(TypeK);
          $$->kind.type = ArrayTypeK;
          $$->attr.low = $3;
          $$->attr.high = $5;
          $$->addChild($8);
      }
    | RECORD fieldDecList END
      {
          $$ = newNode(TypeK);
          $$->kind.type = RecordTypeK;
          $$->addChild($2);
      }
    ;

fieldDecList
    : fieldDec { $$ = $1; }
    | fieldDecList fieldDec { $$ = appendSibling($1, $2); }
    ;

fieldDec
    : idList COLON typeSpec SEMI
      {
          $$ = newNode(DeclareK);
          $$->kind.dec = FieldDecK;
          $$->addChild($1);
          $$->addChild($3);
      }
    ;

procDec
    : PROCEDURE ID LPAREN paramListOpt RPAREN SEMI declarePart programBody SEMI
      {
          TreeNode* head = newNode(RoutineK);
          head->kind.routine = RoutineHeadK;
          head->attr.name = $2;
          head->addChild($4);

          TreeNode* body = newNode(RoutineK);
          body->kind.routine = RoutineBodyK;
          body->addChild($7);
          body->addChild($8);

          $$ = newNode(DeclareK);
          $$->kind.dec = ProcDecK;
          $$->attr.name = $2;
          $$->addChild(head);
          $$->addChild(body);
      }
    | PROCEDURE ID SEMI declarePart programBody SEMI
      {
          TreeNode* head = newNode(RoutineK);
          head->kind.routine = RoutineHeadK;
          head->attr.name = $2;

          TreeNode* body = newNode(RoutineK);
          body->kind.routine = RoutineBodyK;
          body->addChild($4);
          body->addChild($5);

          $$ = newNode(DeclareK);
          $$->kind.dec = ProcDecK;
          $$->attr.name = $2;
          $$->addChild(head);
          $$->addChild(body);
      }
    ;

paramListOpt
    : /* empty */ { $$ = nullptr; }
    | paramList { $$ = $1; }
    ;

paramList
    : paramDecl { $$ = $1; }
    | paramList SEMI paramDecl { $$ = appendSibling($1, $3); }
    ;

paramDecl
    : idList COLON typeSpec
      {
          $$ = newNode(ParamK);
          $$->kind.param = ValueParamK;
          $$->addChild($1);
          $$->addChild($3);
      }
    | VAR idList COLON typeSpec
      {
          $$ = newNode(ParamK);
          $$->kind.param = VarParamK;
          $$->addChild($2);
          $$->addChild($4);
      }
    ;

programBody
    : BEGIN_SYM stmListOpt END
      {
          $$ = newNode(RoutineK);
          $$->kind.routine = RoutineBodyK;
          $$->addChild($2);
      }
    ;

stmListOpt
    : /* empty */ { $$ = nullptr; }
    | stmList { $$ = $1; }
    ;

stmList
    : stm { $$ = $1; }
    | stmList SEMI stm { $$ = appendSibling($1, $3); }
    | stmList SEMI error
      {
          yyerror("invalid statement, skipped");
          yyerrok;
          $$ = $1;
      }
    ;

stm
    : assignStm { $$ = $1; }
    | ifStm { $$ = $1; }
    | whileStm { $$ = $1; }
    | readStm { $$ = $1; }
    | writeStm { $$ = $1; }
    | callStm { $$ = $1; }
    | returnStm { $$ = $1; }
    ;

assignStm
    : variable ASSIGN exp
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = AssignK;
          $$->addChild($1);
          $$->addChild($3);
      }
    ;

ifStm
    : IF exp THEN stmListOpt ELSE stmListOpt FI
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = IfK;
          $$->addChild($2);
          $$->addChild($4);
          $$->addChild($6);
      }
    | IF exp THEN stmListOpt FI
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = IfK;
          $$->addChild($2);
          $$->addChild($4);
      }
    ;

whileStm
    : WHILE exp DO stmListOpt ENDWH
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = WhileK;
          $$->addChild($2);
          $$->addChild($4);
      }
    ;

readStm
    : READ LPAREN variable RPAREN
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = ReadK;
          $$->addChild($3);
      }
    ;

writeStm
    : WRITE LPAREN exp RPAREN
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = WriteK;
          $$->addChild($3);
      }
    ;

callStm
    : CALL ID
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = CallK;
          $$->attr.name = $2;
      }
    | CALL ID LPAREN argListOpt RPAREN
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = CallK;
          $$->attr.name = $2;
          $$->addChild($4);
      }
    ;

argListOpt
    : /* empty */ { $$ = nullptr; }
    | argList { $$ = $1; }
    ;

argList
    : exp { $$ = $1; }
    | argList COMMA exp { $$ = appendSibling($1, $3); }
    ;

returnStm
    : RETURN
      {
          $$ = newNode(StmtK);
          $$->kind.stmt = ReturnK;
      }
    ;

variable
    : ID
      {
          $$ = makeIdNode($1);
      }
    | variable LMIDPAREN exp RMIDPAREN
      {
          $$ = makeOpNode(LMIDPAREN, $1, $3);
      }
    | variable DOT ID
      {
          $$ = makeOpNode(DOT, $1, makeIdNode($3));
      }
    ;

exp
    : orExp { $$ = $1; }
    ;

orExp
    : andExp { $$ = $1; }
    | orExp OR andExp { $$ = makeOpNode(OR, $1, $3); }
    ;

andExp
    : relationExp { $$ = $1; }
    | andExp AND relationExp { $$ = makeOpNode(AND, $1, $3); }
    ;

relationExp
    : arithExp { $$ = $1; }
    | arithExp LT arithExp { $$ = makeOpNode(LT, $1, $3); }
    | arithExp LE arithExp { $$ = makeOpNode(LE, $1, $3); }
    | arithExp GT arithExp { $$ = makeOpNode(GT, $1, $3); }
    | arithExp GE arithExp { $$ = makeOpNode(GE, $1, $3); }
    | arithExp EQ arithExp { $$ = makeOpNode(EQ, $1, $3); }
    | arithExp NE arithExp { $$ = makeOpNode(NE, $1, $3); }
    ;

arithExp
    : term { $$ = $1; }
    | arithExp PLUS term { $$ = makeOpNode(PLUS, $1, $3); }
    | arithExp MINUS term { $$ = makeOpNode(MINUS, $1, $3); }
    ;

term
    : unaryExp { $$ = $1; }
    | term TIMES unaryExp { $$ = makeOpNode(TIMES, $1, $3); }
    | term OVER unaryExp { $$ = makeOpNode(OVER, $1, $3); }
    ;

unaryExp
    : factor { $$ = $1; }
    | PLUS unaryExp %prec UPLUS { $$ = makeUnaryNode(PLUS, $2); }
    | MINUS unaryExp %prec UMINUS { $$ = makeUnaryNode(MINUS, $2); }
    | NOT unaryExp { $$ = makeUnaryNode(NOT, $2); }
    ;

factor
    : NUM { $$ = makeConstNode($1); }
    | CHARC { $$ = makeConstNode($1); }
    | variable { $$ = $1; }
    | LPAREN exp RPAREN { $$ = $2; }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Error at line %d: %s\n", lineno, s);
}
