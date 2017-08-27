#include "obj_parser.hpp"

#if defined(WIN32) || defined(WIN64)
#define strtok_r strtok_s
#define _CRT_SECURE_NO_WARNINGS //no warnings for strtok.
#endif

static bool check_extension(const char* path)
{
    const char* val = strchr(path,'.');
    if(val != NULL)
        return val[1]=='o' && val[2]=='b' && val[3]=='j';
    else
        return false;
}

Mesh* parseObj(const char* path)
{
    FILE* fin = fopen(path,"r");
    std::vector<Point3>vertices;
    std::vector<Normal>normals;
    int buf_size = 512;
    char* buf = (char*)malloc(buf_size);
    Mesh* retval = NULL;
    bool textures = false;
    if(fin!=NULL && check_extension(path))
    {
        uint32_t tris = 0;
        float x,y,z;
        while(fgets(buf, buf_size, fin)!=NULL) //first pass, verts and norms
        {
            if(buf[0]=='v' && buf[1]==' ')//vertex
            {
                strtok(buf," ");
                x = (float)atof(strtok(NULL," "));
                y = (float)atof(strtok(NULL," "));
                z = (float)atof(strtok(NULL," "));
                vertices.push_back(Point3(x,y,z));
            }
            else if(buf[0]=='v' && buf[1]=='n') //normal
            {
                strtok(buf," ");
                x = (float)atof(strtok(NULL," "));
                y = (float)atof(strtok(NULL," "));
                z = (float)atof(strtok(NULL," "));
                normals.push_back(Normal(x,y,z));
            }
            else if(buf[0]=='f' && buf[1]==' ')//face
                tris++;
            else if(buf[0]=='v' && buf[1]=='t')//texture, so expect v/vt/n faces
                textures = true;
        }
        if(tris>0)
        {
            fseek(fin, 0, SEEK_SET); //reposition to beginning
            retval = new Mesh(tris);
            Vertex a,b,c;
            char* token;
            char* pos;
            while(fgets(buf, buf_size, fin)!=NULL) //second pass, faces
            {
                if(buf[0]=='f' && buf[1]==' ')//face
                {
                    strtok_r(buf," ",&pos); //parse f
                    if(textures) //expect v/vt/vn
                    {
                        token = strtok_r(NULL," ",&pos);
                        a.p = vertices.at(atoi(strtok(token,"/"))-1);
                        strtok(NULL,"/"); //avoid vt
                        a.n = normals.at(atoi(strtok(NULL,"/"))-1);

                        token = strtok_r(NULL," ",&pos);
                        b.p = vertices.at(atoi(strtok(token,"/"))-1);
                        strtok(NULL,"/"); //avoid vt
                        b.n = normals.at(atoi(strtok(NULL,"/"))-1);

                        token = strtok_r(NULL," ",&pos);
                        c.p = vertices.at(atoi(strtok(token,"/"))-1);
                        strtok(NULL,"/"); //avoid vt
                        c.n = normals.at(atoi(strtok(NULL,"/"))-1);
                    }
                    else //expect v//vn
                    {
                        token = strtok_r(NULL," ",&pos);
                        a.p = vertices.at(atoi(strtok(token,"/"))-1);
                        a.n = normals.at(atoi(strtok(NULL,"/"))-1);

                        token = strtok_r(NULL," ",&pos);
                        b.p = vertices.at(atoi(strtok(token,"/"))-1);
                        b.n = normals.at(atoi(strtok(NULL,"/"))-1);

                        token = strtok_r(NULL," ",&pos);
                        c.p = vertices.at(atoi(strtok(token,"/"))-1);
                        c.n = normals.at(atoi(strtok(NULL,"/"))-1);
                    }
                    retval->addTriangle(&a,&b,&c);
                }
            }
        }
    }
    else
    {
        free(buf);
        Console.critical("Error opening .obj file");
    }
    return retval;
}
