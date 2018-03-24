/* Created,  24 Mar 2018 */
/* Last Edit 24 Mar 2018 */

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
    float fval;
    char *sval;
}
%start file
%token COLON ":"
%token OUTPUT_DECL "`out` keywork"
%token INTEGRATOR_DECL "`integrator` keyword"
%token RESOLUTION_DECL "`resolution` keyword"
%token SAMPLER_DECL "``sampler` keyword"
%token FILTER_DECL "`filter` keyword"
%token SAMPLER_RAND "`random` keyword"
%token SAMPLER_STRAT "`stratified` keyword"
%token FILTER_BOX "`box` keyword"
%token FILTER_TENT "`tent` keyword"
%token FILTER_GAUSS "`gauss` keyword"
%token FILTER_MITCH "`mitchell` keyword"
%token FILTER_LANC "`lanczos` keyword"
%token INTEGRATOR_PATH_TRACE "`pt` keyword"
%token <ival> INT "integer value"
%token <fval> FLOAT "floating point value"
%token <sval> STRING "quoted string"

%type <ival> filter_type
%type <ival> sampler_type
%type <ival> integrator_type

%%

file: file stmt
|
;

stmt:
OUTPUT_DECL COLON STRING { config.output = $3; }
| RESOLUTION_DECL COLON INT INT {config.resolution[0] = $3;
                                 config.resolution[1] = $4;}
| FILTER_DECL COLON filter_type {}
| SAMPLER_DECL  COLON sampler_type INT {config.type_sampler = $3;config.spp=$4;}
| INTEGRATOR_DECL COLON integrator_type {config.type_integrator = $3;}
;

filter_type:
FILTER_BOX {config.type_filter = BOX_FILTER;}
| FILTER_TENT {config.type_filter = TENT_FILTER;}
| FILTER_GAUSS FLOAT {config.type_filter = GAUSSIAN_FILTER;
                      config.filter_val[0]=$2;}
| FILTER_MITCH FLOAT FLOAT {config.type_filter = MITCHELL_FILTER;
                            config.filter_val[0] = $2;
                            config.filter_val[1] = $3;}
| FILTER_LANC FLOAT{config.type_filter = LANCZOS_FILTER;
                    config.filter_val[0] = $2;}
;

integrator_type: INTEGRATOR_PATH_TRACE {config.type_integrator = PATH_TRACE;};

sampler_type:
SAMPLER_RAND {config.type_sampler = RANDOM_SAMPLER;}
| SAMPLER_STRAT {config.type_sampler = STRATIFIED_SAMPLER;}
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
