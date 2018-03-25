/* Created,  24 Mar 2018 */
/* Last Edit 25 Mar 2018 */

%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include "config_bridge.h"
    
    int yylex();
    int yyparse();
    FILE *yyin;
    void yyerror(const char *s);
    Settings config;
    
%}
%error-verbose
//type that could be returned by flex
%union
{
    int ival;
    struct fvec3_t
    {
        float x;
        float y;
        float z;
    }fvec;
    char *sval;
    
}
%start file
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
%token CAMERA_ORTHOGRAPHIC "`orthographic` keyword"
%token CAMERA_PERSPECTIVE "`perspective` keyword"
%token CAMERA_PANORAMA "`panorama` keyword"
%token POSITION "`position` keyword"
%token TARGET "`target` keyword"
%token UP "`up` keyword"
%token FOV "`fov` keyword"
%token SAMPLER_RAND "`random` keyword"
%token SAMPLER_STRAT "`stratified` keyword"
%token FILTER_BOX "`box` keyword"
%token FILTER_TENT "`tent` keyword"
%token FILTER_GAUSS "`gauss` keyword"
%token FILTER_MITCH "`mitchell` keyword"
%token FILTER_LANC "`lanczos` keyword"
%token VAL_0 "`value0` keyword"
%token VAL_1 "`value1` keyword"
%token INTEGRATOR_PATH_TRACE "`pt` keyword"
%token <ival> INT "integer value"
%token <fvec.x> FLOAT "floating point value"
%token <sval> STRING "quoted string"

%type <ival> sampler_type
%type <ival> integrator_type
%type <fvec.x> number
%type <fvec> vector

%%

file: file stmt
|
;

stmt:
OUTPUT COLON STRING { config.output = $3; }
| RESOLUTION COLON OPEN_CU resolution_type CLOSE_CU
| FILTER COLON OPEN_CU filter_type CLOSE_CU
| SAMPLER  COLON sampler_type {config.type_sampler = $3;}
| SPP COLON INT {config.spp=$3;}
| INTEGRATOR COLON integrator_type {config.type_integrator = $3;}
| CAMERA COLON OPEN_CU camera_type CLOSE_CU
;

resolution_type: resolution_type resolution_stmt | ;
resolution_stmt:
  WIDTH COLON INT {config.resolution[0] = $3; }
| HEIGHT COLON INT {config.resolution[1] = $3; }
;

filter_type: filter_type filter_stmt|;
filter_stmt:
TYPE COLON FILTER_BOX {config.type_filter = BOX_FILTER;}
| TYPE COLON FILTER_TENT {config.type_filter = TENT_FILTER;}
| TYPE COLON FILTER_GAUSS {config.type_filter = GAUSSIAN_FILTER;}
| TYPE COLON FILTER_MITCH {config.type_filter = MITCHELL_FILTER;}
| TYPE COLON FILTER_LANC {config.type_filter = LANCZOS_FILTER;}
| VAL_0 COLON number {config.filter_val[0] = $3;}
| VAL_1 COLON number {config.filter_val[1] = $3;}
;

integrator_type: INTEGRATOR_PATH_TRACE {config.type_integrator = PATH_TRACE;};

sampler_type:
SAMPLER_RAND {config.type_sampler = RANDOM_SAMPLER;}
| SAMPLER_STRAT {config.type_sampler = STRATIFIED_SAMPLER;}
;

camera_type: camera_type camera_stmt|;
camera_stmt:
TYPE COLON CAMERA_ORTHOGRAPHIC {config.type_camera = ORTHOGRAPHIC_CAMERA;}
| TYPE COLON CAMERA_PERSPECTIVE {config.type_camera = PERSPECTIVE_CAMERA;}
| TYPE COLON CAMERA_PANORAMA {config.type_camera = PANORAMA_CAMERA;}
| POSITION COLON vector {config.camera_position[0]=$3.x;
                         config.camera_position[1]=$3.y;
                         config.camera_position[2]=$3.z;}
| TARGET COLON vector {config.camera_target[0]=$3.x;
                       config.camera_target[1]=$3.y;
                       config.camera_target[2]=$3.z;}
| UP COLON vector {config.camera_up[0]=$3.x;
                   config.camera_up[1]=$3.y;
                   config.camera_up[2]=$3.z;}
| FOV COLON FLOAT {config.camera_fov = $3;}
;


vector:
OPEN_SQ number COMMA number COMMA number CLOSE_SQ
{$$.x = $2; $$.y = $4; $$.z = $6;}
;

number:
FLOAT {$$ = $1;}
| INT {$$ = (float)$1;}
;

%%

int main(int argc, char* argv[])
{
    FILE *myfile = fopen(argv[1], "r");
    memset(&config,0,sizeof(Settings));
    if(!myfile)
    {
        fprintf(stderr,"Error opening file\n");
        return -1;
    }
    yyin = myfile;
    
    do
    {
        yyparse();
    }
    while(!feof(yyin));
}

void yyerror(const char *s) {
    fflush(stdout);
    fprintf(stderr,"Error: %s\n",s);
    exit(EXIT_FAILURE);
}
