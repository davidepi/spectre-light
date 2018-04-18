/* Created,  24 Mar 2018 */
/* Last Edit  3 Apr 2018 */

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
    #include "geometry/vec3.hpp"
    #include "geometry/vec2.hpp"
    #include "materials/metals.hpp"
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
    #include "parsers/config_driver.hpp"
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
%token ELEM "`element` keyword"
%token GGX "`ggx` keyword"
%token GLASS "`glass` keyword"
%token GLOSSY "`glossy` keyword"
%token IOR "`ior` keyword"
%token MATTE "`matte` keyword"
%token METAL "`metal keyword"
%token ROUGHNESS "`roughness` keyword"
%token SPECULAR "`specular` keyword"
%token SRC "`src` keyword"
%token PATH_TRACE "`path` keyword"
%token SILVER "`Ag`"
%token ALUMINIUM "`Al`"
%token GOLD "`Au`"
%token COPPER "`Cu`"
%token IRON "`Fe`"
%token MERCURY "`Hg`"
%token LEAD "`Pb`"
%token PLATINUM "`Pt`"
%token TUNGSTEN "`W`"

%token <unsigned int> UINT "positive integer value"
%token <int> INT "integer value"
%token <float> FLOAT "floating point value"
%token <std::string> STRING "quoted string"

%type <float> number
%type <metal_t> element
%type <int> integer
%type <Vec3> vector
%type <Vec2> vector2

%%

%start file;

file
: file stmt
| stmt
;

stmt
: OUTPUT COLON STRING {driver.output = $3.substr(1,$3.size()-2);}
| RESOLUTION COLON OPEN_CU resolution_obj CLOSE_CU
| FILTER COLON OPEN_CU filter_obj CLOSE_CU {driver.build_filter();}
| SAMPLER  COLON RANDOM {driver.sampler_type = SPECTRE_SAMPLER_RANDOM;}
| SAMPLER COLON STRATIFIED {driver.sampler_type = SPECTRE_SAMPLER_STRATIFIED;}
| SPP COLON UINT        {driver.spp = $3;}
| INTEGRATOR COLON PATH_TRACE {/* path_trace is the only available and dflt */}
| CAMERA COLON OPEN_CU camera_obj CLOSE_CU {/* camera depends on resolution */}
| SHAPE COLON STRING {driver.allocate_shape($3.substr(1,$3.size()-2).c_str());}
| WORLD COLON OPEN_CU world_obj CLOSE_CU
| LIGHT COLON OPEN_CU light_obj CLOSE_CU
| TEXTURE COLON STRING {driver.tex_src=$3.substr(1,$3.size()-2);driver.load_texture_folder();}
| TEXTURE COLON OPEN_CU texture_obj CLOSE_CU
| MATERIAL COLON OPEN_CU material_obj CLOSE_CU {driver.deferred_materials.push_back(driver.cur_mat);driver.cur_mat=ParsedMaterial();}
| COMMA
;

resolution_obj: resolution_obj resolution_stmt | resolution_stmt;
resolution_stmt
: WIDTH COLON UINT {driver.width = $3;}
| HEIGHT COLON UINT {driver.height = $3;}
| COMMA
;

filter_obj: filter_obj filter_stmt | filter_stmt;
filter_stmt
: TYPE COLON BOX {driver.filter_type = SPECTRE_FILTER_BOX;}
| TYPE COLON TENT {driver.filter_type = SPECTRE_FILTER_TENT;}
| TYPE COLON GAUSS {driver.filter_type = SPECTRE_FILTER_GAUSS;}
| TYPE COLON MITCHELL {driver.filter_type = SPECTRE_FILTER_MITCHELL;}
| TYPE COLON LANCZOS {driver.filter_type = SPECTRE_FILTER_LANCZOS;}
| VAL_0 COLON number {driver.value0 = $3;}
| VAL_1 COLON number {driver.value1 = $3;}
| COMMA
;

camera_obj: camera_obj camera_stmt | camera_stmt;
camera_stmt
: TYPE COLON ORTHOGRAPHIC {driver.camera_type = SPECTRE_CAMERA_ORTHOGRAPHIC;}
| TYPE COLON PERSPECTIVE {driver.camera_type = SPECTRE_CAMERA_PERSPECTIVE;}
| TYPE COLON PANORAMA {driver.camera_type = SPECTRE_CAMERA_PANORAMA;}
| POSITION COLON vector {driver.camera_pos = Point3($3.x,$3.y,$3.z);}
| TARGET COLON vector {driver.camera_tar = Point3($3.x,$3.y,$3.z);}
| UP COLON vector {driver.camera_up = $3;}
| FOV COLON number {driver.fov = $3;}
| COMMA
;

world_obj: world_name world_rec;
world_rec: world_rec world_stmt | world_rec MATERIAL COLON STRING| world_stmt;
world_name: NAME COLON STRING;
world_stmt
: POSITION COLON vector
| ROTATION COLON vector
| SCALE COLON vector
| SCALE COLON FLOAT
| COMMA
;

light_obj: world_name light_rec;
light_rec: light_rec world_stmt | light_rec light_stmt | light_stmt;
light_stmt: TEMPERATURE COLON UINT | COLOR COLON vector;

texture_obj /* name is already known at this point */
: SRC COLON STRING texture_rec {driver.tex_src=$3.substr(1,$3.size()-2);driver.load_texture_single();}
| texture_rec SRC COLON STRING {driver.tex_src=$4.substr(1,$4.size()-2);driver.load_texture_single();}
| SRC COLON STRING {driver.tex_src = $3.substr(1,$3.size()-2);driver.load_texture_single();} //no comma nor name
| COLOR COLON vector texture_rec {driver.tex_color=$3;driver.load_texture_uniform();}
| texture_rec COLOR COLON vector {driver.tex_color=$4;driver.load_texture_uniform();}
| COLOR COLON vector {driver.tex_color=$3;driver.load_texture_uniform();}
;

texture_rec:texture_rec texture_stmt|texture_stmt;
texture_stmt
: NAME COLON STRING {driver.tex_name = $3.substr(1,$3.size()-2);}
| COMMA
;


material_obj
: NAME COLON STRING material_rec {driver.cur_mat.name = $3.substr(1,$3.size()-2);}
| material_rec NAME COLON STRING {driver.cur_mat.name = $4.substr(1,$4.size()-2);}
| material_rec NAME COLON STRING material_rec {driver.cur_mat.name = $4.substr(1,$4.size()-2);}
| NAME COLON STRING {driver.cur_mat.name = $3.substr(1,$3.size()-2);}
;

material_rec: material_rec material_stmt | material_stmt;
material_stmt
: TYPE COLON MATTE {driver.cur_mat.type = MATTE;}
| TYPE COLON GLOSSY {driver.cur_mat.type = GLOSSY;}
| TYPE COLON METAL {driver.cur_mat.type = METAL;}
| TYPE COLON GLASS {driver.cur_mat.type = GLASS;}
| IOR COLON FLOAT {driver.cur_mat.ior = cauchy($3,0);}
| IOR COLON vector2 {driver.cur_mat.ior = cauchy($3.x,$3.y);}
| IOR COLON vector {driver.cur_mat.ior = cauchy($3.x,$3.y,$3.z);}
| IOR COLON vector vector {driver.cur_mat.ior = sellmeier($3.x,$3.y,$3.z,$4.x,$4.y,$4.z);}
| ROUGHNESS COLON FLOAT {driver.cur_mat.rough_x = $3;}
| ANISOTROPY COLON FLOAT {driver.cur_mat.rough_y = $3;}
| DISTRIBUTION COLON BLINN {driver.cur_mat.dist = SPECTRE_DIST_BLINN;}
| DISTRIBUTION COLON BECKMANN {driver.cur_mat.dist = SPECTRE_DIST_BECKMANN;}
| DISTRIBUTION COLON GGX {driver.cur_mat.dist = SPECTRE_DIST_GGX;}
| DIFFUSE COLON STRING {driver.cur_mat.diffuse = $3.substr(1,$3.size()-2);}
| SPECULAR COLON STRING {driver.cur_mat.specular = $3.substr(1,$3.size()-2);}
| ELEM COLON element {driver.cur_mat.elem = $3;}
| COMMA
;

/* add also elements to materials/metals.hpp file, while respecting indexes.
   Non-existent materials are thrown away here, so no check is performed outside
   the parser */
element
: SILVER {$$ = METAL_SILVER; }
| ALUMINIUM {$$ = METAL_ALUMINIUM; }
| GOLD {$$ = METAL_GOLD; }
| COPPER {$$ = METAL_COPPER; }
| IRON {$$ = METAL_IRON; }
| MERCURY {$$ = METAL_MERCURY; }
| LEAD {$$ = METAL_LEAD; }
| PLATINUM {$$ = METAL_PLATINUM; }
| TUNGSTEN {$$ = METAL_TUNGSTEN; }
;

vector:
OPEN_SQ number COMMA number COMMA number CLOSE_SQ
{ $$ = Vec3($2,$4,$6);}
;

vector2
: OPEN_SQ number COMMA number CLOSE_SQ { $$ = Vec2($2,$4);}
;

number
: FLOAT {$$ = $1;}
| integer {$$ = (float)$1;}
;

integer
: UINT { $$ = $1;}
| INT  { $$ = $1;}
;

%%

void yy::ConfigParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}
