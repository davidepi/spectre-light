/* Created,  23 Mar 2018 */
/* Last Edit 24 Mar 2018 */

%{
#include <cstdlib> //for atof and atoi. They are deprecated because of lack of
                    //error handling, but lex ensures no errors
#include <climits>
#include <cerrno>
#include <string>
#include "obj_parser.tab.hh"
#include "obj_driver.hpp"
#undef yywrap
#define yywrap() 1
static yy::location loc;
%}
%option nounput
%option noinput
%option noyywrap
%option c++
int [0-9]+
float [-+]?([0-9]*\.[0-9]+|[0-9]+)([eE][-+]?[0-9]+)?
string [a-zA-Z_][^ \t\n\r]*
%{
    #define YY_USER_ACTION loc.columns(yyleng);
%}

%%

%{
    loc.step();
%}
f                  { return yy::ObjParser::make_FACE(loc);}
vn                 { return yy::ObjParser::make_NORMAL(loc); }
vt                 { return yy::ObjParser::make_TEXTURE(loc); }
vp\s[^\n\r]*[\n\r] { loc.lines();loc.step(); }
l\s[^\n\r]*[\n\r]  { loc.lines();loc.step(); }
g                  { return yy::ObjParser::make_OBJNAME(loc); }
v                  { return yy::ObjParser::make_VERTEX(loc); }
o                  { return yy::ObjParser::make_OBJNAME(loc); }
s\s[^\n\r]*[\n\r]  { loc.step(); }
mtllib             { return yy::ObjParser::make_MTLFILE(loc); }
usemtl             { return yy::ObjParser::make_USEMTL(loc); }
#[^\n\r]*[\n\r]    { loc.lines(yyleng);loc.step(); }
{int}              { return yy::ObjParser::make_INT(atoi(yytext),loc);}
{float}            { return yy::ObjParser::make_FLOAT(atof(yytext),loc);}
{string}           { return yy::ObjParser::make_STRING(yytext,loc);}
\/                 { return yy::ObjParser::make_SEPARATOR(loc); }
[ \t\r]            { loc.step(); }
\n                 { loc.lines();loc.step(); }
.                  { loc.step(); }
<<EOF>>            { return yy::ObjParser::make_END(loc); }
%%

void ObjDriver::scan_begin()
{
    yyin = fopen(file.c_str(), "r");
    if(!yyin)
    /* error handling */;
}

void ObjDriver::scan_end()
{
    fclose(yyin);
}
