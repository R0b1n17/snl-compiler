%{
#include "globals.h"
#include "y.tab.h"
#include <string.h>

int lineno = 1;
%}

%option noyywrap

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}({letter}|{digit})*
newline     \n
whitespace  [ \t\r]+

%%

"PROGRAM"       { return PROGRAM; }
"PROCEDURE"     { return PROCEDURE; }
"TYPE"          { return TYPE; }
"VAR"           { return VAR; }
"IF"            { return IF; }
"THEN"          { return THEN; }
"ELSE"          { return ELSE; }
"FI"            { return FI; }
"WHILE"         { return WHILE; }
"DO"            { return DO; }
"ENDWH"         { return ENDWH; }
"BEGIN"         { return BEGIN_SYM; }
"END"           { return END; }
"READ"          { return READ; }
"WRITE"         { return WRITE; }
"ARRAY"         { return ARRAY; }
"OF"            { return OF; }
"RECORD"        { return RECORD; }
"RETURN"        { return RETURN; }
"INTEGER"       { return INTEGER_T; }
"CHAR"          { return CHAR_T; }

":="            { return ASSIGN; }
"="             { return EQ; }
"<"             { return LT; }
"+"             { return PLUS; }
"-"             { return MINUS; }
"*"             { return TIMES; }
"/"             { return OVER; }
"("             { return LPAREN; }
")"             { return RPAREN; }
"["             { return LMIDPAREN; }
"]"             { return RMIDPAREN; }
"."             { return DOT; }
":"             { return COLON; }
";"             { return SEMI; }
","             { return COMMA; }
".."            { return RANGE; }

{number}        { yylval.val = atoi(yytext); return NUM; }
{identifier}    { yylval.name = _strdup(yytext); return ID; }
"'"."'"         { yylval.name = _strdup(yytext); return CHARC; }

"{"[^}]*"}"     { /* skip */ }
{newline}       { lineno++; }
{whitespace}    { /* skip */ }
.               { return ERROR; }

%%