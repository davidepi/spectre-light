%{
    #include <stdio.h>
    #include <stdlib.h>
    
    int yylex();
    int yyparse();
    FILE *yyin;
    
    void yyerror(const char *s);
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
%token <ival> INT
%token <fval> FLOAT
%token <sval> STRING
%token FACE NORMAL TEXTURE VERTEX OBJ_NAME MTLFILE USEMTL SEPARATOR OBJNAME
%type <fval> float_num

%%

file:
file stmt
|
;

stmt:
FACE face_point face_point face_point   { printf ("Face\n");}
| TEXTURE float_num float_num {printf("Texture: %f %f\n",$2,$3);}
| VERTEX float_num float_num float_num {printf("Vertex: %f %f %f\n",$2,$3,$4);}
| NORMAL float_num float_num float_num {printf("Normal: %f %f %f\n",$2,$3,$4);}
| USEMTL STRING         {fprintf(stdout,"Use material %s",$2);}
| MTLFILE STRING        {fprintf(stdout,"Parse material %s",$2);}
| OBJNAME STRING        {fprintf(stdout,"Object name %s",$2);}
;

float_num:
INT     {$$ = (float)$1;}
| FLOAT {$$ = $1;}
;

face_point:
INT { printf("Face point: %d\n",$1);}
| INT SEPARATOR INT { printf("Face point: %d/%d\n",$1,$3);}
| INT SEPARATOR SEPARATOR INT { printf("Face point: %d//%d\n",$1,$4);}
| INT SEPARATOR INT SEPARATOR INT { printf("Face point: %d/%d/%d\n",$1,$3,$5);}
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
    fprintf(stderr,"Parse error: %s\n",s);
    exit(EXIT_FAILURE);
}
