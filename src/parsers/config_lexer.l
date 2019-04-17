/* Created   24 Mar 2018 */
/* Last Edit  3 Apr 2018 */

%{
#include <stdlib.h> /* for atof and atoi. They are deprecated because of lack of
                       error handling, but lex ensures no errors */
#include <string.h> /* strncpy used in dequote_and_copy() */
#include "config_parser.tab.h"
#define YY_USER_ACTION yylloc.first_line = yylloc.last_line = yylineno;
long int current_pos;
long int last_line_pos;
long int cur_line;
long int line_pos;
static __inline char* dequote_and_copy(const char* old)
{
    const size_t LEN = strlen(old);
    char* target = (char*)malloc(sizeof(char)*LEN-1); /* -2 char +1 '/0' */
    strncpy(target, old+1, LEN-2);
    target[LEN-2] = 0x0;
    return target;
}
%}
%option yylineno
%option nounput
%option noinput
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
    #define UPDATE_LOC UPDATE_POS;UPDATE_COL
    #define UPDATE_COL yylloc.first_column=yylloc.last_column-(int)yyleng;
    #define UPDATE_POS current_pos+=(int)yyleng;yylloc.last_column+=(int)yyleng;
    #define ZERO_COL yylloc.first_column=1;yylloc.last_column=1;
%}

%%

: { UPDATE_LOC; return COLON; }
\[ { UPDATE_LOC; return OPEN_SQ; }
\] { UPDATE_LOC; return CLOSE_SQ; }
\{ { UPDATE_LOC; return OPEN_CU; }
\} { UPDATE_LOC; return CLOSE_CU; }
, { UPDATE_LOC; return COMMA; }
out { UPDATE_LOC; return OUTPUT; }
integrator { UPDATE_LOC; return INTEGRATOR; }
path         { UPDATE_LOC; return PATH_TRACE; }
resolution { UPDATE_LOC; return RESOLUTION; }
spp {UPDATE_LOC; return SPP; }
width { UPDATE_LOC; return WIDTH; }
height { UPDATE_LOC; return HEIGHT; }
value0 { UPDATE_LOC; return VAL_0; }
value1 { UPDATE_LOC; return VAL_1; }
sampler { UPDATE_LOC; return SAMPLER; }
random { UPDATE_LOC; return RANDOM_TOKEN; }
stratified { UPDATE_LOC; return STRATIFIED_TOKEN; }
filter { UPDATE_LOC; return FILTER; }
type { UPDATE_LOC; return TYPE; }
box { UPDATE_LOC; return BOX_TOKEN; }
tent { UPDATE_LOC; return TENT_TOKEN; }
triangle { UPDATE_LOC; return TENT_TOKEN; }
gauss { UPDATE_LOC; return GAUSS_TOKEN; }
gaussian { UPDATE_LOC; return GAUSS_TOKEN; }
mitchell { UPDATE_LOC; return MITCHELL_TOKEN; }
lanczos { UPDATE_LOC; return LANCZOS_TOKEN; }
unfiltered { UPDATE_LOC; return UNFILTERED_TOKEN; }
trilinear { UPDATE_LOC; return TRILINEAR_TOKEN; }
ewa {UPDATE_LOC; return EWA_TOKEN; }
camera {UPDATE_LOC; return CAMERA; }
perspective { UPDATE_LOC; return PERSPECTIVE_TOKEN; }
panorama {UPDATE_LOC; return PANORAMA_TOKEN; }
orthographic { UPDATE_LOC; return ORTHOGRAPHIC_TOKEN; }
position {UPDATE_LOC; return POSITION; }
target {UPDATE_LOC; return TARGET; }
up { UPDATE_LOC; return UP; }
fov { UPDATE_LOC; return FOV; }
shape { UPDATE_LOC; return SHAPE; }
world { UPDATE_LOC; return WORLD; }
light { UPDATE_LOC; return LIGHT; }
sky { UPDATE_LOC; return SKY_TOKEN;}
name { UPDATE_LOC; return NAME; }
rotation { UPDATE_LOC; return ROTATION; }
scale { UPDATE_LOC; return SCALE; }
shift { UPDATE_LOC; return SHIFT; }
temperature { UPDATE_LOC; return TEMPERATURE; }
material { UPDATE_LOC; return MATERIAL; }
dualmaterial {UPDATE_LOC; return DUALMATERIAL;}
texture { UPDATE_LOC; return TEXTURE; }
src {UPDATE_LOC; return SRC; }
matte { UPDATE_LOC; return MATTE_TOKEN; }
glossy { UPDATE_LOC; return GLOSSY_TOKEN; }
metal { UPDATE_LOC; return METAL_TOKEN; }
glass { UPDATE_LOC; return GLASS_TOKEN; }
ior { UPDATE_LOC; return IOR; }
roughness { UPDATE_LOC; return ROUGHNESS; }
anisotropy { UPDATE_LOC; return ANISOTROPY; }
distribution { UPDATE_LOC; return DISTRIBUTION; }
diffuse { UPDATE_LOC; return DIFFUSE; }
specular { UPDATE_LOC; return SPECULAR; }
bump {/* UPDATE_LOC; return BUMP; */}
normal {UPDATE_LOC; return NORMAL;}
blinn { UPDATE_LOC; return BLINN_TOKEN; }
beckmann { UPDATE_LOC; return BECKMANN_TOKEN; }
ggx { UPDATE_LOC; return GGX_TOKEN; }
color {UPDATE_LOC; return COLOR;}
element {UPDATE_LOC; return ELEM;}
channel {UPDATE_LOC; return CHANNEL_TOKEN;}
"R" {UPDATE_LOC; return CHNR;}
"G" {UPDATE_LOC; return CHNG;}
"B" {UPDATE_LOC; return CHNB;}
"A" {UPDATE_LOC; return CHNA;}
inverted {UPDATE_LOC; return INV;}
true {UPDATE_LOC; return TRUE;}
false {UPDATE_LOC; return FALSE;}
mask {UPDATE_LOC; return MASK;}
first {UPDATE_LOC; return FIRST;}
second {UPDATE_LOC; return SECOND;}
radius {UPDATE_LOC; return RADIUS;}
falloff {UPDATE_LOC; return FALLOFF;}
omni {UPDATE_LOC; return OMNI_TOKEN;}
spot {UPDATE_LOC; return SPOT_TOKEN;}
area {UPDATE_LOC; return AREA_TOKEN;}
sun {UPDATE_LOC; return SUN_TOKEN;}
time {UPDATE_LOC; return TIME;}
latitude {UPDATE_LOC; return LATITUDE;}
longitude {UPDATE_LOC; return LONGITUDE;}
elevation {UPDATE_LOC; return ELEVATION;}
{uint}    { UPDATE_LOC; yylval.uval = atoi(yytext); return UINT; }
{int}    { UPDATE_LOC; yylval.ival = atoi(yytext); return INT; }
{float} { UPDATE_LOC; yylval.fval = atof(yytext); return FLOAT; }
{string} { UPDATE_LOC; yylval.sval = dequote_and_copy(yytext); return STRING; }
{silver} { UPDATE_LOC; return SILVER;}
{aluminium} { UPDATE_LOC; return ALUMINIUM;}
{gold} { UPDATE_LOC; return GOLD;}
{copper} { UPDATE_LOC; return COPPER;}
{iron} { UPDATE_LOC; return IRON;}
{mercury} { UPDATE_LOC; return MERCURY;}
{lead} { UPDATE_LOC; return LEAD;}
{platinum} { UPDATE_LOC; return PLATINUM;}
{tungsten} { UPDATE_LOC; return TUNGSTEN;}
{beryllium} {UPDATE_LOC; return BERYLLIUM;}
{bismuth} {UPDATE_LOC; return BISMUTH;}
{cobalt} {UPDATE_LOC; return COBALT;}
{chromium} {UPDATE_LOC; return CHROMIUM;}
{germanium} {UPDATE_LOC; return GERMANIUM;}
{potassium} {UPDATE_LOC; return POTASSIUM;}
{lithium} {UPDATE_LOC; return LITHIUM;}
{magnesium} {UPDATE_LOC; return MAGNESIUM;}
{manganese} {UPDATE_LOC; return MANGANESE;}
{molybdenum} {UPDATE_LOC; return MOLYBDENUM;}
{sodium} {UPDATE_LOC; return SODIUM;}
{niobium} {UPDATE_LOC; return NIOBIUM;}
{nickel} {UPDATE_LOC; return NICKEL;}
{palladium} {UPDATE_LOC; return PALLADIUM;}
{rhodium} {UPDATE_LOC; return RHODIUM;}
{tantalum} {UPDATE_LOC; return TANTALUM;}
{titanium} {UPDATE_LOC; return TITANIUM;}
{vanadium} {UPDATE_LOC; return VANADIUM;}
{zinc} {UPDATE_LOC; return ZINC;}
{zirconium} {UPDATE_LOC; return ZIRCONIUM;}
#[^\n\r]* {UPDATE_LOC;}
[ \t]+   {UPDATE_LOC;}
[\r]     {UPDATE_POS; ZERO_COL;}
[\n]     {UPDATE_POS; ZERO_COL; cur_line++; last_line_pos=current_pos; }
.        {UPDATE_LOC; /*driver.unknown_char(loc,yytext[0]);*/}
<<EOF>>  {return END; }

%%

int yywrap(void)
{
    return 1;
}

void config_scan_begin()
{
    errno = 0;
    current_pos = 0;
    last_line_pos = 0;
    cur_line = 1;
    ZERO_COL;
}

/* get a portion of the line being parsed */
int config_get_line(char* buf, int len)
{
    int line_offset = 0;
    int i = 0;
    /*
     * entire line can't fit in buffer
     * -4 because if the line is too long the last 3 chars are set to ... and
     * I don't want to show the underline ~~~~ in these characters
     */
    if(current_pos-last_line_pos>=len-4)
    {
        line_offset = last_line_pos;
        last_line_pos = current_pos - len/2;
        line_offset = last_line_pos-line_offset;
    }
    fseek(yyin,last_line_pos,SEEK_SET);
    fread(buf,sizeof(char),len,yyin);
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
