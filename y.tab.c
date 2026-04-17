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
#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

extern int yylex();
extern int lineno;
void yyerror(const char *s);

TreeNode * root = nullptr;

#line 86 "y.tab.c"

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
    ID = 296,                      /* ID  */
    CHARC = 297,                   /* CHARC  */
    NUM = 298                      /* NUM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define PROGRAM 258
#define PROCEDURE 259
#define TYPE 260
#define VAR 261
#define IF 262
#define THEN 263
#define ELSE 264
#define FI 265
#define WHILE 266
#define DO 267
#define ENDWH 268
#define BEGIN_SYM 269
#define END 270
#define READ 271
#define WRITE 272
#define ARRAY 273
#define OF 274
#define RECORD 275
#define RETURN 276
#define INTEGER_T 277
#define CHAR_T 278
#define ASSIGN 279
#define EQ 280
#define LT 281
#define PLUS 282
#define MINUS 283
#define TIMES 284
#define OVER 285
#define LPAREN 286
#define RPAREN 287
#define LMIDPAREN 288
#define RMIDPAREN 289
#define DOT 290
#define COLON 291
#define SEMI 292
#define COMMA 293
#define RANGE 294
#define ERROR 295
#define ID 296
#define CHARC 297
#define NUM 298

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "snl.y"

    int val;
    char * name;
    TreeNode * node;

#line 231 "y.tab.c"

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
  YYSYMBOL_INTEGER_T = 22,                 /* INTEGER_T  */
  YYSYMBOL_CHAR_T = 23,                    /* CHAR_T  */
  YYSYMBOL_ASSIGN = 24,                    /* ASSIGN  */
  YYSYMBOL_EQ = 25,                        /* EQ  */
  YYSYMBOL_LT = 26,                        /* LT  */
  YYSYMBOL_PLUS = 27,                      /* PLUS  */
  YYSYMBOL_MINUS = 28,                     /* MINUS  */
  YYSYMBOL_TIMES = 29,                     /* TIMES  */
  YYSYMBOL_OVER = 30,                      /* OVER  */
  YYSYMBOL_LPAREN = 31,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 32,                    /* RPAREN  */
  YYSYMBOL_LMIDPAREN = 33,                 /* LMIDPAREN  */
  YYSYMBOL_RMIDPAREN = 34,                 /* RMIDPAREN  */
  YYSYMBOL_DOT = 35,                       /* DOT  */
  YYSYMBOL_COLON = 36,                     /* COLON  */
  YYSYMBOL_SEMI = 37,                      /* SEMI  */
  YYSYMBOL_COMMA = 38,                     /* COMMA  */
  YYSYMBOL_RANGE = 39,                     /* RANGE  */
  YYSYMBOL_ERROR = 40,                     /* ERROR  */
  YYSYMBOL_ID = 41,                        /* ID  */
  YYSYMBOL_CHARC = 42,                     /* CHARC  */
  YYSYMBOL_NUM = 43,                       /* NUM  */
  YYSYMBOL_YYACCEPT = 44,                  /* $accept  */
  YYSYMBOL_program = 45,                   /* program  */
  YYSYMBOL_programHead = 46,               /* programHead  */
  YYSYMBOL_declarePart = 47,               /* declarePart  */
  YYSYMBOL_varDecList = 48,                /* varDecList  */
  YYSYMBOL_varIdList = 49,                 /* varIdList  */
  YYSYMBOL_programBody = 50,               /* programBody  */
  YYSYMBOL_stmList = 51,                   /* stmList  */
  YYSYMBOL_stm = 52,                       /* stm  */
  YYSYMBOL_assignStm = 53,                 /* assignStm  */
  YYSYMBOL_ifStm = 54,                     /* ifStm  */
  YYSYMBOL_whileStm = 55,                  /* whileStm  */
  YYSYMBOL_readStm = 56,                   /* readStm  */
  YYSYMBOL_writeStm = 57,                  /* writeStm  */
  YYSYMBOL_returnStm = 58,                 /* returnStm  */
  YYSYMBOL_exp = 59,                       /* exp  */
  YYSYMBOL_simple_exp = 60,                /* simple_exp  */
  YYSYMBOL_term = 61,                      /* term  */
  YYSYMBOL_factor = 62                     /* factor  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   58

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  44
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  37
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  75

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   298


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
      35,    36,    37,    38,    39,    40,    41,    42,    43
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    40,    40,    51,    59,    60,    63,    73,    79,    87,
      91,    92,    93,    96,    97,    98,    99,   100,   101,   104,
     113,   122,   132,   142,   151,   160,   169,   170,   176,   184,
     185,   191,   199,   200,   206,   214,   219,   224
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
  "INTEGER_T", "CHAR_T", "ASSIGN", "EQ", "LT", "PLUS", "MINUS", "TIMES",
  "OVER", "LPAREN", "RPAREN", "LMIDPAREN", "RMIDPAREN", "DOT", "COLON",
  "SEMI", "COMMA", "RANGE", "ERROR", "ID", "CHARC", "NUM", "$accept",
  "program", "programHead", "declarePart", "varDecList", "varIdList",
  "programBody", "stmList", "stm", "assignStm", "ifStm", "whileStm",
  "readStm", "writeStm", "returnStm", "exp", "simple_exp", "term",
  "factor", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-43)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
       5,   -30,    16,    12,   -12,   -43,    11,    21,   -43,    -3,
     -43,    -7,     6,     4,     7,   -28,   -28,    15,    17,   -43,
      19,    30,    10,   -43,   -43,   -43,   -43,   -43,   -43,   -43,
      -3,   -43,   -28,   -43,   -43,    41,    -6,   -23,   -43,    38,
      13,   -28,   -28,   -43,    -7,   -43,    20,    -7,   -28,   -28,
     -28,   -28,   -28,   -28,    -7,    23,    24,   -43,   -43,   -43,
      14,     2,     2,   -23,   -23,   -43,   -43,    40,   -43,   -43,
      -7,   -43,   -43,    47,   -43
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     5,     0,     1,     0,     0,     3,     0,
       4,     0,     0,     7,     0,     0,     0,     0,     0,    25,
       0,     0,    10,    13,    14,    15,    16,    17,    18,     2,
       0,     6,     0,    36,    35,     0,    26,    29,    32,     0,
       0,     0,     0,     9,    12,     8,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,    11,    37,
       0,    28,    27,    30,    31,    33,    34,     0,    23,    24,
       0,    21,    22,     0,    20
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -43,   -43,   -43,   -43,   -43,    28,   -43,   -42,   -43,   -43,
     -43,   -43,   -43,   -43,   -43,   -15,   -17,   -14,   -13
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     7,    10,    14,    12,    21,    22,    23,
      24,    25,    26,    27,    28,    35,    36,    37,    38
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      15,    39,    58,    32,    16,    60,    52,    53,     1,    17,
      18,     4,    67,    33,    19,    34,     5,    46,     6,    48,
      49,    50,    51,    70,    71,     8,    56,    57,    73,    50,
      51,    61,    62,     9,    20,    11,    63,    64,    13,    65,
      66,    29,    30,    42,    31,    43,    40,    44,    41,    47,
      54,     0,    59,    72,    55,    68,    69,    74,    45
};

static const yytype_int8 yycheck[] =
{
       7,    16,    44,    31,    11,    47,    29,    30,     3,    16,
      17,    41,    54,    41,    21,    43,     0,    32,     6,    25,
      26,    27,    28,     9,    10,    37,    41,    42,    70,    27,
      28,    48,    49,    22,    41,    14,    50,    51,    41,    52,
      53,    35,    38,    24,    37,    15,    31,    37,    31,     8,
      12,    -1,    32,    13,    41,    32,    32,    10,    30
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    45,    46,    41,     0,     6,    47,    37,    22,
      48,    14,    50,    41,    49,     7,    11,    16,    17,    21,
      41,    51,    52,    53,    54,    55,    56,    57,    58,    35,
      38,    37,    31,    41,    43,    59,    60,    61,    62,    59,
      31,    31,    24,    15,    37,    49,    59,     8,    25,    26,
      27,    28,    29,    30,    12,    41,    59,    59,    51,    32,
      51,    60,    60,    61,    61,    62,    62,    51,    32,    32,
       9,    10,    13,    51,    10
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    44,    45,    46,    47,    47,    48,    49,    49,    50,
      51,    51,    51,    52,    52,    52,    52,    52,    52,    53,
      54,    54,    55,    56,    57,    58,    59,    59,    59,    60,
      60,    60,    61,    61,    61,    62,    62,    62
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     4,     3,     2,     0,     3,     1,     3,     3,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     3,
       7,     5,     5,     4,     4,     1,     1,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     1,     3
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
#line 41 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->nodekind = ProgramK;
                  (yyval.node)->child[0] = (yyvsp[-3].node); 
                  (yyval.node)->child[1] = (yyvsp[-2].node); 
                  (yyval.node)->child[2] = (yyvsp[-1].node); 
                  root = (yyval.node);
              }
#line 1319 "y.tab.c"
    break;

  case 3: /* programHead: PROGRAM ID SEMI  */
#line 52 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->nodekind = RoutineK;
                  (yyval.node)->attr.name = (yyvsp[-1].name);
              }
#line 1329 "y.tab.c"
    break;

  case 4: /* declarePart: VAR varDecList  */
#line 59 "snl.y"
                             { (yyval.node) = (yyvsp[0].node); }
#line 1335 "y.tab.c"
    break;

  case 5: /* declarePart: %empty  */
#line 60 "snl.y"
                          { (yyval.node) = nullptr; }
#line 1341 "y.tab.c"
    break;

  case 6: /* varDecList: INTEGER_T varIdList SEMI  */
#line 64 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->nodekind = DeclareK;
                  (yyval.node)->kind.dec = IntegerK;
                  (yyval.node)->child[0] = (yyvsp[-1].node); // 这里挂载的是变量链表的头
              }
#line 1352 "y.tab.c"
    break;

  case 7: /* varIdList: ID  */
#line 74 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->attr.name = (yyvsp[0].name);
                  /* 只有一个变量，没有兄弟节点 */
              }
#line 1362 "y.tab.c"
    break;

  case 8: /* varIdList: ID COMMA varIdList  */
#line 80 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->attr.name = (yyvsp[-2].name);
                  (yyval.node)->sibling = (yyvsp[0].node); // 通过 sibling 把后面的变量链表接上来
              }
#line 1372 "y.tab.c"
    break;

  case 9: /* programBody: BEGIN_SYM stmList END  */
#line 87 "snl.y"
                                    { (yyval.node) = (yyvsp[-1].node); }
#line 1378 "y.tab.c"
    break;

  case 10: /* stmList: stm  */
#line 91 "snl.y"
                  { (yyval.node) = (yyvsp[0].node); }
#line 1384 "y.tab.c"
    break;

  case 11: /* stmList: stm SEMI stmList  */
#line 92 "snl.y"
                               { (yyvsp[-2].node)->sibling = (yyvsp[0].node); (yyval.node) = (yyvsp[-2].node); }
#line 1390 "y.tab.c"
    break;

  case 12: /* stmList: stm SEMI  */
#line 93 "snl.y"
                       { (yyval.node) = (yyvsp[-1].node); }
#line 1396 "y.tab.c"
    break;

  case 13: /* stm: assignStm  */
#line 96 "snl.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1402 "y.tab.c"
    break;

  case 14: /* stm: ifStm  */
#line 97 "snl.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1408 "y.tab.c"
    break;

  case 15: /* stm: whileStm  */
#line 98 "snl.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1414 "y.tab.c"
    break;

  case 16: /* stm: readStm  */
#line 99 "snl.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1420 "y.tab.c"
    break;

  case 17: /* stm: writeStm  */
#line 100 "snl.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1426 "y.tab.c"
    break;

  case 18: /* stm: returnStm  */
#line 101 "snl.y"
                        { (yyval.node) = (yyvsp[0].node); }
#line 1432 "y.tab.c"
    break;

  case 19: /* assignStm: ID ASSIGN exp  */
#line 105 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->nodekind = StmtK; (yyval.node)->kind.stmt = AssignK;
                  (yyval.node)->attr.name = (yyvsp[-2].name); (yyval.node)->child[0] = (yyvsp[0].node);
                  (yyval.node)->lineno = lineno;
              }
#line 1443 "y.tab.c"
    break;

  case 20: /* ifStm: IF exp THEN stmList ELSE stmList FI  */
#line 114 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->nodekind = StmtK; (yyval.node)->kind.stmt = IfK;
                  (yyval.node)->child[0] = (yyvsp[-5].node); 
                  (yyval.node)->child[1] = (yyvsp[-3].node); 
                  (yyval.node)->child[2] = (yyvsp[-1].node); 
                  (yyval.node)->lineno = lineno;
              }
#line 1456 "y.tab.c"
    break;

  case 21: /* ifStm: IF exp THEN stmList FI  */
#line 123 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->nodekind = StmtK; (yyval.node)->kind.stmt = IfK;
                  (yyval.node)->child[0] = (yyvsp[-3].node);
                  (yyval.node)->child[1] = (yyvsp[-1].node);
                  (yyval.node)->lineno = lineno;
              }
#line 1468 "y.tab.c"
    break;

  case 22: /* whileStm: WHILE exp DO stmList ENDWH  */
#line 133 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->nodekind = StmtK; (yyval.node)->kind.stmt = WhileK;
                  (yyval.node)->child[0] = (yyvsp[-3].node); 
                  (yyval.node)->child[1] = (yyvsp[-1].node); 
                  (yyval.node)->lineno = lineno;
              }
#line 1480 "y.tab.c"
    break;

  case 23: /* readStm: READ LPAREN ID RPAREN  */
#line 143 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->nodekind = StmtK; (yyval.node)->kind.stmt = ReadK;
                  (yyval.node)->attr.name = (yyvsp[-1].name);
                  (yyval.node)->lineno = lineno;
              }
#line 1491 "y.tab.c"
    break;

  case 24: /* writeStm: WRITE LPAREN exp RPAREN  */
#line 152 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->nodekind = StmtK; (yyval.node)->kind.stmt = WriteK;
                  (yyval.node)->child[0] = (yyvsp[-1].node);
                  (yyval.node)->lineno = lineno;
              }
#line 1502 "y.tab.c"
    break;

  case 25: /* returnStm: RETURN  */
#line 161 "snl.y"
              {
                  (yyval.node) = new TreeNode();
                  (yyval.node)->nodekind = StmtK; (yyval.node)->kind.stmt = ReturnK;
                  (yyval.node)->lineno = lineno;
              }
#line 1512 "y.tab.c"
    break;

  case 26: /* exp: simple_exp  */
#line 169 "snl.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 1518 "y.tab.c"
    break;

  case 27: /* exp: simple_exp LT simple_exp  */
#line 171 "snl.y"
              { 
                  (yyval.node) = new TreeNode(); (yyval.node)->nodekind = ExpK; (yyval.node)->kind.exp = OpK;
                  (yyval.node)->attr.op = LT; (yyval.node)->child[0] = (yyvsp[-2].node); (yyval.node)->child[1] = (yyvsp[0].node);
                  (yyval.node)->lineno = lineno;
              }
#line 1528 "y.tab.c"
    break;

  case 28: /* exp: simple_exp EQ simple_exp  */
#line 177 "snl.y"
              { 
                  (yyval.node) = new TreeNode(); (yyval.node)->nodekind = ExpK; (yyval.node)->kind.exp = OpK;
                  (yyval.node)->attr.op = EQ; (yyval.node)->child[0] = (yyvsp[-2].node); (yyval.node)->child[1] = (yyvsp[0].node);
                  (yyval.node)->lineno = lineno;
              }
#line 1538 "y.tab.c"
    break;

  case 29: /* simple_exp: term  */
#line 184 "snl.y"
                   { (yyval.node) = (yyvsp[0].node); }
#line 1544 "y.tab.c"
    break;

  case 30: /* simple_exp: simple_exp PLUS term  */
#line 186 "snl.y"
              { 
                  (yyval.node) = new TreeNode(); (yyval.node)->nodekind = ExpK; (yyval.node)->kind.exp = OpK;
                  (yyval.node)->attr.op = PLUS; (yyval.node)->child[0] = (yyvsp[-2].node); (yyval.node)->child[1] = (yyvsp[0].node);
                  (yyval.node)->lineno = lineno;
              }
#line 1554 "y.tab.c"
    break;

  case 31: /* simple_exp: simple_exp MINUS term  */
#line 192 "snl.y"
              { 
                  (yyval.node) = new TreeNode(); (yyval.node)->nodekind = ExpK; (yyval.node)->kind.exp = OpK;
                  (yyval.node)->attr.op = MINUS; (yyval.node)->child[0] = (yyvsp[-2].node); (yyval.node)->child[1] = (yyvsp[0].node);
                  (yyval.node)->lineno = lineno;
              }
#line 1564 "y.tab.c"
    break;

  case 32: /* term: factor  */
#line 199 "snl.y"
                     { (yyval.node) = (yyvsp[0].node); }
#line 1570 "y.tab.c"
    break;

  case 33: /* term: term TIMES factor  */
#line 201 "snl.y"
              { 
                  (yyval.node) = new TreeNode(); (yyval.node)->nodekind = ExpK; (yyval.node)->kind.exp = OpK;
                  (yyval.node)->attr.op = TIMES; (yyval.node)->child[0] = (yyvsp[-2].node); (yyval.node)->child[1] = (yyvsp[0].node);
                  (yyval.node)->lineno = lineno;
              }
#line 1580 "y.tab.c"
    break;

  case 34: /* term: term OVER factor  */
#line 207 "snl.y"
              { 
                  (yyval.node) = new TreeNode(); (yyval.node)->nodekind = ExpK; (yyval.node)->kind.exp = OpK;
                  (yyval.node)->attr.op = OVER; (yyval.node)->child[0] = (yyvsp[-2].node); (yyval.node)->child[1] = (yyvsp[0].node);
                  (yyval.node)->lineno = lineno;
              }
#line 1590 "y.tab.c"
    break;

  case 35: /* factor: NUM  */
#line 215 "snl.y"
              { 
                  (yyval.node) = new TreeNode(); (yyval.node)->nodekind = ExpK; (yyval.node)->kind.exp = ConstK;
                  (yyval.node)->attr.val = (yyvsp[0].val); (yyval.node)->lineno = lineno;
              }
#line 1599 "y.tab.c"
    break;

  case 36: /* factor: ID  */
#line 220 "snl.y"
              { 
                  (yyval.node) = new TreeNode(); (yyval.node)->nodekind = ExpK; (yyval.node)->kind.exp = IdK;
                  (yyval.node)->attr.name = (yyvsp[0].name); (yyval.node)->lineno = lineno;
              }
#line 1608 "y.tab.c"
    break;

  case 37: /* factor: LPAREN exp RPAREN  */
#line 225 "snl.y"
              { (yyval.node) = (yyvsp[-1].node); }
#line 1614 "y.tab.c"
    break;


#line 1618 "y.tab.c"

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

#line 228 "snl.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", lineno, s);
}
