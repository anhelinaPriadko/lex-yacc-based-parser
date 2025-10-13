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
#line 2 "cpp_parser.y"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "ast.h"     /* доповнений заголовок AST */
ASTNode* ast_root = nullptr;
void yyerror(const char *s);
int yylex(void);

#line 82 "cpp_parser.tab.cpp"

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

#include "cpp_parser.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_T_INT = 6,                      /* T_INT  */
  YYSYMBOL_T_DOUBLE = 7,                   /* T_DOUBLE  */
  YYSYMBOL_T_BOOL = 8,                     /* T_BOOL  */
  YYSYMBOL_T_VOID = 9,                     /* T_VOID  */
  YYSYMBOL_T_CLASS = 10,                   /* T_CLASS  */
  YYSYMBOL_T_IF = 11,                      /* T_IF  */
  YYSYMBOL_T_ELSE = 12,                    /* T_ELSE  */
  YYSYMBOL_T_FOR = 13,                     /* T_FOR  */
  YYSYMBOL_T_WHILE = 14,                   /* T_WHILE  */
  YYSYMBOL_T_DO = 15,                      /* T_DO  */
  YYSYMBOL_T_RETURN = 16,                  /* T_RETURN  */
  YYSYMBOL_T_PUBLIC = 17,                  /* T_PUBLIC  */
  YYSYMBOL_T_PRIVATE = 18,                 /* T_PRIVATE  */
  YYSYMBOL_T_BREAK = 19,                   /* T_BREAK  */
  YYSYMBOL_T_CONTINUE = 20,                /* T_CONTINUE  */
  YYSYMBOL_T_SWITCH = 21,                  /* T_SWITCH  */
  YYSYMBOL_T_CASE = 22,                    /* T_CASE  */
  YYSYMBOL_T_DEFAULT = 23,                 /* T_DEFAULT  */
  YYSYMBOL_T_SEMI = 24,                    /* T_SEMI  */
  YYSYMBOL_T_COMMA = 25,                   /* T_COMMA  */
  YYSYMBOL_T_COLON = 26,                   /* T_COLON  */
  YYSYMBOL_T_LPAREN = 27,                  /* T_LPAREN  */
  YYSYMBOL_T_RPAREN = 28,                  /* T_RPAREN  */
  YYSYMBOL_T_LBRACE = 29,                  /* T_LBRACE  */
  YYSYMBOL_T_RBRACE = 30,                  /* T_RBRACE  */
  YYSYMBOL_T_ASSIGN = 31,                  /* T_ASSIGN  */
  YYSYMBOL_T_PLUS = 32,                    /* T_PLUS  */
  YYSYMBOL_T_MINUS = 33,                   /* T_MINUS  */
  YYSYMBOL_T_MUL = 34,                     /* T_MUL  */
  YYSYMBOL_T_DIV = 35,                     /* T_DIV  */
  YYSYMBOL_T_MOD = 36,                     /* T_MOD  */
  YYSYMBOL_T_INC = 37,                     /* T_INC  */
  YYSYMBOL_T_DEC = 38,                     /* T_DEC  */
  YYSYMBOL_T_EQ = 39,                      /* T_EQ  */
  YYSYMBOL_T_NEQ = 40,                     /* T_NEQ  */
  YYSYMBOL_T_LT = 41,                      /* T_LT  */
  YYSYMBOL_T_GT = 42,                      /* T_GT  */
  YYSYMBOL_T_LE = 43,                      /* T_LE  */
  YYSYMBOL_T_GE = 44,                      /* T_GE  */
  YYSYMBOL_T_AND = 45,                     /* T_AND  */
  YYSYMBOL_T_OR = 46,                      /* T_OR  */
  YYSYMBOL_T_NOT = 47,                     /* T_NOT  */
  YYSYMBOL_T_DOT = 48,                     /* T_DOT  */
  YYSYMBOL_T_PRINT = 49,                   /* T_PRINT  */
  YYSYMBOL_50_ = 50,                       /* '?'  */
  YYSYMBOL_51_ = 51,                       /* ':'  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_translation_unit = 53,          /* translation_unit  */
  YYSYMBOL_decl_list = 54,                 /* decl_list  */
  YYSYMBOL_declaration = 55,               /* declaration  */
  YYSYMBOL_declaration_specifiers = 56,    /* declaration_specifiers  */
  YYSYMBOL_init_declarator_list = 57,      /* init_declarator_list  */
  YYSYMBOL_init_declarator = 58,           /* init_declarator  */
  YYSYMBOL_function_defdeclarator = 59,    /* function_defdeclarator  */
  YYSYMBOL_parameter_list = 60,            /* parameter_list  */
  YYSYMBOL_parameter_list_nonempty = 61,   /* parameter_list_nonempty  */
  YYSYMBOL_member_list = 62,               /* member_list  */
  YYSYMBOL_compound_stmt = 63,             /* compound_stmt  */
  YYSYMBOL_stmt_list = 64,                 /* stmt_list  */
  YYSYMBOL_stmt = 65,                      /* stmt  */
  YYSYMBOL_expression_stmt = 66,           /* expression_stmt  */
  YYSYMBOL_selection_stmt = 67,            /* selection_stmt  */
  YYSYMBOL_iteration_stmt = 68,            /* iteration_stmt  */
  YYSYMBOL_jump_stmt = 69,                 /* jump_stmt  */
  YYSYMBOL_expr = 70,                      /* expr  */
  YYSYMBOL_assignment_expr = 71,           /* assignment_expr  */
  YYSYMBOL_conditional_expr = 72,          /* conditional_expr  */
  YYSYMBOL_logical_or_expr = 73,           /* logical_or_expr  */
  YYSYMBOL_logical_and_expr = 74,          /* logical_and_expr  */
  YYSYMBOL_equality_expr = 75,             /* equality_expr  */
  YYSYMBOL_relational_expr = 76,           /* relational_expr  */
  YYSYMBOL_additive_expr = 77,             /* additive_expr  */
  YYSYMBOL_multiplicative_expr = 78,       /* multiplicative_expr  */
  YYSYMBOL_unary_expr = 79,                /* unary_expr  */
  YYSYMBOL_postfix_expr = 80,              /* postfix_expr  */
  YYSYMBOL_primary_expr = 81,              /* primary_expr  */
  YYSYMBOL_argument_list = 82,             /* argument_list  */
  YYSYMBOL_argument_list_nonempty = 83     /* argument_list_nonempty  */
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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   257

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  163

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


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
       2,     2,     2,     2,     2,     2,     2,     2,    51,     2,
       2,     2,     2,    50,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    74,    74,    78,    79,    80,    81,    85,    87,    92,
      93,    94,    95,    99,   100,   104,   105,   109,   114,   115,
     119,   121,   126,   127,   128,   132,   136,   137,   141,   142,
     143,   144,   145,   146,   150,   151,   155,   156,   157,   161,
     162,   163,   168,   169,   170,   171,   174,   177,   178,   182,
     183,   188,   189,   193,   194,   198,   199,   200,   204,   205,
     206,   207,   208,   212,   213,   214,   218,   219,   220,   221,
     225,   226,   227,   228,   229,   230,   234,   235,   236,   237,
     238,   242,   243,   244,   245,   249,   250,   254,   255
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
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "ID",
  "STRING", "T_INT", "T_DOUBLE", "T_BOOL", "T_VOID", "T_CLASS", "T_IF",
  "T_ELSE", "T_FOR", "T_WHILE", "T_DO", "T_RETURN", "T_PUBLIC",
  "T_PRIVATE", "T_BREAK", "T_CONTINUE", "T_SWITCH", "T_CASE", "T_DEFAULT",
  "T_SEMI", "T_COMMA", "T_COLON", "T_LPAREN", "T_RPAREN", "T_LBRACE",
  "T_RBRACE", "T_ASSIGN", "T_PLUS", "T_MINUS", "T_MUL", "T_DIV", "T_MOD",
  "T_INC", "T_DEC", "T_EQ", "T_NEQ", "T_LT", "T_GT", "T_LE", "T_GE",
  "T_AND", "T_OR", "T_NOT", "T_DOT", "T_PRINT", "'?'", "':'", "$accept",
  "translation_unit", "decl_list", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "function_defdeclarator",
  "parameter_list", "parameter_list_nonempty", "member_list",
  "compound_stmt", "stmt_list", "stmt", "expression_stmt",
  "selection_stmt", "iteration_stmt", "jump_stmt", "expr",
  "assignment_expr", "conditional_expr", "logical_or_expr",
  "logical_and_expr", "equality_expr", "relational_expr", "additive_expr",
  "multiplicative_expr", "unary_expr", "postfix_expr", "primary_expr",
  "argument_list", "argument_list_nonempty", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-127)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -127,     2,    95,  -127,  -127,  -127,  -127,  -127,     1,  -127,
       3,  -127,    95,   -11,   -23,    -1,  -127,  -127,  -127,  -127,
      69,   210,  -127,    32,     5,    45,     6,    15,  -127,  -127,
    -127,   210,   210,   210,   210,   210,   210,  -127,  -127,  -127,
     -29,     8,    30,    48,    49,    10,    37,    -5,  -127,    42,
    -127,    59,  -127,    79,    69,    81,  -127,  -127,  -127,  -127,
    -127,   210,   210,   210,   210,   210,   210,   210,   210,   210,
     210,   210,   210,   210,   210,   210,   210,  -127,  -127,   107,
    -127,  -127,  -127,   109,  -127,     8,  -127,    63,    30,    48,
      48,    49,    49,    49,    49,    10,    10,  -127,  -127,  -127,
    -127,  -127,    87,    91,  -127,   127,  -127,   210,  -127,   210,
      90,    92,    93,   172,    47,    97,    98,    96,  -127,  -127,
    -127,    32,  -127,  -127,  -127,  -127,  -127,  -127,   100,  -127,
    -127,   210,   203,   210,   111,  -127,   102,  -127,  -127,   210,
    -127,   116,   203,   117,   101,  -127,   121,   172,   210,   172,
     210,    79,   138,   124,  -127,   125,  -127,   172,   172,   115,
    -127,  -127,  -127
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     2,     1,     9,    10,    11,    12,     0,     4,
       0,     5,     6,     0,    15,     0,    13,    23,    24,    22,
      18,     0,     7,     0,     0,     0,     0,    19,    82,    81,
      83,     0,     0,     0,     0,     0,     0,    16,    46,    47,
      49,    51,    53,    55,    58,    63,    66,    70,    76,    15,
      14,     0,    20,     0,     0,     0,    71,    72,    74,    75,
      73,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    85,    77,    78,     0,
       8,    26,    17,     0,    84,    52,    66,     0,    54,    56,
      57,    59,    60,    61,    62,    64,    65,    67,    68,    69,
      48,    87,     0,    86,    80,     0,    21,     0,    79,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    34,    25,
      33,     0,    29,    27,    28,    30,    31,    32,     0,    50,
      88,     0,     0,     0,     0,    44,     0,    42,    43,     0,
      35,     0,     0,     0,     0,    45,     0,     0,     0,     0,
       0,     0,    36,     0,    39,     0,    38,     0,     0,     0,
      37,    41,    40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -127,  -127,  -127,     7,    18,  -127,   132,   156,  -127,  -127,
     142,   -52,  -127,  -110,  -126,  -127,  -127,  -127,   -21,    88,
      55,  -127,   105,   104,    22,    29,    36,    -7,  -127,  -127,
    -127,  -127
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,   120,   121,    15,    16,    18,    26,    27,
      12,   122,   105,   123,   124,   125,   126,   127,   128,    38,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
     102,   103
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      37,    82,     3,   134,    20,    13,   142,    14,    21,     9,
      55,     4,     5,     6,     7,     8,   148,    61,    19,    17,
      10,    62,    76,    22,    23,    56,    57,    58,    59,    60,
      10,    17,    77,    78,    53,    51,    49,   152,    25,   154,
      54,    87,    10,    79,    72,    73,    74,   160,   161,    52,
      28,    29,    30,    63,    86,   101,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    97,    98,    99,    75,    64,
      65,   135,    83,    21,    31,     4,     5,     6,     7,    32,
      33,    70,    71,    80,    34,    35,    89,    90,   130,    66,
      67,    68,    69,   136,    36,    91,    92,    93,    94,   156,
      86,     4,     5,     6,     7,     8,    95,    96,    81,    84,
     141,   104,   143,   106,   107,   108,   109,   131,   146,   132,
     133,   137,   138,   139,   140,   144,   145,   153,   150,   155,
      28,    29,    30,     4,     5,     6,     7,     8,   110,   162,
     111,   112,   113,   114,   147,   149,   115,   116,   117,   151,
     157,   118,   158,   159,    31,    50,    81,   119,    11,    32,
      33,    24,   129,   100,    34,    35,    85,    88,     0,     0,
       0,     0,     0,     0,    36,    28,    29,    30,     4,     5,
       6,     7,     8,   110,     0,   111,   112,   113,   114,     0,
       0,   115,   116,   117,     0,     0,   118,     0,     0,    31,
       0,    81,     0,     0,    32,    33,    28,    29,    30,    34,
      35,     0,     0,    28,    29,    30,     0,     0,     0,    36,
       0,     0,     0,     0,     0,     0,     0,   118,     0,     0,
      31,     0,     0,     0,     0,    32,    33,    31,     0,     0,
      34,    35,    32,    33,     0,     0,     0,    34,    35,     0,
      36,     0,     0,     0,     0,     0,     0,    36
};

static const yytype_int16 yycheck[] =
{
      21,    53,     0,   113,    27,     4,   132,     4,    31,     2,
      31,     6,     7,     8,     9,    10,   142,    46,    29,    12,
       2,    50,    27,    24,    25,    32,    33,    34,    35,    36,
      12,    24,    37,    38,    28,    30,     4,   147,    20,   149,
      25,    62,    24,    48,    34,    35,    36,   157,   158,     4,
       3,     4,     5,    45,    61,    76,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    31,    39,
      40,    24,    54,    31,    27,     6,     7,     8,     9,    32,
      33,    32,    33,    24,    37,    38,    64,    65,   109,    41,
      42,    43,    44,   114,    47,    66,    67,    68,    69,   151,
     107,     6,     7,     8,     9,    10,    70,    71,    29,    28,
     131,     4,   133,     4,    51,    28,    25,    27,   139,    27,
      27,    24,    24,    27,    24,    14,    24,   148,    27,   150,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    24,
      13,    14,    15,    16,    28,    28,    19,    20,    21,    28,
      12,    24,    28,    28,    27,    23,    29,    30,     2,    32,
      33,    19,   107,    75,    37,    38,    61,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    47,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    -1,    13,    14,    15,    16,    -1,
      -1,    19,    20,    21,    -1,    -1,    24,    -1,    -1,    27,
      -1,    29,    -1,    -1,    32,    33,     3,     4,     5,    37,
      38,    -1,    -1,     3,     4,     5,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    24,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    32,    33,    27,    -1,    -1,
      37,    38,    32,    33,    -1,    -1,    -1,    37,    38,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    53,    54,     0,     6,     7,     8,     9,    10,    55,
      56,    59,    62,     4,     4,    57,    58,    55,    59,    29,
      27,    31,    24,    25,    62,    56,    60,    61,     3,     4,
       5,    27,    32,    33,    37,    38,    47,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,     4,
      58,    30,     4,    28,    25,    70,    79,    79,    79,    79,
      79,    46,    50,    45,    39,    40,    41,    42,    43,    44,
      32,    33,    34,    35,    36,    31,    27,    37,    38,    48,
      24,    29,    63,    56,    28,    74,    79,    70,    75,    76,
      76,    77,    77,    77,    77,    78,    78,    79,    79,    79,
      71,    70,    82,    83,     4,    64,     4,    51,    28,    25,
      11,    13,    14,    15,    16,    19,    20,    21,    24,    30,
      55,    56,    63,    65,    66,    67,    68,    69,    70,    72,
      70,    27,    27,    27,    65,    24,    70,    24,    24,    27,
      24,    70,    66,    70,    14,    24,    70,    28,    66,    28,
      27,    28,    65,    70,    65,    70,    63,    12,    28,    28,
      65,    65,    24
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    54,    54,    54,    55,    55,    56,
      56,    56,    56,    57,    57,    58,    58,    59,    60,    60,
      61,    61,    62,    62,    62,    63,    64,    64,    65,    65,
      65,    65,    65,    65,    66,    66,    67,    67,    67,    68,
      68,    68,    69,    69,    69,    69,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75,    75,    76,    76,
      76,    76,    76,    77,    77,    77,    78,    78,    78,    78,
      79,    79,    79,    79,    79,    79,    80,    80,    80,    80,
      80,    81,    81,    81,    81,    82,    82,    83,    83
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     2,     3,     6,     1,
       1,     1,     1,     1,     3,     1,     3,     6,     0,     1,
       2,     4,     0,     2,     2,     3,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     2,     5,     7,     5,     5,
       7,     7,     2,     2,     2,     3,     1,     1,     3,     1,
       5,     1,     3,     1,     3,     1,     3,     3,     1,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     3,
       1,     2,     2,     2,     2,     2,     1,     2,     2,     4,
       3,     1,     1,     1,     3,     0,     1,     1,     3
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
  case 2: /* translation_unit: decl_list  */
#line 74 "cpp_parser.y"
              { (yyval.node) = new BlockStmt((yyvsp[0].node_list)); ast_root = (yyval.node); }
#line 1286 "cpp_parser.tab.cpp"
    break;

  case 3: /* decl_list: %empty  */
#line 78 "cpp_parser.y"
                           { (yyval.node_list) = new std::vector<ASTNode*>(); }
#line 1292 "cpp_parser.tab.cpp"
    break;

  case 4: /* decl_list: decl_list declaration  */
#line 79 "cpp_parser.y"
                          { (yyvsp[-1].node_list)->push_back((yyvsp[0].node)); (yyval.node_list) = (yyvsp[-1].node_list); }
#line 1298 "cpp_parser.tab.cpp"
    break;

  case 5: /* decl_list: decl_list function_defdeclarator  */
#line 80 "cpp_parser.y"
                                     { (yyvsp[-1].node_list)->push_back((yyvsp[0].node)); (yyval.node_list) = (yyvsp[-1].node_list); }
#line 1304 "cpp_parser.tab.cpp"
    break;

  case 6: /* decl_list: decl_list member_list  */
#line 81 "cpp_parser.y"
                          { /* if member_list used at top-level */ (yyval.node_list) = (yyvsp[-1].node_list); }
#line 1310 "cpp_parser.tab.cpp"
    break;

  case 7: /* declaration: declaration_specifiers init_declarator_list T_SEMI  */
#line 86 "cpp_parser.y"
        { VarDeclList* vlist = new VarDeclList((yyvsp[-2].typeDesc), (yyvsp[-1].node_list)); (yyval.node) = vlist; }
#line 1316 "cpp_parser.tab.cpp"
    break;

  case 8: /* declaration: T_CLASS ID T_LBRACE member_list T_RBRACE T_SEMI  */
#line 88 "cpp_parser.y"
        { (yyval.node) = new ClassDecl(std::string((yyvsp[-4].id)), (yyvsp[-2].node_list)); free((yyvsp[-4].id)); }
#line 1322 "cpp_parser.tab.cpp"
    break;

  case 9: /* declaration_specifiers: T_INT  */
#line 92 "cpp_parser.y"
             { (yyval.typeDesc) = new TypeDescriptor("int"); }
#line 1328 "cpp_parser.tab.cpp"
    break;

  case 10: /* declaration_specifiers: T_DOUBLE  */
#line 93 "cpp_parser.y"
             { (yyval.typeDesc) = new TypeDescriptor("double"); }
#line 1334 "cpp_parser.tab.cpp"
    break;

  case 11: /* declaration_specifiers: T_BOOL  */
#line 94 "cpp_parser.y"
             { (yyval.typeDesc) = new TypeDescriptor("bool"); }
#line 1340 "cpp_parser.tab.cpp"
    break;

  case 12: /* declaration_specifiers: T_VOID  */
#line 95 "cpp_parser.y"
             { (yyval.typeDesc) = new TypeDescriptor("void"); }
#line 1346 "cpp_parser.tab.cpp"
    break;

  case 13: /* init_declarator_list: init_declarator  */
#line 99 "cpp_parser.y"
                                { (yyval.node_list) = new std::vector<ASTNode*>(); (yyval.node_list)->push_back((yyvsp[0].node)); }
#line 1352 "cpp_parser.tab.cpp"
    break;

  case 14: /* init_declarator_list: init_declarator_list T_COMMA init_declarator  */
#line 100 "cpp_parser.y"
                                                 { (yyvsp[-2].node_list)->push_back((yyvsp[0].node)); (yyval.node_list) = (yyvsp[-2].node_list); }
#line 1358 "cpp_parser.tab.cpp"
    break;

  case 15: /* init_declarator: ID  */
#line 104 "cpp_parser.y"
                              { (yyval.node) = new VarDecl(std::string((yyvsp[0].id)), nullptr); free((yyvsp[0].id)); }
#line 1364 "cpp_parser.tab.cpp"
    break;

  case 16: /* init_declarator: ID T_ASSIGN expr  */
#line 105 "cpp_parser.y"
                              { (yyval.node) = new VarDecl(std::string((yyvsp[-2].id)), (yyvsp[0].node)); free((yyvsp[-2].id)); }
#line 1370 "cpp_parser.tab.cpp"
    break;

  case 17: /* function_defdeclarator: declaration_specifiers ID T_LPAREN parameter_list T_RPAREN compound_stmt  */
#line 110 "cpp_parser.y"
        { (yyval.node) = new FunctionDecl((yyvsp[-5].typeDesc), std::string((yyvsp[-4].id)), (yyvsp[-2].node_list), dynamic_cast<BlockStmt*>((yyvsp[0].node))); free((yyvsp[-4].id)); }
#line 1376 "cpp_parser.tab.cpp"
    break;

  case 18: /* parameter_list: %empty  */
#line 114 "cpp_parser.y"
                            { (yyval.node_list) = new std::vector<ASTNode*>(); }
#line 1382 "cpp_parser.tab.cpp"
    break;

  case 19: /* parameter_list: parameter_list_nonempty  */
#line 115 "cpp_parser.y"
                            { (yyval.node_list) = (yyvsp[0].node_list); }
#line 1388 "cpp_parser.tab.cpp"
    break;

  case 20: /* parameter_list_nonempty: declaration_specifiers ID  */
#line 120 "cpp_parser.y"
        { (yyval.node_list) = new std::vector<ASTNode*>(); (yyval.node_list)->push_back(new ParamDecl((yyvsp[-1].typeDesc), std::string((yyvsp[0].id)))); free((yyvsp[0].id)); }
#line 1394 "cpp_parser.tab.cpp"
    break;

  case 21: /* parameter_list_nonempty: parameter_list_nonempty T_COMMA declaration_specifiers ID  */
#line 122 "cpp_parser.y"
        { (yyvsp[-3].node_list)->push_back(new ParamDecl((yyvsp[-1].typeDesc), std::string((yyvsp[0].id)))); free((yyvsp[0].id)); (yyval.node_list) = (yyvsp[-3].node_list); }
#line 1400 "cpp_parser.tab.cpp"
    break;

  case 22: /* member_list: %empty  */
#line 126 "cpp_parser.y"
                { (yyval.node_list) = new std::vector<ASTNode*>(); }
#line 1406 "cpp_parser.tab.cpp"
    break;

  case 23: /* member_list: member_list declaration  */
#line 127 "cpp_parser.y"
                            { (yyvsp[-1].node_list)->push_back((yyvsp[0].node)); (yyval.node_list) = (yyvsp[-1].node_list); }
#line 1412 "cpp_parser.tab.cpp"
    break;

  case 24: /* member_list: member_list function_defdeclarator  */
#line 128 "cpp_parser.y"
                                       { (yyvsp[-1].node_list)->push_back((yyvsp[0].node)); (yyval.node_list) = (yyvsp[-1].node_list); }
#line 1418 "cpp_parser.tab.cpp"
    break;

  case 25: /* compound_stmt: T_LBRACE stmt_list T_RBRACE  */
#line 132 "cpp_parser.y"
                                { (yyval.node) = new BlockStmt((yyvsp[-1].node_list)); }
#line 1424 "cpp_parser.tab.cpp"
    break;

  case 26: /* stmt_list: %empty  */
#line 136 "cpp_parser.y"
                { (yyval.node_list) = new std::vector<ASTNode*>(); }
#line 1430 "cpp_parser.tab.cpp"
    break;

  case 27: /* stmt_list: stmt_list stmt  */
#line 137 "cpp_parser.y"
                   { (yyvsp[-1].node_list)->push_back((yyvsp[0].node)); (yyval.node_list) = (yyvsp[-1].node_list); }
#line 1436 "cpp_parser.tab.cpp"
    break;

  case 28: /* stmt: expression_stmt  */
#line 141 "cpp_parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1442 "cpp_parser.tab.cpp"
    break;

  case 29: /* stmt: compound_stmt  */
#line 142 "cpp_parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1448 "cpp_parser.tab.cpp"
    break;

  case 30: /* stmt: selection_stmt  */
#line 143 "cpp_parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1454 "cpp_parser.tab.cpp"
    break;

  case 31: /* stmt: iteration_stmt  */
#line 144 "cpp_parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1460 "cpp_parser.tab.cpp"
    break;

  case 32: /* stmt: jump_stmt  */
#line 145 "cpp_parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1466 "cpp_parser.tab.cpp"
    break;

  case 33: /* stmt: declaration  */
#line 146 "cpp_parser.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 1472 "cpp_parser.tab.cpp"
    break;

  case 34: /* expression_stmt: T_SEMI  */
#line 150 "cpp_parser.y"
                      { (yyval.node) = new ExprStmt(nullptr); }
#line 1478 "cpp_parser.tab.cpp"
    break;

  case 35: /* expression_stmt: expr T_SEMI  */
#line 151 "cpp_parser.y"
                      { (yyval.node) = new ExprStmt((yyvsp[-1].node)); }
#line 1484 "cpp_parser.tab.cpp"
    break;

  case 36: /* selection_stmt: T_IF T_LPAREN expr T_RPAREN stmt  */
#line 155 "cpp_parser.y"
                                                  { (yyval.node) = new IfStmt((yyvsp[-2].node), (yyvsp[0].node), nullptr); }
#line 1490 "cpp_parser.tab.cpp"
    break;

  case 37: /* selection_stmt: T_IF T_LPAREN expr T_RPAREN stmt T_ELSE stmt  */
#line 156 "cpp_parser.y"
                                                  { (yyval.node) = new IfStmt((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1496 "cpp_parser.tab.cpp"
    break;

  case 38: /* selection_stmt: T_SWITCH T_LPAREN expr T_RPAREN compound_stmt  */
#line 157 "cpp_parser.y"
                                                  { (yyval.node) = new SwitchStmt((yyvsp[-2].node), dynamic_cast<BlockStmt*>((yyvsp[0].node))); }
#line 1502 "cpp_parser.tab.cpp"
    break;

  case 39: /* iteration_stmt: T_WHILE T_LPAREN expr T_RPAREN stmt  */
#line 161 "cpp_parser.y"
                                        { (yyval.node) = new WhileStmt((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1508 "cpp_parser.tab.cpp"
    break;

  case 40: /* iteration_stmt: T_DO stmt T_WHILE T_LPAREN expr T_RPAREN T_SEMI  */
#line 162 "cpp_parser.y"
                                                    { (yyval.node) = new DoWhileStmt((yyvsp[-5].node), (yyvsp[-2].node)); }
#line 1514 "cpp_parser.tab.cpp"
    break;

  case 41: /* iteration_stmt: T_FOR T_LPAREN expression_stmt expression_stmt expr T_RPAREN stmt  */
#line 164 "cpp_parser.y"
      { (yyval.node) = new ForStmt((yyvsp[-4].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1520 "cpp_parser.tab.cpp"
    break;

  case 42: /* jump_stmt: T_BREAK T_SEMI  */
#line 168 "cpp_parser.y"
                     { (yyval.node) = new BreakStmt(); }
#line 1526 "cpp_parser.tab.cpp"
    break;

  case 43: /* jump_stmt: T_CONTINUE T_SEMI  */
#line 169 "cpp_parser.y"
                      { (yyval.node) = new ContinueStmt(); }
#line 1532 "cpp_parser.tab.cpp"
    break;

  case 44: /* jump_stmt: T_RETURN T_SEMI  */
#line 170 "cpp_parser.y"
                     { (yyval.node) = new ReturnStmt(nullptr); }
#line 1538 "cpp_parser.tab.cpp"
    break;

  case 45: /* jump_stmt: T_RETURN expr T_SEMI  */
#line 171 "cpp_parser.y"
                         { (yyval.node) = new ReturnStmt((yyvsp[-1].node)); }
#line 1544 "cpp_parser.tab.cpp"
    break;

  case 46: /* expr: assignment_expr  */
#line 174 "cpp_parser.y"
                      { (yyval.node) = (yyvsp[0].node); }
#line 1550 "cpp_parser.tab.cpp"
    break;

  case 47: /* assignment_expr: conditional_expr  */
#line 177 "cpp_parser.y"
                                      { (yyval.node) = (yyvsp[0].node); }
#line 1556 "cpp_parser.tab.cpp"
    break;

  case 48: /* assignment_expr: unary_expr T_ASSIGN assignment_expr  */
#line 178 "cpp_parser.y"
                                        { (yyval.node) = new BinaryExpr("=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1562 "cpp_parser.tab.cpp"
    break;

  case 50: /* conditional_expr: logical_or_expr '?' expr ':' conditional_expr  */
#line 184 "cpp_parser.y"
      { (yyval.node) = new ConditionalExpr((yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1568 "cpp_parser.tab.cpp"
    break;

  case 52: /* logical_or_expr: logical_or_expr T_OR logical_and_expr  */
#line 189 "cpp_parser.y"
                                          { (yyval.node) = new BinaryExpr("||", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1574 "cpp_parser.tab.cpp"
    break;

  case 54: /* logical_and_expr: logical_and_expr T_AND equality_expr  */
#line 194 "cpp_parser.y"
                                         { (yyval.node) = new BinaryExpr("&&", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1580 "cpp_parser.tab.cpp"
    break;

  case 56: /* equality_expr: equality_expr T_EQ relational_expr  */
#line 199 "cpp_parser.y"
                                       { (yyval.node) = new BinaryExpr("==", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1586 "cpp_parser.tab.cpp"
    break;

  case 57: /* equality_expr: equality_expr T_NEQ relational_expr  */
#line 200 "cpp_parser.y"
                                        { (yyval.node) = new BinaryExpr("!=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1592 "cpp_parser.tab.cpp"
    break;

  case 59: /* relational_expr: relational_expr T_LT additive_expr  */
#line 205 "cpp_parser.y"
                                       { (yyval.node) = new BinaryExpr("<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1598 "cpp_parser.tab.cpp"
    break;

  case 60: /* relational_expr: relational_expr T_GT additive_expr  */
#line 206 "cpp_parser.y"
                                       { (yyval.node) = new BinaryExpr(">", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1604 "cpp_parser.tab.cpp"
    break;

  case 61: /* relational_expr: relational_expr T_LE additive_expr  */
#line 207 "cpp_parser.y"
                                       { (yyval.node) = new BinaryExpr("<=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1610 "cpp_parser.tab.cpp"
    break;

  case 62: /* relational_expr: relational_expr T_GE additive_expr  */
#line 208 "cpp_parser.y"
                                       { (yyval.node) = new BinaryExpr(">=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1616 "cpp_parser.tab.cpp"
    break;

  case 64: /* additive_expr: additive_expr T_PLUS multiplicative_expr  */
#line 213 "cpp_parser.y"
                                             { (yyval.node) = new BinaryExpr("+", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1622 "cpp_parser.tab.cpp"
    break;

  case 65: /* additive_expr: additive_expr T_MINUS multiplicative_expr  */
#line 214 "cpp_parser.y"
                                              { (yyval.node) = new BinaryExpr("-", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1628 "cpp_parser.tab.cpp"
    break;

  case 67: /* multiplicative_expr: multiplicative_expr T_MUL unary_expr  */
#line 219 "cpp_parser.y"
                                         { (yyval.node) = new BinaryExpr("*", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1634 "cpp_parser.tab.cpp"
    break;

  case 68: /* multiplicative_expr: multiplicative_expr T_DIV unary_expr  */
#line 220 "cpp_parser.y"
                                         { (yyval.node) = new BinaryExpr("/", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1640 "cpp_parser.tab.cpp"
    break;

  case 69: /* multiplicative_expr: multiplicative_expr T_MOD unary_expr  */
#line 221 "cpp_parser.y"
                                         { (yyval.node) = new BinaryExpr("%", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1646 "cpp_parser.tab.cpp"
    break;

  case 71: /* unary_expr: T_PLUS unary_expr  */
#line 226 "cpp_parser.y"
                       { (yyval.node) = new UnaryExpr("+", (yyvsp[0].node)); }
#line 1652 "cpp_parser.tab.cpp"
    break;

  case 72: /* unary_expr: T_MINUS unary_expr  */
#line 227 "cpp_parser.y"
                       { (yyval.node) = new UnaryExpr("-", (yyvsp[0].node)); }
#line 1658 "cpp_parser.tab.cpp"
    break;

  case 73: /* unary_expr: T_NOT unary_expr  */
#line 228 "cpp_parser.y"
                       { (yyval.node) = new UnaryExpr("!", (yyvsp[0].node)); }
#line 1664 "cpp_parser.tab.cpp"
    break;

  case 74: /* unary_expr: T_INC unary_expr  */
#line 229 "cpp_parser.y"
                       { (yyval.node) = new UnaryExpr("++", (yyvsp[0].node)); }
#line 1670 "cpp_parser.tab.cpp"
    break;

  case 75: /* unary_expr: T_DEC unary_expr  */
#line 230 "cpp_parser.y"
                       { (yyval.node) = new UnaryExpr("--", (yyvsp[0].node)); }
#line 1676 "cpp_parser.tab.cpp"
    break;

  case 77: /* postfix_expr: postfix_expr T_INC  */
#line 235 "cpp_parser.y"
                       { (yyval.node) = new PostfixExpr((yyvsp[-1].node), "++"); }
#line 1682 "cpp_parser.tab.cpp"
    break;

  case 78: /* postfix_expr: postfix_expr T_DEC  */
#line 236 "cpp_parser.y"
                       { (yyval.node) = new PostfixExpr((yyvsp[-1].node), "--"); }
#line 1688 "cpp_parser.tab.cpp"
    break;

  case 79: /* postfix_expr: postfix_expr T_LPAREN argument_list T_RPAREN  */
#line 237 "cpp_parser.y"
                                                 { (yyval.node) = new CallExpr((yyvsp[-3].node), (yyvsp[-1].node_list)); }
#line 1694 "cpp_parser.tab.cpp"
    break;

  case 80: /* postfix_expr: postfix_expr T_DOT ID  */
#line 238 "cpp_parser.y"
                          { (yyval.node) = new MemberExpr((yyvsp[-2].node), std::string((yyvsp[0].id))); free((yyvsp[0].id)); }
#line 1700 "cpp_parser.tab.cpp"
    break;

  case 81: /* primary_expr: ID  */
#line 242 "cpp_parser.y"
              { (yyval.node) = new VarExpr(std::string((yyvsp[0].id))); free((yyvsp[0].id)); }
#line 1706 "cpp_parser.tab.cpp"
    break;

  case 82: /* primary_expr: NUMBER  */
#line 243 "cpp_parser.y"
              { (yyval.node) = new NumberExpr((yyvsp[0].num)); }
#line 1712 "cpp_parser.tab.cpp"
    break;

  case 83: /* primary_expr: STRING  */
#line 244 "cpp_parser.y"
              { (yyval.node) = new StringExpr(std::string((yyvsp[0].str))); free((yyvsp[0].str)); }
#line 1718 "cpp_parser.tab.cpp"
    break;

  case 84: /* primary_expr: T_LPAREN expr T_RPAREN  */
#line 245 "cpp_parser.y"
                           { (yyval.node) = (yyvsp[-1].node); }
#line 1724 "cpp_parser.tab.cpp"
    break;

  case 85: /* argument_list: %empty  */
#line 249 "cpp_parser.y"
                { (yyval.node_list) = new std::vector<ASTNode*>(); }
#line 1730 "cpp_parser.tab.cpp"
    break;

  case 86: /* argument_list: argument_list_nonempty  */
#line 250 "cpp_parser.y"
                           { (yyval.node_list) = (yyvsp[0].node_list); }
#line 1736 "cpp_parser.tab.cpp"
    break;

  case 87: /* argument_list_nonempty: expr  */
#line 254 "cpp_parser.y"
         { (yyval.node_list) = new std::vector<ASTNode*>(); (yyval.node_list)->push_back((yyvsp[0].node)); }
#line 1742 "cpp_parser.tab.cpp"
    break;

  case 88: /* argument_list_nonempty: argument_list_nonempty T_COMMA expr  */
#line 255 "cpp_parser.y"
                                        { (yyvsp[-2].node_list)->push_back((yyvsp[0].node)); (yyval.node_list) = (yyvsp[-2].node_list); }
#line 1748 "cpp_parser.tab.cpp"
    break;


#line 1752 "cpp_parser.tab.cpp"

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

#line 258 "cpp_parser.y"


/* error and helper */
void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
}
