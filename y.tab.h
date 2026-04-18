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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    CALL = 277,                    /* CALL  */
    INTEGER_T = 278,               /* INTEGER_T  */
    CHAR_T = 279,                  /* CHAR_T  */
    ASSIGN = 280,                  /* ASSIGN  */
    EQ = 281,                      /* EQ  */
    LT = 282,                      /* LT  */
    LE = 283,                      /* LE  */
    GT = 284,                      /* GT  */
    GE = 285,                      /* GE  */
    NE = 286,                      /* NE  */
    PLUS = 287,                    /* PLUS  */
    MINUS = 288,                   /* MINUS  */
    TIMES = 289,                   /* TIMES  */
    OVER = 290,                    /* OVER  */
    AND = 291,                     /* AND  */
    OR = 292,                      /* OR  */
    NOT = 293,                     /* NOT  */
    LPAREN = 294,                  /* LPAREN  */
    RPAREN = 295,                  /* RPAREN  */
    LMIDPAREN = 296,               /* LMIDPAREN  */
    RMIDPAREN = 297,               /* RMIDPAREN  */
    DOT = 298,                     /* DOT  */
    COLON = 299,                   /* COLON  */
    SEMI = 300,                    /* SEMI  */
    COMMA = 301,                   /* COMMA  */
    RANGE = 302,                   /* RANGE  */
    ERROR = 303,                   /* ERROR  */
    ID = 304,                      /* ID  */
    NUM = 305,                     /* NUM  */
    CHARC = 306,                   /* CHARC  */
    UPLUS = 307,                   /* UPLUS  */
    UMINUS = 308                   /* UMINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 62 "snl.y"

    int val;
    char* name;
    TreeNode* node;

#line 123 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
