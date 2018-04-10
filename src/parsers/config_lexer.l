/* Created   24 Mar 2018 */
/* Last Edit  3 Apr 2018 */

%{
#include <cstdlib> //for atof and atoi. They are deprecated because of lack of
                      //error handling, but lex ensures no errors
#include <climits>
#include <cerrno>
#include <string>
#include <cstring>
#include "parsers/config_parser.tab.hh"
#include "parsers/config_driver.hpp"
#undef yywrap
#define yywrap() 1
static yy::location loc;
long int current_pos;
long int last_line_pos;
%}
%option nounput
%option noinput
%option noyywrap
uint \+?[0-9]+
int -[0-9]+
float [-+]?([0-9]*\.[0-9]+|[0-9]+)([eE][-+]?[0-9]+)?
string (\"(\\.|[^\\"])*\")|('(\\.|[^'])*')
%{
    #define YY_USER_ACTION loc.columns(yyleng);
    #define UPDATE_POS current_pos+=strlen(yytext)
%}

%%

%{
    loc.step();
%}
: { UPDATE_POS; return yy::ConfigParser::make_COLON(loc); }
\[ { UPDATE_POS; return yy::ConfigParser::make_OPEN_SQ(loc); }
\] { UPDATE_POS; return yy::ConfigParser::make_CLOSE_SQ(loc); }
\{ { UPDATE_POS; return yy::ConfigParser::make_OPEN_CU(loc); }
\} { UPDATE_POS; return yy::ConfigParser::make_CLOSE_CU(loc); }
, { UPDATE_POS; return yy::ConfigParser::make_COMMA(loc); }
out { UPDATE_POS; return yy::ConfigParser::make_OUTPUT(loc); }
integrator { UPDATE_POS; return yy::ConfigParser::make_INTEGRATOR(loc); }
pt         { UPDATE_POS; return yy::ConfigParser::make_PATH_TRACE(loc); }
resolution { UPDATE_POS; return yy::ConfigParser::make_RESOLUTION(loc); }
spp {UPDATE_POS; return yy::ConfigParser::make_SPP(loc); }
width { UPDATE_POS; return yy::ConfigParser::make_WIDTH(loc); }
height { UPDATE_POS; return yy::ConfigParser::make_HEIGHT(loc); }
value0 { UPDATE_POS; return yy::ConfigParser::make_VAL_0(loc); }
value1 { UPDATE_POS; return yy::ConfigParser::make_VAL_1(loc); }
sampler { UPDATE_POS; return yy::ConfigParser::make_SAMPLER(loc); }
random { UPDATE_POS; return yy::ConfigParser::make_RANDOM(loc); }
stratified { UPDATE_POS; return yy::ConfigParser::make_STRATIFIED(loc); }
filter { UPDATE_POS; return yy::ConfigParser::make_FILTER(loc); }
type { UPDATE_POS; return yy::ConfigParser::make_TYPE(loc); }
box { UPDATE_POS; return yy::ConfigParser::make_BOX(loc); }
tent { UPDATE_POS; return yy::ConfigParser::make_TENT(loc); }
triangle { UPDATE_POS; return yy::ConfigParser::make_TENT(loc); }
gauss { UPDATE_POS; return yy::ConfigParser::make_GAUSS(loc); }
gaussian { UPDATE_POS; return yy::ConfigParser::make_GAUSS(loc); }
mitchell { UPDATE_POS; return yy::ConfigParser::make_MITCHELL(loc); }
lanczos { UPDATE_POS; return yy::ConfigParser::make_LANCZOS(loc); }
camera {UPDATE_POS; return yy::ConfigParser::make_CAMERA(loc); }
perspective { UPDATE_POS; return yy::ConfigParser::make_PERSPECTIVE(loc); }
panorama {UPDATE_POS; return yy::ConfigParser::make_PANORAMA(loc); }
orthographic { UPDATE_POS; return yy::ConfigParser::make_ORTHOGRAPHIC(loc); }
position {UPDATE_POS; return yy::ConfigParser::make_POSITION(loc); }
target {UPDATE_POS; return yy::ConfigParser::make_TARGET(loc); }
up { UPDATE_POS; return yy::ConfigParser::make_UP(loc); }
fov { UPDATE_POS; return yy::ConfigParser::make_FOV(loc); }
shape { UPDATE_POS; return yy::ConfigParser::make_SHAPE(loc); }
world { UPDATE_POS; return yy::ConfigParser::make_WORLD(loc); }
light { UPDATE_POS; return yy::ConfigParser::make_LIGHT(loc); }
name { UPDATE_POS; return yy::ConfigParser::make_NAME(loc); }
rotation { UPDATE_POS; return yy::ConfigParser::make_ROTATION(loc); }
scale { UPDATE_POS; return yy::ConfigParser::make_SCALE(loc); }
temperature { UPDATE_POS; return yy::ConfigParser::make_TEMPERATURE(loc); }
material { UPDATE_POS; return yy::ConfigParser::make_MATERIAL(loc); }
texture { UPDATE_POS; return yy::ConfigParser::make_TEXTURE(loc); }
src {UPDATE_POS; return yy::ConfigParser::make_SRC(loc); }
matte { UPDATE_POS; return yy::ConfigParser::make_MATTE(loc); }
glossy { UPDATE_POS; return yy::ConfigParser::make_GLOSSY(loc); }
metal { UPDATE_POS; return yy::ConfigParser::make_METAL(loc); }
glass { UPDATE_POS; return yy::ConfigParser::make_GLASS(loc); }
ior { UPDATE_POS; return yy::ConfigParser::make_IOR(loc); }
roughness { UPDATE_POS; return yy::ConfigParser::make_ROUGHNESS(loc); }
anisotropy { UPDATE_POS; return yy::ConfigParser::make_ANISOTROPY(loc); }
distribution { UPDATE_POS; return yy::ConfigParser::make_DISTRIBUTION(loc); }
diffuse { UPDATE_POS; return yy::ConfigParser::make_DIFFUSE(loc); }
specular { UPDATE_POS; return yy::ConfigParser::make_SPECULAR(loc); }
blinn { UPDATE_POS; return yy::ConfigParser::make_BLINN(loc); }
beckmann { UPDATE_POS; return yy::ConfigParser::make_BECKMANN(loc); }
ggx { UPDATE_POS; return yy::ConfigParser::make_GGX(loc); }
{uint}    { UPDATE_POS; return yy::ConfigParser::make_UINT(atoi(yytext),loc); }
{int}    { UPDATE_POS; return yy::ConfigParser::make_INT(atoi(yytext),loc); }
{float} { UPDATE_POS; return yy::ConfigParser::make_FLOAT(atof(yytext),loc); }
{string} { UPDATE_POS; return yy::ConfigParser::make_STRING(yytext,loc); }
[ \t\r]            {UPDATE_POS; loc.step();}
[\n]     {UPDATE_POS; loc.lines(yyleng);loc.step(); last_line_pos=current_pos; }
.        {UPDATE_POS; driver.unknown_char(loc,yytext[0]);}
<<EOF>>            { UPDATE_POS; return yy::ConfigParser::make_END(loc); }

%%

void ConfigDriver::scan_begin()
{
    errno = 0;
    current_pos = 0;
    last_line_pos = 0;
    yyin = fopen(file.c_str(), "r");
    if(!yyin)
        Console.critical(MESSAGE_INPUT_ERROR,file.c_str(),strerror(errno));
}

void ConfigDriver::scan_end()
{
    fclose(yyin);
}

int ConfigDriver::get_line(char* buf,int len, int col)
{
    int line_offset = 0;
    //entire line can't fit in buffer
    //-4 because if the line is too long the last 3 chars are set to ... and
    //I don't want to show the underline ~~~~ in these characters
    if(current_pos-last_line_pos>=len-4)
    {
        line_offset = last_line_pos;
        last_line_pos = current_pos - len/2;
        line_offset = last_line_pos-line_offset;
    }
    fseek(yyin,last_line_pos,SEEK_SET);
    fread(buf,sizeof(char),len,yyin);
    int i = 0;
    while(i<len)
    {
        if(buf[i]=='\n' || buf[i]=='\r')
            buf[i] = 0;
        if(buf[i]==0)
            break;
        i++;
    }
    if(i==len)
    {
        buf[len-4] = '.';
        buf[len-3] = '.';
        buf[len-2] = '.';
        buf[len-1] = 0;
    }
    if(line_offset!=0)
    {
        buf[0] = '.';
        buf[1] = '.';
        buf[2] = '.';
    }
    return line_offset;
}
