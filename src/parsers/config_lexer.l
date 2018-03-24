/* Created   24 Mar 2018 */
/* Last Edit 24 Mar 2018 */

%{
    #include <stdlib.h>
    #include <string.h>
    #include "config_parser.tab.h"
%}

%%
#[^\n]*[\n\r]      /* skip */ ;
: { return COLON; }
out { return OUTPUT_DECL; }
integrator { return INTEGRATOR_DECL; }
pt         { return INTEGRATOR_PATH_TRACE; }
resolution { return RESOLUTION_DECL; }
sampler { return SAMPLER_DECL; }
random { return SAMPLER_RAND; }
stratified { return SAMPLER_STRAT; }
filter { return FILTER_DECL; }
box { return FILTER_BOX; }
tent { return FILTER_TENT; }
triangle { return FILTER_TENT; }
gauss { return FILTER_GAUSS; }
gaussian { return FILTER_GAUSS; }
mitchell { return FILTER_MITCH; }
lanczos { return FILTER_LANC; }
[0-9]+             { yylval.ival = atoi(yytext); return INT;}
[-+]?([0-9]*\.[0-9]+|[0-9]+)([eE][-+]?[0-9]+)? { yylval.fval = atof(yytext); return FLOAT;}
\".*\" { yylval.sval = strdup(yytext); return STRING; }
'.*.'  { yylval.sval = strdup(yytext); return STRING; }
[ \t\n\r]            /* skip */ ;
%%
