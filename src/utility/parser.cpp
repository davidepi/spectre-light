#include "parser.hpp"

static void parseOutFile(char* string, Settings* out)
{
    char* token = strtok(string," ");
    if(strcmp(token,"out:")==0)
    {
        token = strtok(NULL," ");
        out->output = (char*)malloc(512);
        strncpy(out->output,token,512);
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
    if(strcmp(token,"spp:")==0)
    {
        token = strtok(string," ");
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

static void parseScene()
{

}

Settings Parser::parse(const char* filename)
{
    Console.log(MESSAGE_STARTED_PARSING,"");
    size_t buf_size = 512;
    char* buf = (char*)malloc(buf_size);
    FILE* fin = fopen(filename,"r");
    Settings out;
    out.resolution[0] = 800;
    out.resolution[1] = 600;
    out.spp = 256;
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
                    if (buf[1] == 'p')
                        parseSpp(buf, &out);
                    else
                        parseScene();
                    break;
                }
                case 'c':
                    parseCamera(buf, &out);
                    break;
                default:
                    continue;
            }
        }
        fclose(fin);
    }
    else
        Console.critical("Error opening input file");
    Console.log(MESSAGE_ENDED_PARSING,"");
    return out;
}