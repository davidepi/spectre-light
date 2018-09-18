/* A Bison parser, made by GNU Bison 3.1.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 8 "config_parser.y" /* yacc.c:339  */

    #include "parsers/parsed_structs.h"
    #include <stdio.h>
    extern FILE* yyin;
    int yylex(void);
    void yyerror(char const*);
    void parse_config(FILE* opened_file, struct ParsedScene* scene_initialized);
    struct ParsedScene* parsed;
    float vec[3];
    /* add a string to the Parsed data and avoid a leak if overwriting */
    #define ADD_STRING(DST,SRC) if(DST==NULL)free(DST);DST=SRC;

#line 79 "config_parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "config_parser.tab.h".  */
#ifndef YY_YY_CONFIG_PARSER_TAB_H_INCLUDED
# define YY_YY_CONFIG_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    END = 0,
    INVALID = 258,
    COLON = 259,
    OPEN_SQ = 260,
    CLOSE_SQ = 261,
    OPEN_CU = 262,
    CLOSE_CU = 263,
    COMMA = 264,
    OUTPUT = 265,
    INTEGRATOR = 266,
    RESOLUTION = 267,
    WIDTH = 268,
    HEIGHT = 269,
    SAMPLER = 270,
    SPP = 271,
    FILTER = 272,
    TYPE = 273,
    CAMERA = 274,
    ORTHOGRAPHIC_TOKEN = 275,
    PERSPECTIVE_TOKEN = 276,
    PANORAMA_TOKEN = 277,
    POSITION = 278,
    TARGET = 279,
    UP = 280,
    FOV = 281,
    RANDOM_TOKEN = 282,
    STRATIFIED_TOKEN = 283,
    BOX_TOKEN = 284,
    TENT_TOKEN = 285,
    GAUSS_TOKEN = 286,
    MITCHELL_TOKEN = 287,
    LANCZOS_TOKEN = 288,
    UNFILTERED_TOKEN = 289,
    TRILINEAR_TOKEN = 290,
    EWA_TOKEN = 291,
    VAL_0 = 292,
    VAL_1 = 293,
    SHAPE = 294,
    WORLD = 295,
    LIGHT = 296,
    TEMPERATURE = 297,
    NAME = 298,
    ROTATION = 299,
    SCALE = 300,
    SHIFT = 301,
    COLOR = 302,
    MATERIAL = 303,
    DUALMATERIAL = 304,
    TEXTURE = 305,
    ANISOTROPY = 306,
    BECKMANN_TOKEN = 307,
    BLINN_TOKEN = 308,
    DIFFUSE = 309,
    DISTRIBUTION = 310,
    ELEM = 311,
    GGX_TOKEN = 312,
    GLASS_TOKEN = 313,
    GLOSSY_TOKEN = 314,
    IOR = 315,
    MATTE_TOKEN = 316,
    METAL_TOKEN = 317,
    ROUGHNESS = 318,
    SPECULAR = 319,
    NORMAL = 320,
    SRC = 321,
    PATH_TRACE = 322,
    CHNR = 323,
    CHNG = 324,
    CHNB = 325,
    CHNA = 326,
    INV = 327,
    MASK = 328,
    FIRST = 329,
    SECOND = 330,
    RADIUS = 331,
    FALLOFF = 332,
    OMNI_TOKEN = 333,
    SPOT_TOKEN = 334,
    AREA_TOKEN = 335,
    SILVER = 336,
    ALUMINIUM = 337,
    GOLD = 338,
    COPPER = 339,
    IRON = 340,
    MERCURY = 341,
    LEAD = 342,
    PLATINUM = 343,
    TUNGSTEN = 344,
    BERYLLIUM = 345,
    BISMUTH = 346,
    COBALT = 347,
    CHROMIUM = 348,
    GERMANIUM = 349,
    POTASSIUM = 350,
    LITHIUM = 351,
    MAGNESIUM = 352,
    MANGANESE = 353,
    MOLYBDENUM = 354,
    SODIUM = 355,
    NIOBIUM = 356,
    NICKEL = 357,
    PALLADIUM = 358,
    RHODIUM = 359,
    TANTALUM = 360,
    TITANIUM = 361,
    VANADIUM = 362,
    ZINC = 363,
    ZIRCONIUM = 364,
    UINT = 365,
    INT = 366,
    FLOAT = 367,
    STRING = 368
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 131 "config_parser.y" /* yacc.c:355  */

    float fval;
    int ival;
    unsigned int uval;
    char* sval;

#line 241 "config_parser.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_CONFIG_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 272 "config_parser.tab.c" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

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
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  30
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   354

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  26
/* YYNRULES -- Number of rules.  */
#define YYNRULES  153
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  301

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   368

#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   151,   151,   152,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   167,   169,   171,   172,   173,   175,
     178,   178,   180,   181,   182,   185,   185,   187,   188,   189,
     190,   191,   192,   193,   194,   197,   197,   199,   200,   201,
     202,   203,   204,   205,   206,   209,   209,   211,   212,   213,
     214,   215,   216,   217,   218,   219,   222,   222,   224,   225,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   235,
     236,   239,   239,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   254,   254,   256,   257,   258,   259,
     260,   261,   262,   263,   264,   265,   266,   267,   268,   269,
     270,   271,   272,   273,   276,   276,   278,   279,   280,   281,
     282,   283,   290,   291,   292,   293,   294,   295,   296,   297,
     298,   299,   300,   301,   302,   303,   304,   305,   306,   307,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   321,   321,   324,   325,   329,   330,   331,   332,   336,
     341,   345,   346,   347
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "$undefined", "\"invalid character\"",
  "\":\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\",\"",
  "\"`out` keywork\"", "\"`integrator` keyword\"",
  "\"`resolution` keyword\"", "\"`width` keyword\"",
  "\"`height` keyword\"", "\"``sampler` keyword\"", "\"`spp` keyword\"",
  "\"`filter` keyword\"", "\"`type` keyword\"", "\"`camera` keyword\"",
  "\"`orthographic` keyword\"", "\"`perspective` keyword\"",
  "\"`panorama` keyword\"", "\"`position` keyword\"",
  "\"`target` keyword\"", "\"`up` keyword\"", "\"`fov` keyword\"",
  "\"`random` keyword\"", "\"`stratified` keyword\"", "\"`box` keyword\"",
  "\"`tent` keyword\"", "\"`gauss` keyword\"", "\"`mitchell` keyword\"",
  "\"`lanczos` keyword\"", "\"`unfiltered` keyword\"",
  "\"`trilinear` keyword\"", "\"`ewa` keyword\"", "\"`value0` keyword\"",
  "\"`value1` keyword\"", "\"`shape` keyword\"", "\"`world` keyword\"",
  "\"`light` keyword\"", "\"`temperature` keyword\"", "\"`name` keyword\"",
  "\"`rotation` keyword\"", "\"`scale` keyword\"", "\"`shift` keyword\"",
  "\"`color` keyword\"", "\"`material` keyword\"",
  "\"`dualmaterial` keyword\"", "\"`texture` keyword\"",
  "\"`anisotropy` keyword\"", "\"`beckmann` keyword\"",
  "\"`blinn` keyword\"", "\"`diffuse` keyword\"",
  "\"`distribution` keyword\"", "\"`element` keyword\"",
  "\"`ggx` keyword\"", "\"`glass` keyword\"", "\"`glossy` keyword\"",
  "\"`ior` keyword\"", "\"`matte` keyword\"", "\"`metal keyword\"",
  "\"`roughness` keyword\"", "\"`specular` keyword\"",
  "\"`normal` keyword\"", "\"`src` keyword\"", "\"`path` keyword\"",
  "\"Red channel attribute\"", "\"Green channel attribute\"",
  "\"Blue channel attribute\"", "\"Alpha channel attribute\"",
  "\"inverted attribute\"", "\"`mask` keyword\"", "\"`first` keyword\"",
  "\"`second` keyword\"", "\"`radius` keyword\"", "\"`falloff` keyword\"",
  "\"`omni` keyword\"", "\"`spot` keyword\"", "\"`area` keyword\"",
  "\"`Ag`\"", "\"`Al`\"", "\"`Au`\"", "\"`Cu`\"", "\"`Fe`\"", "\"`Hg`\"",
  "\"`Pb`\"", "\"`Pt`\"", "\"`W`\"", "\"`Be`\"", "\"`Bi`\"", "\"`Co`\"",
  "\"`Cr`\"", "\"`Ge`\"", "\"`K`\"", "\"`Li`\"", "\"`Mg`\"", "\"`Mn`\"",
  "\"`Mo`\"", "\"`Na`\"", "\"`Nb`\"", "\"`Ni`\"", "\"`Pd`\"", "\"`Rh`\"",
  "\"`Ta`\"", "\"`Ti`\"", "\"`V`\"", "\"`Zn`\"", "\"`Zr`\"",
  "\"positive integer value\"", "\"integer value\"",
  "\"floating point value\"", "\"quoted string\"", "$accept", "file",
  "stmt", "resolution_obj", "resolution_stmt", "filter_obj", "filter_stmt",
  "camera_obj", "camera_stmt", "world_obj", "world_stmt", "light_obj",
  "light_stmt", "texture_obj", "texture_stmt", "material_obj",
  "material_stmt", "dualmaterial_obj", "dualmaterial_stmt", "element",
  "attributes", "attribute", "channel", "vector", "vector2", "number", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368
};
# endif

#define YYPACT_NINF -273

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-273)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     224,  -273,     6,    17,    26,    34,    71,    98,   101,   117,
     120,   125,   132,   133,   146,   116,  -273,   -89,    84,   145,
      55,    44,   155,   156,    59,   166,   167,     4,   170,   172,
    -273,  -273,  -273,  -273,    46,  -273,  -273,  -273,   121,   158,
    -273,    75,     9,   151,  -273,     5,     0,  -273,   176,   181,
      20,  -273,  -273,   183,   184,   188,    53,  -273,  -273,   189,
     193,   197,   199,   200,   229,  -273,  -273,   204,   205,   206,
     214,   223,   228,    49,  -273,  -273,   240,   246,   247,   252,
     253,   255,   256,   257,   258,    -3,  -273,  -273,   267,   300,
     301,   302,   303,   304,   305,   306,   307,   308,   135,  -273,
    -273,   309,   310,   311,   312,    -6,  -273,  -273,   313,   314,
     315,   316,   317,   318,    95,  -273,    86,   118,  -273,  -273,
     192,   -47,   -47,  -273,  -273,    67,   319,   319,   319,   -47,
    -273,  -273,   319,   210,   319,    -4,   212,   213,  -273,  -273,
      21,   319,   217,   215,   319,    -4,   319,   -47,   -47,  -273,
    -273,   187,   216,   -47,   218,    24,   194,    -1,   -47,   219,
     220,  -273,  -273,   221,   222,   225,   226,  -273,  -273,   111,
     227,     3,     3,   319,   230,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,   -47,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,   198,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,  -273,  -273,   -47,  -273,  -273,  -273,
    -273,  -273,  -273,  -273,   198,  -273,  -273,  -273,  -273,  -273,
    -273,   -47,  -273,  -273,  -273,  -273,  -273,  -273,   321,  -273,
    -273,  -273,  -273,  -273,   198,  -273,  -273,   327,   198,   328,
     -47,  -273,   -47,   -47,   332,    13,   336,   -47,  -273,   338,
    -273
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    19,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     3,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,     2,     4,    10,     0,     7,     8,     9,     0,     0,
      12,     0,     0,     0,    16,     0,     0,    24,     0,     0,
       0,    21,    34,     0,     0,     0,     0,    26,    44,     0,
       0,     0,     0,     0,     0,    36,    55,     0,     0,     0,
       0,     0,     0,     0,    46,    70,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,   103,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    85,
     111,     0,     0,     0,     0,     0,   105,    83,     0,     0,
       0,     0,     0,     0,     0,    72,     0,     0,     5,    20,
       0,     0,     0,     6,    25,     0,     0,     0,     0,     0,
      11,    35,     0,     0,     0,     0,     0,     0,    13,    45,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    14,
      56,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    17,    84,     0,     0,     0,     0,    18,   104,     0,
       0,     0,     0,     0,     0,    15,    71,    22,    23,    27,
      28,    29,    30,    31,   152,   153,   151,    32,    33,    37,
      38,    39,     0,    40,    41,    42,    43,    48,    47,    49,
      50,    51,    52,    53,    62,    63,    61,    64,    59,    58,
      65,    66,    67,    60,    68,    69,    90,    88,    87,    89,
      86,    95,    99,    97,    96,    98,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   102,     0,    93,    92,    91,
      94,   100,   101,   106,   109,   107,   108,    80,    81,    82,
      74,     0,    75,    76,    77,    78,    79,    73,     0,   145,
     146,   147,   148,   144,    54,   142,   143,     0,   110,     0,
       0,   141,     0,     0,     0,     0,     0,     0,   150,     0,
     149
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -273,  -273,   330,  -273,   296,  -273,   291,  -273,   284,  -273,
     276,  -273,   265,  -273,   237,  -273,   254,  -273,   248,  -273,
      90,  -272,  -273,    85,   -76,  -122
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    15,    16,    50,    51,    56,    57,    64,    65,    73,
      74,    85,    86,   114,   115,    98,    99,   105,   106,   255,
     284,   285,   286,   193,   258,   187
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     188,   192,   167,   100,   256,   149,    75,   196,   271,   107,
      17,    43,   291,   201,   100,    76,   291,   108,    75,   298,
      77,    18,   297,   212,    32,   214,   215,    76,   118,    47,
      19,   221,    77,    48,    49,   259,   260,   101,    20,    78,
      79,    80,    81,   109,    82,   110,   111,   112,   101,   273,
     275,    78,    79,    80,    81,    47,    82,   138,    66,    48,
      49,   123,    52,   184,   185,   186,   113,   102,   103,   104,
     278,    53,    67,    83,    84,    21,   223,   224,   102,   103,
     104,   225,    35,    36,    66,    83,    84,   189,   190,   191,
      54,    55,    68,    69,    70,   272,   274,    71,    67,   204,
     205,   206,    22,   175,   107,    23,   184,   185,   186,   184,
     185,   186,   108,   184,   185,   186,    30,    44,    68,    69,
      70,    24,    72,    71,    25,     1,     2,     3,     4,    26,
      52,     5,     6,     7,   287,     8,    27,    28,   109,    53,
     110,   111,   112,   161,    87,   267,   268,   269,    72,   289,
      29,    33,    34,    88,    37,     9,    10,    11,    54,    55,
      87,   113,    38,    39,    12,    13,    14,    58,   294,    88,
     295,   296,    40,    41,    42,   299,    59,    45,    89,    46,
     116,    60,    61,    62,    63,   117,    90,   120,   121,    91,
      92,    93,   122,   125,    89,    94,   177,   126,    95,    96,
      97,   127,    90,   128,   129,    91,    92,    93,   132,   133,
     134,    94,   194,   195,    95,    96,    97,   197,   135,   199,
     200,   179,   180,   181,   182,   183,   207,   136,   178,   210,
     211,   213,   137,     1,     2,     3,     4,   130,    58,     5,
       6,     7,   257,     8,   140,   216,   217,    59,   218,   219,
     141,   142,    60,    61,    62,    63,   143,   144,   276,   145,
     146,   147,   148,     9,    10,    11,   279,   280,   281,   282,
     283,   151,    12,    13,    14,   226,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   163,   164,   165,   166,   169,   170,   171,
     172,   173,   174,   198,   192,   202,   203,   208,   209,   220,
     290,   222,   261,   262,   263,   264,   292,   293,   265,   266,
     270,   297,   298,   277,   300,    31,   119,   124,   131,   139,
     150,   176,   162,   168,   288
};

static const yytype_uint16 yycheck[] =
{
     122,     5,     8,     9,     5,     8,     9,   129,     5,     9,
       4,     7,   284,   135,     9,    18,   288,    17,     9,     6,
      23,     4,     9,   145,   113,   147,   148,    18,     8,     9,
       4,   153,    23,    13,    14,   157,   158,    43,     4,    42,
      43,    44,    45,    43,    47,    45,    46,    47,    43,   171,
     172,    42,    43,    44,    45,     9,    47,     8,     9,    13,
      14,     8,     9,   110,   111,   112,    66,    73,    74,    75,
     192,    18,    23,    76,    77,     4,    52,    53,    73,    74,
      75,    57,    27,    28,     9,    76,    77,    20,    21,    22,
      37,    38,    43,    44,    45,   171,   172,    48,    23,    78,
      79,    80,     4,     8,     9,     4,   110,   111,   112,   110,
     111,   112,    17,   110,   111,   112,     0,   113,    43,    44,
      45,     4,    73,    48,     4,     9,    10,    11,    12,     4,
       9,    15,    16,    17,   256,    19,     4,     4,    43,    18,
      45,    46,    47,     8,     9,    34,    35,    36,    73,   271,
       4,    67,     7,    18,   110,    39,    40,    41,    37,    38,
       9,    66,     7,     7,    48,    49,    50,     9,   290,    18,
     292,   293,   113,     7,     7,   297,    18,     7,    43,     7,
       4,    23,    24,    25,    26,     4,    51,     4,     4,    54,
      55,    56,     4,     4,    43,    60,   110,     4,    63,    64,
      65,     4,    51,     4,     4,    54,    55,    56,     4,     4,
       4,    60,   127,   128,    63,    64,    65,   132,     4,   134,
     135,    29,    30,    31,    32,    33,   141,     4,   110,   144,
     145,   146,     4,     9,    10,    11,    12,     8,     9,    15,
      16,    17,   157,    19,     4,    58,    59,    18,    61,    62,
       4,     4,    23,    24,    25,    26,     4,     4,   173,     4,
       4,     4,     4,    39,    40,    41,    68,    69,    70,    71,
      72,     4,    48,    49,    50,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   113,     5,   113,   113,   110,   113,   113,
       9,   113,   113,   113,   113,   113,     9,     9,   113,   113,
     113,     9,     6,   113,     6,    15,    50,    56,    64,    73,
      85,   114,    98,   105,   264
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    11,    12,    15,    16,    17,    19,    39,
      40,    41,    48,    49,    50,   115,   116,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       0,   116,   113,    67,     7,    27,    28,   110,     7,     7,
     113,     7,     7,     7,   113,     7,     7,     9,    13,    14,
     117,   118,     9,    18,    37,    38,   119,   120,     9,    18,
      23,    24,    25,    26,   121,   122,     9,    23,    43,    44,
      45,    48,    73,   123,   124,     9,    18,    23,    42,    43,
      44,    45,    47,    76,    77,   125,   126,     9,    18,    43,
      51,    54,    55,    56,    60,    63,    64,    65,   129,   130,
       9,    43,    73,    74,    75,   131,   132,     9,    17,    43,
      45,    46,    47,    66,   127,   128,     4,     4,     8,   118,
       4,     4,     4,     8,   120,     4,     4,     4,     4,     4,
       8,   122,     4,     4,     4,     4,     4,     4,     8,   124,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     8,
     126,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     8,   130,     4,     4,     4,     4,     8,   132,     4,
       4,     4,     4,     4,     4,     8,   128,   110,   110,    29,
      30,    31,    32,    33,   110,   111,   112,   139,   139,    20,
      21,    22,     5,   137,   137,   137,   139,   137,   113,   137,
     137,   139,   113,   113,    78,    79,    80,   137,   110,   113,
     137,   137,   139,   137,   139,   139,    58,    59,    61,    62,
     113,   139,   113,    52,    53,    57,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   133,     5,   137,   138,   139,
     139,   113,   113,   113,   113,   113,   113,    34,    35,    36,
     113,     5,   138,   139,   138,   139,   137,   113,   139,    68,
      69,    70,    71,    72,   134,   135,   136,   139,   134,   139,
       9,   135,     9,     9,   139,   139,   139,     9,     6,   139,
       6
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   114,   115,   115,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     117,   117,   118,   118,   118,   119,   119,   120,   120,   120,
     120,   120,   120,   120,   120,   121,   121,   122,   122,   122,
     122,   122,   122,   122,   122,   123,   123,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   125,   125,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   127,   127,   128,   128,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   129,   129,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   131,   131,   132,   132,   132,   132,
     132,   132,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   133,   133,
     133,   134,   134,   135,   135,   136,   136,   136,   136,   137,
     138,   139,   139,   139
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,     1,     3,     5,     5,     3,     3,     3,
       3,     5,     3,     5,     5,     5,     3,     5,     5,     1,
       2,     1,     3,     3,     1,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     4,     1,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     2,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     2,     1,     3,     3,     3,     3,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     1,     1,     1,     1,     1,     7,
       5,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
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

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
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
    default: /* Avoid compiler warnings. */
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

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

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
      yychar = yylex ();
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
  *++yylsp = yylloc;
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
        case 4:
#line 156 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->output,(yyvsp[0].sval));}
#line 1705 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 7:
#line 159 "config_parser.y" /* yacc.c:1666  */
    {parsed->sampler_type = RANDOM;}
#line 1711 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 8:
#line 160 "config_parser.y" /* yacc.c:1666  */
    {parsed->sampler_type = STRATIFIED;}
#line 1717 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 9:
#line 161 "config_parser.y" /* yacc.c:1666  */
    {parsed->spp = (yyvsp[0].uval);}
#line 1723 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 10:
#line 162 "config_parser.y" /* yacc.c:1666  */
    {/* path_trace is the only available and dflt */}
#line 1729 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 11:
#line 163 "config_parser.y" /* yacc.c:1666  */
    {/* camera depends on resolution */}
#line 1735 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 12:
#line 164 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableStack(&(parsed->parsed_mesh_object),(yyvsp[0].sval));}
#line 1741 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 13:
#line 165 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableParsed(&
(parsed->parsed_mesh_world),&(parsed->cur_mesh));init_ParsedMeshWorld(&(parsed->cur_mesh.mesh));}
#line 1748 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 14:
#line 167 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableParsed(&
(parsed->parsed_lights),&(parsed->cur_light));init_ParsedLight(&(parsed->cur_light.light));}
#line 1755 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 15:
#line 169 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableParsed(&
(parsed->parsed_textures),&(parsed->cur_tex));init_ParsedTexture(&(parsed->cur_tex.tex));}
#line 1762 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 16:
#line 171 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableStack(&(parsed->children),(yyvsp[0].sval));}
#line 1768 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 17:
#line 172 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableParsed(&(parsed->parsed_materials),&(parsed->cur_mat));init_ParsedMaterial(&(parsed->cur_mat.mat));}
#line 1774 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 18:
#line 173 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableParsed(&
(parsed->parsed_dualmaterials),&(parsed->cur_dualmat));init_ParsedDualMaterial(&(parsed->cur_dualmat.dualmat));}
#line 1781 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 22:
#line 180 "config_parser.y" /* yacc.c:1666  */
    {parsed->width = (yyvsp[0].uval);}
#line 1787 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 23:
#line 181 "config_parser.y" /* yacc.c:1666  */
    {parsed->height = (yyvsp[0].uval);}
#line 1793 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 27:
#line 187 "config_parser.y" /* yacc.c:1666  */
    {parsed->filter_type = BOX;}
#line 1799 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 28:
#line 188 "config_parser.y" /* yacc.c:1666  */
    {parsed->filter_type = TENT;}
#line 1805 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 29:
#line 189 "config_parser.y" /* yacc.c:1666  */
    {parsed->filter_type = GAUSS;}
#line 1811 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 30:
#line 190 "config_parser.y" /* yacc.c:1666  */
    {parsed->filter_type = MITCHELL;}
#line 1817 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 31:
#line 191 "config_parser.y" /* yacc.c:1666  */
    {parsed->filter_type = LANCZOS;}
#line 1823 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 32:
#line 192 "config_parser.y" /* yacc.c:1666  */
    {parsed->value0 = (yyvsp[0].fval);}
#line 1829 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 33:
#line 193 "config_parser.y" /* yacc.c:1666  */
    {parsed->value1 = (yyvsp[0].fval);}
#line 1835 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 37:
#line 199 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_type = ORTHOGRAPHIC;}
#line 1841 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 38:
#line 200 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_type = PERSPECTIVE;}
#line 1847 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 39:
#line 201 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_type = PANORAMA;}
#line 1853 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 40:
#line 202 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_pos[0] = vec[0];parsed->camera_pos[1] = vec[1];parsed->camera_pos[2] = vec[2];}
#line 1859 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 41:
#line 203 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_tar[0] = vec[0];parsed->camera_tar[1] = vec[1];parsed->camera_tar[2] = vec[2];}
#line 1865 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 42:
#line 204 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_up[0] = vec[0];parsed->camera_up[1] = vec[1];parsed->camera_up[2] = vec[2];}
#line 1871 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 43:
#line 205 "config_parser.y" /* yacc.c:1666  */
    {parsed->fov = (yyvsp[0].fval);}
#line 1877 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 47:
#line 211 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mesh.mesh.name,(yyvsp[0].sval));}
#line 1883 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 48:
#line 212 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mesh.mesh.position[0] = vec[0];parsed->cur_mesh.mesh.position[1] = vec[1];parsed->cur_mesh.mesh.position[2] = vec[2];}
#line 1889 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 49:
#line 213 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mesh.mesh.rotation[0] = vec[0];parsed->cur_mesh.mesh.rotation[1] = vec[1];parsed->cur_mesh.mesh.rotation[2] = vec[2];}
#line 1895 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 50:
#line 214 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mesh.mesh.scale[0] = vec[0];parsed->cur_mesh.mesh.scale[1] = vec[1];parsed->cur_mesh.mesh.scale[2] = vec[2];}
#line 1901 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 51:
#line 215 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mesh.mesh.scale[0] = (yyvsp[0].fval);parsed->cur_mesh.mesh.scale[1] = (yyvsp[0].fval);parsed->cur_mesh.mesh.scale[2] = (yyvsp[0].fval);}
#line 1907 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 52:
#line 216 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mesh.mesh.material_name,(yyvsp[0].sval));}
#line 1913 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 53:
#line 217 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mask.mask_tex,(yyvsp[0].sval)); parsed->cur_mesh.mesh.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
#line 1919 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 54:
#line 218 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mask.mask_tex,(yyvsp[-1].sval)); parsed->cur_mesh.mesh.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
#line 1925 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 58:
#line 224 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_light.light.name,(yyvsp[0].sval));}
#line 1931 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 59:
#line 225 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.temperature = (yyvsp[0].uval);}
#line 1937 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 60:
#line 226 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.color[0] = vec[0];parsed->cur_light.light.color[1] = vec[1];parsed->cur_light.light.color[2] = vec[2];}
#line 1943 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 61:
#line 227 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.type = AREA;}
#line 1949 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 62:
#line 228 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.type = OMNI;}
#line 1955 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 63:
#line 229 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.type = SPOT;}
#line 1961 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 64:
#line 230 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.position[0] = vec[0];parsed->cur_light.light.position[1] = vec[1];parsed->cur_light.light.position[2] = vec[2];}
#line 1967 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 65:
#line 231 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mesh.mesh.rotation[0] = vec[0];parsed->cur_mesh.mesh.rotation[1] = vec[1];parsed->cur_mesh.mesh.rotation[2] = vec[2];}
#line 1973 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 66:
#line 232 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.scale[0] = vec[0];parsed->cur_light.light.scale[1] = vec[1];parsed->cur_light.light.scale[2] = vec[2];}
#line 1979 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 67:
#line 233 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.scale[0] = (yyvsp[0].fval);parsed->cur_light.light.scale[1] = (yyvsp[0].fval);parsed->cur_light.light.scale[2] = (yyvsp[0].fval);}
#line 1985 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 68:
#line 234 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.radius = (yyvsp[0].fval);}
#line 1991 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 69:
#line 235 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.falloff = (yyvsp[0].fval);}
#line 1997 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 73:
#line 241 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_tex.tex.name,(yyvsp[0].sval));}
#line 2003 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 74:
#line 242 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_tex.tex.src,(yyvsp[0].sval));}
#line 2009 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 75:
#line 243 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.scale[0] = vec[0]; parsed->cur_tex.tex.scale[1]=vec[1];}
#line 2015 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 76:
#line 244 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.scale[0] = (yyvsp[0].fval); parsed->cur_tex.tex.scale[1]=(yyvsp[0].fval);}
#line 2021 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 77:
#line 245 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.shift[0] = vec[0]; parsed->cur_tex.tex.shift[1]=vec[1];}
#line 2027 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 78:
#line 246 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.shift[0] = (yyvsp[0].fval); parsed->cur_tex.tex.shift[1]=(yyvsp[0].fval);}
#line 2033 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 79:
#line 247 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.color[0] = vec[0]; parsed->cur_tex.tex.color[1] = vec[1]; parsed->cur_tex.tex.color[2] = vec[2];}
#line 2039 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 80:
#line 248 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.filter = UNFILTERED;}
#line 2045 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 81:
#line 249 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.filter = TRILINEAR;}
#line 2051 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 82:
#line 250 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.filter = EWA;}
#line 2057 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 86:
#line 256 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mat.mat.name,(yyvsp[0].sval));}
#line 2063 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 87:
#line 257 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.type = MATTE;}
#line 2069 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 88:
#line 258 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.type = GLOSSY;}
#line 2075 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 89:
#line 259 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.type = METAL;}
#line 2081 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 90:
#line 260 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.type = GLASS;}
#line 2087 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 91:
#line 261 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.ior[0] = (yyvsp[0].fval); parsed->cur_mat.mat.ior[1] = 0.f; parsed->cur_mat.mat.ior[2] = 0.f;}
#line 2093 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 92:
#line 262 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.ior[0] = vec[0]; parsed->cur_mat.mat.ior[1] = vec[1]; parsed->cur_mat.mat.ior[2] = 0.f;}
#line 2099 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 93:
#line 263 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.ior[0] = vec[0]; parsed->cur_mat.mat.ior[1] = vec[1]; parsed->cur_mat.mat.ior[2] = vec[2];}
#line 2105 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 94:
#line 264 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.rough_x = (yyvsp[0].fval);}
#line 2111 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 95:
#line 265 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.rough_y = (yyvsp[0].fval);}
#line 2117 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 96:
#line 266 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.dist = BLINN;}
#line 2123 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 97:
#line 267 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.dist = BECKMANN;}
#line 2129 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 98:
#line 268 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.dist = GGX;}
#line 2135 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 99:
#line 269 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mat.mat.diffuse,(yyvsp[0].sval));}
#line 2141 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 100:
#line 270 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mat.mat.specular,(yyvsp[0].sval));}
#line 2147 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 101:
#line 271 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mat.mat.normal,(yyvsp[0].sval));}
#line 2153 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 102:
#line 272 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.elem = (yyvsp[0].ival);}
#line 2159 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 106:
#line 278 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_dualmat.dualmat.name,(yyvsp[0].sval));}
#line 2165 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 107:
#line 279 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_dualmat.dualmat.first,(yyvsp[0].sval));}
#line 2171 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 108:
#line 280 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_dualmat.dualmat.second,(yyvsp[0].sval));}
#line 2177 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 109:
#line 281 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mask.mask_tex,(yyvsp[0].sval));parsed->cur_dualmat.dualmat.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
#line 2183 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 110:
#line 282 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mask.mask_tex,(yyvsp[-1].sval)); parsed->cur_dualmat.dualmat.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
#line 2189 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 112:
#line 290 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_SILVER; }
#line 2195 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 113:
#line 291 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_ALUMINIUM; }
#line 2201 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 114:
#line 292 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_GOLD; }
#line 2207 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 115:
#line 293 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_COPPER; }
#line 2213 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 116:
#line 294 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_IRON; }
#line 2219 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 117:
#line 295 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_MERCURY; }
#line 2225 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 118:
#line 296 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_LEAD; }
#line 2231 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 119:
#line 297 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_PLATINUM; }
#line 2237 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 120:
#line 298 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_TUNGSTEN; }
#line 2243 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 121:
#line 299 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_BERYLLIUM; }
#line 2249 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 122:
#line 300 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_BISMUTH; }
#line 2255 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 123:
#line 301 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_COBALT; }
#line 2261 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 124:
#line 302 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_CHROMIUM; }
#line 2267 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 125:
#line 303 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_GERMANIUM; }
#line 2273 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 126:
#line 304 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_POTASSIUM; }
#line 2279 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 127:
#line 305 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_LITHIUM; }
#line 2285 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 128:
#line 306 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_MAGNESIUM; }
#line 2291 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 129:
#line 307 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_MANGANESE; }
#line 2297 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 130:
#line 308 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_MOLYBDENUM; }
#line 2303 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 131:
#line 309 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_SODIUM; }
#line 2309 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 132:
#line 310 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_NIOBIUM; }
#line 2315 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 133:
#line 311 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_NICKEL; }
#line 2321 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 134:
#line 312 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_PALLADIUM; }
#line 2327 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 135:
#line 313 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_RHODIUM; }
#line 2333 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 136:
#line 314 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_TANTALUM; }
#line 2339 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 137:
#line 315 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_TITANIUM; }
#line 2345 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 138:
#line 316 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_VANADIUM; }
#line 2351 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 139:
#line 317 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_ZINC; }
#line 2357 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 140:
#line 318 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_ZIRCONIUM; }
#line 2363 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 143:
#line 324 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mask.mask_chn = (yyvsp[0].ival);}
#line 2369 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 144:
#line 325 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mask.mask_inv = 1;}
#line 2375 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 145:
#line 329 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = RED;}
#line 2381 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 146:
#line 330 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = GREEN;}
#line 2387 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 147:
#line 331 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = BLUE;}
#line 2393 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 148:
#line 332 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = ALPHA;}
#line 2399 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 149:
#line 337 "config_parser.y" /* yacc.c:1666  */
    {vec[0] = (yyvsp[-5].fval); vec[1] = (yyvsp[-3].fval); vec[2] = (yyvsp[-1].fval);}
#line 2405 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 150:
#line 341 "config_parser.y" /* yacc.c:1666  */
    {vec[0] = (yyvsp[-3].fval); vec[1] = (yyvsp[-1].fval);}
#line 2411 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 151:
#line 345 "config_parser.y" /* yacc.c:1666  */
    {(yyval.fval) = (yyvsp[0].fval);}
#line 2417 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 152:
#line 346 "config_parser.y" /* yacc.c:1666  */
    {(yyval.fval) = (float)(yyvsp[0].uval);}
#line 2423 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 153:
#line 347 "config_parser.y" /* yacc.c:1666  */
    {(yyval.fval) = (float)(yyvsp[0].ival);}
#line 2429 "config_parser.tab.c" /* yacc.c:1666  */
    break;


#line 2433 "config_parser.tab.c" /* yacc.c:1666  */
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
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
  return yyresult;
}
#line 350 "config_parser.y" /* yacc.c:1910  */


/* parse the scene, given an already opened file that will not be closed and a scene already initialized */
void parse_config(FILE* opened_file, struct ParsedScene* scene_initialized)
{
    yyin = opened_file;
    parsed = scene_initialized;
    yyparse();
}

void yyerror (const char* msg)
{
    printf("error");
    /* driver.error(l,m); */
}
