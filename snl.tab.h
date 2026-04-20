/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SNL_TAB_H_INCLUDED
# define YY_YY_SNL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    PROGRAM = 258,                 /* PROGRAM  */
    PROCEDURE = 259,               /* PROCEDURE  */
    TYPE = 260,                    /* TYPE  */
    VAR = 261,                     /* VAR  */
    IF = 262,                      /* IF  */
    THEN = 263,                    /* THEN  */
    ELSE = 264,                    /* ELSE  */
    FI = 265,                      /* FI  */
    WHILE = 266,                   /* WHILE  */
    DO = 267,                      /* DO  */
    ENDWH = 268,                   /* ENDWH  */
    BEGIN_SYM = 269,               /* BEGIN_SYM  */
    END = 270,                     /* END  */
    READ = 271,                    /* READ  */
    WRITE = 272,                   /* WRITE  */
    ARRAY = 273,                   /* ARRAY  */
    OF = 274,                      /* OF  */
    RECORD = 275,                  /* RECORD  */
    RETURN = 276,                  /* RETURN  */
    INTEGER_T = 277,               /* INTEGER_T  */
    CHAR_T = 278,                  /* CHAR_T  */
    ASSIGN = 279,                  /* ASSIGN  */
    EQ = 280,                      /* EQ  */
    LT = 281,                      /* LT  */
    PLUS = 282,                    /* PLUS  */
    MINUS = 283,                   /* MINUS  */
    TIMES = 284,                   /* TIMES  */
    OVER = 285,                    /* OVER  */
    LPAREN = 286,                  /* LPAREN  */
    RPAREN = 287,                  /* RPAREN  */
    LMIDPAREN = 288,               /* LMIDPAREN  */
    RMIDPAREN = 289,               /* RMIDPAREN  */
    DOT = 290,                     /* DOT  */
    COLON = 291,                   /* COLON  */
    SEMI = 292,                    /* SEMI  */
    COMMA = 293,                   /* COMMA  */
    RANGE = 294,                   /* RANGE  */
    ERROR = 295,                   /* ERROR  */
    NUM = 296,                     /* NUM  */
    ID = 297,                      /* ID  */
    CHARC = 298                    /* CHARC  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 17 "snl.y"

    int val;
    char * name;
    TreeNode * node;

#line 113 "snl.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_SNL_TAB_H_INCLUDED  */
