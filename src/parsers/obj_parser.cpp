#include "obj_parser.hpp"

#define BUFFER_SIZE 4096
#define END_OF_BUFFER_GUARD 0x7 //unused ASCII char, keep it as kinda EOF
#define TOKEN_SIZE 255

static inline void get_next_token(char **source, char *buffer, int max_size,
                                  int* read_bytes, char* buffer_ro, FILE* in);
static inline void feed_buffer(int* read_bytes, char* buffer_ro, FILE* input);
ObjParser::ObjParser()
{
    buffer_ro = NULL;
}

ObjParser::~ObjParser()
{
    if(buffer_ro!=NULL)
        delete buffer_ro;
}

void ObjParser::start_parsing(const char *path)
{
    ObjParser::path = path;
    lineno = 1;
    fin = fopen(path,"r");
    groups_as_names = false;
    if(fin!=NULL)
    {
        buffer_ro = (char*)malloc(sizeof(char)*(BUFFER_SIZE+1));
        read_bytes = (int)fread(buffer_ro, sizeof(char), BUFFER_SIZE, fin);
        buffer_ro[read_bytes] = END_OF_BUFFER_GUARD;
        buffer = buffer_ro;
    }
    else
        Console.severe(MESSAGE_INPUT_ERROR,path,strerror(errno));
}

void ObjParser::end_parsing()
{
    fclose(fin);
    fin = NULL;
}

Mesh* ObjParser::parse()
{
    Mesh* obj = new Mesh(1000); //initialize random number of tris
    bool res = parse_internal(obj);
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

bool ObjParser::parse_internal(Mesh* obj)
{
    if(fin==NULL)
        return false;
    std::vector<Vertex>face_tmp;
    //records which materials were already used in this object
    std::unordered_map<std::string,unsigned char> used_materials;
    //the current material to be assigned to every face (should change while
    // parsing faces)
    unsigned char current_material = 0;
    //start clear
    materials.clear();
    materials.push_back(MtlLib.get_default());
    material_association.clear();
    face_no = 0;
    object_name = "";
    char token[TOKEN_SIZE];
        while(*buffer != END_OF_BUFFER_GUARD)
        {
            get_next_token(&buffer, token, TOKEN_SIZE,
                           &read_bytes, buffer_ro, fin);
            switch(token[0])
            {
                case 'v':
                {
                    switch(token[1])
                    {
                        case 't': //textures
                        {
                            float u, v;
                            get_next_token(&buffer, token, TOKEN_SIZE,
                                           &read_bytes, buffer_ro, fin);
                            u = strtof(token,NULL);
                            get_next_token(&buffer, token, TOKEN_SIZE,
                                           &read_bytes, buffer_ro, fin);
                            v = strtof(token, NULL);
                            textures.emplace_back(u, v);
                            break;
                        }
                        case 'n': //normals
                        {
                            float x, y, z;
                            get_next_token(&buffer, token, TOKEN_SIZE,
                                           &read_bytes, buffer_ro, fin);
                            x = strtof(token,NULL);
                            get_next_token(&buffer, token, TOKEN_SIZE,
                                           &read_bytes, buffer_ro, fin);
                            y = strtof(token,NULL);
                            get_next_token(&buffer, token, TOKEN_SIZE,
                                           &read_bytes, buffer_ro, fin);
                            z = strtof(token,NULL);
                            normals.emplace_back(x, y, z);
                            break;
                        }
                        default: //vertices
                        {
                            float x, y, z;
                            get_next_token(&buffer, token, TOKEN_SIZE,
                                           &read_bytes, buffer_ro, fin);
                            x = strtof(token, NULL);
                            get_next_token(&buffer, token, TOKEN_SIZE,
                                           &read_bytes, buffer_ro, fin);
                            y = strtof(token, NULL);
                            get_next_token(&buffer, token, TOKEN_SIZE,
                                           &read_bytes, buffer_ro, fin);
                            z = strtof(token, NULL);
                            vertices.emplace_back(x, y, z);
                        }
                    }
                    break;
                }
                case 'u':
                {
                    if(strcmp(token, "usemtl") == 0) //usemtl keyword
                    {
                        //get material name
                        get_next_token(&buffer, token, TOKEN_SIZE,
                                       &read_bytes, buffer_ro, fin);
                        //check if material was already used and s
                        std::unordered_map<std::string,unsigned
                        char>::const_iterator it = used_materials.find(token);
                        if(it==used_materials.end())
                        {
                            //material not used, insert into arrays
                            used_materials.insert({{token,
                                                  used_materials.size()}});
                            const Bsdf* cur_mat = MtlLib.get(token);
                            if(cur_mat==NULL)
                            {
                                cur_mat = MtlLib.get_default();
                                Console.warning(MESSAGE_MISSING_MATERIAL,
                                                token,path);
                            }
                            materials.push_back(cur_mat);
                        }
                        else
                            current_material = it->second;
                    }
                    break;
                }
                case 'o':
                {
                    //old object finished, bail out
                    if(object_name!="")
                    {
                        //since the original get_next_token already ate the 'o'
                        buffer--;
                        return true;
                    }
                    get_next_token(&buffer, token, TOKEN_SIZE,
                                   &read_bytes, buffer_ro, fin);
                    object_name = std::string(token);
                    break;
                }
                case 'g':
                {
                    if(object_name!="" && groups_as_names)
                    {
                        //since the original get_next_token already ate the 'g'
                        buffer--;
                        return true;
                    }
                    //probably the file uses groups as object names
                    if(object_name == "" || groups_as_names)
                    {
                        groups_as_names = true;
                        get_next_token(&buffer, token, TOKEN_SIZE,
                                       &read_bytes, buffer_ro, fin);
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
                        get_next_token(&buffer, token, TOKEN_SIZE,
                                       &read_bytes, buffer_ro, fin);
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
                            int vert_size = (int)vertices.size();
                            if(vert_idx<0)
                                vert_idx = vert_size - vert_idx;
                            else if(vert_idx>0 && vert_idx<=vert_size)
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
                            int text_size = (int)textures.size();
                            if(text_idx<0)
                                text_idx = text_size - text_idx;
                            else if(text_idx>0 && text_idx<=text_size)
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
                            int norm_size = (int)normals.size();
                            if(norm_idx<0)
                                norm_idx = norm_size - norm_idx;
                            else if(norm_idx>0 && norm_idx<=norm_size)
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
                        material_association.push_back(current_material);
                        face_no++;
                    }
                    else if(face_tmp.size()>3)//quad or n-gon
                    {
                        obj->add_triangle(&face_tmp.at(0),&face_tmp.at(1),
                                          &face_tmp.at(2));
                        material_association.push_back(current_material);
                        face_no++;
                        for(unsigned long i=3;i<face_tmp.size();i++)
                        {
                            obj->add_triangle(&face_tmp.at(0),
                                              &face_tmp.at(i-1),
                                              &face_tmp.at(i));
                            material_association.push_back(current_material);
                            face_no++;
                        }
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
            //skip rest of line /////////////
            while(*buffer!='\n')
            {
                if(*buffer==END_OF_BUFFER_GUARD)
                {
                    feed_buffer(&read_bytes, buffer_ro, fin);
                    buffer = buffer_ro;
                    if(*buffer == END_OF_BUFFER_GUARD) //end of file
                        return true; //TODO: check this.
                }
                buffer++;
            }
            //////////////////////////////////
            if(*buffer != END_OF_BUFFER_GUARD)
            {
                buffer++;
                lineno++;
            }
        }
    return true;
}

const std::string& ObjParser::get_mesh_name()const 
{
    return object_name;
}

unsigned char ObjParser::get_material_no()const
{
    if(materials.size()>256)
        Console.warning(MESSAGE_OVERFLOW_MATERIALS,path);
    return (unsigned char)materials.size();
}

void ObjParser::get_materials(const Bsdf** out_materials)const
{
    for(int i=0;i<min((int)materials.size(),256);i++)
        out_materials[i] = materials[i];
}

unsigned int ObjParser::get_face_no() const
{
    return face_no;
}

void ObjParser::get_material_association(unsigned char* out_association)const
{
    for(unsigned int i=0;i<face_no;i++)
        out_association[i] = material_association[i];
}

static inline void get_next_token(char** source, char* token_buf, int max_size,
                                  int* read_bytes, char* buffer_ro, FILE* input)
{
    //skip spaces
    while(**source==' ' || **source=='\t')
    {
        if(**source==END_OF_BUFFER_GUARD)
        {
            feed_buffer(read_bytes, buffer_ro, input);
            *source = buffer_ro;
            if(**source == END_OF_BUFFER_GUARD)
                return;
        }
        (*source)++;
    }
    //get token
    int i = 0;
    char current = **source;
    while(current != ' ' && current != '\n' && current != '\r')
    {
        if(**source==END_OF_BUFFER_GUARD)
        {
            feed_buffer(read_bytes, buffer_ro, input);
            *source = buffer_ro;
            if(**source == END_OF_BUFFER_GUARD) //end of file
                break; //break instead of return since I want an ok token
        }
        //update buffer if there is space left
        if(i < max_size - 1) //max_size-1 is reserved for last '\0'
            token_buf[i++] = current;
        (*source)++;
        current = **source;
    }
    token_buf[i] = 0x0; //transform buffer to null terminated string
}

static inline void feed_buffer(int* read_bytes, char* buffer_ro, FILE* input)
{
    *read_bytes = (int)fread(buffer_ro, sizeof(char), BUFFER_SIZE, input);
    buffer_ro[*read_bytes] = END_OF_BUFFER_GUARD;
}
