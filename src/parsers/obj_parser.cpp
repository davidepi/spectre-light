#include "obj_parser.hpp"

#define BUFFER_SIZE 4096
#define END_OF_BUFFER_GUARD 0x7 //unused ASCII char, keep it as kinda EOF
#define TOKEN_SIZE 255

static inline void skip_spaces(char** source);
static inline void skip_line(char** source);
static inline void get_next_token(char **source, char *buffer, int max_size);

ObjParser::ObjParser()
{
    lineno = 1;
}

void ObjParser::parse_obj(const char *path)
{
    FILE* fin = fopen(path,"r");
    std::vector<Point3>vertices;
    std::vector<Vec2> textures;
    std::vector<Normal>normals;
    const Bsdf* current_material;
    std::string object_name = "";
    bool groups_as_names = false;
    char read_buffer[BUFFER_SIZE+1];
    char* buffer;
    char token[TOKEN_SIZE];
    int read_bytes;
    if(fin!=NULL)
    {
        uint32_t tris = 0;
        //first pass, verts and norms
        while ((read_bytes = (int)fread(read_buffer,1,BUFFER_SIZE, fin)) != 0)
        {
            buffer = read_buffer;
            buffer[read_bytes] = END_OF_BUFFER_GUARD;
            while(*buffer!=END_OF_BUFFER_GUARD)
            {
                skip_spaces(&buffer);
                switch (*buffer)
                {
                    case 'v':
                    {
                        buffer++;
                        switch (*buffer)
                        {
                            case 't': //textures
                            {
                                buffer++;
                                float u, v;
                                u = strtof(buffer, &buffer);
                                v = strtof(buffer, &buffer);
                                textures.emplace_back(u, v);
                                fprintf(stdout, "Line %d: texture(%f,%f)\n",
                                        lineno,
                                        u, v);
                                break;
                            }
                            case 'n': //normals
                            {
                                buffer++;
                                float x, y, z;
                                x = strtof(buffer, &buffer);
                                y = strtof(buffer, &buffer);
                                z = strtof(buffer, &buffer);
                                normals.emplace_back(x, y, z);
                                fprintf(stdout, "Line %d: normal(%f,%f,%f)\n",
                                        lineno, x, y, z);
                                break;
                            }
                            default: //vertices
                            {
                                buffer++;
                                float x, y, z;
                                x = strtof(buffer, &buffer);
                                y = strtof(buffer, &buffer);
                                z = strtof(buffer, &buffer);
                                fprintf(stdout, "Line %d: vertex(%f,%f,%f)\n",
                                        lineno, x, y, z);
                                vertices.emplace_back(x, y, z);
                            }
                                //TODO: handle end of buffer
                        }
                        break;
                    }
                    case 'u':
                    {
                        get_next_token(&buffer, token, TOKEN_SIZE);
                        if (strcmp(token, "usemtl") == 0) //usemtl keyword
                        {
                            //get material name
                            get_next_token(&buffer, token, TOKEN_SIZE);
                            //retrieve material, assuming Default mat exists
                            current_material = MtlLib.get(token);
                            if (current_material == NULL)
                                current_material = MtlLib.get_default();
                            printf("Line %d: material: %s\n",lineno,token);
                        }
                        break;
                    }
                    case 'o':
                    {
                        buffer++;
                        get_next_token(&buffer, token, TOKEN_SIZE);
                        object_name = std::string(token);
                        printf("Line %d: name: %s\n",lineno,token);
                        break;
                    }
                    case 'g':
                    {
                        //probably the file uses groups as object names
                        if(object_name=="" || groups_as_names)
                        {
                            groups_as_names = true;
                            buffer++;
                            get_next_token(&buffer, token, TOKEN_SIZE);
                            object_name = std::string(token);
                            printf("Line %d: name: %s\n",lineno,token);
                        }
                        //else the file uses both so skip the group name
                        break;
                    }
                    default:
                        /*skip unknown line*/;
                }
                skip_line(&buffer);
                if(*buffer!=END_OF_BUFFER_GUARD)
                {
                    buffer++;
                    lineno++;
                }
            }
        }
    }
}

static inline void skip_spaces(char** source)
{
    while(**source==' ' || **source=='\t')
        (*source)++;
}

static inline void skip_line(char** source)
{
    while(**source!='\n' && **source!=END_OF_BUFFER_GUARD)
        (*source)++;
}

static inline void get_next_token(char **source, char *buffer, int max_size)
{
    skip_spaces(source);
    int i=0;
    char current = **source;
    while(current!=' ' && current!='\n' && current!='\r'
          && current!=END_OF_BUFFER_GUARD)
    {
        //update buffer if there is space left
        if(i<max_size-1) //max_size-1 is reserved for last '\0'
            buffer[i++] = current;
        (*source)++;
        current = **source;
    }
    buffer[i] = 0x0; //transform buffer to null terminated string
}
