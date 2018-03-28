/* Created,  23 Mar 2018 */
/* Last Edit 24 Mar 2018 */

%{
    #include <cstdio>
    #include <cstdlib>
    #include <vector>
    #include <geometry/vec3.hpp>
    #include <utility/console.hpp>
    
    std::vector<Vec3> vertices;
%}
%error-verbose
%define api.prefix {obj}
//type that could be returned by flex
%union
{
    int ival;
    float fval;
    char *sval;
}
%start file
%token <ival> INT "integer value"
%token <fval> FLOAT "floating point value"
%token <sval> STRING "string"
%token FACE "face declaration"
%token NORMAL "normal declaration"
%token TEXTURE "texture declaration"
%token VERTEX "vertex declaration"
%token OBJNAME "object name"
%token MTLFILE "material .mtl file path"
%token USEMTL "material name"
%token SEPARATOR " / separator"
%token ENDOFFILE "end of file"

%type <fval> float_num

%%

file:
file stmt
| ENDOFFILE
;

stmt:
FACE face_point face_point face_point
| TEXTURE float_num float_num {printf("Texture: %f %f\n",$2,$3);}
| VERTEX float_num float_num float_num {vertices.push_back(Vec3($2,$3,$4));}
| NORMAL float_num float_num float_num {printf("Normal: %f %f %f\n",$2,$3,$4);}
| USEMTL STRING         {fprintf(stdout,"Use material %s\n",$2);}
| MTLFILE STRING        {fprintf(stdout,"Parse material %s\n",$2);}
| OBJNAME STRING        {fprintf(stdout,"Object name %s\n",$2);}
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

void objFlexLexer::error(const char *s) {
    Console.critical(s);
    exit(EXIT_FAILURE);
}
