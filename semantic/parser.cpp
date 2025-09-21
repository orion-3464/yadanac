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
#define YYPURE 2

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* "%code top" blocks.  */
#line 1 "parser.y"

    #include <stdio.h>
    #include <stdlib.h>

#line 73 "parser.cpp"




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

#include "parser.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_and = 3,                      /* "and"  */
  YYSYMBOL_T_as = 4,                       /* "as"  */
  YYSYMBOL_T_begin = 5,                    /* "begin"  */
  YYSYMBOL_T_break = 6,                    /* "break"  */
  YYSYMBOL_T_byte = 7,                     /* "byte"  */
  YYSYMBOL_T_cont = 8,                     /* "continue"  */
  YYSYMBOL_T_decl = 9,                     /* "decl"  */
  YYSYMBOL_T_def = 10,                     /* "def"  */
  YYSYMBOL_T_elif = 11,                    /* "elif"  */
  YYSYMBOL_T_else = 12,                    /* "else"  */
  YYSYMBOL_T_end = 13,                     /* "end"  */
  YYSYMBOL_T_exit = 14,                    /* "exit"  */
  YYSYMBOL_T_false = 15,                   /* "false"  */
  YYSYMBOL_T_if = 16,                      /* "if"  */
  YYSYMBOL_T_is = 17,                      /* "is"  */
  YYSYMBOL_T_int = 18,                     /* "int"  */
  YYSYMBOL_T_loop = 19,                    /* "loop"  */
  YYSYMBOL_T_not = 20,                     /* "not"  */
  YYSYMBOL_T_or = 21,                      /* "or"  */
  YYSYMBOL_T_ref = 22,                     /* "ref"  */
  YYSYMBOL_T_ret = 23,                     /* "return"  */
  YYSYMBOL_T_skip = 24,                    /* "skip"  */
  YYSYMBOL_T_true = 25,                    /* "true"  */
  YYSYMBOL_T_var = 26,                     /* "var"  */
  YYSYMBOL_T_asgn = 27,                    /* ":="  */
  YYSYMBOL_T_col = 28,                     /* ":"  */
  YYSYMBOL_T_geq = 29,                     /* ">="  */
  YYSYMBOL_T_leq = 30,                     /* "<="  */
  YYSYMBOL_T_neq = 31,                     /* "<>"  */
  YYSYMBOL_T_id = 32,                      /* T_id  */
  YYSYMBOL_T_const = 33,                   /* T_const  */
  YYSYMBOL_T_str = 34,                     /* T_str  */
  YYSYMBOL_T_char = 35,                    /* T_char  */
  YYSYMBOL_T_auto_end = 36,                /* T_auto_end  */
  YYSYMBOL_UNOTNOT = 37,                   /* UNOTNOT  */
  YYSYMBOL_38_ = 38,                       /* '='  */
  YYSYMBOL_39_ = 39,                       /* '>'  */
  YYSYMBOL_40_ = 40,                       /* '<'  */
  YYSYMBOL_41_ = 41,                       /* '+'  */
  YYSYMBOL_42_ = 42,                       /* '-'  */
  YYSYMBOL_43_ = 43,                       /* '|'  */
  YYSYMBOL_44_ = 44,                       /* '*'  */
  YYSYMBOL_45_ = 45,                       /* '/'  */
  YYSYMBOL_46_ = 46,                       /* '%'  */
  YYSYMBOL_47_ = 47,                       /* '&'  */
  YYSYMBOL_UPLUS = 48,                     /* UPLUS  */
  YYSYMBOL_UMINUS = 49,                    /* UMINUS  */
  YYSYMBOL_UNOT = 50,                      /* UNOT  */
  YYSYMBOL_51_ = 51,                       /* '!'  */
  YYSYMBOL_52_ = 52,                       /* ','  */
  YYSYMBOL_53_ = 53,                       /* '['  */
  YYSYMBOL_54_ = 54,                       /* ']'  */
  YYSYMBOL_55_ = 55,                       /* '('  */
  YYSYMBOL_56_ = 56,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 57,                  /* $accept  */
  YYSYMBOL_program = 58,                   /* program  */
  YYSYMBOL_func_def = 59,                  /* func_def  */
  YYSYMBOL_local_def_list = 60,            /* local_def_list  */
  YYSYMBOL_header = 61,                    /* header  */
  YYSYMBOL_is_data_type = 62,              /* is_data_type  */
  YYSYMBOL_col_fpar_def = 63,              /* col_fpar_def  */
  YYSYMBOL_fpar_def_list = 64,             /* fpar_def_list  */
  YYSYMBOL_fpar_def = 65,                  /* fpar_def  */
  YYSYMBOL_id_list = 66,                   /* id_list  */
  YYSYMBOL_data_type = 67,                 /* data_type  */
  YYSYMBOL_fpar_type = 68,                 /* fpar_type  */
  YYSYMBOL_bracket_int_const_list = 69,    /* bracket_int_const_list  */
  YYSYMBOL_local_def = 70,                 /* local_def  */
  YYSYMBOL_type = 71,                      /* type  */
  YYSYMBOL_func_decl = 72,                 /* func_decl  */
  YYSYMBOL_var_def = 73,                   /* var_def  */
  YYSYMBOL_block = 74,                     /* block  */
  YYSYMBOL_stmt_list = 75,                 /* stmt_list  */
  YYSYMBOL_stmt = 76,                      /* stmt  */
  YYSYMBOL_elif_cond_block_list = 77,      /* elif_cond_block_list  */
  YYSYMBOL_else_col_block = 78,            /* else_col_block  */
  YYSYMBOL_one_id = 79,                    /* one_id  */
  YYSYMBOL_col_id = 80,                    /* col_id  */
  YYSYMBOL_l_value = 81,                   /* l_value  */
  YYSYMBOL_expr = 82,                      /* expr  */
  YYSYMBOL_proc_call = 83,                 /* proc_call  */
  YYSYMBOL_one_col_expr = 84,              /* one_col_expr  */
  YYSYMBOL_expr_list = 85,                 /* expr_list  */
  YYSYMBOL_func_call = 86,                 /* func_call  */
  YYSYMBOL_one_expr = 87,                  /* one_expr  */
  YYSYMBOL_cond = 88                       /* cond  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;



/* Unqualified %code blocks.  */
#line 11 "parser.y"

    #include "lexer.hpp"

#line 203 "parser.cpp"

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   288

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  57
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  158

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


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
       2,     2,     2,    51,     2,     2,     2,    46,    47,     2,
      55,    56,    44,    41,    52,    42,     2,    45,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      40,    38,    39,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    53,     2,    54,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    43,     2,     2,     2,     2,     2,
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
      35,    36,    37,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   117,   117,   120,   123,   124,   127,   130,   131,   134,
     135,   138,   139,   142,   145,   146,   149,   150,   153,   154,
     155,   158,   159,   162,   163,   164,   167,   170,   173,   176,
     177,   180,   181,   184,   185,   186,   187,   188,   189,   190,
     191,   192,   195,   196,   199,   200,   203,   204,   207,   208,
     211,   212,   213,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     235,   238,   239,   242,   243,   246,   249,   250,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263
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
  "\"end of file\"", "error", "\"invalid token\"", "\"and\"", "\"as\"",
  "\"begin\"", "\"break\"", "\"byte\"", "\"continue\"", "\"decl\"",
  "\"def\"", "\"elif\"", "\"else\"", "\"end\"", "\"exit\"", "\"false\"",
  "\"if\"", "\"is\"", "\"int\"", "\"loop\"", "\"not\"", "\"or\"",
  "\"ref\"", "\"return\"", "\"skip\"", "\"true\"", "\"var\"", "\":=\"",
  "\":\"", "\">=\"", "\"<=\"", "\"<>\"", "T_id", "T_const", "T_str",
  "T_char", "T_auto_end", "UNOTNOT", "'='", "'>'", "'<'", "'+'", "'-'",
  "'|'", "'*'", "'/'", "'%'", "'&'", "UPLUS", "UMINUS", "UNOT", "'!'",
  "','", "'['", "']'", "'('", "')'", "$accept", "program", "func_def",
  "local_def_list", "header", "is_data_type", "col_fpar_def",
  "fpar_def_list", "fpar_def", "id_list", "data_type", "fpar_type",
  "bracket_int_const_list", "local_def", "type", "func_decl", "var_def",
  "block", "stmt_list", "stmt", "elif_cond_block_list", "else_col_block",
  "one_id", "col_id", "l_value", "expr", "proc_call", "one_col_expr",
  "expr_list", "func_call", "one_expr", "cond", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-86)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-51)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,    -5,    23,   -86,    34,   -86,   -86,     4,    27,   144,
     -86,   -86,   -86,    24,   -86,   197,    29,    29,    -5,   -86,
      55,    30,    33,   -86,    36,    -8,   -86,   -86,   -86,   -86,
     -86,   -86,   -86,    -1,   -86,   -86,   -86,   -86,    41,   -86,
     -86,   -86,   -86,    55,   -86,    21,   -86,   -86,    66,    66,
      66,    55,    32,   213,   -86,    43,   -86,    49,    66,   -86,
      66,   -86,   112,    66,    66,    12,    40,   178,   -86,   -86,
      66,    66,   -86,   -86,   -86,   194,     7,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      55,    55,   166,   166,   241,    42,   241,   -86,   -86,   241,
     227,    60,   -86,    24,   -86,   241,    37,   220,   -86,   -86,
     241,   241,   241,   241,   241,   241,    67,    67,    67,   -86,
     -86,   -86,   -86,   -86,    83,   -86,   -86,     4,    52,   -86,
       4,    50,   -86,   -86,   -86,    52,   -86,    18,   -86,   -86,
      66,   -86,    61,    56,    55,    77,   -86,   241,   -86,    62,
      51,   166,    56,    65,   166,   -86,   -86,   -86
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     7,     4,     1,     0,     9,     0,
      17,    16,     8,     0,     6,     0,    48,    48,     0,    36,
       0,    46,     0,    33,     0,    71,    51,    23,     5,    24,
      25,     3,    31,     0,    35,    14,    11,    31,     0,    40,
      41,    27,    66,     0,    65,    50,    53,    54,     0,     0,
       0,     0,    55,    78,    57,     0,    47,     0,     0,    14,
       0,    70,     0,     0,     0,     0,    10,     0,    49,    80,
      76,     0,    58,    59,    67,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    37,     0,    73,    30,    32,    34,
       0,     0,    15,     0,    29,    73,     0,     0,    56,    79,
      88,    87,    84,    83,    86,    85,    60,    61,    69,    62,
      63,    64,    68,    81,    82,    42,    39,     0,    72,    52,
       0,    21,    13,    18,    12,    77,    75,    44,    21,    28,
       0,    19,     0,    26,     0,     0,    38,    74,    21,     0,
       0,     0,    20,     0,     0,    45,    22,    43
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -86,   -86,   107,   -86,   104,   -86,   -86,   -86,    20,    68,
     -80,   -86,   -24,   -86,     2,   -86,   -86,   -85,    88,    -2,
     -86,   -86,   -86,   113,    -9,   -46,   -86,   -86,    28,   -86,
     -86,   -42
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     2,     3,     9,     5,     8,    14,    66,    36,    65,
      12,   132,   143,    28,   133,    29,    30,    31,    62,    32,
     137,   146,    57,    39,    52,    53,    34,    61,   128,    54,
     106,    55
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      33,    69,    72,    73,    74,    75,    33,   125,   126,    76,
      90,    10,    94,    37,    96,     1,   101,    99,   100,   -50,
      60,   131,    11,     6,   105,   107,    63,     4,    91,   144,
     145,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   102,   -50,    90,   138,   123,   124,
     141,     7,    64,    33,    90,    13,    35,    38,    33,   127,
      98,    58,    56,   109,    91,    98,   155,    10,    59,   157,
      42,    92,    91,    68,   102,    43,    70,    93,    11,   154,
      44,    42,   130,    33,    33,    64,    90,    45,    46,    26,
      47,    44,   103,   136,   147,   153,    48,    49,    45,    46,
      26,    47,   150,   142,   140,   151,    50,    48,    49,   149,
      51,    86,    87,    88,    89,   148,    27,    50,    16,   156,
      17,    71,    41,   134,   152,    67,    19,    95,    20,   139,
      40,    21,     0,   135,     0,    22,    23,     0,     0,     0,
       0,     0,    33,     0,    25,    33,    26,     0,    97,    15,
      16,     0,    17,    18,     1,     0,     0,     0,    19,     0,
      20,     0,     0,    21,     0,     0,     0,    22,    23,     0,
      24,    15,    16,     0,    17,     0,    25,     0,    26,     0,
      19,     0,    20,     0,    16,    21,    17,     0,     0,    22,
      23,   104,    19,     0,    20,     0,     0,    21,    25,     0,
      26,    22,    23,    16,     0,    17,     0,     0,     0,     0,
      25,    19,    26,    20,     0,     0,    21,     0,     0,     0,
      22,    23,     0,    77,    78,    79,     0,     0,     0,    25,
       0,    26,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    77,    78,    79,     0,     0,     0,     0,     0,
     108,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      89,    83,    84,    85,    86,    87,    88,    89,    83,    84,
      85,    86,    87,    88,    89,     0,   108,     0,     0,     0,
       0,   129,    83,    84,    85,    86,    87,    88,    89
};

static const yytype_int16 yycheck[] =
{
       9,    43,    48,    49,    50,    51,    15,    92,    93,    51,
       3,     7,    58,    15,    60,    10,     4,    63,    64,    27,
      28,   101,    18,     0,    70,    71,    27,    32,    21,    11,
      12,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    32,    53,     3,   127,    90,    91,
     130,    17,    53,    62,     3,    28,    32,    28,    67,    17,
      62,    28,    32,    56,    21,    67,   151,     7,    32,   154,
      15,    28,    21,    32,    32,    20,    55,    28,    18,    28,
      25,    15,    22,    92,    93,    53,     3,    32,    33,    34,
      35,    25,    52,    56,   140,    33,    41,    42,    32,    33,
      34,    35,   144,    53,    52,    28,    51,    41,    42,    53,
      55,    44,    45,    46,    47,    54,     9,    51,     6,    54,
       8,    55,    18,   103,   148,    37,    14,    59,    16,   127,
      17,    19,    -1,   105,    -1,    23,    24,    -1,    -1,    -1,
      -1,    -1,   151,    -1,    32,   154,    34,    -1,    36,     5,
       6,    -1,     8,     9,    10,    -1,    -1,    -1,    14,    -1,
      16,    -1,    -1,    19,    -1,    -1,    -1,    23,    24,    -1,
      26,     5,     6,    -1,     8,    -1,    32,    -1,    34,    -1,
      14,    -1,    16,    -1,     6,    19,     8,    -1,    -1,    23,
      24,    13,    14,    -1,    16,    -1,    -1,    19,    32,    -1,
      34,    23,    24,     6,    -1,     8,    -1,    -1,    -1,    -1,
      32,    14,    34,    16,    -1,    -1,    19,    -1,    -1,    -1,
      23,    24,    -1,    29,    30,    31,    -1,    -1,    -1,    32,
      -1,    34,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    29,    30,    31,    -1,    -1,    -1,    -1,    -1,
      56,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    41,    42,    43,    44,    45,    46,    47,    41,    42,
      43,    44,    45,    46,    47,    -1,    56,    -1,    -1,    -1,
      -1,    54,    41,    42,    43,    44,    45,    46,    47
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    10,    58,    59,    32,    61,     0,    17,    62,    60,
       7,    18,    67,    28,    63,     5,     6,     8,     9,    14,
      16,    19,    23,    24,    26,    32,    34,    59,    70,    72,
      73,    74,    76,    81,    83,    32,    65,    76,    28,    80,
      80,    61,    15,    20,    25,    32,    33,    35,    41,    42,
      51,    55,    81,    82,    86,    88,    32,    79,    28,    32,
      28,    84,    75,    27,    53,    66,    64,    75,    32,    88,
      55,    55,    82,    82,    82,    82,    88,    29,    30,    31,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
       3,    21,    28,    28,    82,    66,    82,    36,    76,    82,
      82,     4,    32,    52,    13,    82,    87,    82,    56,    56,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    88,    88,    74,    74,    17,    85,    54,
      22,    67,    68,    71,    65,    85,    56,    77,    67,    71,
      52,    67,    53,    69,    11,    12,    78,    82,    54,    53,
      88,    28,    69,    33,    28,    74,    54,    74
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    57,    58,    59,    60,    60,    61,    62,    62,    63,
      63,    64,    64,    65,    66,    66,    67,    67,    68,    68,
      68,    69,    69,    70,    70,    70,    71,    72,    73,    74,
      74,    75,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    77,    77,    78,    78,    79,    79,    80,    80,
      81,    81,    81,    82,    82,    82,    82,    82,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    82,
      83,    84,    84,    85,    85,    86,    87,    87,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     4,     0,     2,     3,     0,     2,     0,
       3,     0,     3,     4,     0,     2,     1,     1,     1,     2,
       4,     0,     4,     1,     1,     1,     2,     2,     5,     4,
       3,     0,     2,     1,     3,     1,     1,     3,     6,     4,
       2,     2,     0,     5,     0,     3,     0,     1,     0,     2,
       1,     1,     4,     1,     1,     1,     3,     1,     2,     2,
       3,     3,     3,     3,     3,     1,     1,     2,     3,     3,
       2,     0,     3,     0,     3,     4,     0,     2,     1,     3,
       2,     3,     3,     3,     3,     3,     3,     3,     3
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
        yyerror (&yylloc, YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
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
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
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
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}






/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* Lookahead token kind.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs = 0;

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

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc);
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
      yyerror_range[1] = yylloc;
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
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: func_def  */
#line 117 "parser.y"
                   { std::cout << "AST: " << *(yyvsp[0].localdef) << std::endl; delete (yyvsp[0].localdef); }
#line 1415 "parser.cpp"
    break;

  case 3: /* func_def: "def" header local_def_list block  */
#line 120 "parser.y"
                                                { (yyval.localdef) = new FuncDef((yyvsp[-2].header), (yyvsp[-1].localdeflist), (yyvsp[0].block)); }
#line 1421 "parser.cpp"
    break;

  case 4: /* local_def_list: %empty  */
#line 123 "parser.y"
                                                           { (yyval.localdeflist) = new LocalDefList(); }
#line 1427 "parser.cpp"
    break;

  case 5: /* local_def_list: local_def_list local_def  */
#line 124 "parser.y"
                                           { (yyvsp[-1].localdeflist)->append((yyvsp[0].localdef)); (yyval.localdeflist) = (yyvsp[-1].localdeflist); }
#line 1433 "parser.cpp"
    break;

  case 6: /* header: T_id is_data_type col_fpar_def  */
#line 127 "parser.y"
                                         { (yyval.header) = new Header(new Id(*(yyvsp[-2].name)), (yyvsp[-1].isdatatype), (yyvsp[0].colfpardef)); delete (yyvsp[-2].name); }
#line 1439 "parser.cpp"
    break;

  case 7: /* is_data_type: %empty  */
#line 130 "parser.y"
                                         { (yyval.isdatatype) = nullptr; }
#line 1445 "parser.cpp"
    break;

  case 8: /* is_data_type: "is" data_type  */
#line 131 "parser.y"
                                 { (yyval.isdatatype) = new IsDataType((yyvsp[0].datatype)); }
#line 1451 "parser.cpp"
    break;

  case 9: /* col_fpar_def: %empty  */
#line 134 "parser.y"
                                                                 { (yyval.colfpardef) = nullptr; }
#line 1457 "parser.cpp"
    break;

  case 10: /* col_fpar_def: ":" fpar_def fpar_def_list  */
#line 135 "parser.y"
                                             { (yyvsp[0].fpardeflist)->append((yyvsp[-1].fpardef)); (yyval.colfpardef) = new ColFparDef((yyvsp[0].fpardeflist)); }
#line 1463 "parser.cpp"
    break;

  case 11: /* fpar_def_list: %empty  */
#line 138 "parser.y"
                                                                 { (yyval.fpardeflist) = new FparDefList(); }
#line 1469 "parser.cpp"
    break;

  case 12: /* fpar_def_list: fpar_def_list ',' fpar_def  */
#line 139 "parser.y"
                                             { (yyvsp[-2].fpardeflist)->append((yyvsp[0].fpardef)); (yyval.fpardeflist) = (yyvsp[-2].fpardeflist); }
#line 1475 "parser.cpp"
    break;

  case 13: /* fpar_def: T_id id_list "as" fpar_type  */
#line 142 "parser.y"
                                          { (yyvsp[-2].idlist)->prepend(new Id(*(yyvsp[-3].name))); (yyval.fpardef) = new FparDef((yyvsp[-2].idlist), (yyvsp[0].fpartype)); delete (yyvsp[-3].name);}
#line 1481 "parser.cpp"
    break;

  case 14: /* id_list: %empty  */
#line 145 "parser.y"
                           { (yyval.idlist) = new IdList(); }
#line 1487 "parser.cpp"
    break;

  case 15: /* id_list: id_list T_id  */
#line 146 "parser.y"
                       { (yyvsp[-1].idlist)->append(new Id(*(yyvsp[0].name))); (yyval.idlist) = (yyvsp[-1].idlist); delete (yyvsp[0].name); }
#line 1493 "parser.cpp"
    break;

  case 16: /* data_type: "int"  */
#line 149 "parser.y"
                     { (yyval.datatype) = new DataType(*(yyvsp[0].dtype)); delete (yyvsp[0].dtype); }
#line 1499 "parser.cpp"
    break;

  case 17: /* data_type: "byte"  */
#line 150 "parser.y"
                     { (yyval.datatype) = new DataType(*(yyvsp[0].dtype)); delete (yyvsp[0].dtype); }
#line 1505 "parser.cpp"
    break;

  case 18: /* fpar_type: type  */
#line 153 "parser.y"
                                                                                        { (yyval.fpartype) = (yyvsp[0].fpartype); }
#line 1511 "parser.cpp"
    break;

  case 19: /* fpar_type: "ref" data_type  */
#line 154 "parser.y"
                                                                                { (yyval.fpartype) = new RefPar((yyvsp[0].datatype)); }
#line 1517 "parser.cpp"
    break;

  case 20: /* fpar_type: data_type '[' ']' bracket_int_const_list  */
#line 155 "parser.y"
                                                        { (yyval.fpartype) = new ArrayPar((yyvsp[-3].datatype), (yyvsp[0].bracketlist)); }
#line 1523 "parser.cpp"
    break;

  case 21: /* bracket_int_const_list: %empty  */
#line 158 "parser.y"
                                                                                                 { (yyval.bracketlist) = new BracketList(); }
#line 1529 "parser.cpp"
    break;

  case 22: /* bracket_int_const_list: bracket_int_const_list '[' T_const ']'  */
#line 159 "parser.y"
                                                                 { (yyvsp[-3].bracketlist)->append(new Const((yyvsp[-1].num))); (yyval.bracketlist) = (yyvsp[-3].bracketlist); }
#line 1535 "parser.cpp"
    break;

  case 23: /* local_def: func_def  */
#line 162 "parser.y"
                        { (yyval.localdef) = (yyvsp[0].localdef); }
#line 1541 "parser.cpp"
    break;

  case 24: /* local_def: func_decl  */
#line 163 "parser.y"
                        { (yyval.localdef) = (yyvsp[0].localdef); }
#line 1547 "parser.cpp"
    break;

  case 25: /* local_def: var_def  */
#line 164 "parser.y"
                        { (yyval.localdef) = (yyvsp[0].localdef); }
#line 1553 "parser.cpp"
    break;

  case 26: /* type: data_type bracket_int_const_list  */
#line 167 "parser.y"
                                           { (yyval.fpartype) = new Type((yyvsp[-1].datatype), (yyvsp[0].bracketlist)); }
#line 1559 "parser.cpp"
    break;

  case 27: /* func_decl: "decl" header  */
#line 170 "parser.y"
                             { (yyval.localdef) = new FuncDecl((yyvsp[0].header)); }
#line 1565 "parser.cpp"
    break;

  case 28: /* var_def: "var" T_id id_list "is" type  */
#line 173 "parser.y"
                                       {(yyvsp[-2].idlist)->prepend(new Id(*(yyvsp[-3].name))); (yyval.localdef) = new VarDef((yyvsp[-2].idlist), (yyvsp[0].fpartype)); delete (yyvsp[-3].name);}
#line 1571 "parser.cpp"
    break;

  case 29: /* block: "begin" stmt stmt_list "end"  */
#line 176 "parser.y"
                                       {(yyvsp[-1].block)->prepend((yyvsp[-2].stmt)); (yyval.block) = (yyvsp[-1].block);}
#line 1577 "parser.cpp"
    break;

  case 30: /* block: stmt stmt_list T_auto_end  */
#line 177 "parser.y"
                                       {(yyvsp[-1].block)->prepend((yyvsp[-2].stmt)); (yyval.block) = (yyvsp[-1].block);}
#line 1583 "parser.cpp"
    break;

  case 31: /* stmt_list: %empty  */
#line 180 "parser.y"
                                 { (yyval.block) = new Block(); }
#line 1589 "parser.cpp"
    break;

  case 32: /* stmt_list: stmt_list stmt  */
#line 181 "parser.y"
                             { (yyvsp[-1].block)->append((yyvsp[0].stmt)); (yyval.block) = (yyvsp[-1].block); }
#line 1595 "parser.cpp"
    break;

  case 33: /* stmt: "skip"  */
#line 184 "parser.y"
                                                                        { (yyval.stmt) = new Skip(); }
#line 1601 "parser.cpp"
    break;

  case 34: /* stmt: l_value ":=" expr  */
#line 185 "parser.y"
                                                                                                                        { (yyval.stmt) = new Assign((yyvsp[-2].lvalue), (yyvsp[0].expr)); }
#line 1607 "parser.cpp"
    break;

  case 35: /* stmt: proc_call  */
#line 186 "parser.y"
                                                                                                                                { (yyval.stmt) = (yyvsp[0].stmt); }
#line 1613 "parser.cpp"
    break;

  case 36: /* stmt: "exit"  */
#line 187 "parser.y"
                                                                                                                                { (yyval.stmt) = new Exit(); }
#line 1619 "parser.cpp"
    break;

  case 37: /* stmt: "return" ":" expr  */
#line 188 "parser.y"
                                                                        { (yyval.stmt) = new Return((yyvsp[0].expr)); }
#line 1625 "parser.cpp"
    break;

  case 38: /* stmt: "if" cond ":" block elif_cond_block_list else_col_block  */
#line 189 "parser.y"
                                                                        { (yyval.stmt) = new IfThenElse((yyvsp[-4].expr), (yyvsp[-2].block), (yyvsp[-1].eliflist), (yyvsp[0].stmt)); }
#line 1631 "parser.cpp"
    break;

  case 39: /* stmt: "loop" one_id ":" block  */
#line 190 "parser.y"
                                                                                                                { (yyval.stmt) = new Loop((yyvsp[-2].expr), (yyvsp[0].block)); }
#line 1637 "parser.cpp"
    break;

  case 40: /* stmt: "break" col_id  */
#line 191 "parser.y"
                                                                                                                        { (yyval.stmt) = new Break((yyvsp[0].colid)); }
#line 1643 "parser.cpp"
    break;

  case 41: /* stmt: "continue" col_id  */
#line 192 "parser.y"
                                                                                                                        { (yyval.stmt) = new Continue((yyvsp[0].colid)); }
#line 1649 "parser.cpp"
    break;

  case 42: /* elif_cond_block_list: %empty  */
#line 195 "parser.y"
                                                                                                         { (yyval.eliflist) = new ElifList(); }
#line 1655 "parser.cpp"
    break;

  case 43: /* elif_cond_block_list: elif_cond_block_list "elif" cond ":" block  */
#line 196 "parser.y"
                                                                     { Elif *elif= new Elif((yyvsp[-2].expr), (yyvsp[0].block)); (yyvsp[-4].eliflist)->append(elif); (yyval.eliflist) = (yyvsp[-4].eliflist); }
#line 1661 "parser.cpp"
    break;

  case 44: /* else_col_block: %empty  */
#line 199 "parser.y"
                                           { (yyval.stmt) = nullptr; }
#line 1667 "parser.cpp"
    break;

  case 45: /* else_col_block: "else" ":" block  */
#line 200 "parser.y"
                                   { (yyval.stmt) = new Else((yyvsp[0].block)); }
#line 1673 "parser.cpp"
    break;

  case 46: /* one_id: %empty  */
#line 203 "parser.y"
                 { (yyval.expr) = nullptr; }
#line 1679 "parser.cpp"
    break;

  case 47: /* one_id: T_id  */
#line 204 "parser.y"
                 { (yyval.expr) = new Id(*(yyvsp[0].name)); delete (yyvsp[0].name); }
#line 1685 "parser.cpp"
    break;

  case 48: /* col_id: %empty  */
#line 207 "parser.y"
                        { (yyval.colid) = nullptr; }
#line 1691 "parser.cpp"
    break;

  case 49: /* col_id: ":" T_id  */
#line 208 "parser.y"
                    { (yyval.colid) = new ColId(new Id(*(yyvsp[0].name))); delete (yyvsp[0].name); }
#line 1697 "parser.cpp"
    break;

  case 50: /* l_value: T_id  */
#line 211 "parser.y"
                                { (yyval.lvalue) = new LValue(new Id(*(yyvsp[0].name))); delete (yyvsp[0].name); }
#line 1703 "parser.cpp"
    break;

  case 51: /* l_value: T_str  */
#line 212 "parser.y"
                                { (yyval.lvalue) = new LValue(new Str(*(yyvsp[0].str))); delete (yyvsp[0].str); }
#line 1709 "parser.cpp"
    break;

  case 52: /* l_value: l_value '[' expr ']'  */
#line 213 "parser.y"
                                { (yyvsp[-3].lvalue)->append((yyvsp[-1].expr)); (yyval.lvalue) = (yyvsp[-3].lvalue); }
#line 1715 "parser.cpp"
    break;

  case 53: /* expr: T_const  */
#line 216 "parser.y"
                                                { (yyval.expr) = new Const((yyvsp[0].num)); }
#line 1721 "parser.cpp"
    break;

  case 54: /* expr: T_char  */
#line 217 "parser.y"
                                                { (yyval.expr) = new Char((yyvsp[0].ch_cnst)); }
#line 1727 "parser.cpp"
    break;

  case 55: /* expr: l_value  */
#line 218 "parser.y"
                                                { (yyval.expr) = (yyvsp[0].lvalue); }
#line 1733 "parser.cpp"
    break;

  case 56: /* expr: '(' expr ')'  */
#line 219 "parser.y"
                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 1739 "parser.cpp"
    break;

  case 57: /* expr: func_call  */
#line 220 "parser.y"
                                                { (yyval.expr) = (yyvsp[0].expr); }
#line 1745 "parser.cpp"
    break;

  case 58: /* expr: '+' expr  */
#line 221 "parser.y"
                                        { (yyval.expr) = new UnaryOpExpr(*(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1751 "parser.cpp"
    break;

  case 59: /* expr: '-' expr  */
#line 222 "parser.y"
                                        { (yyval.expr) = new UnaryOpExpr(*(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1757 "parser.cpp"
    break;

  case 60: /* expr: expr '+' expr  */
#line 223 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1763 "parser.cpp"
    break;

  case 61: /* expr: expr '-' expr  */
#line 224 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1769 "parser.cpp"
    break;

  case 62: /* expr: expr '*' expr  */
#line 225 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1775 "parser.cpp"
    break;

  case 63: /* expr: expr '/' expr  */
#line 226 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1781 "parser.cpp"
    break;

  case 64: /* expr: expr '%' expr  */
#line 227 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1787 "parser.cpp"
    break;

  case 65: /* expr: "true"  */
#line 228 "parser.y"
                                                        { (yyval.expr) = new BoolVal(*(yyvsp[0].btype)); delete (yyvsp[0].btype); }
#line 1793 "parser.cpp"
    break;

  case 66: /* expr: "false"  */
#line 229 "parser.y"
                                                        { (yyval.expr) = new BoolVal(*(yyvsp[0].btype)); delete (yyvsp[0].btype); }
#line 1799 "parser.cpp"
    break;

  case 67: /* expr: '!' expr  */
#line 230 "parser.y"
                                        { (yyval.expr) = new UnaryOpExpr(*(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1805 "parser.cpp"
    break;

  case 68: /* expr: expr '&' expr  */
#line 231 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1811 "parser.cpp"
    break;

  case 69: /* expr: expr '|' expr  */
#line 232 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1817 "parser.cpp"
    break;

  case 70: /* proc_call: T_id one_col_expr  */
#line 235 "parser.y"
                                { (yyval.stmt) = new ProcCall(new Id(*(yyvsp[-1].name)), (yyvsp[0].onecolexpr)); delete (yyvsp[-1].name); }
#line 1823 "parser.cpp"
    break;

  case 71: /* one_col_expr: %empty  */
#line 238 "parser.y"
                                                 { (yyval.onecolexpr) = nullptr; }
#line 1829 "parser.cpp"
    break;

  case 72: /* one_col_expr: ":" expr expr_list  */
#line 239 "parser.y"
                                     {(yyvsp[0].exprlist)->prepend((yyvsp[-1].expr)); (yyval.onecolexpr) = new OneColExpr((yyvsp[0].exprlist));}
#line 1835 "parser.cpp"
    break;

  case 73: /* expr_list: %empty  */
#line 242 "parser.y"
                                         { (yyval.exprlist) = new ExprList(); }
#line 1841 "parser.cpp"
    break;

  case 74: /* expr_list: expr_list ',' expr  */
#line 243 "parser.y"
                                 { (yyvsp[-2].exprlist)->append((yyvsp[0].expr)); (yyval.exprlist) = (yyvsp[-2].exprlist); }
#line 1847 "parser.cpp"
    break;

  case 75: /* func_call: T_id '(' one_expr ')'  */
#line 246 "parser.y"
                                    { (yyval.expr) = new FuncCall(new Id(*(yyvsp[-3].name)), (yyvsp[-1].expr)); delete (yyvsp[-3].name); }
#line 1853 "parser.cpp"
    break;

  case 76: /* one_expr: %empty  */
#line 249 "parser.y"
                                 { (yyval.expr) = nullptr; }
#line 1859 "parser.cpp"
    break;

  case 77: /* one_expr: expr expr_list  */
#line 250 "parser.y"
                             {(yyvsp[0].exprlist)->prepend((yyvsp[-1].expr)); (yyval.expr) = (yyvsp[0].exprlist);}
#line 1865 "parser.cpp"
    break;

  case 78: /* cond: expr  */
#line 253 "parser.y"
                                                        { (yyval.expr) = (yyvsp[0].expr); }
#line 1871 "parser.cpp"
    break;

  case 79: /* cond: '(' cond ')'  */
#line 254 "parser.y"
                                                { (yyval.expr) = (yyvsp[-1].expr); }
#line 1877 "parser.cpp"
    break;

  case 80: /* cond: "not" cond  */
#line 255 "parser.y"
                                        { (yyval.expr) = new NotCond((yyvsp[0].expr)); }
#line 1883 "parser.cpp"
    break;

  case 81: /* cond: cond "and" cond  */
#line 256 "parser.y"
                                                { (yyval.expr) = new BinOpCond((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1889 "parser.cpp"
    break;

  case 82: /* cond: cond "or" cond  */
#line 257 "parser.y"
                                                { (yyval.expr) = new BinOpCond((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1895 "parser.cpp"
    break;

  case 83: /* cond: expr '=' expr  */
#line 258 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1901 "parser.cpp"
    break;

  case 84: /* cond: expr "<>" expr  */
#line 259 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1907 "parser.cpp"
    break;

  case 85: /* cond: expr '<' expr  */
#line 260 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1913 "parser.cpp"
    break;

  case 86: /* cond: expr '>' expr  */
#line 261 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1919 "parser.cpp"
    break;

  case 87: /* cond: expr "<=" expr  */
#line 262 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1925 "parser.cpp"
    break;

  case 88: /* cond: expr ">=" expr  */
#line 263 "parser.y"
                                                { (yyval.expr) = new BinOpExpr((yyvsp[-2].expr), *(yyvsp[-1].op), (yyvsp[0].expr)); delete (yyvsp[-1].op); }
#line 1931 "parser.cpp"
    break;


#line 1935 "parser.cpp"

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
  *++yylsp = yyloc;

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
      yyerror (&yylloc, YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

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
  yyerror (&yylloc, YY_("memory exhausted"));
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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 266 "parser.y"


void yyerror(YYLTYPE *locp, const char *msg) {
	printf("Syntax error: %s\n at line %d\n", msg, locp->last_line);
	exit(42);
}

int main(int argc, char* argv[]) {
    extern FILE *yyin;
    extern int block_style;
    void detect_block_style(FILE *);
     
    FILE* f = fopen(argv[1], "r");
    if (!f) {
        perror("fopen");
        exit(1);
    }   

    yyin = f;

    detect_block_style(yyin);

    printf("Using %s%s%s syntax.\n",
       block_style == 1 ? "\033[0;33m" : "\033[0;34m",
       block_style == 1 ? "block-delimiter" : "indentation",
       "\033[0m");

	int res = yyparse();
    switch(res) {
        case 0:
            printf("\033[1;32m Successful parsing\n \033[0m");
            break;

        case 1:
            printf("\033[1;31m Syntaxt error in parsing\n \033[0m");
            break;
        
        case 2:
            printf("\033[1;31m Parsing failed due to memory exhaustion\n \033[0m");
            break;
    }

	return res;
}
