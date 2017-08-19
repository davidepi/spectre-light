#include "parser.hpp"

#define SETTINGS_OUT_SIZE 512

Settings::Settings()
{
    output = (char*)malloc(SETTINGS_OUT_SIZE);
    strcpy(output,"test.ppm");
    resolution[0] = 800;
    resolution[1] = 600;
    spp = 256;
    ct = ORTHOGRAPHIC;
    ft = BOX;
    f_val[0] = 1;
    f_val[1] = 1;
    it = DIRECT_LIGHT;
    sc = new Scene;
}

Settings::~Settings()
{
    free(output);
}

static void parseOutFile(char* string, Settings* out)
{
    char* token = strtok(string," \n");
    if(strcmp(token,"out:")==0)
    {
        token = strtok(NULL," \n");
        strncpy(out->output,token,SETTINGS_OUT_SIZE);
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

static void parseResolution(char* string, Settings* out)
{
    char* token = strtok(string," ");
    if(strcmp(token,"resolution:")==0)
    {
        token = strtok(NULL," ");
        out->resolution[0] = atoi(token);
        token = strtok(NULL," ");
        out->resolution[1] = atoi(token);
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

static void parseSpp(char* string, Settings* out)
{
    char* token = strtok(string," ");
    if(strcmp(token,"sampler:")==0)
    {
        token = strtok(NULL," ");
        if(strcmp(token,"random")==0)
            out->st = RANDOM;
        else
            out->st = STRATIFIED;
        token = strtok(NULL," ");
        out->spp = atoi(token);
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

static void parseCamera(char* string, Settings* out)
{
    char* savestring;
    char* token = strtok_r(string," ",&savestring);
    char* val;
    if(strcmp(token,"camera:")==0)
    {
        token = strtok_r(NULL," ",&savestring); //parse camera type
        if(strcmp(token,"perspective")==0)
            out->ct = PERSPECTIVE;
        else
            out->ct = ORTHOGRAPHIC;

        token = strtok_r(NULL," ",&savestring); //parse Vec3 position
        val = strtok(token,"(), "); //parse x
        out->camera_pos.x = (float)atof(val);
        val = strtok(NULL,"(), "); //parse y
        out->camera_pos.y = (float)atof(val);
        val = strtok(NULL,"(), "); //parse z
        out->camera_pos.z = (float)atof(val);

        token = strtok_r(NULL," ",&savestring); //parse Vec3 target
        val = strtok(token,"(), "); //parse x
        out->camera_target.x = (float)atof(val);
        val = strtok(NULL,"(), "); //parse y
        out->camera_target.y = (float)atof(val);
        val = strtok(NULL,"(), "); //parse z
        out->camera_target.z = (float)atof(val);

        token = strtok_r(NULL," ",&savestring); //parse Vec3 up
        val = strtok(token,"(), "); //parse x
        out->camera_up.x = (float)atof(val);
        val = strtok(NULL,"(), "); //parse y
        out->camera_up.y = (float)atof(val);
        val = strtok(NULL,"(), "); //parse z
        out->camera_up.z = (float)atof(val);

        if(out->ct == PERSPECTIVE) //parse fov
        {
            token = strtok_r(NULL," ",&savestring);
            out->camera_fov = toRad(atof(token));
        }
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

static void parseFilter(char* string, Settings* out)
{
    char* token = strtok(string," ");
    if(strcmp(token,"filter:")==0)
    {
        token = strtok(NULL," "); //parse camera type
        if(strcmp(token,"box")==0)
            out->ft = BOX;
        else if(strcmp(token,"tent")==0)
            out->ft = TENT;
        else if(strcmp(token,"gaussian")==0)
        {
            out->ft = GAUSSIAN;
            token = strtok(NULL," ");
            out->f_val[0] = (float)atof(token);
        }
        else if(strcmp(token,"mitchell")==0)
        {
            out->ft = MITCHELL;
            token = strtok(NULL," ");
            out->f_val[0] = (float)atof(token);
            token = strtok(NULL," ");
            out->f_val[1] = (float)atof(token);
        }
        else
        {
            out->ft = LANCZOS;
            token = strtok(NULL, " ");
            out->f_val[0] = (float) atof(token);
        }
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

static void parseIntegrator(char* string, Settings* out)
{
    char* token = strtok(string," ");
    if(strcmp(token,"integrator:")==0)
    {
        token = strtok(NULL," \n");
        if(strcmp(token,"direct")==0)
            out->it = DIRECT_LIGHT;
        else
            out->it = PATH_TRACE;
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

static void parseMaterial(char* string, Settings* out)
{
    char* stringpos;
    char* token = strtok_r(string," ",&stringpos);
    unsigned char r,g,b;
    char* val;
    Bdf* addme;
    if(strcmp(token,"material:")==0)
    {
        char name[64];
        Bsdf* mat;
        token = strtok_r(NULL," ",&stringpos);
        strncpy(name,token,64);
        mat = MtlLib.edit(name); //retrieve material
        if(mat==NULL) //new material
        {
            mat = new Bsdf();
            MtlLib.add(name,mat);
        }
        token = strtok_r(NULL," ",&stringpos); //retrieve material type
        if(strcmp(token,"diffuse")==0)
        {
            token = strtok_r(NULL," ",&stringpos); //parse diffuse color in rgb
            val = strtok(token,"(), "); //parse x
            r = (unsigned char)atoi(val);
            val = strtok(NULL,"(), "); //parse y
            g = (unsigned char)atoi(val);
            val = strtok(NULL,"(), "); //parse z
            b = (unsigned char)atoi(val);
            Color diffuse(r,g,b);

            token = strtok_r(NULL," ",&stringpos); //parse roughness value
            float rough = (float)atof(token);
            if(rough>0) //oren-nayar
                addme = new OrenNayar(diffuse,rough);
            else //lambertian
                addme = new Lambertian(diffuse);
        }
        else if(strcmp(token,"reflection")==0)
        {
            token = strtok_r(NULL," ",&stringpos);//parse reflected color, rgb
            val = strtok(token,"(), "); //parse x
            r = (unsigned char)atoi(val);
            val = strtok(NULL,"(), "); //parse y
            g = (unsigned char)atoi(val);
            val = strtok(NULL,"(), "); //parse z
            b = (unsigned char)atoi(val);
            Color reflected(r,g,b);

            token = strtok_r(NULL," ",&stringpos);
            if(token[0]=='(') //conductor
            {
                val = strtok(token,"(), "); //parse x
                r = (unsigned char)atoi(val);
                val = strtok(NULL,"(), "); //parse y
                g = (unsigned char)atoi(val);
                val = strtok(NULL,"(), "); //parse z
                b = (unsigned char)atoi(val);
                Color absorbed(r,g,b);

                token = strtok_r(NULL," ",&stringpos);
                val = strtok(token,"(), "); //parse x
                r = (unsigned char)atoi(val);
                val = strtok(NULL,"(), "); //parse y
                g = (unsigned char)atoi(val);
                val = strtok(NULL,"(), "); //parse z
                b = (unsigned char)atoi(val);
                Color emitted(r,g,b);

                addme = new Reflection(reflected,absorbed,emitted);
            }
            else //dielectric
            {
                float etai = (float)atof(token);

                token = strtok_r(NULL," ",&stringpos); //parse ior transmitted
                float etat = (float)atof(token);

                addme = new Reflection(reflected,etai,etat);
            }
        }
        else if(strcmp(token,"refraction")==0)
        {
            token = strtok_r(NULL," ",&stringpos);//parse refracted color, rgb
            val = strtok(token,"(), "); //parse x
            r = (unsigned char)atoi(val);
            val = strtok(NULL,"(), "); //parse y
            g = (unsigned char)atoi(val);
            val = strtok(NULL,"(), "); //parse z
            b = (unsigned char)atoi(val);
            Color refracted(r,g,b);

            token = strtok_r(NULL," ",&stringpos); //parse ior incident
            float etai = (float)atof(token);

            token = strtok_r(NULL," ",&stringpos); //parse ior transmitted
            float etat = (float)atof(token);

            addme = new Refraction(refracted,etai,etat);
        }
        else;
        mat->inheritBdf(addme);
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

static void parseShape(char* string, std::unordered_map<std::string,int>* map,
                        Settings* out)
{
    char* token = strtok(string," \n");
    if(strcmp(token,"asset:")==0)
    {
        std::string name(strtok(NULL," \n"));
        token = strtok(NULL," \n");
        Shape* res;
        if(strcmp(token,"sphere")==0) //sdl sphere
            res = new Sphere((float)atof(strtok(NULL," \n")));
        else
        {
            res = parseObj(token);
            Mesh* mesh = (Mesh*)res;
            //otherwise adding the mesh to the world will fail miserably
            mesh->finalize();
        }
        if(res!=NULL)
            map->insert(std::make_pair(name,out->sc->inheritShape(res)));
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

static void parseLight(char* string, std::unordered_map<std::string,int>* map,
                       Settings* out)
{
    char* pos;
    char* token = strtok_r(string," \n",&pos);

    if(strcmp(token,"light:")==0)
    {
        std::string name(strtok_r(NULL," \n",&pos));
        std::unordered_map<std::string,int>::const_iterator got=map->find(name);
        if(got!=map->end())
        {
            char* val;
            float x,y,z;
            unsigned char r,g,b;

            //parse position
            token = strtok_r(NULL," ",&pos);//parse refracted color, rgb
            val = strtok(token,"(), "); //parse x
            x = (float)atof(val);
            val = strtok(NULL,"(), "); //parse y
            y = (float)atof(val);
            val = strtok(NULL,"(), "); //parse z
            z = (float)atof(val);

            Matrix4* m = new Matrix4();
            m->setTranslation(Vec3(x,y,z));

            //parse spectrum
            token = strtok_r(NULL," ",&pos);//parse refracted color, rgb
            val = strtok(token,"(), "); //parse x
            r = (unsigned char)atoi(val);
            val = strtok(NULL,"(), "); //parse y
            g = (unsigned char)atoi(val);
            val = strtok(NULL,"(), "); //parse z
            b = (unsigned char)atoi(val);

            out->sc->addLight(got->second,m,Color(r,g,b));
        }
        else
        {
            char outm[256];
            //string not in localization.h since this parses will be changed
            snprintf(outm,256,"Could not find asset %s",name.c_str());
            Console.warning(outm);
        }
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

static void parseWorld(char* string, std::unordered_map<std::string,int>* map,
                       Settings* out)
{
    char* pos;
    char* token = strtok_r(string," \n",&pos);

    if(strcmp(token,"world:")==0)
    {
        std::string name(strtok_r(NULL," \n",&pos));
        const Bsdf* mat = MtlLib.get(strtok_r(NULL," \n",&pos));
        if(mat == NULL)
        {
            char outm[256];
            //string not in localization.h since this parses will be changed
            snprintf(outm,256,"Could not find material for %s",name.c_str());
            Console.warning(outm);
            return;
        }
        std::unordered_map<std::string,int>::const_iterator got=map->find(name);
        if(got!=map->end())
        {
            char* val;
            float x,y,z;

            //parse position
            token = strtok_r(NULL," ",&pos);//parse refracted color, rgb
            val = strtok(token,"(), "); //parse x
            x = (float)atof(val);
            val = strtok(NULL,"(), "); //parse y
            y = (float)atof(val);
            val = strtok(NULL,"(), "); //parse z
            z = (float)atof(val);

            Matrix4* m = new Matrix4();
            m->setTranslation(Vec3(x,y,z));

            out->sc->addAsset(got->second,m,mat);
        }
        else
        {
            char outm[256];
            //string not in localization.h since this parses will be changed
            snprintf(outm,256,"Could not find asset %s",name.c_str());
            Console.warning(outm);
        }
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

void Parser::parse(const char* filename, Settings* out)
{
    Console.log(MESSAGE_STARTED_PARSING,NULL);
    size_t buf_size = 512;
    char* buf = (char*)malloc(buf_size);
    FILE* fin = fopen(filename,"r");
    if(fin!=NULL)
    {
        while (getline(&buf, &buf_size, fin)!=-1) //first pass
        {
            switch (buf[0]) //call various parsers
            {
                case '#':
                    continue;
                case 'o':
                    parseOutFile(buf,out);
                    break;
                case 'r':
                    parseResolution(buf, out);
                    break;
                case 's':
                    parseSpp(buf, out);
                    break;
                case 'c':
                    parseCamera(buf, out);
                    break;
                case 'f':
                    parseFilter(buf,out);
                    break;
                case 'i':
                    parseIntegrator(buf,out);
                    break;
                case 'm':
                    parseMaterial(buf,out);
                    break;
                case 'a':
                    parseShape(buf, &(Parser::shapeids), out);
                    break;
                default:
                    continue;
            }
        }
        fseek(fin,0,SEEK_SET);//restart from beginning of file
        while (getline(&buf, &buf_size, fin)!=-1)//second pass, world and lights
        {
            switch (buf[0])
            {
                case '#':
                    continue;
                case 'l':
                    parseLight(buf, &(Parser::shapeids), out);
                    break;
                case 'w':
                    parseWorld(buf, &(Parser::shapeids), out);
                    break;
                default:
                    continue;
            }
        }
        fclose(fin);
        free(buf);
    }
    else
        Console.critical("Error opening input file");
    Console.log(MESSAGE_ENDED_PARSING,NULL);
}