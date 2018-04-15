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

Mesh* ObjParser::parse_obj(const char* path)
{
    Mesh* obj = new Mesh(1000); //initialize random number of tris
    bool res = parse(path, obj);
    if(res)
    {
        obj->finalize();
        return obj;
    }
    else
    {
        Console.warning(MESSAGE_OBJ_ERROR,path);
        delete obj;
        return NULL;
    }
}

bool ObjParser::parse(const char *path, Mesh* obj)
{
    FILE* fin = fopen(path,"r");
    std::vector<Point3>vertices;
    std::vector<Point2> textures;
    std::vector<Normal>normals;
    std::vector<Vertex>face_tmp;
    const Bsdf* current_material;
    std::string object_name = "";
    bool groups_as_names = false;
    char read_buffer[BUFFER_SIZE+1];
    char* buffer;
    char token[TOKEN_SIZE];
    int read_bytes;
    if(fin==NULL)
    {
        Console.severe(MESSAGE_INPUT_ERROR,path,strerror(errno));
        return false;
    }
    uint32_t tris = 0;
    //first pass, verts and norms
    while((read_bytes = (int)fread(read_buffer, 1, BUFFER_SIZE, fin)) != 0)
    {
        buffer = read_buffer;
        buffer[read_bytes] = END_OF_BUFFER_GUARD;
        while(*buffer != END_OF_BUFFER_GUARD)
        {
            skip_spaces(&buffer);
            switch(*buffer)
            {
                case 'v':
                {
                    buffer++;
                    switch(*buffer)
                    {
                        case 't': //textures
                        {
                            buffer++;
                            float u, v;
                            u = strtof(buffer, &buffer);
                            v = strtof(buffer, &buffer);
                            textures.emplace_back(u, v);
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
                            break;
                        }
                        default: //vertices
                        {
                            buffer++;
                            float x, y, z;
                            x = strtof(buffer, &buffer);
                            y = strtof(buffer, &buffer);
                            z = strtof(buffer, &buffer);
                            vertices.emplace_back(x, y, z);
                        }
                            //TODO: handle end of buffer
                    }
                    break;
                }
                case 'u':
                {
                    get_next_token(&buffer, token, TOKEN_SIZE);
                    if(strcmp(token, "usemtl") == 0) //usemtl keyword
                    {
                        //get material name
                        get_next_token(&buffer, token, TOKEN_SIZE);
                        //retrieve material, assuming Default mat exists
                        current_material = MtlLib.get(token);
                        if(current_material == NULL)
                            current_material = MtlLib.get_default();
                    }
                    break;
                }
                case 'o':
                {
                    buffer++;
                    get_next_token(&buffer, token, TOKEN_SIZE);
                    object_name = std::string(token);
                    break;
                }
                case 'g':
                {
                    //probably the file uses groups as object names
                    if(object_name == "" || groups_as_names)
                    {
                        groups_as_names = true;
                        buffer++;
                        get_next_token(&buffer, token, TOKEN_SIZE);
                        object_name = std::string(token);
                    }
                    //else the file uses both so skip the group name
                    break;
                }
                case 'f': //process face
                {
                    buffer++;
                    while(*buffer == ' ') //load every component of the face
                    {
                        get_next_token(&buffer, token, TOKEN_SIZE);
                        char* tk_idx = token; //token index
                        //process face
                        int vert_idx = 0;
                        int text_idx = 0;
                        int norm_idx = 0;
                        vert_idx = (int)strtol(tk_idx, &tk_idx, 10);
                        Vertex res;
                        if(*token != '\0')
                        {
                            tk_idx++;
                            if(*token != '/') //v/vt/vn
                                text_idx = (int)strtol(tk_idx, &tk_idx, 10);
                            tk_idx++;
                            norm_idx = (int)strtol(tk_idx, &tk_idx, 10);
                        }
                        //check indexes consistency
                        if(vert_idx != 0)
                        {
                            if(vert_idx<0)
                                vert_idx = (int)(vertices.size()-vert_idx);
                            else if(vert_idx>0 && vert_idx<=vertices.size())
                                vert_idx--;
                            else
                            {
                                Console.severe(MESSAGE_INDEX_OBJ,
                                               path, lineno);
                                return false;
                            }
                            res.p = vertices.at((unsigned long)vert_idx);
                        }
                        if(text_idx != 0)
                        {
                            if(text_idx<0)
                                text_idx = (int)(textures.size()-text_idx);
                            else if(text_idx>0 && text_idx<=textures.size())
                                text_idx--;
                            else
                            {
                                Console.severe(MESSAGE_INDEX_OBJ,
                                               path, lineno);
                                return false;
                            }
                            res.t = textures.at((unsigned long)text_idx);
                        }
                        if(norm_idx != 0)
                        {
                            if(norm_idx<0)
                                norm_idx = (int)(normals.size()-norm_idx);
                            else if(norm_idx>0 && norm_idx<=normals.size())
                                norm_idx--;
                            else
                            {
                                Console.severe(MESSAGE_INDEX_OBJ,
                                               path, lineno);
                                return false;
                            }
                            res.n = normals.at((unsigned long)norm_idx);
                        }
                        else
                        {
                            Console.severe(MESSAGE_MISSING_NORMALS,path);
                            return false;
                        }
                        face_tmp.push_back(res);
                    }
                    if(face_tmp.size() == 3)//triangle
                    {
                        obj->add_triangle(&face_tmp.at(0),&face_tmp.at(1),
                                          &face_tmp.at(2));
                    }
                    else if(face_tmp.size()>3)//quad or n-gon
                    {
                        obj->add_triangle(&face_tmp.at(0),&face_tmp.at(1),
                                          &face_tmp.at(2));
                        for(unsigned long i=3;i<face_tmp.size();i++)
                            obj->add_triangle(&face_tmp.at(0),&face_tmp.at(i-1),
                                              &face_tmp.at(i));
                    }
                    else //face with less than 2 vertex. not even writing to
                    {    // console
                        return false;
                    }
                    face_tmp.clear();
                    break;
                }
                default:
                    /*skip unknown line*/;
            }
            skip_line(&buffer);
            if(*buffer != END_OF_BUFFER_GUARD)
            {
                buffer++;
                lineno++;
            }
        }
    }
    return true;
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

static inline void get_next_token(char** source, char* buffer, int max_size)
{
    skip_spaces(source);
    int i = 0;
    char current = **source;
    while(current != ' ' && current != '\n' && current != '\r'
          && current != END_OF_BUFFER_GUARD)
    {
        //update buffer if there is space left
        if(i < max_size - 1) //max_size-1 is reserved for last '\0'
            buffer[i++] = current;
        (*source)++;
        current = **source;
    }
    buffer[i] = 0x0; //transform buffer to null terminated string
}
