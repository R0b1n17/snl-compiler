%{
#include "globals.h"
#include "y.tab.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lineno = 1;
static const long SNL_INT_MIN = -32768;
static const long SNL_INT_MAX = 32767;
%}

%option noyywrap
%x COMMENT

digit       [0-9]
number      {digit}+
letter      [a-zA-Z]
identifier  {letter}({letter}|{digit})*
newline     \n
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
"CALL"          { return CALL; }
"INTEGER"       { return INTEGER_T; }
"CHAR"          { return CHAR_T; }
"AND"           { return AND; }
"OR"            { return OR; }
"NOT"           { return NOT; }

":="            { return ASSIGN; }
"<="            { return LE; }
">="            { return GE; }
"<>"            { return NE; }
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

{number} {
    errno = 0;
    long v = strtol(yytext, nullptr, 10);
    if (errno == ERANGE || v < SNL_INT_MIN || v > SNL_INT_MAX) {
        fprintf(stderr, "Line %d: integer out of range [%ld,%ld]: %s\n", lineno, SNL_INT_MIN, SNL_INT_MAX, yytext);
        return ERROR;
    }
    yylval.val = (int)v;
    return NUM;
}

{identifier} {
    char* dup = strdup(yytext);
    if (dup == nullptr) {
        fprintf(stderr, "Line %d: out of memory while reading identifier\n", lineno);
        return ERROR;
    }
    yylval.name = dup;
    return ID;
}

\'(\\n|\\t|\\\\|\\'|\\0|[^\\'\n])\' {
    char c = 0;
    if (yytext[1] == '\\') {
        switch (yytext[2]) {
            case 'n': c = '\n'; break;
            case 't': c = '\t'; break;
            case '\\': c = '\\'; break;
            case '\'': c = '\''; break;
            case '0': c = '\0'; break;
            default:
                fprintf(stderr, "Line %d: invalid escape sequence in char literal %s\n", lineno, yytext);
                return ERROR;
        }
    } else {
        c = yytext[1];
    }
    yylval.val = (unsigned char)c;
    return CHARC;
}

"{"             { BEGIN(COMMENT); }
<COMMENT>"}"     { BEGIN(INITIAL); }
<COMMENT>{newline} { lineno++; }
<COMMENT>.       { /* skip */ }
<COMMENT><<EOF>> {
    fprintf(stderr, "Line %d: unterminated comment\n", lineno);
    return ERROR;
}

{newline}       { lineno++; }
[ \t\r]+       { /* skip */ }

. {
    fprintf(stderr, "Line %d: illegal character '%c'\n", lineno, yytext[0]);
    return ERROR;
}

%%
