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
%option nounistd
%option never-interactive
uint \+?[0-9]+
int -[0-9]+
float [-+]?([0-9]*\.[0-9]+|[0-9]+)([eE][-+]?[0-9]+)?
string (\"(\\.|[^\\"])*\")|('(\\.|[^'])*')
silver [Aa][Gg]
aluminium [Aa][Ll]
gold [Aa][Uu]
copper [Cc][Uu]
iron [Ff][Ee]
mercury [Hh][Gg]
lead [Pp][Bb]
platinum [Pp][Tt]
tungsten [Ww]
beryllium [Bb][Ee]
bismuth [Bb][Ii]
cobalt [Cc][Oo]
chromium [Cc][Rr]
germanium [Gg][Ee]
potassium [Kk]
lithium [Ll][Ii]
magnesium [Mm][Gg]
manganese [Mm][Nn]
molybdenum [Mm][Oo]
sodium [Nn][Aa]
niobium [Nn][Bb]
nickel [Nn][Ii]
palladium [Pp][Dd]
rhodium [Rr][Hh]
tantalum [Tt][Aa]
titanium [Tt][Ii]
vanadium [Vv]
zinc [Zz][Nn]
zirconium [Zz][Rr]

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
path         { UPDATE_POS; return yy::ConfigParser::make_PATH_TRACE(loc); }
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
unfiltered { UPDATE_POS; return yy::ConfigParser::make_UNFILTERED(loc); }
trilinear { UPDATE_POS; return yy::ConfigParser::make_TRILINEAR(loc); }
ewa {UPDATE_POS; return yy::ConfigParser::make_EWA(loc); }
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
shift { UPDATE_POS; return yy::ConfigParser::make_SHIFT(loc); }
temperature { UPDATE_POS; return yy::ConfigParser::make_TEMPERATURE(loc); }
material { UPDATE_POS; return yy::ConfigParser::make_MATERIAL(loc); }
dualmaterial {UPDATE_POS; return yy::ConfigParser::make_DUALMATERIAL(loc);}
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
bump {/* UPDATE_POS; return yy::ConfigParser::make_BUMP(loc); */}
normal {UPDATE_POS; return yy::ConfigParser::make_NORMAL(loc);}
blinn { UPDATE_POS; return yy::ConfigParser::make_BLINN(loc); }
beckmann { UPDATE_POS; return yy::ConfigParser::make_BECKMANN(loc); }
ggx { UPDATE_POS; return yy::ConfigParser::make_GGX(loc); }
color {UPDATE_POS; return yy::ConfigParser::make_COLOR(loc);}
element {UPDATE_POS; return yy::ConfigParser::make_ELEM(loc);}
"using channel R" {UPDATE_POS; return yy::ConfigParser::make_CHNR(loc);}
"using channel G" {UPDATE_POS; return yy::ConfigParser::make_CHNG(loc);}
"using channel B" {UPDATE_POS; return yy::ConfigParser::make_CHNB(loc);}
"using channel A" {UPDATE_POS; return yy::ConfigParser::make_CHNA(loc);}
inverted {UPDATE_POS; return yy::ConfigParser::make_INV(loc);}
mask {UPDATE_POS; return yy::ConfigParser::make_MASK(loc);}
first {UPDATE_POS; return yy::ConfigParser::make_FIRST(loc);}
second {UPDATE_POS; return yy::ConfigParser::make_SECOND(loc);}
radius {UPDATE_POS; return yy::ConfigParser::make_RADIUS(loc);}
falloff {UPDATE_POS; return yy::ConfigParser::make_FALLOFF(loc);}
omni {UPDATE_POS; return yy::ConfigParser::make_OMNI(loc);}
spot {UPDATE_POS; return yy::ConfigParser::make_SPOT(loc);}
area {UPDATE_POS; return yy::ConfigParser::make_AREA(loc);}
{uint}    { UPDATE_POS; return yy::ConfigParser::make_UINT(atoi(yytext),loc); }
{int}    { UPDATE_POS; return yy::ConfigParser::make_INT(atoi(yytext),loc); }
{float} { UPDATE_POS; return yy::ConfigParser::make_FLOAT(atof(yytext),loc); }
{string} { UPDATE_POS; return yy::ConfigParser::make_STRING(yytext,loc); }
{silver} { UPDATE_POS; return yy::ConfigParser::make_SILVER(loc);}
{aluminium} { UPDATE_POS; return yy::ConfigParser::make_ALUMINIUM(loc);}
{gold} { UPDATE_POS; return yy::ConfigParser::make_GOLD(loc);}
{copper} { UPDATE_POS; return yy::ConfigParser::make_COPPER(loc);}
{iron} { UPDATE_POS; return yy::ConfigParser::make_IRON(loc);}
{mercury} { UPDATE_POS; return yy::ConfigParser::make_MERCURY(loc);}
{lead} { UPDATE_POS; return yy::ConfigParser::make_LEAD(loc);}
{platinum} { UPDATE_POS; return yy::ConfigParser::make_PLATINUM(loc);}
{tungsten} { UPDATE_POS; return yy::ConfigParser::make_TUNGSTEN(loc);}
{beryllium} {UPDATE_POS; return yy::ConfigParser::make_BERYLLIUM(loc);}
{bismuth} {UPDATE_POS; return yy::ConfigParser::make_BISMUTH(loc);}
{cobalt} {UPDATE_POS; return yy::ConfigParser::make_COBALT(loc);}
{chromium} {UPDATE_POS; return yy::ConfigParser::make_CHROMIUM(loc);}
{germanium} {UPDATE_POS; return yy::ConfigParser::make_GERMANIUM(loc);}
{potassium} {UPDATE_POS; return yy::ConfigParser::make_POTASSIUM(loc);}
{lithium} {UPDATE_POS; return yy::ConfigParser::make_LITHIUM(loc);}
{magnesium} {UPDATE_POS; return yy::ConfigParser::make_MAGNESIUM(loc);}
{manganese} {UPDATE_POS; return yy::ConfigParser::make_MANGANESE(loc);}
{molybdenum} {UPDATE_POS; return yy::ConfigParser::make_MOLYBDENUM(loc);}
{sodium} {UPDATE_POS; return yy::ConfigParser::make_SODIUM(loc);}
{niobium} {UPDATE_POS; return yy::ConfigParser::make_NIOBIUM(loc);}
{nickel} {UPDATE_POS; return yy::ConfigParser::make_NICKEL(loc);}
{palladium} {UPDATE_POS; return yy::ConfigParser::make_PALLADIUM(loc);}
{rhodium} {UPDATE_POS; return yy::ConfigParser::make_RHODIUM(loc);}
{tantalum} {UPDATE_POS; return yy::ConfigParser::make_TANTALUM(loc);}
{titanium} {UPDATE_POS; return yy::ConfigParser::make_TITANIUM(loc);}
{vanadium} {UPDATE_POS; return yy::ConfigParser::make_VANADIUM(loc);}
{zinc} {UPDATE_POS; return yy::ConfigParser::make_ZINC(loc);}
{zirconium} {UPDATE_POS; return yy::ConfigParser::make_ZIRCONIUM(loc);}
#[^\n\r]* {UPDATE_POS; loc.step();}
[ \t\r]   {UPDATE_POS; loc.step();}
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

int ConfigDriver::get_line(char* buf,int len)
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
