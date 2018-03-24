%{
    #include <stdio.h>
    #include <stdlib.h>
    
    int yylex();
    int yyparse();
    FILE *yyin;
    
    void yyerror(const char *s);
    void objparser_set_facedata(int, int, int);
    extern int yylineno;
    int objparser_current_face = 0;
    typedef struct
    {
        int v;
        int vt;
        int vn;
    }objparser_face_t;
    objparser_face_t objparser_face_data[3];
%}
%error-verbose
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

%type <fval> float_num

%%

file:
file stmt
|
;

stmt:
FACE face_point face_point face_point   {}
| TEXTURE float_num float_num {printf("Texture: %f %f\n",$2,$3);}
| VERTEX float_num float_num float_num {printf("Vertex: %f %f %f\n",$2,$3,$4);}
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
INT                               { objparser_set_facedata($1,-1,-1); }
| INT SEPARATOR INT               { objparser_set_facedata($1,$3,-1); }
| INT SEPARATOR SEPARATOR INT     { objparser_set_facedata($1,-1,$4); }
| INT SEPARATOR INT SEPARATOR INT { objparser_set_facedata($1,$3,$5); }
;

%%

int main(int argc, char* argv[])
{
    FILE *myfile = fopen(argv[1], "r");
    if(!myfile)
    {
        fprintf(stderr,"Error opening file\n");
        return -1;
    }
    yyin = myfile;
    
    do
    {
        yyparse();
    }
    while(!feof(yyin));
}

void yyerror(const char *s) {
    fflush(stdout);
    fprintf(stderr,"Error at line %d: %s\n",yylineno,s);
    exit(EXIT_FAILURE);
}

void objparser_set_facedata(int v, int vt, int vn)
{
    objparser_face_data[objparser_current_face].v = v;
    objparser_face_data[objparser_current_face].vt = vt;
    objparser_face_data[objparser_current_face].vn = vn;
    objparser_current_face++;
    if(objparser_current_face>2)
    {
        printf("Face: %d/%d/%d %d/%d/%d %d/%d/%d\n",
        objparser_face_data[0].v,
        objparser_face_data[0].vt,
        objparser_face_data[0].vn,
        objparser_face_data[1].v,
        objparser_face_data[1].vt,
        objparser_face_data[1].vn,
        objparser_face_data[2].v,
        objparser_face_data[2].vt,
        objparser_face_data[2].vn
        );
        objparser_current_face = 0;
    }
}
