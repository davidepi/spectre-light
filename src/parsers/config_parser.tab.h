/* A Bison parser, made by GNU Bison 3.1.  */

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
    SUN_TOKEN = 336,
    TIME = 337,
    LATITUDE = 338,
    LONGITUDE = 339,
    ELEVATION = 340,
    SILVER = 341,
    ALUMINIUM = 342,
    GOLD = 343,
    COPPER = 344,
    IRON = 345,
    MERCURY = 346,
    LEAD = 347,
    PLATINUM = 348,
    TUNGSTEN = 349,
    BERYLLIUM = 350,
    BISMUTH = 351,
    COBALT = 352,
    CHROMIUM = 353,
    GERMANIUM = 354,
    POTASSIUM = 355,
    LITHIUM = 356,
    MAGNESIUM = 357,
    MANGANESE = 358,
    MOLYBDENUM = 359,
    SODIUM = 360,
    NIOBIUM = 361,
    NICKEL = 362,
    PALLADIUM = 363,
    RHODIUM = 364,
    TANTALUM = 365,
    TITANIUM = 366,
    VANADIUM = 367,
    ZINC = 368,
    ZIRCONIUM = 369,
    UINT = 370,
    INT = 371,
    FLOAT = 372,
    STRING = 373
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 137 "config_parser.y" /* yacc.c:1919  */

    float fval;
    int ival;
    unsigned int uval;
    char* sval;

#line 181 "config_parser.tab.h" /* yacc.c:1919  */
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
