%{
#include "globals.h"
#include "y.tab.h"
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lineno = 1;
int comment_depth = 0;
%}

%option noyywrap
%x COMMENT

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}({letter}|{digit})*
newline     \n
whitespace  [ \t\r]+
charconst   \'(\\[nt0\\\']|[^\\\'\n])\'

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
"CALL"          { return CALL; }
"ARRAY"         { return ARRAY; }
"OF"            { return OF; }
"RECORD"        { return RECORD; }
"RETURN"        { return RETURN; }
"AND"           { return AND; }
"OR"            { return OR; }
"NOT"           { return NOT; }
"INTEGER"       { return INTEGER_T; }
"CHAR"          { return CHAR_T; }

":="            { return ASSIGN; }
"<="            { return LE; }
">="            { return GE; }
"<>"            { return NEQ; }
"="             { return EQ; }
"<"             { return LT; }
">"             { return GT; }
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

{number}        {
                    errno = 0;
                    long value = strtol(yytext, NULL, 10);
                    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
                        fprintf(stderr, "Lexical error at line %d: integer out of range '%s'\n", lineno, yytext);
                        yylval.val = 0;
                        return NUM;
                    }
                    yylval.val = (int)value;
                    return NUM;
                }
{identifier}    { yylval.name = strdup(yytext); return ID; }
{charconst}     { yylval.name = strdup(yytext); return CHARC; }

"{"             { comment_depth = 1; BEGIN(COMMENT); }
<COMMENT>"{"    { comment_depth++; }
<COMMENT>"}"    { if (--comment_depth == 0) BEGIN(INITIAL); }
<COMMENT>{newline} { lineno++; }
<COMMENT>.      { /* skip */ }
<COMMENT><<EOF>> {
                    fprintf(stderr, "Lexical error at line %d: unterminated comment\n", lineno);
                    BEGIN(INITIAL);
                    yyterminate();
                }
{newline}       { lineno++; }
{whitespace}    { /* skip */ }
.               {
                    fprintf(stderr, "Lexical error at line %d: illegal character '%s'\n", lineno, yytext);
                    /* skip illegal char */
                }

%%
