/* Created,  23 Mar 2018 */
/* Last Edit 24 Mar 2018 */
//https://www.gnu.org/software/bison/manual/html_node/Calc_002b_002b-Parser.html

%skeleton "lalr1.cc"
%require "3.0.4"
%defines
%define parser_class_name {ObjParser}
%define api.value.type variant
%code requires
{
    #include <string>
    class ObjDriver;
}
%param{ ObjDriver& driver }
%initial-action
{
    @$.begin.filename = @$.end.filename = &driver.file;
};
%define parse.trace
%define parse.error verbose
%code
{
    #include "obj_driver.hpp"
}
%start file
%define api.token.prefix {OBJ_}
%token END 0 "end of file"
%token FACE "face declaration"
%token NORMAL "normal declaration"
%token TEXTURE "texture declaration"
%token VERTEX "vertex declaration"
%token OBJNAME "object name"
%token MTLFILE "material .mtl file path"
%token USEMTL "material name"
%token SEPARATOR " / separator"
%token <int> INT "integer value"
%token <float> FLOAT "floating point value"
%token <std::string> STRING "string"

%type <float> float_num

%%

file
: file stmt
| stmt
;

stmt:
FACE face_point face_point face_point
| TEXTURE float_num float_num
| VERTEX float_num float_num float_num
| NORMAL float_num float_num float_num
| USEMTL STRING  { std::cout<< $2 << std::endl; }
| MTLFILE STRING { std::cout<< $2 << std::endl; }
| OBJNAME STRING { std::cout<< $2 << std::endl; }
;

float_num:
INT     {$$ = (float)$1;}
| FLOAT {$$ = $1;}
;

face_point:
INT
| INT SEPARATOR INT
| INT SEPARATOR SEPARATOR INT
| INT SEPARATOR INT SEPARATOR INT
;

%%

void yy::ObjParser::error (const location_type& l, const std::string& m)
{
    driver.error(l,m);
}

void yy::ObjParser::error (const std::string& m)
{
    driver.error(m);
}
