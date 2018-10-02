/* Created,  24 Mar 2018 */
/* Last Edit  3 Apr 2018 */

%define lr.type lalr
%define parse.trace
%define parse.error verbose
%locations
%{
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
%}

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
%token ORTHOGRAPHIC_TOKEN "`orthographic` keyword"
%token PERSPECTIVE_TOKEN "`perspective` keyword"
%token PANORAMA_TOKEN "`panorama` keyword"
%token POSITION "`position` keyword"
%token TARGET "`target` keyword"
%token UP "`up` keyword"
%token FOV "`fov` keyword"
%token RANDOM_TOKEN "`random` keyword"
%token STRATIFIED_TOKEN "`stratified` keyword"
%token BOX_TOKEN "`box` keyword"
%token TENT_TOKEN "`tent` keyword"
%token GAUSS_TOKEN "`gauss` keyword"
%token MITCHELL_TOKEN "`mitchell` keyword"
%token LANCZOS_TOKEN "`lanczos` keyword"
%token UNFILTERED_TOKEN "`unfiltered` keyword"
%token TRILINEAR_TOKEN "`trilinear` keyword"
%token EWA_TOKEN "`ewa` keyword"
%token VAL_0 "`value0` keyword"
%token VAL_1 "`value1` keyword"
%token SHAPE "`shape` keyword"
%token WORLD "`world` keyword"
%token LIGHT "`light` keyword"
%token TEMPERATURE "`temperature` keyword"
%token NAME "`name` keyword"
%token ROTATION "`rotation` keyword"
%token SCALE "`scale` keyword"
%token SHIFT "`shift` keyword"
%token COLOR "`color` keyword"
%token MATERIAL "`material` keyword"
%token DUALMATERIAL "`dualmaterial` keyword"
%token TEXTURE "`texture` keyword"
%token ANISOTROPY "`anisotropy` keyword"
%token BECKMANN_TOKEN "`beckmann` keyword"
%token BLINN_TOKEN "`blinn` keyword"
%token DIFFUSE "`diffuse` keyword"
%token DISTRIBUTION "`distribution` keyword"
%token ELEM "`element` keyword"
%token GGX_TOKEN "`ggx` keyword"
%token GLASS_TOKEN "`glass` keyword"
%token GLOSSY_TOKEN "`glossy` keyword"
%token IOR "`ior` keyword"
%token MATTE_TOKEN "`matte` keyword"
%token METAL_TOKEN "`metal keyword"
%token ROUGHNESS "`roughness` keyword"
%token SPECULAR "`specular` keyword"
/* %token BUMP "`bump` keyword" */
%token NORMAL "`normal` keyword"
%token SRC "`src` keyword"
%token PATH_TRACE "`path` keyword"
%token CHNR "Red channel attribute"
%token CHNG "Green channel attribute"
%token CHNB "Blue channel attribute"
%token CHNA "Alpha channel attribute"
%token INV "inverted attribute"
%token MASK "`mask` keyword"
%token FIRST "`first` keyword"
%token SECOND "`second` keyword"
%token RADIUS "`radius` keyword"
%token FALLOFF "`falloff` keyword"
%token OMNI_TOKEN "`omni` keyword"
%token SPOT_TOKEN "`spot` keyword"
%token AREA_TOKEN "`area` keyword"
%token SILVER "`Ag`"
%token ALUMINIUM "`Al`"
%token GOLD "`Au`"
%token COPPER "`Cu`"
%token IRON "`Fe`"
%token MERCURY "`Hg`"
%token LEAD "`Pb`"
%token PLATINUM "`Pt`"
%token TUNGSTEN "`W`"
%token BERYLLIUM "`Be`"
%token BISMUTH "`Bi`"
%token COBALT "`Co`"
%token CHROMIUM "`Cr`"
%token GERMANIUM "`Ge`"
%token POTASSIUM "`K`"
%token LITHIUM "`Li`"
%token MAGNESIUM "`Mg`"
%token MANGANESE "`Mn`"
%token MOLYBDENUM "`Mo`"
%token SODIUM "`Na`"
%token NIOBIUM "`Nb`"
%token NICKEL "`Ni`"
%token PALLADIUM "`Pd`"
%token RHODIUM "`Rh`"
%token TANTALUM "`Ta`"
%token TITANIUM "`Ti`"
%token VANADIUM "`V`"
%token ZINC "`Zn`"
%token ZIRCONIUM "`Zr`"

%union{
    float fval;
    int ival;
    unsigned int uval;
    char* sval;
}

%token <uval> UINT "positive integer value"
%token <ival> INT "integer value"
%token <fval> FLOAT "floating point value"
%token <sval> STRING "quoted string"
%type <fval> number
%type <ival> channel
%type <ival> element

%%

%start config;

config: file {parsed->successful = 1;}

file
: file stmt
| stmt
;

stmt
: OUTPUT COLON STRING {ADD_STRING(parsed->output,$3);}
| RESOLUTION COLON OPEN_CU resolution_obj CLOSE_CU
| FILTER COLON OPEN_CU filter_obj CLOSE_CU
| SAMPLER  COLON RANDOM_TOKEN {parsed->sampler_type = RANDOM;}
| SAMPLER COLON STRATIFIED_TOKEN {parsed->sampler_type = STRATIFIED;}
| SPP COLON UINT        {parsed->spp = $3;}
| INTEGRATOR COLON PATH_TRACE {/* path_trace is the only available and dflt */}
| CAMERA COLON OPEN_CU camera_obj CLOSE_CU {/* camera depends on resolution */}
| SHAPE COLON STRING {push_ResizableStack(&(parsed->parsed_mesh_object),$3);}
| WORLD COLON OPEN_CU world_obj CLOSE_CU {push_ResizableParsed(&
(parsed->parsed_mesh_world),&(parsed->cur_mesh));init_ParsedMeshWorld(&(parsed->cur_mesh.mesh));}
| LIGHT COLON OPEN_CU light_obj CLOSE_CU {push_ResizableParsed(&
(parsed->parsed_lights),&(parsed->cur_light));init_ParsedLight(&(parsed->cur_light.light));}
| TEXTURE COLON OPEN_CU texture_obj CLOSE_CU {push_ResizableParsed(&
(parsed->parsed_textures),&(parsed->cur_tex));init_ParsedTexture(&(parsed->cur_tex.tex));}
| MATERIAL COLON STRING {push_ResizableStack(&(parsed->children),$3);}
| MATERIAL COLON OPEN_CU material_obj CLOSE_CU {push_ResizableParsed(&(parsed->parsed_materials),&(parsed->cur_mat));init_ParsedMaterial(&(parsed->cur_mat.mat));}
| DUALMATERIAL COLON OPEN_CU dualmaterial_obj CLOSE_CU {push_ResizableParsed(&
(parsed->parsed_dualmaterials),&(parsed->cur_dualmat));init_ParsedDualMaterial(&(parsed->cur_dualmat.dualmat));}
| COMMA
;

resolution_obj: resolution_obj resolution_stmt | resolution_stmt;
resolution_stmt
: WIDTH COLON UINT {parsed->width = $3;}
| HEIGHT COLON UINT {parsed->height = $3;}
| COMMA
;

filter_obj: filter_obj filter_stmt | filter_stmt;
filter_stmt
: TYPE COLON BOX_TOKEN {parsed->filter_type = BOX;}
| TYPE COLON TENT_TOKEN {parsed->filter_type = TENT;}
| TYPE COLON GAUSS_TOKEN {parsed->filter_type = GAUSS;}
| TYPE COLON MITCHELL_TOKEN {parsed->filter_type = MITCHELL;}
| TYPE COLON LANCZOS_TOKEN {parsed->filter_type = LANCZOS;}
| VAL_0 COLON number {parsed->value0 = $3;}
| VAL_1 COLON number {parsed->value1 = $3;}
| COMMA
;

camera_obj: camera_obj camera_stmt | camera_stmt;
camera_stmt
: TYPE COLON ORTHOGRAPHIC_TOKEN {parsed->camera_type = ORTHOGRAPHIC;}
| TYPE COLON PERSPECTIVE_TOKEN {parsed->camera_type = PERSPECTIVE;}
| TYPE COLON PANORAMA_TOKEN {parsed->camera_type = PANORAMA;}
| POSITION COLON vector {parsed->camera_pos[0] = vec[0];parsed->camera_pos[1] = vec[1];parsed->camera_pos[2] = vec[2];}
| TARGET COLON vector {parsed->camera_tar[0] = vec[0];parsed->camera_tar[1] = vec[1];parsed->camera_tar[2] = vec[2];}
| UP COLON vector {parsed->camera_up[0] = vec[0];parsed->camera_up[1] = vec[1];parsed->camera_up[2] = vec[2];}
| FOV COLON number {parsed->fov = $3;}
| COMMA
;

world_obj: world_obj world_stmt | world_stmt
world_stmt
: NAME COLON STRING {ADD_STRING(parsed->cur_mesh.mesh.name,$3);}
| POSITION COLON vector {parsed->cur_mesh.mesh.position[0] = vec[0];parsed->cur_mesh.mesh.position[1] = vec[1];parsed->cur_mesh.mesh.position[2] = vec[2];}
| ROTATION COLON vector {parsed->cur_mesh.mesh.rotation[0] = vec[0];parsed->cur_mesh.mesh.rotation[1] = vec[1];parsed->cur_mesh.mesh.rotation[2] = vec[2];}
| SCALE COLON vector {parsed->cur_mesh.mesh.scale[0] = vec[0];parsed->cur_mesh.mesh.scale[1] = vec[1];parsed->cur_mesh.mesh.scale[2] = vec[2];}
| SCALE COLON number {parsed->cur_mesh.mesh.scale[0] = $3;parsed->cur_mesh.mesh.scale[1] = $3;parsed->cur_mesh.mesh.scale[2] = $3;}
| MATERIAL COLON STRING {ADD_STRING(parsed->cur_mesh.mesh.material_name,$3);}
| MASK COLON STRING {ADD_STRING(parsed->cur_mask.mask_tex,$3); parsed->cur_mesh.mesh.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
| MASK COLON STRING attributes {ADD_STRING(parsed->cur_mask.mask_tex,$3); parsed->cur_mesh.mesh.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
| COMMA
;

light_obj: light_obj light_stmt | light_stmt;
light_stmt
: NAME COLON STRING {ADD_STRING(parsed->cur_light.light.name,$3);}
| TEMPERATURE COLON UINT {parsed->cur_light.light.temperature = $3;}
| COLOR COLON vector {parsed->cur_light.light.color[0] = vec[0];parsed->cur_light.light.color[1] = vec[1];parsed->cur_light.light.color[2] = vec[2];}
| TYPE COLON AREA_TOKEN {parsed->cur_light.light.type = AREA;}
| TYPE COLON OMNI_TOKEN {parsed->cur_light.light.type = OMNI;}
| TYPE COLON SPOT_TOKEN {parsed->cur_light.light.type = SPOT;}
| POSITION COLON vector {parsed->cur_light.light.position[0] = vec[0];parsed->cur_light.light.position[1] = vec[1];parsed->cur_light.light.position[2] = vec[2];}
| ROTATION COLON vector {parsed->cur_mesh.mesh.rotation[0] = vec[0];parsed->cur_mesh.mesh.rotation[1] = vec[1];parsed->cur_mesh.mesh.rotation[2] = vec[2];}
| SCALE COLON vector {parsed->cur_light.light.scale[0] = vec[0];parsed->cur_light.light.scale[1] = vec[1];parsed->cur_light.light.scale[2] = vec[2];}
| SCALE COLON number {parsed->cur_light.light.scale[0] = $3;parsed->cur_light.light.scale[1] = $3;parsed->cur_light.light.scale[2] = $3;}
| RADIUS COLON number {parsed->cur_light.light.radius = $3;}
| FALLOFF COLON number {parsed->cur_light.light.falloff = $3;}
| COMMA
;

texture_obj: texture_obj texture_stmt|texture_stmt;
texture_stmt
: SRC COLON STRING {ADD_STRING(parsed->cur_tex.tex.src,$3);}
| NAME COLON STRING {ADD_STRING(parsed->cur_tex.tex.name,$3);}
| SCALE COLON vector2 {parsed->cur_tex.tex.scale[0] = vec[0]; parsed->cur_tex.tex.scale[1]=vec[1];}
| SCALE COLON number {parsed->cur_tex.tex.scale[0] = $3; parsed->cur_tex.tex.scale[1]=$3;}
| SHIFT COLON vector2 {parsed->cur_tex.tex.shift[0] = vec[0]; parsed->cur_tex.tex.shift[1]=vec[1];}
| SHIFT COLON number {parsed->cur_tex.tex.shift[0] = $3; parsed->cur_tex.tex.shift[1]=$3;}
| COLOR COLON vector {parsed->cur_tex.tex.color[0] = vec[0]; parsed->cur_tex.tex.color[1] = vec[1]; parsed->cur_tex.tex.color[2] = vec[2];}
| FILTER COLON UNFILTERED_TOKEN {parsed->cur_tex.tex.filter = UNFILTERED;}
| FILTER COLON TRILINEAR_TOKEN {parsed->cur_tex.tex.filter = TRILINEAR;}
| FILTER COLON EWA_TOKEN {parsed->cur_tex.tex.filter = EWA;}
| COMMA
;

material_obj: material_obj material_stmt | material_stmt;
material_stmt
: NAME COLON STRING {ADD_STRING(parsed->cur_mat.mat.name,$3);}
| TYPE COLON MATTE_TOKEN {parsed->cur_mat.mat.type = MATTE;}
| TYPE COLON GLOSSY_TOKEN {parsed->cur_mat.mat.type = GLOSSY;}
| TYPE COLON METAL_TOKEN {parsed->cur_mat.mat.type = METAL;}
| TYPE COLON GLASS_TOKEN {parsed->cur_mat.mat.type = GLASS;}
| IOR COLON number {parsed->cur_mat.mat.ior[0] = $3; parsed->cur_mat.mat.ior[1] = 0.f; parsed->cur_mat.mat.ior[2] = 0.f;}
| IOR COLON vector2 {parsed->cur_mat.mat.ior[0] = vec[0]; parsed->cur_mat.mat.ior[1] = vec[1]; parsed->cur_mat.mat.ior[2] = 0.f;}
| IOR COLON vector {parsed->cur_mat.mat.ior[0] = vec[0]; parsed->cur_mat.mat.ior[1] = vec[1]; parsed->cur_mat.mat.ior[2] = vec[2];}
| ROUGHNESS COLON number {parsed->cur_mat.mat.rough_x = $3;}
| ANISOTROPY COLON number {parsed->cur_mat.mat.rough_y = $3;}
| DISTRIBUTION COLON BLINN_TOKEN {parsed->cur_mat.mat.dist = BLINN;}
| DISTRIBUTION COLON BECKMANN_TOKEN {parsed->cur_mat.mat.dist = BECKMANN;}
| DISTRIBUTION COLON GGX_TOKEN {parsed->cur_mat.mat.dist = GGX;}
| DIFFUSE COLON STRING {ADD_STRING(parsed->cur_mat.mat.diffuse,$3);}
| SPECULAR COLON STRING {ADD_STRING(parsed->cur_mat.mat.specular,$3);}
| NORMAL COLON STRING {ADD_STRING(parsed->cur_mat.mat.normal,$3);}
| ELEM COLON element {parsed->cur_mat.mat.elem = $3;}
| COMMA
;

dualmaterial_obj: dualmaterial_obj dualmaterial_stmt | dualmaterial_stmt;
dualmaterial_stmt
: NAME COLON STRING {ADD_STRING(parsed->cur_dualmat.dualmat.name,$3);}
| FIRST COLON STRING {ADD_STRING(parsed->cur_dualmat.dualmat.first,$3);}
| SECOND COLON STRING {ADD_STRING(parsed->cur_dualmat.dualmat.second,$3);}
| MASK COLON STRING {ADD_STRING(parsed->cur_mask.mask_tex,$3);parsed->cur_dualmat.dualmat.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
| MASK COLON STRING attributes {ADD_STRING(parsed->cur_mask.mask_tex,$3); parsed->cur_dualmat.dualmat.mask = parsed->cur_mask;init_ParsedMask(&(parsed->cur_mask));}
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
| BERYLLIUM {$$ = METAL_BERYLLIUM; }
| BISMUTH {$$ = METAL_BISMUTH; }
| COBALT {$$ = METAL_COBALT; }
| CHROMIUM {$$ = METAL_CHROMIUM; }
| GERMANIUM {$$ = METAL_GERMANIUM; }
| POTASSIUM {$$ = METAL_POTASSIUM; }
| LITHIUM {$$ = METAL_LITHIUM; }
| MAGNESIUM {$$ = METAL_MAGNESIUM; }
| MANGANESE {$$ = METAL_MANGANESE; }
| MOLYBDENUM {$$ = METAL_MOLYBDENUM; }
| SODIUM {$$ = METAL_SODIUM; }
| NIOBIUM {$$ = METAL_NIOBIUM; }
| NICKEL {$$ = METAL_NICKEL; }
| PALLADIUM {$$ = METAL_PALLADIUM; }
| RHODIUM {$$ = METAL_RHODIUM; }
| TANTALUM {$$ = METAL_TANTALUM; }
| TITANIUM {$$ = METAL_TITANIUM; }
| VANADIUM {$$ = METAL_VANADIUM; }
| ZINC {$$ = METAL_ZINC; }
| ZIRCONIUM {$$ = METAL_ZIRCONIUM; }
;

attributes: attributes attribute | attribute;

attribute
: channel {parsed->cur_mask.mask_chn = $1;}
| INV {parsed->cur_mask.mask_inv = 1;}
;

channel
: CHNR  {$$ = RED;}
| CHNG  {$$ = GREEN;}
| CHNB  {$$ = BLUE;}
| CHNA  {$$ = ALPHA;}
;

vector
:OPEN_SQ number COMMA number COMMA number CLOSE_SQ
{vec[0] = $2; vec[1] = $4; vec[2] = $6;}
;

vector2
:OPEN_SQ number COMMA number CLOSE_SQ {vec[0] = $2; vec[1] = $4;}
;

number
: FLOAT {$$ = $1;}
| UINT {$$ = (float)$1;}
| INT {$$ = (float)$1;}
;

%%

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
    /* Should be enough. Really. */
    parsed->error_msg = (char*)malloc(FINAL_MSG_BUFFER);
    /*
     tested againts:
     - token len > buffer len
     - line len > buf len
     - token at beginning and line len > buf len
     - token at end and line len > buf len
     - underline wrong token
     */
    if(yylloc.first_column>0 && yylloc.first_line == yylloc.last_line&&yylloc.last_column-yylloc.first_column<=BUFFER-5) /* prev. segfault if token len >buf */
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
    else /* just print the error */
        snprintf(parsed->error_msg, FINAL_MSG_BUFFER, "%%s:%d.%d: " BLD "%s" NRM, yylloc.last_line, yylloc.first_column, msg);
}
