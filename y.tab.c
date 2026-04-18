/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "snl.y"

#include "globals.h"
#include <stdio.h>
#include <string>

extern int yylex();
extern int lineno;
void yyerror(const char *s);

TreeNode* root = nullptr;
static constexpr const char* TYPE_INTEGER_NAME = "INTEGER";
static constexpr const char* TYPE_CHAR_NAME = "CHAR";

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

#line 132 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 241 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_PROGRAM = 3,                    /* PROGRAM  */
  YYSYMBOL_PROCEDURE = 4,                  /* PROCEDURE  */
  YYSYMBOL_TYPE = 5,                       /* TYPE  */
  YYSYMBOL_VAR = 6,                        /* VAR  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_THEN = 8,                       /* THEN  */
  YYSYMBOL_ELSE = 9,                       /* ELSE  */
  YYSYMBOL_FI = 10,                        /* FI  */
  YYSYMBOL_WHILE = 11,                     /* WHILE  */
  YYSYMBOL_DO = 12,                        /* DO  */
  YYSYMBOL_ENDWH = 13,                     /* ENDWH  */
  YYSYMBOL_BEGIN_SYM = 14,                 /* BEGIN_SYM  */
  YYSYMBOL_END = 15,                       /* END  */
  YYSYMBOL_READ = 16,                      /* READ  */
  YYSYMBOL_WRITE = 17,                     /* WRITE  */
  YYSYMBOL_ARRAY = 18,                     /* ARRAY  */
  YYSYMBOL_OF = 19,                        /* OF  */
  YYSYMBOL_RECORD = 20,                    /* RECORD  */
  YYSYMBOL_RETURN = 21,                    /* RETURN  */
  YYSYMBOL_CALL = 22,                      /* CALL  */
  YYSYMBOL_INTEGER_T = 23,                 /* INTEGER_T  */
  YYSYMBOL_CHAR_T = 24,                    /* CHAR_T  */
  YYSYMBOL_ASSIGN = 25,                    /* ASSIGN  */
  YYSYMBOL_EQ = 26,                        /* EQ  */
  YYSYMBOL_LT = 27,                        /* LT  */
  YYSYMBOL_LE = 28,                        /* LE  */
  YYSYMBOL_GT = 29,                        /* GT  */
  YYSYMBOL_GE = 30,                        /* GE  */
  YYSYMBOL_NE = 31,                        /* NE  */
  YYSYMBOL_PLUS = 32,                      /* PLUS  */
  YYSYMBOL_MINUS = 33,                     /* MINUS  */
  YYSYMBOL_TIMES = 34,                     /* TIMES  */
  YYSYMBOL_OVER = 35,                      /* OVER  */
  YYSYMBOL_AND = 36,                       /* AND  */
  YYSYMBOL_OR = 37,                        /* OR  */
  YYSYMBOL_NOT = 38,                       /* NOT  */
  YYSYMBOL_LPAREN = 39,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 40,                    /* RPAREN  */
  YYSYMBOL_LMIDPAREN = 41,                 /* LMIDPAREN  */
  YYSYMBOL_RMIDPAREN = 42,                 /* RMIDPAREN  */
  YYSYMBOL_DOT = 43,                       /* DOT  */
  YYSYMBOL_COLON = 44,                     /* COLON  */
  YYSYMBOL_SEMI = 45,                      /* SEMI  */
  YYSYMBOL_COMMA = 46,                     /* COMMA  */
  YYSYMBOL_RANGE = 47,                     /* RANGE  */
  YYSYMBOL_ERROR = 48,                     /* ERROR  */
  YYSYMBOL_ID = 49,                        /* ID  */
  YYSYMBOL_NUM = 50,                       /* NUM  */
  YYSYMBOL_CHARC = 51,                     /* CHARC  */
  YYSYMBOL_UPLUS = 52,                     /* UPLUS  */
  YYSYMBOL_UMINUS = 53,                    /* UMINUS  */
  YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
  YYSYMBOL_program = 55,                   /* program  */
  YYSYMBOL_programHead = 56,               /* programHead  */
  YYSYMBOL_declarePart = 57,               /* declarePart  */
  YYSYMBOL_declItem = 58,                  /* declItem  */
  YYSYMBOL_typeDecPart = 59,               /* typeDecPart  */
  YYSYMBOL_typeDecList = 60,               /* typeDecList  */
  YYSYMBOL_typeDec = 61,                   /* typeDec  */
  YYSYMBOL_varDecPart = 62,                /* varDecPart  */
  YYSYMBOL_varDecList = 63,                /* varDecList  */
  YYSYMBOL_varDec = 64,                    /* varDec  */
  YYSYMBOL_idList = 65,                    /* idList  */
  YYSYMBOL_typeSpec = 66,                  /* typeSpec  */
  YYSYMBOL_fieldDecList = 67,              /* fieldDecList  */
  YYSYMBOL_fieldDec = 68,                  /* fieldDec  */
  YYSYMBOL_procDec = 69,                   /* procDec  */
  YYSYMBOL_paramListOpt = 70,              /* paramListOpt  */
  YYSYMBOL_paramList = 71,                 /* paramList  */
  YYSYMBOL_paramDecl = 72,                 /* paramDecl  */
  YYSYMBOL_programBody = 73,               /* programBody  */
  YYSYMBOL_stmListOpt = 74,                /* stmListOpt  */
  YYSYMBOL_stmList = 75,                   /* stmList  */
  YYSYMBOL_stm = 76,                       /* stm  */
  YYSYMBOL_assignStm = 77,                 /* assignStm  */
  YYSYMBOL_ifStm = 78,                     /* ifStm  */
  YYSYMBOL_whileStm = 79,                  /* whileStm  */
  YYSYMBOL_readStm = 80,                   /* readStm  */
  YYSYMBOL_writeStm = 81,                  /* writeStm  */
  YYSYMBOL_callStm = 82,                   /* callStm  */
  YYSYMBOL_argListOpt = 83,                /* argListOpt  */
  YYSYMBOL_argList = 84,                   /* argList  */
  YYSYMBOL_returnStm = 85,                 /* returnStm  */
  YYSYMBOL_variable = 86,                  /* variable  */
  YYSYMBOL_exp = 87,                       /* exp  */
  YYSYMBOL_orExp = 88,                     /* orExp  */
  YYSYMBOL_andExp = 89,                    /* andExp  */
  YYSYMBOL_relationExp = 90,               /* relationExp  */
  YYSYMBOL_arithExp = 91,                  /* arithExp  */
  YYSYMBOL_term = 92,                      /* term  */
  YYSYMBOL_unaryExp = 93,                  /* unaryExp  */
  YYSYMBOL_factor = 94                     /* factor  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   179

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  41
/* YYNRULES -- Number of rules.  */
#define YYNRULES  92
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  181

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   308


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    97,    97,   105,   115,   124,   125,   129,   130,   131,
     135,   139,   140,   144,   151,   160,   164,   165,   169,   176,
     185,   186,   190,   196,   202,   208,   216,   225,   226,   230,
     240,   258,   278,   279,   283,   284,   288,   295,   305,   314,
     315,   319,   320,   321,   330,   331,   332,   333,   334,   335,
     336,   340,   350,   358,   368,   378,   387,   396,   402,   412,
     413,   417,   418,   422,   430,   434,   438,   445,   449,   450,
     454,   455,   459,   460,   461,   462,   463,   464,   465,   469,
     470,   471,   475,   476,   477,   481,   482,   483,   484,   488,
     489,   490,   491
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "PROGRAM", "PROCEDURE",
  "TYPE", "VAR", "IF", "THEN", "ELSE", "FI", "WHILE", "DO", "ENDWH",
  "BEGIN_SYM", "END", "READ", "WRITE", "ARRAY", "OF", "RECORD", "RETURN",
  "CALL", "INTEGER_T", "CHAR_T", "ASSIGN", "EQ", "LT", "LE", "GT", "GE",
  "NE", "PLUS", "MINUS", "TIMES", "OVER", "AND", "OR", "NOT", "LPAREN",
  "RPAREN", "LMIDPAREN", "RMIDPAREN", "DOT", "COLON", "SEMI", "COMMA",
  "RANGE", "ERROR", "ID", "NUM", "CHARC", "UPLUS", "UMINUS", "$accept",
  "program", "programHead", "declarePart", "declItem", "typeDecPart",
  "typeDecList", "typeDec", "varDecPart", "varDecList", "varDec", "idList",
  "typeSpec", "fieldDecList", "fieldDec", "procDec", "paramListOpt",
  "paramList", "paramDecl", "programBody", "stmListOpt", "stmList", "stm",
  "assignStm", "ifStm", "whileStm", "readStm", "writeStm", "callStm",
  "argListOpt", "argList", "returnStm", "variable", "exp", "orExp",
  "andExp", "relationExp", "arithExp", "term", "unaryExp", "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-94)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-16)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      95,   -31,   -24,    21,   -94,   -94,   -11,   -94,    43,   -94,
      16,    17,    19,    56,   -94,   -94,   -94,   -94,    32,    50,
      52,    74,    10,   -94,    64,   -94,    25,   -94,    58,     3,
       3,    45,    90,   -94,    54,   -94,   124,    96,   -94,   -94,
     -94,   -94,   -94,   -94,   -94,   -94,    15,   -94,    27,   -94,
     -94,    70,   -94,   -94,   -94,    70,    91,     3,     3,     3,
       3,   -94,   -94,    65,   134,   106,   108,   -94,    85,     9,
     -94,   -94,   133,    97,     3,   109,   -94,     6,     3,     3,
      98,   101,    82,   111,   107,   -94,    43,   112,   101,   -94,
     -94,   -94,   110,   113,   -94,   -94,   -94,   -94,   114,    56,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,    56,    39,   116,     3,   -94,   -94,   -94,   115,
     -94,    86,    70,   117,    27,   118,   119,    87,    22,   -94,
     -94,   -94,   -94,   125,   108,   -94,    59,    59,    59,    59,
      59,    59,     9,     9,   -94,   -94,   146,   -94,   -94,   120,
     121,   -94,   -94,    70,   -94,   -94,   -94,   -94,   123,    70,
     -94,   -94,    56,   -94,   -94,   -94,     3,   -94,    43,   122,
     126,   151,   -94,   128,   132,   -94,   -94,   -94,   145,    70,
     -94
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     5,     3,     0,     1,     0,     4,
       0,     0,     0,    39,     6,     7,     8,     9,     0,     0,
       0,     0,     0,    11,     0,    20,     0,    16,     0,     0,
       0,     0,     0,    63,     0,    64,     0,    40,    41,    44,
      45,    46,    47,    48,    49,    50,     0,     2,    32,     5,
      14,     0,    12,    19,    17,     0,     0,     0,     0,     0,
       0,    89,    90,    91,     0,    67,    68,    70,    72,    79,
      82,    85,     0,     0,     0,    57,    38,     0,     0,     0,
       0,     0,     0,     0,    33,    34,     0,     0,     0,    22,
      23,    24,     0,     0,    21,    86,    87,    88,     0,    39,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    39,     0,     0,    59,    43,    42,    51,     0,
      66,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      13,    18,    92,     0,    69,    71,    77,    73,    74,    75,
      76,    78,    80,    81,    83,    84,     0,    55,    56,     0,
      60,    61,    65,     0,    36,     5,    35,    31,     0,     0,
      26,    28,    39,    53,    54,    58,     0,    37,     0,     0,
       0,     0,    62,     0,     0,    29,    52,    30,     0,     0,
      25
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -94,   -94,   -94,   -45,   -94,   -94,   -94,   143,   -94,   -94,
     140,   -43,   -52,   -94,    40,   -94,   -94,   -94,    51,   -85,
     -93,   -94,    99,   -94,   -94,   -94,   -94,   -94,   -94,   -94,
     -94,   -94,   -13,   -28,   -94,    77,    78,    18,    28,   -49,
     -94
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     3,     4,     8,    14,    15,    22,    23,    16,    26,
      27,    28,    92,   128,   129,    17,    83,    84,    85,    18,
      36,    37,    38,    39,    40,    41,    42,    43,    44,   149,
     150,    45,    63,    64,    65,    66,    67,    68,    69,    70,
      71
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,   125,    72,    93,    86,    82,   133,   116,    95,    96,
      97,    20,     5,    29,   -10,   -10,   -10,    30,    20,   146,
      24,     7,    31,    32,   -10,     6,    24,    33,    34,   -15,
     -15,   -15,    98,    81,     9,    57,    58,   160,   121,   -15,
      78,    59,    60,   110,   111,   127,   114,    10,    11,    12,
     118,   119,    35,    61,    62,    35,    79,    13,    80,    21,
     113,   144,   145,    29,    46,    19,    21,    30,    25,   171,
     154,    25,    31,    32,    25,    47,    25,    33,    34,   147,
      79,    82,    80,   173,    73,   127,    46,   151,    87,    48,
      88,   108,   109,    89,    90,    49,     1,    50,     2,    46,
      51,   167,    55,    75,    56,    35,    79,   170,    80,    53,
     168,   102,   103,   104,   105,   106,   107,   108,   109,    91,
     136,   137,   138,   139,   140,   141,   122,   180,    56,    74,
     153,   159,    56,    56,   162,   163,   142,   143,   172,    76,
      94,    77,    99,   100,   101,   112,    35,   120,   115,    46,
      25,   123,   124,   126,   132,   130,   148,   152,   131,   164,
     165,   176,   155,   157,   179,    52,    54,   166,   161,   158,
     169,   175,   174,   177,   178,   156,   117,   134,     0,   135
};

static const yytype_int16 yycheck[] =
{
      13,    86,    30,    55,    49,    48,    99,     1,    57,    58,
      59,     1,    43,     7,     4,     5,     6,    11,     1,   112,
       1,     0,    16,    17,    14,    49,     1,    21,    22,     4,
       5,     6,    60,     6,    45,    32,    33,    15,    81,    14,
      25,    38,    39,    34,    35,    88,    74,     4,     5,     6,
      78,    79,    49,    50,    51,    49,    41,    14,    43,    49,
      73,   110,   111,     7,    77,    49,    49,    11,    49,   162,
     122,    49,    16,    17,    49,    43,    49,    21,    22,    40,
      41,   124,    43,   168,    39,   128,    99,   115,    18,    39,
      20,    32,    33,    23,    24,    45,     1,    45,     3,   112,
      26,   153,    44,    49,    46,    49,    41,   159,    43,    45,
     155,    26,    27,    28,    29,    30,    31,    32,    33,    49,
     102,   103,   104,   105,   106,   107,    44,   179,    46,    39,
      44,    44,    46,    46,     9,    10,   108,   109,   166,    15,
      49,    45,     8,    37,    36,    12,    49,    49,    39,   162,
      49,    40,    45,    41,    40,    45,    40,    42,    45,    13,
      40,    10,    45,    45,    19,    22,    26,    46,   128,    50,
      47,    45,    50,    45,    42,   124,    77,   100,    -1,   101
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     1,     3,    55,    56,    43,    49,     0,    57,    45,
       4,     5,     6,    14,    58,    59,    62,    69,    73,    49,
       1,    49,    60,    61,     1,    49,    63,    64,    65,     7,
      11,    16,    17,    21,    22,    49,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    85,    86,    43,    39,    45,
      45,    26,    61,    45,    64,    44,    46,    32,    33,    38,
      39,    50,    51,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    87,    39,    39,    49,    15,    45,    25,    41,
      43,     6,    65,    70,    71,    72,    57,    18,    20,    23,
      24,    49,    66,    66,    49,    93,    93,    93,    87,     8,
      37,    36,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    12,    86,    87,    39,     1,    76,    87,    87,
      49,    65,    44,    40,    45,    73,    41,    65,    67,    68,
      45,    45,    40,    74,    89,    90,    91,    91,    91,    91,
      91,    91,    92,    92,    93,    93,    74,    40,    40,    83,
      84,    87,    42,    44,    66,    45,    72,    45,    50,    44,
      15,    68,     9,    10,    13,    40,    46,    66,    57,    47,
      66,    74,    87,    73,    50,    45,    10,    45,    42,    19,
      66
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    55,    56,    57,    57,    58,    58,    58,
      59,    60,    60,    61,    61,    62,    63,    63,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    67,    67,    68,
      69,    69,    70,    70,    71,    71,    72,    72,    73,    74,
      74,    75,    75,    75,    76,    76,    76,    76,    76,    76,
      76,    77,    78,    78,    79,    80,    81,    82,    82,    83,
      83,    84,    84,    85,    86,    86,    86,    87,    88,    88,
      89,    89,    90,    90,    90,    90,    90,    90,    90,    91,
      91,    91,    92,    92,    92,    93,    93,    93,    93,    94,
      94,    94,    94
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     2,     3,     0,     2,     1,     1,     1,
       2,     1,     2,     4,     2,     2,     1,     2,     4,     2,
       1,     3,     1,     1,     1,     8,     3,     1,     2,     4,
       9,     6,     0,     1,     1,     3,     3,     4,     3,     0,
       1,     1,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     7,     5,     5,     4,     4,     2,     5,     0,
       1,     1,     3,     1,     1,     4,     3,     1,     1,     3,
       1,     3,     1,     3,     3,     3,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     2,     2,     2,     1,
       1,     1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: programHead declarePart programBody DOT  */
#line 98 "snl.y"
      {
          (yyval.node) = newNode(ProgramK);
          (yyval.node)->addChild((yyvsp[-3].node));
          (yyval.node)->addChild((yyvsp[-2].node));
          (yyval.node)->addChild((yyvsp[-1].node));
          root = (yyval.node);
      }
#line 1446 "y.tab.c"
    break;

  case 3: /* program: error DOT  */
#line 106 "snl.y"
      {
          yyerror("syntax error in program");
          yyerrok;
          root = nullptr;
          (yyval.node) = nullptr;
      }
#line 1457 "y.tab.c"
    break;

  case 4: /* programHead: PROGRAM ID SEMI  */
#line 116 "snl.y"
      {
          (yyval.node) = newNode(RoutineK);
          (yyval.node)->kind.routine = RoutineHeadK;
          (yyval.node)->attr.name = (yyvsp[-1].name);
      }
#line 1467 "y.tab.c"
    break;

  case 5: /* declarePart: %empty  */
#line 124 "snl.y"
                  { (yyval.node) = nullptr; }
#line 1473 "y.tab.c"
    break;

  case 6: /* declarePart: declarePart declItem  */
#line 125 "snl.y"
                           { (yyval.node) = appendSibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1479 "y.tab.c"
    break;

  case 7: /* declItem: typeDecPart  */
#line 129 "snl.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1485 "y.tab.c"
    break;

  case 8: /* declItem: varDecPart  */
#line 130 "snl.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1491 "y.tab.c"
    break;

  case 9: /* declItem: procDec  */
#line 131 "snl.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1497 "y.tab.c"
    break;

  case 10: /* typeDecPart: TYPE typeDecList  */
#line 135 "snl.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 1503 "y.tab.c"
    break;

  case 11: /* typeDecList: typeDec  */
#line 139 "snl.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1509 "y.tab.c"
    break;

  case 12: /* typeDecList: typeDecList typeDec  */
#line 140 "snl.y"
                          { (yyval.node) = appendSibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1515 "y.tab.c"
    break;

  case 13: /* typeDec: ID EQ typeSpec SEMI  */
#line 145 "snl.y"
      {
          (yyval.node) = newNode(DeclareK);
          (yyval.node)->kind.dec = TypeDecK;
          (yyval.node)->attr.name = (yyvsp[-3].name);
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1526 "y.tab.c"
    break;

  case 14: /* typeDec: error SEMI  */
#line 152 "snl.y"
      {
          yyerror("invalid type declaration");
          yyerrok;
          (yyval.node) = nullptr;
      }
#line 1536 "y.tab.c"
    break;

  case 15: /* varDecPart: VAR varDecList  */
#line 160 "snl.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1542 "y.tab.c"
    break;

  case 16: /* varDecList: varDec  */
#line 164 "snl.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1548 "y.tab.c"
    break;

  case 17: /* varDecList: varDecList varDec  */
#line 165 "snl.y"
                        { (yyval.node) = appendSibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1554 "y.tab.c"
    break;

  case 18: /* varDec: idList COLON typeSpec SEMI  */
#line 170 "snl.y"
      {
          (yyval.node) = newNode(DeclareK);
          (yyval.node)->kind.dec = VarDecK;
          (yyval.node)->addChild((yyvsp[-3].node));
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1565 "y.tab.c"
    break;

  case 19: /* varDec: error SEMI  */
#line 177 "snl.y"
      {
          yyerror("invalid variable declaration");
          yyerrok;
          (yyval.node) = nullptr;
      }
#line 1575 "y.tab.c"
    break;

  case 20: /* idList: ID  */
#line 185 "snl.y"
         { (yyval.node) = makeIdNode((yyvsp[0].name)); }
#line 1581 "y.tab.c"
    break;

  case 21: /* idList: idList COMMA ID  */
#line 186 "snl.y"
                      { (yyval.node) = appendSibling((yyvsp[-2].node), makeIdNode((yyvsp[0].name))); }
#line 1587 "y.tab.c"
    break;

  case 22: /* typeSpec: INTEGER_T  */
#line 191 "snl.y"
      {
          (yyval.node) = newNode(TypeK);
          (yyval.node)->kind.type = BaseTypeK;
          (yyval.node)->attr.name = TYPE_INTEGER_NAME;
      }
#line 1597 "y.tab.c"
    break;

  case 23: /* typeSpec: CHAR_T  */
#line 197 "snl.y"
      {
          (yyval.node) = newNode(TypeK);
          (yyval.node)->kind.type = BaseTypeK;
          (yyval.node)->attr.name = TYPE_CHAR_NAME;
      }
#line 1607 "y.tab.c"
    break;

  case 24: /* typeSpec: ID  */
#line 203 "snl.y"
      {
          (yyval.node) = newNode(TypeK);
          (yyval.node)->kind.type = AliasTypeK;
          (yyval.node)->attr.name = (yyvsp[0].name);
      }
#line 1617 "y.tab.c"
    break;

  case 25: /* typeSpec: ARRAY LMIDPAREN NUM RANGE NUM RMIDPAREN OF typeSpec  */
#line 209 "snl.y"
      {
          (yyval.node) = newNode(TypeK);
          (yyval.node)->kind.type = ArrayTypeK;
          (yyval.node)->attr.low = (yyvsp[-5].val);
          (yyval.node)->attr.high = (yyvsp[-3].val);
          (yyval.node)->addChild((yyvsp[0].node));
      }
#line 1629 "y.tab.c"
    break;

  case 26: /* typeSpec: RECORD fieldDecList END  */
#line 217 "snl.y"
      {
          (yyval.node) = newNode(TypeK);
          (yyval.node)->kind.type = RecordTypeK;
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1639 "y.tab.c"
    break;

  case 27: /* fieldDecList: fieldDec  */
#line 225 "snl.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1645 "y.tab.c"
    break;

  case 28: /* fieldDecList: fieldDecList fieldDec  */
#line 226 "snl.y"
                            { (yyval.node) = appendSibling((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1651 "y.tab.c"
    break;

  case 29: /* fieldDec: idList COLON typeSpec SEMI  */
#line 231 "snl.y"
      {
          (yyval.node) = newNode(DeclareK);
          (yyval.node)->kind.dec = FieldDecK;
          (yyval.node)->addChild((yyvsp[-3].node));
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1662 "y.tab.c"
    break;

  case 30: /* procDec: PROCEDURE ID LPAREN paramListOpt RPAREN SEMI declarePart programBody SEMI  */
#line 241 "snl.y"
      {
          TreeNode* head = newNode(RoutineK);
          head->kind.routine = RoutineHeadK;
          head->attr.name = (yyvsp[-7].name);
          head->addChild((yyvsp[-5].node));

          TreeNode* body = newNode(RoutineK);
          body->kind.routine = RoutineBodyK;
          body->addChild((yyvsp[-2].node));
          body->addChild((yyvsp[-1].node));

          (yyval.node) = newNode(DeclareK);
          (yyval.node)->kind.dec = ProcDecK;
          (yyval.node)->attr.name = (yyvsp[-7].name);
          (yyval.node)->addChild(head);
          (yyval.node)->addChild(body);
      }
#line 1684 "y.tab.c"
    break;

  case 31: /* procDec: PROCEDURE ID SEMI declarePart programBody SEMI  */
#line 259 "snl.y"
      {
          TreeNode* head = newNode(RoutineK);
          head->kind.routine = RoutineHeadK;
          head->attr.name = (yyvsp[-4].name);

          TreeNode* body = newNode(RoutineK);
          body->kind.routine = RoutineBodyK;
          body->addChild((yyvsp[-2].node));
          body->addChild((yyvsp[-1].node));

          (yyval.node) = newNode(DeclareK);
          (yyval.node)->kind.dec = ProcDecK;
          (yyval.node)->attr.name = (yyvsp[-4].name);
          (yyval.node)->addChild(head);
          (yyval.node)->addChild(body);
      }
#line 1705 "y.tab.c"
    break;

  case 32: /* paramListOpt: %empty  */
#line 278 "snl.y"
                  { (yyval.node) = nullptr; }
#line 1711 "y.tab.c"
    break;

  case 33: /* paramListOpt: paramList  */
#line 279 "snl.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1717 "y.tab.c"
    break;

  case 34: /* paramList: paramDecl  */
#line 283 "snl.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1723 "y.tab.c"
    break;

  case 35: /* paramList: paramList SEMI paramDecl  */
#line 284 "snl.y"
                               { (yyval.node) = appendSibling((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1729 "y.tab.c"
    break;

  case 36: /* paramDecl: idList COLON typeSpec  */
#line 289 "snl.y"
      {
          (yyval.node) = newNode(ParamK);
          (yyval.node)->kind.param = ValueParamK;
          (yyval.node)->addChild((yyvsp[-2].node));
          (yyval.node)->addChild((yyvsp[0].node));
      }
#line 1740 "y.tab.c"
    break;

  case 37: /* paramDecl: VAR idList COLON typeSpec  */
#line 296 "snl.y"
      {
          (yyval.node) = newNode(ParamK);
          (yyval.node)->kind.param = VarParamK;
          (yyval.node)->addChild((yyvsp[-2].node));
          (yyval.node)->addChild((yyvsp[0].node));
      }
#line 1751 "y.tab.c"
    break;

  case 38: /* programBody: BEGIN_SYM stmListOpt END  */
#line 306 "snl.y"
      {
          (yyval.node) = newNode(RoutineK);
          (yyval.node)->kind.routine = RoutineBodyK;
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1761 "y.tab.c"
    break;

  case 39: /* stmListOpt: %empty  */
#line 314 "snl.y"
                  { (yyval.node) = nullptr; }
#line 1767 "y.tab.c"
    break;

  case 40: /* stmListOpt: stmList  */
#line 315 "snl.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1773 "y.tab.c"
    break;

  case 41: /* stmList: stm  */
#line 319 "snl.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 1779 "y.tab.c"
    break;

  case 42: /* stmList: stmList SEMI stm  */
#line 320 "snl.y"
                       { (yyval.node) = appendSibling((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1785 "y.tab.c"
    break;

  case 43: /* stmList: stmList SEMI error  */
#line 322 "snl.y"
      {
          yyerror("invalid statement, skipped");
          yyerrok;
          (yyval.node) = (yyvsp[-2].node);
      }
#line 1795 "y.tab.c"
    break;

  case 44: /* stm: assignStm  */
#line 330 "snl.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1801 "y.tab.c"
    break;

  case 45: /* stm: ifStm  */
#line 331 "snl.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1807 "y.tab.c"
    break;

  case 46: /* stm: whileStm  */
#line 332 "snl.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1813 "y.tab.c"
    break;

  case 47: /* stm: readStm  */
#line 333 "snl.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1819 "y.tab.c"
    break;

  case 48: /* stm: writeStm  */
#line 334 "snl.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 1825 "y.tab.c"
    break;

  case 49: /* stm: callStm  */
#line 335 "snl.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1831 "y.tab.c"
    break;

  case 50: /* stm: returnStm  */
#line 336 "snl.y"
                { (yyval.node) = (yyvsp[0].node); }
#line 1837 "y.tab.c"
    break;

  case 51: /* assignStm: variable ASSIGN exp  */
#line 341 "snl.y"
      {
          (yyval.node) = newNode(StmtK);
          (yyval.node)->kind.stmt = AssignK;
          (yyval.node)->addChild((yyvsp[-2].node));
          (yyval.node)->addChild((yyvsp[0].node));
      }
#line 1848 "y.tab.c"
    break;

  case 52: /* ifStm: IF exp THEN stmListOpt ELSE stmListOpt FI  */
#line 351 "snl.y"
      {
          (yyval.node) = newNode(StmtK);
          (yyval.node)->kind.stmt = IfK;
          (yyval.node)->addChild((yyvsp[-5].node));
          (yyval.node)->addChild((yyvsp[-3].node));
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1860 "y.tab.c"
    break;

  case 53: /* ifStm: IF exp THEN stmListOpt FI  */
#line 359 "snl.y"
      {
          (yyval.node) = newNode(StmtK);
          (yyval.node)->kind.stmt = IfK;
          (yyval.node)->addChild((yyvsp[-3].node));
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1871 "y.tab.c"
    break;

  case 54: /* whileStm: WHILE exp DO stmListOpt ENDWH  */
#line 369 "snl.y"
      {
          (yyval.node) = newNode(StmtK);
          (yyval.node)->kind.stmt = WhileK;
          (yyval.node)->addChild((yyvsp[-3].node));
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1882 "y.tab.c"
    break;

  case 55: /* readStm: READ LPAREN variable RPAREN  */
#line 379 "snl.y"
      {
          (yyval.node) = newNode(StmtK);
          (yyval.node)->kind.stmt = ReadK;
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1892 "y.tab.c"
    break;

  case 56: /* writeStm: WRITE LPAREN exp RPAREN  */
#line 388 "snl.y"
      {
          (yyval.node) = newNode(StmtK);
          (yyval.node)->kind.stmt = WriteK;
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1902 "y.tab.c"
    break;

  case 57: /* callStm: CALL ID  */
#line 397 "snl.y"
      {
          (yyval.node) = newNode(StmtK);
          (yyval.node)->kind.stmt = CallK;
          (yyval.node)->attr.name = (yyvsp[0].name);
      }
#line 1912 "y.tab.c"
    break;

  case 58: /* callStm: CALL ID LPAREN argListOpt RPAREN  */
#line 403 "snl.y"
      {
          (yyval.node) = newNode(StmtK);
          (yyval.node)->kind.stmt = CallK;
          (yyval.node)->attr.name = (yyvsp[-3].name);
          (yyval.node)->addChild((yyvsp[-1].node));
      }
#line 1923 "y.tab.c"
    break;

  case 59: /* argListOpt: %empty  */
#line 412 "snl.y"
                  { (yyval.node) = nullptr; }
#line 1929 "y.tab.c"
    break;

  case 60: /* argListOpt: argList  */
#line 413 "snl.y"
              { (yyval.node) = (yyvsp[0].node); }
#line 1935 "y.tab.c"
    break;

  case 61: /* argList: exp  */
#line 417 "snl.y"
          { (yyval.node) = (yyvsp[0].node); }
#line 1941 "y.tab.c"
    break;

  case 62: /* argList: argList COMMA exp  */
#line 418 "snl.y"
                        { (yyval.node) = appendSibling((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1947 "y.tab.c"
    break;

  case 63: /* returnStm: RETURN  */
#line 423 "snl.y"
      {
          (yyval.node) = newNode(StmtK);
          (yyval.node)->kind.stmt = ReturnK;
      }
#line 1956 "y.tab.c"
    break;

  case 64: /* variable: ID  */
#line 431 "snl.y"
      {
          (yyval.node) = makeIdNode((yyvsp[0].name));
      }
#line 1964 "y.tab.c"
    break;

  case 65: /* variable: variable LMIDPAREN exp RMIDPAREN  */
#line 435 "snl.y"
      {
          (yyval.node) = makeOpNode(LMIDPAREN, (yyvsp[-3].node), (yyvsp[-1].node));
      }
#line 1972 "y.tab.c"
    break;

  case 66: /* variable: variable DOT ID  */
#line 439 "snl.y"
      {
          (yyval.node) = makeOpNode(DOT, (yyvsp[-2].node), makeIdNode((yyvsp[0].name)));
      }
#line 1980 "y.tab.c"
    break;

  case 67: /* exp: orExp  */
#line 445 "snl.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1986 "y.tab.c"
    break;

  case 68: /* orExp: andExp  */
#line 449 "snl.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 1992 "y.tab.c"
    break;

  case 69: /* orExp: orExp OR andExp  */
#line 450 "snl.y"
                      { (yyval.node) = makeOpNode(OR, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1998 "y.tab.c"
    break;

  case 70: /* andExp: relationExp  */
#line 454 "snl.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 2004 "y.tab.c"
    break;

  case 71: /* andExp: andExp AND relationExp  */
#line 455 "snl.y"
                             { (yyval.node) = makeOpNode(AND, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2010 "y.tab.c"
    break;

  case 72: /* relationExp: arithExp  */
#line 459 "snl.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2016 "y.tab.c"
    break;

  case 73: /* relationExp: arithExp LT arithExp  */
#line 460 "snl.y"
                           { (yyval.node) = makeOpNode(LT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2022 "y.tab.c"
    break;

  case 74: /* relationExp: arithExp LE arithExp  */
#line 461 "snl.y"
                           { (yyval.node) = makeOpNode(LE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2028 "y.tab.c"
    break;

  case 75: /* relationExp: arithExp GT arithExp  */
#line 462 "snl.y"
                           { (yyval.node) = makeOpNode(GT, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2034 "y.tab.c"
    break;

  case 76: /* relationExp: arithExp GE arithExp  */
#line 463 "snl.y"
                           { (yyval.node) = makeOpNode(GE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2040 "y.tab.c"
    break;

  case 77: /* relationExp: arithExp EQ arithExp  */
#line 464 "snl.y"
                           { (yyval.node) = makeOpNode(EQ, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2046 "y.tab.c"
    break;

  case 78: /* relationExp: arithExp NE arithExp  */
#line 465 "snl.y"
                           { (yyval.node) = makeOpNode(NE, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2052 "y.tab.c"
    break;

  case 79: /* arithExp: term  */
#line 469 "snl.y"
           { (yyval.node) = (yyvsp[0].node); }
#line 2058 "y.tab.c"
    break;

  case 80: /* arithExp: arithExp PLUS term  */
#line 470 "snl.y"
                         { (yyval.node) = makeOpNode(PLUS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2064 "y.tab.c"
    break;

  case 81: /* arithExp: arithExp MINUS term  */
#line 471 "snl.y"
                          { (yyval.node) = makeOpNode(MINUS, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2070 "y.tab.c"
    break;

  case 82: /* term: unaryExp  */
#line 475 "snl.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2076 "y.tab.c"
    break;

  case 83: /* term: term TIMES unaryExp  */
#line 476 "snl.y"
                          { (yyval.node) = makeOpNode(TIMES, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2082 "y.tab.c"
    break;

  case 84: /* term: term OVER unaryExp  */
#line 477 "snl.y"
                         { (yyval.node) = makeOpNode(OVER, (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2088 "y.tab.c"
    break;

  case 85: /* unaryExp: factor  */
#line 481 "snl.y"
             { (yyval.node) = (yyvsp[0].node); }
#line 2094 "y.tab.c"
    break;

  case 86: /* unaryExp: PLUS unaryExp  */
#line 482 "snl.y"
                                { (yyval.node) = makeUnaryNode(PLUS, (yyvsp[0].node)); }
#line 2100 "y.tab.c"
    break;

  case 87: /* unaryExp: MINUS unaryExp  */
#line 483 "snl.y"
                                  { (yyval.node) = makeUnaryNode(MINUS, (yyvsp[0].node)); }
#line 2106 "y.tab.c"
    break;

  case 88: /* unaryExp: NOT unaryExp  */
#line 484 "snl.y"
                   { (yyval.node) = makeUnaryNode(NOT, (yyvsp[0].node)); }
#line 2112 "y.tab.c"
    break;

  case 89: /* factor: NUM  */
#line 488 "snl.y"
          { (yyval.node) = makeConstNode((yyvsp[0].val)); }
#line 2118 "y.tab.c"
    break;

  case 90: /* factor: CHARC  */
#line 489 "snl.y"
            { (yyval.node) = makeConstNode((yyvsp[0].val)); }
#line 2124 "y.tab.c"
    break;

  case 91: /* factor: variable  */
#line 490 "snl.y"
               { (yyval.node) = (yyvsp[0].node); }
#line 2130 "y.tab.c"
    break;

  case 92: /* factor: LPAREN exp RPAREN  */
#line 491 "snl.y"
                        { (yyval.node) = (yyvsp[-1].node); }
#line 2136 "y.tab.c"
    break;


#line 2140 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 494 "snl.y"


void yyerror(const char* s) {
    fprintf(stderr, "Error at line %d: %s\n", lineno, s);
}
