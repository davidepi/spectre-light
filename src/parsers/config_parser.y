/* Created,  24 Mar 2018 */
/* Last Edit 25 Mar 2018 */

%skeleton "lalr1.cc"
%require "3.0.4"
%defines
%define parser_class_name {ConfigParser}
%define api.token.constructor
%define api.value.type variant
%define parse.assert
%code requires
{
    #include <string>
    class ConfigDriver;
}
%param{ ConfigDriver& driver }
%initial-action
{
    @$.begin.filename = @$.end.filename = &driver.file;
};
%define parse.trace
%define parse.error verbose
%code
{
    #include "config_driver.hpp"
}

%define api.token.prefix {CONFIG_}
%token END 0 "end of file"
%token INVALID "invalid character"
%token COLON ":"
%token OPEN_SQ "["
%token CLOSE_SQ "]"
%token OPEN_CU "{"
%token CLOSE_CU "}"
%token COMMA ","
%token OUTPUT "`out` keywork"
%token INTEGRATOR "`integrator` keyword"
%token RESOLUTION "`resolution` keyword"
%token WIDTH "`width` keyword"
%token HEIGHT "`height` keyword"
%token SAMPLER "``sampler` keyword"
%token SPP "`spp` keyword"
%token FILTER "`filter` keyword"
%token TYPE "`type` keyword"
%token CAMERA "`camera` keyword"
%token ORTHOGRAPHIC "`orthographic` keyword"
%token PERSPECTIVE "`perspective` keyword"
%token PANORAMA "`panorama` keyword"
%token POSITION "`position` keyword"
%token TARGET "`target` keyword"
%token UP "`up` keyword"
%token FOV "`fov` keyword"
%token RANDOM "`random` keyword"
%token STRATIFIED "`stratified` keyword"
%token BOX "`box` keyword"
%token TENT "`tent` keyword"
%token GAUSS "`gauss` keyword"
%token MITCHELL "`mitchell` keyword"
%token LANCZOS "`lanczos` keyword"
%token VAL_0 "`value0` keyword"
%token VAL_1 "`value1` keyword"
%token SHAPE "`shape` keyword"
%token WORLD "`world` keyword"
%token LIGHT "`light` keyword"
%token TEMPERATURE "`temperature` keyword"
%token NAME "`name` keyword"
%token ROTATION "`rotation` keyword"
%token SCALE "`scale` keyword"
%token COLOR "`color` keyword"
%token MATERIAL "`material` keyword"
%token TEXTURE "`texture` keyword"
%token ANISOTROPY "`anisotropy` keyword"
%token BECKMANN "`beckmann` keyword"
%token BLINN "`blinn` keyword"
%token DIFFUSE "`diffuse` keyword"
%token DISTRIBUTION "`distribution` keyword"
%token ELEMENT "`element` keyword"
%token GGX "`ggx` keyword"
%token GLASS "`glass` keyword"
%token GLOSSY "`glossy` keyword"
%token IOR "`ior` keyword"
%token MATTE "`matte` keyword"
%token METAL "`metal keyword"
%token ROUGHNESS "`roughness` keyword"
%token SPECULAR "`specular` keyword"
%token SRC "`src` keyword"
%token PATH_TRACE "`pt` keyword"

%token <int> INT "integer value"
%token <float> FLOAT "floating point value"
%token <std::string> STRING "quoted string"

%type <float> number
%type <float> vector

%%

%start file;

file
: file stmt
| stmt
| INVALID /*no problem with invalid chars between stmts */
/* TODO: NONONO IT IS A BIG PROBLEM!
   as soon as an invalid statement is matched the object is broken
   everythin after the object is parsed as invalid character instead of the object continuation which is not noice.
 These should be catched at flex level */
;

stmt
: OUTPUT COLON STRING
| RESOLUTION COLON OPEN_CU resolution_obj CLOSE_CU
| FILTER COLON OPEN_CU filter_obj CLOSE_CU
| SAMPLER  COLON RANDOM
| SAMPLER COLON STRATIFIED
| SPP COLON INT
| INTEGRATOR COLON PATH_TRACE
| CAMERA COLON OPEN_CU camera_obj CLOSE_CU
| SHAPE COLON STRING
| WORLD COLON OPEN_CU world_obj CLOSE_CU
| LIGHT COLON OPEN_CU light_obj CLOSE_CU
| TEXTURE COLON STRING
| TEXTURE COLON OPEN_CU texture_obj CLOSE_CU
| MATERIAL COLON OPEN_CU material_obj CLOSE_CU
| INVALID /*no problem with invalid chars between stmts */
          /* TODO: NONONO IT IS A FUCKING BIG PROBLEM!!!! */
;

resolution_obj: resolution_obj resolution_stmt | resolution_stmt;
resolution_stmt
: WIDTH COLON INT
| HEIGHT COLON INT
;

filter_obj: filter_obj filter_stmt | filter_stmt;
filter_stmt
: TYPE COLON BOX
| TYPE COLON TENT
| TYPE COLON GAUSS
| TYPE COLON MITCHELL
| TYPE COLON LANCZOS
| VAL_0 COLON number
| VAL_1 COLON number
;

camera_obj: camera_obj camera_stmt | camera_stmt;
camera_stmt
: TYPE COLON ORTHOGRAPHIC
| TYPE COLON PERSPECTIVE
| TYPE COLON PANORAMA
| POSITION COLON vector
| TARGET COLON vector
| UP COLON vector
| FOV COLON FLOAT
;

world_obj: world_name world_rec;
world_rec: world_rec world_stmt | world_rec MATERIAL COLON STRING| world_stmt;
world_name: NAME COLON STRING;
world_stmt
: POSITION COLON vector
| ROTATION COLON vector
| SCALE COLON vector
| SCALE COLON FLOAT
;

light_obj: world_name light_rec;
light_rec: light_rec world_stmt | light_rec light_stmt | light_stmt;
light_stmt: TEMPERATURE COLON INT | COLOR COLON vector;

texture_obj
: SRC COLON STRING
| NAME COLON STRING SRC COLON STRING
| SRC COLON STRING NAME COLON STRING
;

material_obj: material_obj material_stmt | material_stmt;
material_stmt
: NAME COLON STRING
| TYPE COLON MATTE
| TYPE COLON GLOSSY
| TYPE COLON METAL
| TYPE COLON GLASS
| IOR COLON FLOAT
| ELEMENT COLON STRING
| ROUGHNESS COLON FLOAT
| ANISOTROPY COLON FLOAT
| DISTRIBUTION COLON BLINN
| DISTRIBUTION COLON BECKMANN
| DISTRIBUTION COLON GGX
| DIFFUSE COLON vector
| DIFFUSE COLON STRING
| SPECULAR COLON vector
| SPECULAR COLON STRING
;

vector:
OPEN_SQ number COMMA number COMMA number CLOSE_SQ
{ $$ = $2;}
;

number
: FLOAT {$$ = $1;}
| INT {$$ = (float)$1;}
;

%%

void yy::ConfigParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}
