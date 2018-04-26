#include "parser_obj.hpp"

#ifdef TESTS
//extreme value to test every case
#define BUFFER_SIZE 3
#else
#define BUFFER_SIZE 4096
#endif
#define END_OF_BUFFER_GUARD 0x7 //unused ASCII char, keep it as kinda EOF
#define TOKEN_SIZE 255

static inline void get_next_token(char** source, char* buffer, int max_size,
                                  int* read_bytes, char* buffer_ro, FILE* in);

static inline void feed_buffer(int* read_bytes, char* buffer_ro, FILE* input);

ParserObj::ParserObj()
{
    buffer_ro = NULL;
    fin = NULL;
}

ParserObj::~ParserObj()
{
    if(buffer_ro != NULL)
    {
        buffer_ro = NULL;
        delete buffer_ro;
    }
}

void ParserObj::start_parsing(const char* path)
{
    ParserObj::path = path;
    lineno = 1;
    face_no = 0; //used to know when nothing was parsed
    fin = fopen(path, "r");
    groups_as_names = false;
    craft_token = '\0';
    if(buffer_ro == NULL)
        buffer_ro = (char*)malloc(sizeof(char)*(BUFFER_SIZE+1));
    if(fin != NULL)
    {
        read_bytes = (int)fread(buffer_ro, sizeof(char), BUFFER_SIZE, fin);
        buffer_ro[read_bytes] = END_OF_BUFFER_GUARD;
        buffer = buffer_ro;
    }
    else
        Console.severe(MESSAGE_INPUT_ERROR, path, strerror(errno));
}

void ParserObj::end_parsing()
{
    if(buffer_ro != NULL)
    {
        buffer_ro = NULL;
        delete buffer_ro;
    }
    if(fin != NULL)
    {
        fclose(fin);
        fin = NULL;
    }
}

bool ParserObj::get_next_mesh(Mesh* obj)
{
    face_no = 0; //avoid materials init in finalize_mesh()
    if(fin == NULL)
    {
        finalize_mesh(obj);
        return false;
    }
    std::vector<Vertex> face_tmp;
    bool retval = false;
    //records which materials were already used in this object
    std::unordered_map<std::string, unsigned char> used_materials;
    //the current material to be assigned to every face (should change while
    // parsing faces)
    unsigned char current_material = 0;
    //start clear
    materials.clear();
    //used as a boolean. Described in the 'o' and 'g' switch
    materials.push_back(MtlLib.get_default());
    material_association.clear();
    used_materials.insert({{"Default", 0}});
    object_name = "";
    char token[TOKEN_SIZE];
    while(*buffer != END_OF_BUFFER_GUARD)
    {
        if(craft_token)
        {
            token[0] = craft_token;
            token[1] = '\0';
            craft_token = 0;
        }
        else
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
                        u = strtof(token, NULL);
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
                        x = strtof(token, NULL);
                        get_next_token(&buffer, token, TOKEN_SIZE,
                                       &read_bytes, buffer_ro, fin);
                        y = strtof(token, NULL);
                        get_next_token(&buffer, token, TOKEN_SIZE,
                                       &read_bytes, buffer_ro, fin);
                        z = strtof(token, NULL);
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
                    std::unordered_map<std::string, unsigned
                    char>::const_iterator it = used_materials.find(token);
                    if(it == used_materials.end())
                    {
                        const Bsdf* cur_mat = MtlLib.get(token);
                        if(cur_mat == NULL)
                        {
                            cur_mat = MtlLib.get_default();
                            //insert as default material
                            used_materials.insert({{token, 0}});
                            current_material = 0;
                            Console.warning(MESSAGE_MISSING_MATERIAL,
                                            token, path);
                        }
                        else
                        {
                            current_material = materials.size();
                            used_materials.insert({{token, current_material}});
                            materials.push_back(cur_mat);
                        }
                    }
                    else
                        current_material = it->second;
                }
                break;
            }
            case 'o':
            {
                //old object finished, bail out
                if(object_name != "")
                {
                    //since the original get_next_token already ate the 'g'
                    //buffer needs to be decremented. But buffer could have
                    //been replaced with another fread...
                    //so with this variable I record the fact that the
                    //next switch will need to craft a 'o\0' token
                    craft_token = 'o';
                    finalize_mesh(obj);
                    return retval;
                }
                get_next_token(&buffer, token, TOKEN_SIZE,
                               &read_bytes, buffer_ro, fin);
                object_name = std::string(token);
                break;
            }
            case 'g':
            {
                if(object_name != "" && groups_as_names)
                {
                    //like in the 'o' switch, but craft a 'g' instead
                    craft_token = 'g';
                    finalize_mesh(obj);;
                    return retval;
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
                bool recreate_normals = false;
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
                    if(*tk_idx != '\0')
                    {
                        tk_idx++;
                        if(*tk_idx != '/') //v/vt/vn
                            text_idx = (int)strtol(tk_idx, &tk_idx, 10);
                        tk_idx++;
                        norm_idx = (int)strtol(tk_idx, &tk_idx, 10);
                    }
                    //check indexes consistency
                    if(vert_idx != 0)
                    {
                        int vert_size = (int)vertices.size();
                        if(vert_idx<0)
                            vert_idx = vert_size+vert_idx;
                        else if(vert_idx>0 && vert_idx<=vert_size)
                            vert_idx--;
                        else
                        {
                            Console.severe(MESSAGE_INDEX_OBJ,
                                           path, lineno);
                            finalize_mesh(obj);
                            return false;
                        }
                        res.p = vertices.at((unsigned long)vert_idx);
                    }
                    if(text_idx != 0)
                    {
                        int text_size = (int)textures.size();
                        if(text_idx<0)
                            text_idx = text_size+text_idx;
                        else if(text_idx>0 && text_idx<=text_size)
                            text_idx--;
                        else
                        {
                            Console.severe(MESSAGE_INDEX_OBJ,
                                           path, lineno);
                            finalize_mesh(obj);
                            return false;
                        }
                        res.t = textures.at((unsigned long)text_idx);
                    }
                    if(norm_idx != 0)
                    {
                        int norm_size = (int)normals.size();
                        if(norm_idx<0)
                            norm_idx = norm_size+norm_idx;
                        else if(norm_idx>0 && norm_idx<=norm_size)
                            norm_idx--;
                        else
                        {
                            Console.severe(MESSAGE_INDEX_OBJ,
                                           path, lineno);
                            finalize_mesh(obj);
                            return false;
                        }
                        res.n = normals.at((unsigned long)norm_idx);
                    }
                    else
                    {
                        recreate_normals = true;
                    }
                    face_tmp.push_back(res);
                    //  Never managed to reach this point.
                    //  TODO: try with non POSIX files
                    // if(*buffer == END_OF_BUFFER_GUARD)
                    // {
                    //     feed_buffer(&read_bytes, buffer_ro, fin);
                    //     buffer = buffer_ro;
                    // }
                }
                if(recreate_normals)
                {
                    //the normal should be created for the entire face
                    //no risk of losing info: if the normal is missing
                    //for one vertex it MUST be missing for every vertex
                    //of the face
                    Vec3 u = face_tmp[1].p-face_tmp[0].p;
                    Vec3 v = face_tmp[2].p-face_tmp[0].p;
                    Normal face_normal = (Normal)cross(u, v);
                    face_normal.normalize();
                    for(int i = 0; i<(int)face_tmp.size(); i++)
                        face_tmp[i].n = face_normal;
                }
                if(face_tmp.size() == 3)//triangle
                {
                    retval = true; //case for no-name but >1 triangle added
                    obj->add_triangle(&face_tmp.at(0), &face_tmp.at(1),
                                      &face_tmp.at(2));
                    material_association.push_back(current_material);
                    face_no++;
                }
                else if(face_tmp.size()>3)//quad or n-gon
                {
                    retval = true; //case for no-name but >1 triangle added
                    obj->add_triangle(&face_tmp.at(0), &face_tmp.at(1),
                                      &face_tmp.at(2));
                    material_association.push_back(current_material);
                    face_no++;
                    for(unsigned long i = 3; i<face_tmp.size(); i++)
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
                    finalize_mesh(obj);
                    return false;
                }
                face_tmp.clear();
                break;
            }
            default:
                /*skip unknown line*/;
        }
        //skip rest of line /////////////
        while(*buffer != '\n')
        {
            if(*buffer == END_OF_BUFFER_GUARD)
            {
                feed_buffer(&read_bytes, buffer_ro, fin);
                buffer = buffer_ro;
            }
            else
                buffer++;
        }
        //////////////////////////////////
        if(*buffer != END_OF_BUFFER_GUARD)
        {
            buffer++;
            lineno++;
            //avoid leaving buffer pointer on the guard while there
            //are still bytes to read
            if(*buffer == END_OF_BUFFER_GUARD)
            {
                feed_buffer(&read_bytes, buffer_ro, fin);
                buffer = buffer_ro;
                //if buffer is still equal END_OF_BUFFER_GUARD the file is ended
            }
        }
    }
    finalize_mesh(obj);;
    return retval;
}

void ParserObj::finalize_mesh(Mesh* obj)
{
    //finalize mesh (to avoid freeing already freed object on dealloc)
    obj->finalize();
    //set name for unnamed meshes
    if(object_name == "")
        object_name = "Unnamed";
    if(face_no>0)
    {
        //reorganize materials
        std::vector<const Bsdf*> old_materials = materials;
        materials.clear();
        //compress array of used materials
        //use counting sort to determine position
        //-1 = not used
        short index = -1;
        short count[256];
        memset(&count, index, sizeof(short)*256);
        //count the used materials and use i as their new index
        for(unsigned int i = 0; i<face_no; i++)
        {
            if(count[material_association[i]] == -1)
                count[material_association[i]] = ++index;
        }
        //update materials array
        materials.resize(index+1);
        for(short i = 0; i<256; i++)
        {
            if(count[i] != -1)
                materials[count[i]] = old_materials[i];
        }
        //update index for faces
        for(unsigned int i = 0; i<face_no; i++)
            material_association[i] = count[material_association[i]];
    }
}

const std::string& ParserObj::get_mesh_name() const
{
    return object_name;
}

unsigned char ParserObj::get_material_no() const
{
    //no checks for overflow but seriously... more than 255 materials???
    return (unsigned char)materials.size();
}

void ParserObj::get_materials(const Bsdf** out_materials) const
{
    for(int i = 0; i<min((int)materials.size(), 256); i++)
        out_materials[i] = materials[i];
}

unsigned int ParserObj::get_face_no() const
{
    return face_no;
}

void ParserObj::get_material_association(unsigned char* out_association) const
{
    for(unsigned int i = 0; i<face_no; i++)
        out_association[i] = material_association[i];
}

static inline void get_next_token(char** source, char* token_buf, int max_size,
                                  int* read_bytes, char* buffer_ro, FILE* input)
{
    char current = **source;
    //skip spaces
    while(current == ' ' || current == '\t' || current == END_OF_BUFFER_GUARD)
    {
        if(current == END_OF_BUFFER_GUARD)
        {
            feed_buffer(read_bytes, buffer_ro, input);
            *source = buffer_ro;
            current = **source;
            //should never happen
            //TODO: try with non POSIX files
            //if(current == END_OF_BUFFER_GUARD)
            //    return;
        }
        else
        {
            (*source)++;
            current = **source;
        }
    }
    //get token
    int i = 0;
    while(current != ' ' && current != '\n' && current != '\r')
    {
        if(current == END_OF_BUFFER_GUARD)
        {
            feed_buffer(read_bytes, buffer_ro, input);
            *source = buffer_ro;
            current = **source;
            //should never happen
            //TODO: try with non POSIX files
            //if(current == END_OF_BUFFER_GUARD) //end of file
            //    break; //break instead of return since I want an ok token
        }
        else
        {
            //update buffer if there is space left
            if(i<max_size-1) //max_size-1 is reserved for last '\0'
                token_buf[i++] = current;
            (*source)++;
            current = **source;
        }
    }
    token_buf[i] = 0x0; //transform buffer to null terminated string
}

static inline void feed_buffer(int* read_bytes, char* buffer_ro, FILE* input)
{
    *read_bytes = (int)fread(buffer_ro, sizeof(char), BUFFER_SIZE, input);
    buffer_ro[*read_bytes] = END_OF_BUFFER_GUARD;
}
