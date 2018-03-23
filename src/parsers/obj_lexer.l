%{
#include <stdlib.h> //for atof and atoi. They are deprecated because of lack of
                    //error handling, but lex ensures no errors
#include <string.h>
#include "obj_parser.tab.h"
#define YY_DECL int yylex()
%}
%%
f                  { return FACE;}
vn                 { return NORMAL; }
vt                 { return TEXTURE;}
vp\s[^\n]*\n       /* skip */ ;
l\s[^\n]*\n        /* skip */ ;
v                  { return VERTEX; }
o                  { return OBJNAME; }
g                  { return OBJNAME; }
s\s[^\n]*\n        /* skip */ ;
mtllib             { return MTLFILE; }
usemtl             { return USEMTL; }
#[^\n]*\n          /* skip */ ;
[0-9]+             { yylval.ival = atoi(yytext); return INT;}
[-+]?([0-9]*\.[0-9]+|[0-9]+)([eE][-+]?[0-9]+)? { yylval.fval = atof(yytext); return FLOAT;}
[a-zA-Z_][^ \t\n]* { yylval.sval = strdup(yytext); return STRING;}
[/]                { return SEPARATOR; }
[ \t\n]            /* skip */ ;
%%
