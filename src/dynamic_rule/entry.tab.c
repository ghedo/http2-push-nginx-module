/* A Bison parser, made by GNU Bison 2.7.  */

/* Bison implementation for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.7"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
/* Line 371 of yacc.c  */
#line 1 "entry.y"

#include <stdio.h>
#include <cstdarg>
#include "entry.hpp"
#define YYDEBUG 1
extern "C" {
/* prototypes */
nodeType *opr(int oper, int nops, ...);
nodeType *id_int(int i);
nodeType *id_str(int i);
nodeType *id_json(std::string &sValue);
nodeType *id_var(std::string &sValue);
nodeType *con_int(int value);
nodeType *con_str(std::string &sValue);
nodeType *con_json(std::string &sValue);
void freeNode(nodeType *p);
extern int yylex(void);
void yyerror(const char *s);
}
int ex(nodeType *p, std::string *str_ret = NULL);

std::map<int, nodeEnum> g_id_type;
int g_sym_int[26];
std::string g_sym_str[26];
cJSON *g_sym_json[26];
std::string g_buf_str, g_append_str;
std::string g_request_url, g_request_path;
typedef struct ngx_http_request_s ngx_http_request_t;
ngx_http_request_t *g_request;
objectTypeEnum g_object_type;
cJSON *g_json_root;
std::set<std::string> g_push_ret;

/* Line 371 of yacc.c  */
#line 102 "entry.tab.c"

# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "entry.tab.h".  */
#ifndef YY_YY_ENTRY_TAB_H_INCLUDED
# define YY_YY_ENTRY_TAB_H_INCLUDED
/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     STR = 259,
     JSON_CON = 260,
     OBJECT_TYPE = 261,
     INT_VARIABLE = 262,
     STR_VARIABLE = 263,
     JSON_VARIABLE = 264,
     VARIABLE = 265,
     STR_CON_BEGIN = 266,
     STR_CON_END = 267,
     JSON_VAR_BEGIN = 268,
     INT_VAR_BEGIN = 269,
     STR_VAR_BEGIN = 270,
     JSON_CON_BEGIN = 271,
     WHILE = 272,
     IF = 273,
     FOR = 274,
     PRINT = 275,
     PUSH = 276,
     PARSE_JSON = 277,
     REQUEST_URL = 278,
     REQUEST_PATH = 279,
     IFX = 280,
     ELSE = 281,
     NE = 282,
     EQ = 283,
     LE = 284,
     GE = 285,
     REGEX = 286,
     STR_APPEND_END = 287,
     STR_APPEND = 288,
     UMINUS = 289
   };
#endif


#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */

#endif /* !YY_YY_ENTRY_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

/* Line 390 of yacc.c  */
#line 201 "entry.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(N) (N)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
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
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#   if ! defined malloc && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (YYID (0))
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   383

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  6
/* YYNRULES -- Number of rules.  */
#define YYNRULES  41
/* YYNRULES -- Number of states.  */
#define YYNSTATES  101

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   289

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      44,    45,    37,    34,     2,    35,    27,    38,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    46,    42,
      29,    43,    28,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    47,     2,    48,     2,     2,     2,     2,
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
      25,    26,    30,    31,    32,    33,    36,    39,    40,    41
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,     9,    11,    14,    18,    22,
      29,    35,    41,    47,    52,    57,    63,    71,    77,    85,
      89,    91,    94,    96,   100,   103,   105,   107,   109,   112,
     115,   119,   123,   127,   131,   135,   139,   143,   147,   151,
     155,   159
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      50,     0,    -1,    51,    -1,    51,    52,    -1,    -1,    42,
      -1,    54,    42,    -1,    20,    54,    42,    -1,    21,    54,
      42,    -1,    13,     9,    43,    22,    54,    42,    -1,    14,
       7,    43,    54,    42,    -1,    15,     8,    43,    54,    42,
      -1,    13,     9,    43,    54,    42,    -1,    10,    39,    54,
      42,    -1,    10,    36,    54,    42,    -1,    17,    44,    54,
      45,    52,    -1,    19,    44,    54,    46,    54,    45,    52,
      -1,    18,    44,    54,    45,    52,    -1,    18,    44,    54,
      45,    52,    26,    52,    -1,    47,    53,    48,    -1,    52,
      -1,    53,    52,    -1,     3,    -1,    11,     4,    12,    -1,
      16,     5,    -1,    10,    -1,    23,    -1,    24,    -1,    13,
       9,    -1,    35,    54,    -1,    54,    34,    54,    -1,    54,
      35,    54,    -1,    54,    37,    54,    -1,    54,    38,    54,
      -1,    54,    29,    54,    -1,    54,    28,    54,    -1,    54,
      33,    54,    -1,    54,    32,    54,    -1,    54,    30,    54,
      -1,    54,    31,    54,    -1,    54,    40,    54,    -1,    44,
      54,    45,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    59,    59,    63,    64,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      86,    87,    91,    92,    93,    94,    95,    96,    97,    98,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "STR", "JSON_CON", "OBJECT_TYPE",
  "INT_VARIABLE", "STR_VARIABLE", "JSON_VARIABLE", "VARIABLE",
  "STR_CON_BEGIN", "STR_CON_END", "JSON_VAR_BEGIN", "INT_VAR_BEGIN",
  "STR_VAR_BEGIN", "JSON_CON_BEGIN", "WHILE", "IF", "FOR", "PRINT", "PUSH",
  "PARSE_JSON", "REQUEST_URL", "REQUEST_PATH", "IFX", "ELSE", "'.'", "'>'",
  "'<'", "NE", "EQ", "LE", "GE", "'+'", "'-'", "REGEX", "'*'", "'/'",
  "STR_APPEND_END", "STR_APPEND", "UMINUS", "';'", "'='", "'('", "')'",
  "':'", "'{'", "'}'", "$accept", "program", "function", "stmt",
  "stmt_list", "expr", YY_NULL
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,    46,    62,    60,
     282,   283,   284,   285,    43,    45,   286,    42,    47,   287,
     288,   289,    59,    61,    40,    41,    58,   123,   125
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    52,    52,    52,    52,    52,
      53,    53,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     2,     3,     3,     6,
       5,     5,     5,     4,     4,     5,     7,     5,     7,     3,
       1,     2,     1,     3,     2,     1,     1,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3
};

/* YYDEFACT[STATE-NAME] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,     0,     2,     1,    22,    25,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    26,    27,     0,     5,
       0,     0,     3,     0,     0,     0,     0,    28,     0,     0,
      24,     0,     0,     0,    25,     0,     0,     0,    29,     0,
      20,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     0,     0,    23,     0,     0,     0,
       0,     0,     0,    28,     7,     8,    41,    19,    21,    35,
      34,    38,    39,    37,    36,    30,    31,    32,    33,    40,
      14,    13,     0,     0,     0,     0,     0,     0,     0,     0,
      12,    10,    11,    15,    17,     0,     9,     0,     0,    18,
      16
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    22,    41,    23
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -32
static const yytype_int16 yypact[] =
{
     -32,     1,    80,   -32,   -32,   -23,    -2,    -6,     4,     9,
       7,   -26,   -25,   -20,   122,   122,   -32,   -32,   122,   -32,
     122,    80,   -32,   221,   122,   122,    15,   -13,     2,     3,
     -32,   122,   122,   122,   -32,    35,   236,   251,   -32,   149,
     -32,    40,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   -32,   266,   281,   -32,   107,   122,   122,
     167,   185,   130,   -32,   -32,   -32,   -32,   -32,   -32,    -9,
      -9,    -9,    -9,    -9,    -9,   -31,   -31,    12,    12,   -32,
     -32,   -32,   122,   296,   311,   326,    80,    80,   122,   341,
     -32,   -32,   -32,   -32,    36,   203,   -32,    80,    80,   -32,
     -32
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -32,   -32,   -32,   -21,   -32,   -10
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      40,     3,    26,    27,    36,    37,    50,    51,    38,    52,
      39,    28,    30,    24,    54,    55,    25,    29,    31,    32,
      68,    60,    61,    62,    33,    48,    49,    56,    50,    51,
      57,    52,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,     4,    63,    58,    59,    83,    84,    85,
       5,     6,    52,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    97,    16,    17,    93,    94,     0,     0,     0,
       0,     0,    89,     0,     0,    18,    99,   100,    95,     0,
       0,     0,    19,     4,    20,     0,     0,    21,    67,     0,
       5,     6,     0,     7,     8,     9,    10,    11,    12,    13,
      14,    15,     0,    16,    17,     0,     0,     0,     0,     0,
       4,     0,     0,     0,     0,    18,     0,    34,     6,     0,
      35,     0,    19,    10,    20,     4,     0,    21,     0,    82,
      16,    17,    34,     6,     0,    35,     0,     0,    10,     0,
       0,     0,    18,     0,     0,    16,    17,     0,     0,     0,
       0,    20,     0,     0,     0,     0,     0,    18,    42,    43,
      44,    45,    46,    47,    48,    49,    20,    50,    51,     0,
      52,     0,     0,     0,     0,     0,    88,    42,    43,    44,
      45,    46,    47,    48,    49,     0,    50,    51,     0,    52,
       0,     0,     0,     0,    66,    42,    43,    44,    45,    46,
      47,    48,    49,     0,    50,    51,     0,    52,     0,     0,
       0,     0,    86,    42,    43,    44,    45,    46,    47,    48,
      49,     0,    50,    51,     0,    52,     0,     0,     0,     0,
      87,    42,    43,    44,    45,    46,    47,    48,    49,     0,
      50,    51,     0,    52,     0,     0,     0,     0,    98,    42,
      43,    44,    45,    46,    47,    48,    49,     0,    50,    51,
       0,    52,     0,    53,    42,    43,    44,    45,    46,    47,
      48,    49,     0,    50,    51,     0,    52,     0,    64,    42,
      43,    44,    45,    46,    47,    48,    49,     0,    50,    51,
       0,    52,     0,    65,    42,    43,    44,    45,    46,    47,
      48,    49,     0,    50,    51,     0,    52,     0,    80,    42,
      43,    44,    45,    46,    47,    48,    49,     0,    50,    51,
       0,    52,     0,    81,    42,    43,    44,    45,    46,    47,
      48,    49,     0,    50,    51,     0,    52,     0,    90,    42,
      43,    44,    45,    46,    47,    48,    49,     0,    50,    51,
       0,    52,     0,    91,    42,    43,    44,    45,    46,    47,
      48,    49,     0,    50,    51,     0,    52,     0,    92,    42,
      43,    44,    45,    46,    47,    48,    49,     0,    50,    51,
       0,    52,     0,    96
};

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-32)))

#define yytable_value_is_error(Yytable_value) \
  YYID (0)

static const yytype_int8 yycheck[] =
{
      21,     0,     4,     9,    14,    15,    37,    38,    18,    40,
      20,     7,     5,    36,    24,    25,    39,     8,    44,    44,
      41,    31,    32,    33,    44,    34,    35,    12,    37,    38,
      43,    40,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,     3,     9,    43,    43,    57,    58,    59,
      10,    11,    40,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    26,    23,    24,    86,    87,    -1,    -1,    -1,
      -1,    -1,    82,    -1,    -1,    35,    97,    98,    88,    -1,
      -1,    -1,    42,     3,    44,    -1,    -1,    47,    48,    -1,
      10,    11,    -1,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,    -1,    -1,    35,    -1,    10,    11,    -1,
      13,    -1,    42,    16,    44,     3,    -1,    47,    -1,    22,
      23,    24,    10,    11,    -1,    13,    -1,    -1,    16,    -1,
      -1,    -1,    35,    -1,    -1,    23,    24,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    -1,    35,    28,    29,
      30,    31,    32,    33,    34,    35,    44,    37,    38,    -1,
      40,    -1,    -1,    -1,    -1,    -1,    46,    28,    29,    30,
      31,    32,    33,    34,    35,    -1,    37,    38,    -1,    40,
      -1,    -1,    -1,    -1,    45,    28,    29,    30,    31,    32,
      33,    34,    35,    -1,    37,    38,    -1,    40,    -1,    -1,
      -1,    -1,    45,    28,    29,    30,    31,    32,    33,    34,
      35,    -1,    37,    38,    -1,    40,    -1,    -1,    -1,    -1,
      45,    28,    29,    30,    31,    32,    33,    34,    35,    -1,
      37,    38,    -1,    40,    -1,    -1,    -1,    -1,    45,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    37,    38,
      -1,    40,    -1,    42,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    37,    38,    -1,    40,    -1,    42,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    37,    38,
      -1,    40,    -1,    42,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    37,    38,    -1,    40,    -1,    42,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    37,    38,
      -1,    40,    -1,    42,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    37,    38,    -1,    40,    -1,    42,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    37,    38,
      -1,    40,    -1,    42,    28,    29,    30,    31,    32,    33,
      34,    35,    -1,    37,    38,    -1,    40,    -1,    42,    28,
      29,    30,    31,    32,    33,    34,    35,    -1,    37,    38,
      -1,    40,    -1,    42
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    50,    51,     0,     3,    10,    11,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    23,    24,    35,    42,
      44,    47,    52,    54,    36,    39,     4,     9,     7,     8,
       5,    44,    44,    44,    10,    13,    54,    54,    54,    54,
      52,    53,    28,    29,    30,    31,    32,    33,    34,    35,
      37,    38,    40,    42,    54,    54,    12,    43,    43,    43,
      54,    54,    54,     9,    42,    42,    45,    48,    52,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      42,    42,    22,    54,    54,    54,    45,    45,    46,    54,
      42,    42,    42,    52,    52,    54,    42,    26,    45,    52,
      52
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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
      YYERROR;							\
    }								\
while (YYID (0))

/* Error token number */
#define YYTERROR	1
#define YYERRCODE	256


/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */
#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULL, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULL;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - Assume YYFAIL is not used.  It's too flawed to consider.  See
       <http://lists.gnu.org/archive/html/bison-patches/2009-12/msg00024.html>
       for details.  YYERROR is fine as it does not invoke this
       function.
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULL, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
        break;
    }
}




/* The lookahead symbol.  */
int yychar;


#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval YY_INITIAL_VALUE(yyval_default);

/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
/* Line 1792 of yacc.c  */
#line 59 "entry.y"
    { }
    break;

  case 3:
/* Line 1792 of yacc.c  */
#line 63 "entry.y"
    {ex((yyvsp[(2) - (2)].n_ptr)); freeNode((yyvsp[(2) - (2)].n_ptr)); }
    break;

  case 5:
/* Line 1792 of yacc.c  */
#line 68 "entry.y"
    { (yyval.n_ptr) = opr(';', 2, NULL, NULL); }
    break;

  case 6:
/* Line 1792 of yacc.c  */
#line 69 "entry.y"
    { (yyval.n_ptr) = (yyvsp[(1) - (2)].n_ptr); }
    break;

  case 7:
/* Line 1792 of yacc.c  */
#line 70 "entry.y"
    { (yyval.n_ptr) = opr(PRINT, 1, (yyvsp[(2) - (3)].n_ptr)); }
    break;

  case 8:
/* Line 1792 of yacc.c  */
#line 71 "entry.y"
    { (yyval.n_ptr) = opr(PUSH, 1, (yyvsp[(2) - (3)].n_ptr)); }
    break;

  case 9:
/* Line 1792 of yacc.c  */
#line 72 "entry.y"
    { (yyval.n_ptr) = opr(PARSE_JSON, 2, id_json((yyvsp[(2) - (6)].s_entry)), (yyvsp[(5) - (6)].n_ptr)); }
    break;

  case 10:
/* Line 1792 of yacc.c  */
#line 73 "entry.y"
    { (yyval.n_ptr) = opr('=', 2, id_int((yyvsp[(2) - (5)].i_entry)), (yyvsp[(4) - (5)].n_ptr)); }
    break;

  case 11:
/* Line 1792 of yacc.c  */
#line 74 "entry.y"
    { (yyval.n_ptr) = opr('=', 2, id_str((yyvsp[(2) - (5)].i_entry)), (yyvsp[(4) - (5)].n_ptr)); }
    break;

  case 12:
/* Line 1792 of yacc.c  */
#line 75 "entry.y"
    { (yyval.n_ptr) = opr('=', 2, id_json((yyvsp[(2) - (5)].s_entry)), (yyvsp[(4) - (5)].n_ptr)); }
    break;

  case 13:
/* Line 1792 of yacc.c  */
#line 76 "entry.y"
    { (yyval.n_ptr) = opr('~', 2, id_var((yyvsp[(1) - (4)].s_entry)), (yyvsp[(3) - (4)].n_ptr)); }
    break;

  case 14:
/* Line 1792 of yacc.c  */
#line 77 "entry.y"
    { (yyval.n_ptr) = opr(REGEX, 2, id_var((yyvsp[(1) - (4)].s_entry)), (yyvsp[(3) - (4)].n_ptr)); }
    break;

  case 15:
/* Line 1792 of yacc.c  */
#line 78 "entry.y"
    { (yyval.n_ptr) = opr(WHILE, 2, (yyvsp[(3) - (5)].n_ptr), (yyvsp[(5) - (5)].n_ptr)); }
    break;

  case 16:
/* Line 1792 of yacc.c  */
#line 79 "entry.y"
    { (yyval.n_ptr) = opr(FOR, 3, (yyvsp[(3) - (7)].n_ptr), (yyvsp[(5) - (7)].n_ptr), (yyvsp[(7) - (7)].n_ptr)); }
    break;

  case 17:
/* Line 1792 of yacc.c  */
#line 80 "entry.y"
    { (yyval.n_ptr) = opr(IF, 2, (yyvsp[(3) - (5)].n_ptr), (yyvsp[(5) - (5)].n_ptr)); }
    break;

  case 18:
/* Line 1792 of yacc.c  */
#line 81 "entry.y"
    { (yyval.n_ptr) = opr(IF, 3, (yyvsp[(3) - (7)].n_ptr), (yyvsp[(5) - (7)].n_ptr), (yyvsp[(7) - (7)].n_ptr)); }
    break;

  case 19:
/* Line 1792 of yacc.c  */
#line 82 "entry.y"
    { (yyval.n_ptr) = (yyvsp[(2) - (3)].n_ptr); }
    break;

  case 20:
/* Line 1792 of yacc.c  */
#line 86 "entry.y"
    { (yyval.n_ptr) = (yyvsp[(1) - (1)].n_ptr); }
    break;

  case 21:
/* Line 1792 of yacc.c  */
#line 87 "entry.y"
    { (yyval.n_ptr) = opr(';', 2, (yyvsp[(1) - (2)].n_ptr), (yyvsp[(2) - (2)].n_ptr)); }
    break;

  case 22:
/* Line 1792 of yacc.c  */
#line 91 "entry.y"
    { (yyval.n_ptr) = con_int((yyvsp[(1) - (1)].i_entry)); }
    break;

  case 23:
/* Line 1792 of yacc.c  */
#line 92 "entry.y"
    {(yyval.n_ptr) = con_str((yyvsp[(2) - (3)].s_entry));}
    break;

  case 24:
/* Line 1792 of yacc.c  */
#line 93 "entry.y"
    {(yyval.n_ptr) = con_json((yyvsp[(2) - (2)].s_entry));}
    break;

  case 25:
/* Line 1792 of yacc.c  */
#line 94 "entry.y"
    { (yyval.n_ptr) = id_var((yyvsp[(1) - (1)].s_entry)); }
    break;

  case 26:
/* Line 1792 of yacc.c  */
#line 95 "entry.y"
    { (yyval.n_ptr) = con_str(g_request_url); }
    break;

  case 27:
/* Line 1792 of yacc.c  */
#line 96 "entry.y"
    { (yyval.n_ptr) = con_str(g_request_path); }
    break;

  case 28:
/* Line 1792 of yacc.c  */
#line 97 "entry.y"
    { (yyval.n_ptr) = id_json((yyvsp[(2) - (2)].s_entry)); }
    break;

  case 29:
/* Line 1792 of yacc.c  */
#line 98 "entry.y"
    { (yyval.n_ptr) = opr(UMINUS, 1, (yyvsp[(2) - (2)].n_ptr)); }
    break;

  case 30:
/* Line 1792 of yacc.c  */
#line 99 "entry.y"
    { (yyval.n_ptr) = opr('+', 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 31:
/* Line 1792 of yacc.c  */
#line 100 "entry.y"
    { (yyval.n_ptr) = opr('-', 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 32:
/* Line 1792 of yacc.c  */
#line 101 "entry.y"
    { (yyval.n_ptr) = opr('*', 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 33:
/* Line 1792 of yacc.c  */
#line 102 "entry.y"
    { (yyval.n_ptr) = opr('/', 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 34:
/* Line 1792 of yacc.c  */
#line 103 "entry.y"
    { (yyval.n_ptr) = opr('<', 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 35:
/* Line 1792 of yacc.c  */
#line 104 "entry.y"
    { (yyval.n_ptr) = opr('>', 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 36:
/* Line 1792 of yacc.c  */
#line 105 "entry.y"
    { (yyval.n_ptr) = opr(GE, 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 37:
/* Line 1792 of yacc.c  */
#line 106 "entry.y"
    { (yyval.n_ptr) = opr(LE, 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 38:
/* Line 1792 of yacc.c  */
#line 107 "entry.y"
    { (yyval.n_ptr) = opr(NE, 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 39:
/* Line 1792 of yacc.c  */
#line 108 "entry.y"
    { (yyval.n_ptr) = opr(EQ, 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 40:
/* Line 1792 of yacc.c  */
#line 109 "entry.y"
    { (yyval.n_ptr) = opr(STR_APPEND, 2, (yyvsp[(1) - (3)].n_ptr), (yyvsp[(3) - (3)].n_ptr)); }
    break;

  case 41:
/* Line 1792 of yacc.c  */
#line 110 "entry.y"
    { (yyval.n_ptr) = (yyvsp[(2) - (3)].n_ptr); }
    break;


/* Line 1792 of yacc.c  */
#line 1762 "entry.tab.c"
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


/* Line 2055 of yacc.c  */
#line 113 "entry.y"


#define SIZEOF_NODETYPE ((char *)&p->con_int - (char *)p)

nodeType *con_int(int value) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(intConNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeIntCon;
    p->con_int.value = value;
    return p;
}

nodeType *con_str(std::string &sValue) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(strConNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeStrCon;
    p->con_str.p_value = new std::string(sValue);
    if (p->con_str.p_value == NULL) {
        yyerror("out of memory");
    }
    return p;
}

nodeType *con_json(std::string &sValue) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(jsonConNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeJsonCon;
    std::vector<std::string> split_ret;
    split_string(sValue, split_ret, ".");

    p->con_json.cjson = walk_through_json(g_json_root, split_ret);
    if (p->con_json.cjson == NULL) {
        yyerror("json walk error");
    }
    return p;
}

static nodeEnum get_var_type(int i) {
    std::map<int, nodeEnum>::iterator iter = g_id_type.find(i);
    if (iter == g_id_type.end()) {
        return typeNodeUnknown;
    }
    return iter->second;
}

static nodeType *create_int_id_node(int i) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(intIdNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeIntId;
    p->int_id.i = i;
    return p;
}

static nodeType *create_str_id_node(int i) {
    nodeType *p;
    size_t nodeSize;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(strIdNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeStrId;
    p->str_id.i = i;
    return p;
}

static nodeType *create_json_id_node(std::string &sValue) {
    nodeType *p;
    size_t nodeSize;
    if (sValue.empty()) {
        yyerror("empty json key");
    }
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(jsonIdNodeType);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeJsonId;
    p->json_id.i = (char)(*sValue.begin()) - 'a';
    p->json_id.need_free = false;
    if (sValue.size() == 1) {
        p->json_id.path = NULL;
    } else {
        p->json_id.path = new std::string(sValue.begin() + 2, sValue.end());
    }
    return p;
}

nodeType *id_var(std::string &sValue) {
    nodeType *p;
    int i = (char)(*sValue.begin()) - 'a';
    nodeEnum node_type = get_var_type(i);
    if (node_type == typeNodeUnknown) {
        yyerror("can't find var");
        return NULL;
    }
    if (node_type == typeIntId) {
        p = create_int_id_node(i);
    } else if (node_type == typeStrId) {
        p = create_str_id_node(i);
    } else if (node_type == typeJsonId) {
        p = create_json_id_node(sValue);
    }
    return p;
}

nodeType *id_int(int i) {
    nodeType *p;
    p = create_int_id_node(i);
    g_id_type[i] = typeIntId;
    return p;
}

nodeType *id_str(int i) {
    nodeType *p;
    p = create_str_id_node(i);
    g_id_type[i] = typeStrId;
    return p;
}

nodeType *id_json(std::string &sValue) {
    nodeType *p;
    p = create_json_id_node(sValue);
    g_id_type[p->json_id.i] = typeJsonId;
    return p;
}

nodeType *opr(int oper, int nops, ...) {
    va_list ap;
    nodeType *p;
    size_t nodeSize;
    int i;
    /* allocate node */
    nodeSize = SIZEOF_NODETYPE + sizeof(oprNodeType) +
               (nops - 1) * sizeof(nodeType*);
    if ((p = (nodeType *)malloc(nodeSize)) == NULL) {
        yyerror("out of memory");
    }
    /* copy information */
    p->type = typeOpr;
    p->opr.oper = oper;
    p->opr.nops = nops;
    va_start(ap, nops);
    for (i = 0; i < nops; i++) {
        p->opr.op[i] = va_arg(ap, nodeType*);
    }
    va_end(ap);
    return p;
}

void freeNode(nodeType *p) {
    int i;
    if (!p) return;
    if (p->type == typeStrCon) {
        delete p->con_str.p_value;
    } else if (p->type == typeJsonId && p->json_id.path != NULL) {
        delete p->json_id.path;
    }
    if (p->type == typeOpr) {
        for (i = 0; i < p->opr.nops; i++)
            freeNode(p->opr.op[i]);
    }
    free (p);
}

void yyerror(const char *s) {
    fprintf(stdout, "%s\n", s);
}
