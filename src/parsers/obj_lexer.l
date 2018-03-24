/* Created,  23 Mar 2018 */
/* Last Edit 24 Mar 2018 */

%option yylineno
%{
#include <stdlib.h> //for atof and atoi. They are deprecated because of lack of
                    //error handling, but lex ensures no errors
#include <string.h>
#include "obj_parser.tab.h"
%}
%%
f                  { return FACE;}
vn                 { return NORMAL; }
vt                 { return TEXTURE;}
vp\s[^\n\r]*[\n\r] /* skip */ ;
l\s[^\n\r]*[\n\r]  /* skip */ ;
v                  { return VERTEX; }
o                  { return OBJNAME; }
g                  { return OBJNAME; }
s\s[^\n\r]*[\n\r]    /* skip */ ;
mtllib             { return MTLFILE; }
usemtl             { return USEMTL; }
#[^\n]*[\n\r]      /* skip */ ;
[0-9]+             { yylval.ival = atoi(yytext); return INT;}
[-+]?([0-9]*\.[0-9]+|[0-9]+)([eE][-+]?[0-9]+)? { yylval.fval = atof(yytext); return FLOAT;}
[a-zA-Z_][^ \t\n]* { yylval.sval = strdup(yytext); return STRING;}
\/                 { return SEPARATOR; }
[ \t\r\n]          /* skip */ ;
.                  /* skip */ ;
%%
