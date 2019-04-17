/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
    CHANNEL_TOKEN = 324,
    CHNR = 325,
    CHNG = 326,
    CHNB = 327,
    CHNA = 328,
    INV = 329,
    TRUE = 330,
    FALSE = 331,
    MASK = 332,
    FIRST = 333,
    SECOND = 334,
    RADIUS = 335,
    FALLOFF = 336,
    OMNI_TOKEN = 337,
    SPOT_TOKEN = 338,
    AREA_TOKEN = 339,
    SUN_TOKEN = 340,
    TIME = 341,
    LATITUDE = 342,
    LONGITUDE = 343,
    ELEVATION = 344,
    SILVER = 345,
    ALUMINIUM = 346,
    GOLD = 347,
    COPPER = 348,
    IRON = 349,
    MERCURY = 350,
    LEAD = 351,
    PLATINUM = 352,
    TUNGSTEN = 353,
    BERYLLIUM = 354,
    BISMUTH = 355,
    COBALT = 356,
    CHROMIUM = 357,
    GERMANIUM = 358,
    POTASSIUM = 359,
    LITHIUM = 360,
    MAGNESIUM = 361,
    MANGANESE = 362,
    MOLYBDENUM = 363,
    SODIUM = 364,
    NIOBIUM = 365,
    NICKEL = 366,
    PALLADIUM = 367,
    RHODIUM = 368,
    TANTALUM = 369,
    TITANIUM = 370,
    VANADIUM = 371,
    ZINC = 372,
    ZIRCONIUM = 373,
    UINT = 374,
    INT = 375,
    FLOAT = 376,
    STRING = 377
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 141 "config_parser.y" /* yacc.c:1909  */

    float fval;
    int ival;
    unsigned int uval;
    char* sval;

#line 185 "config_parser.tab.h" /* yacc.c:1909  */
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
