/* A Bison parser, made by GNU Bison 3.2.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

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
    SKY_TOKEN = 297,
    TEMPERATURE = 298,
    NAME = 299,
    ROTATION = 300,
    SCALE = 301,
    SHIFT = 302,
    COLOR = 303,
    MATERIAL = 304,
    DUALMATERIAL = 305,
    TEXTURE = 306,
    ANISOTROPY = 307,
    BECKMANN_TOKEN = 308,
    BLINN_TOKEN = 309,
    DIFFUSE = 310,
    DISTRIBUTION = 311,
    ELEM = 312,
    GGX_TOKEN = 313,
    GLASS_TOKEN = 314,
    GLOSSY_TOKEN = 315,
    IOR = 316,
    MATTE_TOKEN = 317,
    METAL_TOKEN = 318,
    ROUGHNESS = 319,
    SPECULAR = 320,
    NORMAL = 321,
    SRC = 322,
    PATH_TRACE = 323,
    CHNR = 324,
    CHNG = 325,
    CHNB = 326,
    CHNA = 327,
    INV = 328,
    MASK = 329,
    FIRST = 330,
    SECOND = 331,
    RADIUS = 332,
    FALLOFF = 333,
    OMNI_TOKEN = 334,
    SPOT_TOKEN = 335,
    AREA_TOKEN = 336,
    SUN_TOKEN = 337,
    TIME = 338,
    LATITUDE = 339,
    LONGITUDE = 340,
    ELEVATION = 341,
    SILVER = 342,
    ALUMINIUM = 343,
    GOLD = 344,
    COPPER = 345,
    IRON = 346,
    MERCURY = 347,
    LEAD = 348,
    PLATINUM = 349,
    TUNGSTEN = 350,
    BERYLLIUM = 351,
    BISMUTH = 352,
    COBALT = 353,
    CHROMIUM = 354,
    GERMANIUM = 355,
    POTASSIUM = 356,
    LITHIUM = 357,
    MAGNESIUM = 358,
    MANGANESE = 359,
    MOLYBDENUM = 360,
    SODIUM = 361,
    NIOBIUM = 362,
    NICKEL = 363,
    PALLADIUM = 364,
    RHODIUM = 365,
    TANTALUM = 366,
    TITANIUM = 367,
    VANADIUM = 368,
    ZINC = 369,
    ZIRCONIUM = 370,
    UINT = 371,
    INT = 372,
    FLOAT = 373,
    STRING = 374
};
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 138 "config_parser.y" /* yacc.c:1912  */

    float fval;
    int ival;
    unsigned int uval;
    char* sval;

#line 185 "config_parser.tab.h" /* yacc.c:1912  */
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
