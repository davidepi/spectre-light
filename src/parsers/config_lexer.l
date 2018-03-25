/* Created   24 Mar 2018 */
/* Last Edit 25 Mar 2018 */

%{
    #include <stdlib.h>
    #include <string.h>
    #include "config_parser.tab.h"
%}

%%
#[^\n]*[\n\r]      /* skip */ ;
: { return COLON; }
\[ { return OPEN_SQ;}
\] { return CLOSE_SQ;}
\{ { return OPEN_CU; }
\} { return CLOSE_CU; }
, { return COMMA; }
out { return OUTPUT; }
integrator { return INTEGRATOR; }
pt         { return INTEGRATOR_PATH_TRACE; }
resolution { return RESOLUTION; }
spp {return SPP;}
width { return WIDTH; }
height { return HEIGHT; }
value0 { return VAL_0; }
value1 { return VAL_1; }
sampler { return SAMPLER; }
random { return SAMPLER_RAND; }
stratified { return SAMPLER_STRAT; }
filter { return FILTER; }
type { return TYPE; }
box { return FILTER_BOX; }
tent { return FILTER_TENT; }
triangle { return FILTER_TENT; }
gauss { return FILTER_GAUSS; }
gaussian { return FILTER_GAUSS; }
mitchell { return FILTER_MITCH; }
lanczos { return FILTER_LANC; }
camera {return CAMERA;}
perspective { return CAMERA_PERSPECTIVE; }
panorama {return CAMERA_PANORAMA;}
orthographic { return CAMERA_ORTHOGRAPHIC; }
[0-9]+             { yylval.ival = atoi(yytext); return INT;}
[-+]?([0-9]*\.[0-9]+|[0-9]+)([eE][-+]?[0-9]+)? { yylval.fvec.x = atof(yytext); return FLOAT;}
\".*\" { yylval.sval = strdup(yytext); return STRING; }
'.*.'  { yylval.sval = strdup(yytext); return STRING; }
[ \t\n\r]            /* skip */ ;
%%
