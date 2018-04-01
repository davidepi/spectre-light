/* Created   24 Mar 2018 */
/* Last Edit 31 Mar 2018 */

%{
#include <cstdlib> //for atof and atoi. They are deprecated because of lack of
                      //error handling, but lex ensures no errors
#include <climits>
#include <cerrno>
#include <string>
#include "config_parser.tab.hh"
#include "config_driver.hpp"
#undef yywrap
#define yywrap() 1
static yy::location loc;
%}
%option nounput
%option noinput
%option noyywrap
%option debug
int [0-9]+
float [-+]?([0-9]*\.[0-9]+|[0-9]+)([eE][-+]?[0-9]+)?
string '.*.'|\".*\"
%{
    #define YY_USER_ACTION loc.columns(yyleng);
%}

%%

%{
    loc.step();
%}
#[^\n]*[\n\r]      /* skip */ ;
: { return yy::ConfigParser::make_COLON(loc); }
\[ { return yy::ConfigParser::make_OPEN_SQ(loc); }
\] { return yy::ConfigParser::make_CLOSE_SQ(loc); }
\{ { return yy::ConfigParser::make_OPEN_CU(loc); }
\} { return yy::ConfigParser::make_CLOSE_CU(loc); }
, { return yy::ConfigParser::make_COMMA(loc); }
out { return yy::ConfigParser::make_OUTPUT(loc); }
integrator { return yy::ConfigParser::make_INTEGRATOR(loc); }
pt         { return yy::ConfigParser::make_PATH_TRACE(loc); }
resolution { return yy::ConfigParser::make_RESOLUTION(loc); }
spp {return yy::ConfigParser::make_SPP(loc); }
width { return yy::ConfigParser::make_WIDTH(loc); }
height { return yy::ConfigParser::make_HEIGHT(loc); }
value0 { return yy::ConfigParser::make_VAL_0(loc); }
value1 { return yy::ConfigParser::make_VAL_1(loc); }
sampler { return yy::ConfigParser::make_SAMPLER(loc); }
random { return yy::ConfigParser::make_RANDOM(loc); }
stratified { return yy::ConfigParser::make_STRATIFIED(loc); }
filter { return yy::ConfigParser::make_FILTER(loc); }
type { return yy::ConfigParser::make_TYPE(loc); }
box { return yy::ConfigParser::make_BOX(loc); }
tent { return yy::ConfigParser::make_TENT(loc); }
triangle { return yy::ConfigParser::make_TENT(loc); }
gauss { return yy::ConfigParser::make_GAUSS(loc); }
gaussian { return yy::ConfigParser::make_GAUSS(loc); }
mitchell { return yy::ConfigParser::make_MITCHELL(loc); }
lanczos { return yy::ConfigParser::make_LANCZOS(loc); }
camera {return yy::ConfigParser::make_CAMERA(loc); }
perspective { return yy::ConfigParser::make_PERSPECTIVE(loc); }
panorama {return yy::ConfigParser::make_PANORAMA(loc); }
orthographic { return yy::ConfigParser::make_ORTHOGRAPHIC(loc); }
position {return yy::ConfigParser::make_POSITION(loc); }
target {return yy::ConfigParser::make_TARGET(loc); }
up { return yy::ConfigParser::make_UP(loc); }
fov { return yy::ConfigParser::make_FOV(loc); }
shape { return yy::ConfigParser::make_SHAPE(loc); }
world { return yy::ConfigParser::make_WORLD(loc); }
light { return yy::ConfigParser::make_LIGHT(loc); }
name { return yy::ConfigParser::make_NAME(loc); }
rotation { return yy::ConfigParser::make_ROTATION(loc); }
scale { return yy::ConfigParser::make_SCALE(loc); }
temperature { return yy::ConfigParser::make_TEMPERATURE(loc); }
material { return yy::ConfigParser::make_MATERIAL(loc); }
texture { return yy::ConfigParser::make_TEXTURE(loc); }
src {return yy::ConfigParser::make_SRC(loc); }
matte { return yy::ConfigParser::make_MATTE(loc); }
glossy { return yy::ConfigParser::make_GLOSSY(loc); }
metal { return yy::ConfigParser::make_METAL(loc); }
glass { return yy::ConfigParser::make_GLASS(loc); }
ior { return yy::ConfigParser::make_IOR(loc); }
roughness { return yy::ConfigParser::make_ROUGHNESS(loc); }
anisotropy { return yy::ConfigParser::make_ANISOTROPY(loc); }
distribution { return yy::ConfigParser::make_DISTRIBUTION(loc); }
diffuse { return yy::ConfigParser::make_DIFFUSE(loc); }
specular { return yy::ConfigParser::make_SPECULAR(loc); }
blinn { return yy::ConfigParser::make_BLINN(loc); }
beckmann { return yy::ConfigParser::make_BECKMANN(loc); }
ggx { return yy::ConfigParser::make_GGX(loc); }
{int}    { return yy::ConfigParser::make_INT(atoi(yytext),loc); }
{float} { return yy::ConfigParser::make_FLOAT(atof(yytext),loc); }
{string} { return yy::ConfigParser::make_STRING(yytext,loc); }
[ \t\r]            {loc.step();}
[\n]               {loc.lines(yyleng);loc.step();}
.                  {yy::ConfigParser::make_INVALID(loc);}
<<EOF>>            { return yy::ConfigParser::make_END(loc); }

%%

void ConfigDriver::scan_begin()
{
    yyin = fopen(file.c_str(), "r");
    if(!yyin)
    /* error handling */;
}

void ConfigDriver::scan_end()
{
    fclose(yyin);
}
