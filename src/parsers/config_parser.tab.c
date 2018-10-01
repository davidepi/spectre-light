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
    extern int config_get_line(char* buf, int len);
    int yylex(void);
    void yyerror(char const*);
    void parse_config(FILE* opened_file, struct ParsedScene* scene_initialized);
    struct ParsedScene* parsed;
    float vec[3];
    /* add a string to the Parsed data and avoid a leak if overwriting */
    #define ADD_STRING(DST,SRC) if(DST==NULL)free(DST);DST=SRC;

#line 80 "config_parser.tab.c" /* yacc.c:339  */

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
#line 132 "config_parser.y" /* yacc.c:355  */

    float fval;
    int ival;
    unsigned int uval;
    char* sval;

#line 242 "config_parser.tab.c" /* yacc.c:355  */
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

#line 273 "config_parser.tab.c" /* yacc.c:358  */

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
#define YYFINAL  31
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   341

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  114
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  154
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  302

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
       0,   151,   151,   154,   155,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   170,   172,   174,   175,   176,
     178,   181,   181,   183,   184,   185,   188,   188,   190,   191,
     192,   193,   194,   195,   196,   197,   200,   200,   202,   203,
     204,   205,   206,   207,   208,   209,   212,   212,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   225,   225,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   242,   242,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   253,   254,   257,   257,   259,   260,   261,
     262,   263,   264,   265,   266,   267,   268,   269,   270,   271,
     272,   273,   274,   275,   276,   279,   279,   281,   282,   283,
     284,   285,   286,   293,   294,   295,   296,   297,   298,   299,
     300,   301,   302,   303,   304,   305,   306,   307,   308,   309,
     310,   311,   312,   313,   314,   315,   316,   317,   318,   319,
     320,   321,   324,   324,   327,   328,   332,   333,   334,   335,
     339,   344,   348,   349,   350
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
  "\"floating point value\"", "\"quoted string\"", "$accept", "config",
  "file", "stmt", "resolution_obj", "resolution_stmt", "filter_obj",
  "filter_stmt", "camera_obj", "camera_stmt", "world_obj", "world_stmt",
  "light_obj", "light_stmt", "texture_obj", "texture_stmt", "material_obj",
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

#define YYPACT_NINF -274

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-274)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     116,  -274,     6,    17,    26,    34,    71,    98,   101,   112,
     117,   120,   125,   132,   133,   150,   116,  -274,   -89,    85,
     144,    55,    44,   155,   156,    59,   167,   170,     4,   172,
     173,  -274,  -274,  -274,  -274,    46,  -274,  -274,  -274,   121,
     158,  -274,    75,     9,   151,  -274,     5,     0,  -274,   169,
     183,    20,  -274,  -274,   184,   188,   189,    53,  -274,  -274,
     192,   193,   197,   199,   200,   214,  -274,  -274,   204,   205,
     206,   217,   229,   230,    49,  -274,  -274,   231,   232,   237,
     239,   250,   251,   252,   253,   284,    -3,  -274,  -274,   285,
     286,   287,   288,   289,   290,   291,   292,   293,   294,   135,
    -274,  -274,   295,   296,   297,   298,    -6,  -274,  -274,   299,
     300,   301,   302,   303,   304,    95,  -274,   108,   201,  -274,
    -274,   215,   -47,   -47,  -274,  -274,    67,   180,   180,   180,
     -47,  -274,  -274,   180,   196,   180,    -4,   202,   203,  -274,
    -274,    21,   180,   207,   208,   180,    -4,   180,   -47,   -47,
    -274,  -274,   166,   209,   -47,   210,    24,   178,    -1,   -47,
     211,   212,  -274,  -274,   213,   216,   218,   219,  -274,  -274,
     111,   220,     3,     3,   180,   221,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,   -47,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,   181,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,  -274,  -274,   -47,  -274,  -274,
    -274,  -274,  -274,  -274,  -274,   181,  -274,  -274,  -274,  -274,
    -274,  -274,   -47,  -274,  -274,  -274,  -274,  -274,  -274,   305,
    -274,  -274,  -274,  -274,  -274,   181,  -274,  -274,   309,   181,
     310,   -47,  -274,   -47,   -47,   311,    13,   306,   -47,  -274,
     307,  -274
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     4,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     1,     3,     5,    11,     0,     8,     9,    10,     0,
       0,    13,     0,     0,     0,    17,     0,     0,    25,     0,
       0,     0,    22,    35,     0,     0,     0,     0,    27,    45,
       0,     0,     0,     0,     0,     0,    37,    56,     0,     0,
       0,     0,     0,     0,     0,    47,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    58,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      86,   112,     0,     0,     0,     0,     0,   106,    84,     0,
       0,     0,     0,     0,     0,     0,    73,     0,     0,     6,
      21,     0,     0,     0,     7,    26,     0,     0,     0,     0,
       0,    12,    36,     0,     0,     0,     0,     0,     0,    14,
      46,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      15,    57,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    18,    85,     0,     0,     0,     0,    19,   105,
       0,     0,     0,     0,     0,     0,    16,    72,    23,    24,
      28,    29,    30,    31,    32,   153,   154,   152,    33,    34,
      38,    39,    40,     0,    41,    42,    43,    44,    49,    48,
      50,    51,    52,    53,    54,    63,    64,    62,    65,    60,
      59,    66,    67,    68,    61,    69,    70,    91,    89,    88,
      90,    87,    96,   100,    98,    97,    99,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,   103,     0,    94,    93,
      92,    95,   101,   102,   107,   110,   108,   109,    81,    82,
      83,    75,     0,    76,    77,    78,    79,    80,    74,     0,
     146,   147,   148,   149,   145,    55,   143,   144,     0,   111,
       0,     0,   142,     0,     0,     0,     0,     0,     0,   151,
       0,   150
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -274,  -274,  -274,   312,  -274,   259,  -274,   270,  -274,   265,
    -274,   261,  -274,   254,  -274,   222,  -274,   240,  -274,   235,
    -274,    73,  -273,  -274,    84,   -77,  -123
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    15,    16,    17,    51,    52,    57,    58,    65,    66,
      74,    75,    86,    87,   115,   116,    99,   100,   106,   107,
     256,   285,   286,   287,   194,   259,   188
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
     189,   193,   168,   101,   257,   150,    76,   197,   272,   108,
      18,    44,   292,   202,   101,    77,   292,   109,    76,   299,
      78,    19,   298,   213,    33,   215,   216,    77,   119,    48,
      20,   222,    78,    49,    50,   260,   261,   102,    21,    79,
      80,    81,    82,   110,    83,   111,   112,   113,   102,   274,
     276,    79,    80,    81,    82,    48,    83,   139,    67,    49,
      50,   124,    53,   185,   186,   187,   114,   103,   104,   105,
     279,    54,    68,    84,    85,    22,   224,   225,   103,   104,
     105,   226,    36,    37,    67,    84,    85,   190,   191,   192,
      55,    56,    69,    70,    71,   273,   275,    72,    68,   205,
     206,   207,    23,   176,   108,    24,   185,   186,   187,   185,
     186,   187,   109,   185,   186,   187,    25,    45,    69,    70,
      71,    26,    73,    72,    27,     1,     2,     3,     4,    28,
      53,     5,     6,     7,   288,     8,    29,    30,   110,    54,
     111,   112,   113,   162,    88,   268,   269,   270,    73,   290,
      31,    35,    34,    89,    38,     9,    10,    11,    55,    56,
      88,   114,    39,    40,    12,    13,    14,    59,   295,    89,
     296,   297,    41,   117,    42,   300,    60,    43,    90,    46,
      47,    61,    62,    63,    64,   193,    91,   118,   121,    92,
      93,    94,   122,   123,    90,    95,   126,   127,    96,    97,
      98,   128,    91,   129,   130,    92,    93,    94,   133,   134,
     135,    95,   195,   196,    96,    97,    98,   198,   178,   200,
     201,   136,   131,    59,   217,   218,   208,   219,   220,   211,
     212,   214,    60,   137,   138,   141,   142,    61,    62,    63,
      64,   143,   258,   144,   180,   181,   182,   183,   184,   280,
     281,   282,   283,   284,   145,   146,   147,   148,   277,   227,
     228,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   149,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   164,
     165,   166,   167,   170,   171,   172,   173,   174,   175,   199,
     120,   179,   299,   301,   291,   203,   204,   209,   293,   294,
     298,   210,   221,   223,   262,   263,   264,   125,    32,   265,
     132,   266,   267,   271,   278,   140,     0,   177,   289,   163,
     151,   169
};

static const yytype_int16 yycheck[] =
{
     123,     5,     8,     9,     5,     8,     9,   130,     5,     9,
       4,     7,   285,   136,     9,    18,   289,    17,     9,     6,
      23,     4,     9,   146,   113,   148,   149,    18,     8,     9,
       4,   154,    23,    13,    14,   158,   159,    43,     4,    42,
      43,    44,    45,    43,    47,    45,    46,    47,    43,   172,
     173,    42,    43,    44,    45,     9,    47,     8,     9,    13,
      14,     8,     9,   110,   111,   112,    66,    73,    74,    75,
     193,    18,    23,    76,    77,     4,    52,    53,    73,    74,
      75,    57,    27,    28,     9,    76,    77,    20,    21,    22,
      37,    38,    43,    44,    45,   172,   173,    48,    23,    78,
      79,    80,     4,     8,     9,     4,   110,   111,   112,   110,
     111,   112,    17,   110,   111,   112,     4,   113,    43,    44,
      45,     4,    73,    48,     4,     9,    10,    11,    12,     4,
       9,    15,    16,    17,   257,    19,     4,     4,    43,    18,
      45,    46,    47,     8,     9,    34,    35,    36,    73,   272,
       0,     7,    67,    18,   110,    39,    40,    41,    37,    38,
       9,    66,     7,     7,    48,    49,    50,     9,   291,    18,
     293,   294,   113,     4,     7,   298,    18,     7,    43,     7,
       7,    23,    24,    25,    26,     5,    51,     4,     4,    54,
      55,    56,     4,     4,    43,    60,     4,     4,    63,    64,
      65,     4,    51,     4,     4,    54,    55,    56,     4,     4,
       4,    60,   128,   129,    63,    64,    65,   133,   110,   135,
     136,     4,     8,     9,    58,    59,   142,    61,    62,   145,
     146,   147,    18,     4,     4,     4,     4,    23,    24,    25,
      26,     4,   158,     4,    29,    30,    31,    32,    33,    68,
      69,    70,    71,    72,     4,     4,     4,     4,   174,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   113,
      51,   110,     6,     6,     9,   113,   113,   110,     9,     9,
       9,   113,   113,   113,   113,   113,   113,    57,    16,   113,
      65,   113,   113,   113,   113,    74,    -1,   115,   265,    99,
      86,   106
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    11,    12,    15,    16,    17,    19,    39,
      40,    41,    48,    49,    50,   115,   116,   117,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     0,   117,   113,    67,     7,    27,    28,   110,     7,
       7,   113,     7,     7,     7,   113,     7,     7,     9,    13,
      14,   118,   119,     9,    18,    37,    38,   120,   121,     9,
      18,    23,    24,    25,    26,   122,   123,     9,    23,    43,
      44,    45,    48,    73,   124,   125,     9,    18,    23,    42,
      43,    44,    45,    47,    76,    77,   126,   127,     9,    18,
      43,    51,    54,    55,    56,    60,    63,    64,    65,   130,
     131,     9,    43,    73,    74,    75,   132,   133,     9,    17,
      43,    45,    46,    47,    66,   128,   129,     4,     4,     8,
     119,     4,     4,     4,     8,   121,     4,     4,     4,     4,
       4,     8,   123,     4,     4,     4,     4,     4,     4,     8,
     125,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       8,   127,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     8,   131,     4,     4,     4,     4,     8,   133,
       4,     4,     4,     4,     4,     4,     8,   129,   110,   110,
      29,    30,    31,    32,    33,   110,   111,   112,   140,   140,
      20,    21,    22,     5,   138,   138,   138,   140,   138,   113,
     138,   138,   140,   113,   113,    78,    79,    80,   138,   110,
     113,   138,   138,   140,   138,   140,   140,    58,    59,    61,
      62,   113,   140,   113,    52,    53,    57,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   134,     5,   138,   139,
     140,   140,   113,   113,   113,   113,   113,   113,    34,    35,
      36,   113,     5,   139,   140,   139,   140,   138,   113,   140,
      68,    69,    70,    71,    72,   135,   136,   137,   140,   135,
     140,     9,   136,     9,     9,   140,   140,   140,     9,     6,
     140,     6
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,   114,   115,   116,   116,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   118,   119,   119,   119,   120,   120,   121,   121,
     121,   121,   121,   121,   121,   121,   122,   122,   123,   123,
     123,   123,   123,   123,   123,   123,   124,   124,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   126,   126,   127,
     127,   127,   127,   127,   127,   127,   127,   127,   127,   127,
     127,   127,   128,   128,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   130,   130,   131,   131,   131,
     131,   131,   131,   131,   131,   131,   131,   131,   131,   131,
     131,   131,   131,   131,   131,   132,   132,   133,   133,   133,
     133,   133,   133,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   135,   135,   136,   136,   137,   137,   137,   137,
     138,   139,   140,   140,   140
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     1,     3,     5,     5,     3,     3,
       3,     3,     5,     3,     5,     5,     5,     3,     5,     5,
       1,     2,     1,     3,     3,     1,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     1,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     1,     2,     1,     3,     3,
       3,     3,     3,     3,     3,     4,     1,     2,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     2,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     2,     1,     3,     3,     3,
       3,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       7,     5,     1,     1,     1
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
        case 2:
#line 151 "config_parser.y" /* yacc.c:1666  */
    {parsed->successful = 1;}
#line 1704 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 5:
#line 159 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->output,(yyvsp[0].sval));}
#line 1710 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 8:
#line 162 "config_parser.y" /* yacc.c:1666  */
    {parsed->sampler_type = RANDOM;}
#line 1716 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 9:
#line 163 "config_parser.y" /* yacc.c:1666  */
    {parsed->sampler_type = STRATIFIED;}
#line 1722 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 10:
#line 164 "config_parser.y" /* yacc.c:1666  */
    {parsed->spp = (yyvsp[0].uval);}
#line 1728 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 11:
#line 165 "config_parser.y" /* yacc.c:1666  */
    {/* path_trace is the only available and dflt */}
#line 1734 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 12:
#line 166 "config_parser.y" /* yacc.c:1666  */
    {/* camera depends on resolution */}
#line 1740 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 13:
#line 167 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableStack(&(parsed->parsed_mesh_object),(yyvsp[0].sval));}
#line 1746 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 14:
#line 168 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableParsed(&
(parsed->parsed_mesh_world),&(parsed->cur_mesh));init_ParsedMeshWorld(&(parsed->cur_mesh.mesh));}
#line 1753 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 15:
#line 170 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableParsed(&
(parsed->parsed_lights),&(parsed->cur_light));init_ParsedLight(&(parsed->cur_light.light));}
#line 1760 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 16:
#line 172 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableParsed(&
(parsed->parsed_textures),&(parsed->cur_tex));init_ParsedTexture(&(parsed->cur_tex.tex));}
#line 1767 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 17:
#line 174 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableStack(&(parsed->children),(yyvsp[0].sval));}
#line 1773 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 18:
#line 175 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableParsed(&(parsed->parsed_materials),&(parsed->cur_mat));init_ParsedMaterial(&(parsed->cur_mat.mat));}
#line 1779 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 19:
#line 176 "config_parser.y" /* yacc.c:1666  */
    {push_ResizableParsed(&
(parsed->parsed_dualmaterials),&(parsed->cur_dualmat));init_ParsedDualMaterial(&(parsed->cur_dualmat.dualmat));}
#line 1786 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 23:
#line 183 "config_parser.y" /* yacc.c:1666  */
    {parsed->width = (yyvsp[0].uval);}
#line 1792 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 24:
#line 184 "config_parser.y" /* yacc.c:1666  */
    {parsed->height = (yyvsp[0].uval);}
#line 1798 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 28:
#line 190 "config_parser.y" /* yacc.c:1666  */
    {parsed->filter_type = BOX;}
#line 1804 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 29:
#line 191 "config_parser.y" /* yacc.c:1666  */
    {parsed->filter_type = TENT;}
#line 1810 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 30:
#line 192 "config_parser.y" /* yacc.c:1666  */
    {parsed->filter_type = GAUSS;}
#line 1816 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 31:
#line 193 "config_parser.y" /* yacc.c:1666  */
    {parsed->filter_type = MITCHELL;}
#line 1822 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 32:
#line 194 "config_parser.y" /* yacc.c:1666  */
    {parsed->filter_type = LANCZOS;}
#line 1828 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 33:
#line 195 "config_parser.y" /* yacc.c:1666  */
    {parsed->value0 = (yyvsp[0].fval);}
#line 1834 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 34:
#line 196 "config_parser.y" /* yacc.c:1666  */
    {parsed->value1 = (yyvsp[0].fval);}
#line 1840 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 38:
#line 202 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_type = ORTHOGRAPHIC;}
#line 1846 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 39:
#line 203 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_type = PERSPECTIVE;}
#line 1852 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 40:
#line 204 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_type = PANORAMA;}
#line 1858 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 41:
#line 205 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_pos[0] = vec[0];parsed->camera_pos[1] = vec[1];parsed->camera_pos[2] = vec[2];}
#line 1864 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 42:
#line 206 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_tar[0] = vec[0];parsed->camera_tar[1] = vec[1];parsed->camera_tar[2] = vec[2];}
#line 1870 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 43:
#line 207 "config_parser.y" /* yacc.c:1666  */
    {parsed->camera_up[0] = vec[0];parsed->camera_up[1] = vec[1];parsed->camera_up[2] = vec[2];}
#line 1876 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 44:
#line 208 "config_parser.y" /* yacc.c:1666  */
    {parsed->fov = (yyvsp[0].fval);}
#line 1882 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 48:
#line 214 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mesh.mesh.name,(yyvsp[0].sval));}
#line 1888 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 49:
#line 215 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mesh.mesh.position[0] = vec[0];parsed->cur_mesh.mesh.position[1] = vec[1];parsed->cur_mesh.mesh.position[2] = vec[2];}
#line 1894 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 50:
#line 216 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mesh.mesh.rotation[0] = vec[0];parsed->cur_mesh.mesh.rotation[1] = vec[1];parsed->cur_mesh.mesh.rotation[2] = vec[2];}
#line 1900 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 51:
#line 217 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mesh.mesh.scale[0] = vec[0];parsed->cur_mesh.mesh.scale[1] = vec[1];parsed->cur_mesh.mesh.scale[2] = vec[2];}
#line 1906 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 52:
#line 218 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mesh.mesh.scale[0] = (yyvsp[0].fval);parsed->cur_mesh.mesh.scale[1] = (yyvsp[0].fval);parsed->cur_mesh.mesh.scale[2] = (yyvsp[0].fval);}
#line 1912 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 53:
#line 219 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mesh.mesh.material_name,(yyvsp[0].sval));}
#line 1918 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 54:
#line 220 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mask.mask_tex,(yyvsp[0].sval)); parsed->cur_mesh.mesh.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
#line 1924 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 55:
#line 221 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mask.mask_tex,(yyvsp[-1].sval)); parsed->cur_mesh.mesh.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
#line 1930 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 59:
#line 227 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_light.light.name,(yyvsp[0].sval));}
#line 1936 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 60:
#line 228 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.temperature = (yyvsp[0].uval);}
#line 1942 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 61:
#line 229 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.color[0] = vec[0];parsed->cur_light.light.color[1] = vec[1];parsed->cur_light.light.color[2] = vec[2];}
#line 1948 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 62:
#line 230 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.type = AREA;}
#line 1954 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 63:
#line 231 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.type = OMNI;}
#line 1960 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 64:
#line 232 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.type = SPOT;}
#line 1966 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 65:
#line 233 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.position[0] = vec[0];parsed->cur_light.light.position[1] = vec[1];parsed->cur_light.light.position[2] = vec[2];}
#line 1972 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 66:
#line 234 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mesh.mesh.rotation[0] = vec[0];parsed->cur_mesh.mesh.rotation[1] = vec[1];parsed->cur_mesh.mesh.rotation[2] = vec[2];}
#line 1978 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 67:
#line 235 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.scale[0] = vec[0];parsed->cur_light.light.scale[1] = vec[1];parsed->cur_light.light.scale[2] = vec[2];}
#line 1984 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 68:
#line 236 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.scale[0] = (yyvsp[0].fval);parsed->cur_light.light.scale[1] = (yyvsp[0].fval);parsed->cur_light.light.scale[2] = (yyvsp[0].fval);}
#line 1990 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 69:
#line 237 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.radius = (yyvsp[0].fval);}
#line 1996 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 70:
#line 238 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_light.light.falloff = (yyvsp[0].fval);}
#line 2002 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 74:
#line 244 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_tex.tex.src,(yyvsp[0].sval));}
#line 2008 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 75:
#line 245 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_tex.tex.name,(yyvsp[0].sval));}
#line 2014 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 76:
#line 246 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.scale[0] = vec[0]; parsed->cur_tex.tex.scale[1]=vec[1];}
#line 2020 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 77:
#line 247 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.scale[0] = (yyvsp[0].fval); parsed->cur_tex.tex.scale[1]=(yyvsp[0].fval);}
#line 2026 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 78:
#line 248 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.shift[0] = vec[0]; parsed->cur_tex.tex.shift[1]=vec[1];}
#line 2032 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 79:
#line 249 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.shift[0] = (yyvsp[0].fval); parsed->cur_tex.tex.shift[1]=(yyvsp[0].fval);}
#line 2038 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 80:
#line 250 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.color[0] = vec[0]; parsed->cur_tex.tex.color[1] = vec[1]; parsed->cur_tex.tex.color[2] = vec[2];}
#line 2044 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 81:
#line 251 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.filter = UNFILTERED;}
#line 2050 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 82:
#line 252 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.filter = TRILINEAR;}
#line 2056 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 83:
#line 253 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_tex.tex.filter = EWA;}
#line 2062 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 87:
#line 259 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mat.mat.name,(yyvsp[0].sval));}
#line 2068 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 88:
#line 260 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.type = MATTE;}
#line 2074 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 89:
#line 261 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.type = GLOSSY;}
#line 2080 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 90:
#line 262 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.type = METAL;}
#line 2086 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 91:
#line 263 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.type = GLASS;}
#line 2092 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 92:
#line 264 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.ior[0] = (yyvsp[0].fval); parsed->cur_mat.mat.ior[1] = 0.f; parsed->cur_mat.mat.ior[2] = 0.f;}
#line 2098 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 93:
#line 265 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.ior[0] = vec[0]; parsed->cur_mat.mat.ior[1] = vec[1]; parsed->cur_mat.mat.ior[2] = 0.f;}
#line 2104 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 94:
#line 266 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.ior[0] = vec[0]; parsed->cur_mat.mat.ior[1] = vec[1]; parsed->cur_mat.mat.ior[2] = vec[2];}
#line 2110 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 95:
#line 267 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.rough_x = (yyvsp[0].fval);}
#line 2116 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 96:
#line 268 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.rough_y = (yyvsp[0].fval);}
#line 2122 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 97:
#line 269 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.dist = BLINN;}
#line 2128 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 98:
#line 270 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.dist = BECKMANN;}
#line 2134 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 99:
#line 271 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.dist = GGX;}
#line 2140 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 100:
#line 272 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mat.mat.diffuse,(yyvsp[0].sval));}
#line 2146 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 101:
#line 273 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mat.mat.specular,(yyvsp[0].sval));}
#line 2152 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 102:
#line 274 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mat.mat.normal,(yyvsp[0].sval));}
#line 2158 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 103:
#line 275 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mat.mat.elem = (yyvsp[0].ival);}
#line 2164 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 107:
#line 281 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_dualmat.dualmat.name,(yyvsp[0].sval));}
#line 2170 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 108:
#line 282 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_dualmat.dualmat.first,(yyvsp[0].sval));}
#line 2176 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 109:
#line 283 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_dualmat.dualmat.second,(yyvsp[0].sval));}
#line 2182 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 110:
#line 284 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mask.mask_tex,(yyvsp[0].sval));parsed->cur_dualmat.dualmat.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
#line 2188 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 111:
#line 285 "config_parser.y" /* yacc.c:1666  */
    {ADD_STRING(parsed->cur_mask.mask_tex,(yyvsp[-1].sval)); parsed->cur_dualmat.dualmat.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
#line 2194 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 113:
#line 293 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_SILVER; }
#line 2200 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 114:
#line 294 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_ALUMINIUM; }
#line 2206 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 115:
#line 295 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_GOLD; }
#line 2212 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 116:
#line 296 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_COPPER; }
#line 2218 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 117:
#line 297 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_IRON; }
#line 2224 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 118:
#line 298 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_MERCURY; }
#line 2230 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 119:
#line 299 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_LEAD; }
#line 2236 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 120:
#line 300 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_PLATINUM; }
#line 2242 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 121:
#line 301 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_TUNGSTEN; }
#line 2248 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 122:
#line 302 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_BERYLLIUM; }
#line 2254 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 123:
#line 303 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_BISMUTH; }
#line 2260 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 124:
#line 304 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_COBALT; }
#line 2266 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 125:
#line 305 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_CHROMIUM; }
#line 2272 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 126:
#line 306 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_GERMANIUM; }
#line 2278 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 127:
#line 307 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_POTASSIUM; }
#line 2284 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 128:
#line 308 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_LITHIUM; }
#line 2290 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 129:
#line 309 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_MAGNESIUM; }
#line 2296 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 130:
#line 310 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_MANGANESE; }
#line 2302 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 131:
#line 311 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_MOLYBDENUM; }
#line 2308 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 132:
#line 312 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_SODIUM; }
#line 2314 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 133:
#line 313 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_NIOBIUM; }
#line 2320 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 134:
#line 314 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_NICKEL; }
#line 2326 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 135:
#line 315 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_PALLADIUM; }
#line 2332 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 136:
#line 316 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_RHODIUM; }
#line 2338 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 137:
#line 317 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_TANTALUM; }
#line 2344 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 138:
#line 318 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_TITANIUM; }
#line 2350 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 139:
#line 319 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_VANADIUM; }
#line 2356 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 140:
#line 320 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_ZINC; }
#line 2362 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 141:
#line 321 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = METAL_ZIRCONIUM; }
#line 2368 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 144:
#line 327 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mask.mask_chn = (yyvsp[0].ival);}
#line 2374 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 145:
#line 328 "config_parser.y" /* yacc.c:1666  */
    {parsed->cur_mask.mask_inv = 1;}
#line 2380 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 146:
#line 332 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = RED;}
#line 2386 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 147:
#line 333 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = GREEN;}
#line 2392 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 148:
#line 334 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = BLUE;}
#line 2398 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 149:
#line 335 "config_parser.y" /* yacc.c:1666  */
    {(yyval.ival) = ALPHA;}
#line 2404 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 150:
#line 340 "config_parser.y" /* yacc.c:1666  */
    {vec[0] = (yyvsp[-5].fval); vec[1] = (yyvsp[-3].fval); vec[2] = (yyvsp[-1].fval);}
#line 2410 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 151:
#line 344 "config_parser.y" /* yacc.c:1666  */
    {vec[0] = (yyvsp[-3].fval); vec[1] = (yyvsp[-1].fval);}
#line 2416 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 152:
#line 348 "config_parser.y" /* yacc.c:1666  */
    {(yyval.fval) = (yyvsp[0].fval);}
#line 2422 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 153:
#line 349 "config_parser.y" /* yacc.c:1666  */
    {(yyval.fval) = (float)(yyvsp[0].uval);}
#line 2428 "config_parser.tab.c" /* yacc.c:1666  */
    break;

  case 154:
#line 350 "config_parser.y" /* yacc.c:1666  */
    {(yyval.fval) = (float)(yyvsp[0].ival);}
#line 2434 "config_parser.tab.c" /* yacc.c:1666  */
    break;


#line 2438 "config_parser.tab.c" /* yacc.c:1666  */
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
#line 353 "config_parser.y" /* yacc.c:1910  */


/* parse the scene, given an already opened file that will not be closed and a scene already initialized */
void parse_config(FILE* opened_file, struct ParsedScene* scene_initialized)
{
    yyin = opened_file;
    parsed = scene_initialized;
    yyparse();
}

void yyerror (const char* msg)
{
#ifndef WIN32
#define GRN "\x1B[32m"
#define NRM "\x1B[0m"
#define BLD "\x1B[1m"
#else
#define GRN
#define NRM
#define BLD
#endif
#define BUFFER 128
#define FINAL_MSG_BUFFER 1024
    int i;
    int end_col = 0<yylloc.last_column?yylloc.last_column-1:0;
    parsed->successful = 0;
    /* Should be enough. Really.*/
    parsed->error_msg = (char*)malloc(FINAL_MSG_BUFFER);
    //tested againts: token len > buffer len
    //line len > buf len
    //token at beginning and line len > buf len
    //token at end and line len > buf len
    //underline wrong token
    if(yylloc.first_column>0 && yylloc.first_line == yylloc.last_line&&yylloc.last_column-yylloc.first_column<=BUFFER-5) //prev. segfault if token len >buf
    {
        char buf[128];
        char under[128];
        int offset = config_get_line(buf, 128);
        for(i = 0; i<yylloc.first_column-1-offset; i++)
            under[i] = ' ';
        for(i = yylloc.first_column-1-offset; i<end_col-offset; i++)
            under[i] = '~';
        under[end_col-offset] = 0;
        snprintf(parsed->error_msg, FINAL_MSG_BUFFER, "%%s:%d.%d: " BLD "%s" NRM "\n%s\n%%" GRN "%s" NRM, yylloc.last_line, yylloc.first_column, msg, buf, under);
    }
    else //just print the error
        snprintf(parsed->error_msg, FINAL_MSG_BUFFER, "%%s:%d.%d: " BLD "%s" NRM, yylloc.last_line, yylloc.first_column, msg);
}
