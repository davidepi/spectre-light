#include "parser.hpp"

#define SETTINGS_OUT_SIZE 512

Settings::Settings()
{
    output = (char*)malloc(SETTINGS_OUT_SIZE);
    strcpy(output,"~/Desktop/test.ppm");
    resolution[0] = 800;
    resolution[1] = 600;
    spp = 256;
    ct = ORTHOGRAPHIC;
    ft = BOX;
    f_val[0] = 1;
    f_val[1] = 1;
    it = DIRECT_LIGHT;
}

Settings::~Settings()
{
    free(output);
}

static void parseOutFile(char* string, Settings* out)
{
    char* token = strtok(string," ");
    if(strcmp(token,"out:")==0)
    {
        token = strtok(NULL," ");
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
    char** savestring = &string;
    char* token = strtok_r(string," ",savestring);
    char* val;
    if(strcmp(token,"camera:")==0)
    {
        token = strtok_r(string," ",savestring); //parse camera type
        if(strcmp(token,"perspective")==0)
            out->ct = PERSPECTIVE;
        else
            out->ct = ORTHOGRAPHIC;

        token = strtok_r(string," ",savestring); //parse Vec3 position
        val = strtok(token,"(), "); //parse x
        out->camera_pos.x = (float)atof(val);
        val = strtok(NULL,"(), "); //parse y
        out->camera_pos.y = (float)atof(val);
        val = strtok(NULL,"(), "); //parse z
        out->camera_pos.z = (float)atof(val);

        token = strtok_r(string," ",savestring); //parse Vec3 target
        val = strtok(token,"(), "); //parse x
        out->camera_target.x = (float)atof(val);
        val = strtok(NULL,"(), "); //parse y
        out->camera_target.y = (float)atof(val);
        val = strtok(NULL,"(), "); //parse z
        out->camera_target.z = (float)atof(val);

        token = strtok_r(string," ",savestring); //parse Vec3 up
        val = strtok(token,"(), "); //parse x
        out->camera_up.x = (float)atof(val);
        val = strtok(NULL,"(), "); //parse y
        out->camera_up.y = (float)atof(val);
        val = strtok(NULL,"(), "); //parse z
        out->camera_up.z = (float)atof(val);

        if(out->ct == PERSPECTIVE) //parse fov
        {
            token = strtok_r(string," ",savestring);
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
        token = strtok(NULL," ");
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

static void parseScene()
{

}

Settings Parser::parse(const char* filename)
{
    Console.log(MESSAGE_STARTED_PARSING,NULL);
    size_t buf_size = 512;
    char* buf = (char*)malloc(buf_size);
    FILE* fin = fopen(filename,"r");
    Settings out;
    if(fin!=NULL)
    {
        while (getline(&buf, &buf_size, fin)!=-1)
        {
            switch (buf[0]) //call various parsers
            {
                case '#':
                    continue;
                case 'o':
                    parseOutFile(buf,&out);
                    break;
                case 'r':
                    parseResolution(buf, &out);
                    break;
                case 's':
                {
                    if (buf[1] == 'a')
                        parseSpp(buf, &out);
                    else
                        parseScene();
                    break;
                }
                case 'c':
                    parseCamera(buf, &out);
                    break;
                case 'f':
                    parseFilter(buf,&out);
                    break;
                case 'i':
                    parseIntegrator(buf,&out);
                    break;
                default:
                    continue;
            }
        }
        fclose(fin);
    }
    else
        Console.critical("Error opening input file");
    Console.log(MESSAGE_ENDED_PARSING,NULL);
    return out;
}