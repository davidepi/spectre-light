/**
 * \cond
 *  No documentation for files under parser/ folder since they will be replaced
 *  by flex/bison parsing as soon as possible
 */

#include "parser.hpp"

#define SETTINGS_OUT_SIZE 512
#if defined(WIN32) || defined(WIN64)
#define strtok_r strtok_s
#define _CRT_SECURE_NO_WARNINGS //no warnings for strtok
#endif

Settings::Settings()
{
    output = (char*)malloc(SETTINGS_OUT_SIZE);
    strcpy(output,"test.ppm");
    resolution[0] = 800;
    resolution[1] = 600;
    spp = 256;
    type_camera = ORTHOGRAPHIC;
    type_filter = BOX;
    f_val[0] = 1;
    f_val[1] = 1;
    type_integrator = DIRECT_LIGHT;
    scene = new Scene;
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
            out->type_sampler = RANDOM;
        else
            out->type_sampler = STRATIFIED;
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
            out->type_camera = PERSPECTIVE;
        else if(strcmp(token,"panorama")==0)
            out->type_camera = PANORAMA;
        else
            out->type_camera = ORTHOGRAPHIC;

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

        if(out->type_camera == PERSPECTIVE) //parse fov
        {
            token = strtok_r(NULL," ",&savestring);
            out->camera_fov = toRad((float)atof(token));
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
    char* token = strtok(string," \n");
    if(strcmp(token,"filter:")==0)
    {
        token = strtok(NULL," \n"); //parse camera type
        if(strcmp(token,"box")==0)
            out->type_filter = BOX;
        else if(strcmp(token,"tent")==0)
            out->type_filter = TENT;
        else if(strcmp(token,"gaussian")==0)
        {
            out->type_filter = GAUSSIAN;
            token = strtok(NULL," ");
            out->f_val[0] = (float)atof(token);
        }
        else if(strcmp(token,"mitchell")==0)
        {
            out->type_filter = MITCHELL;
            token = strtok(NULL," ");
            out->f_val[0] = (float)atof(token);
            token = strtok(NULL," ");
            out->f_val[1] = (float)atof(token);
        }
        else
        {
            out->type_filter = LANCZOS;
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
            out->type_integrator = DIRECT_LIGHT;
        else
            out->type_integrator = PATH_TRACE;
    }
    else
    {
        char outm[256];
        //string not in localization.h since this parses will be changed
        snprintf(outm,256,"Unknown keyword while parsing: %s",token);
        Console.warning(outm);
    }
}

static void parseMaterial(char* string)
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
            ColorRGB diffuse(r,g,b);

            token = strtok_r(NULL," ",&stringpos); //parse roughness value
            float rough = (float)atof(token);
            if(rough>0) //oren-nayar
                addme = new OrenNayar(Spectrum(diffuse,false),rough);
            else //lambertian
                addme = new Lambertian(Spectrum(diffuse,false));
        }
        //glossy reflection (color) <distribution> parameters
        else if(strcmp(token,"glossy")==0)
        {
            token = strtok_r(NULL," \n",&stringpos);
            Fresnel* d;
            MicrofacetDist* md;
            ColorRGB spec;
            if(strcmp(token,"reflection")==0)
            {
                token = strtok_r(NULL," \n",&stringpos);
                //parse color
                val = strtok(token,"(), "); //parse x
                r = (unsigned char)atoi(val);
                val = strtok(NULL,"(), "); //parse y
                g = (unsigned char)atoi(val);
                val = strtok(NULL,"(), "); //parse z
                b = (unsigned char)atoi(val);
                spec = ColorRGB(r,g,b);
                
                
                token = strtok_r(NULL," \n",&stringpos);
                if(token[0]!='[' && token[0]!='{') //conductor
                {
                    switch(token[0])
                    {
                        case 'A':
                            if(token[1]=='u')
                                d = new Conductor(GOLD.n,GOLD.k);
                            else if(token[1]=='g')
                                d = new Conductor(SILVER.n,SILVER.k);
                            else
                                d = new Conductor(ALUMINIUM.n,ALUMINIUM.k);
                            break;
                        case 'C':
                            d = new Conductor(COPPER.n,COPPER.k);
                            break;
                        case 'H':
                            d = new Conductor(MERCURY.n,MERCURY.k);
                            break;
                        case 'P':
                            if(token[1]=='b')
                                d = new Conductor(LEAD.n,LEAD.k);
                            else
                                d = new Conductor(PLATINUM.n,PLATINUM.k);
                            break;
                        case 'W':
                            d = new Conductor(TUNGSTEN.n,TUNGSTEN.k);
                            break;
                        case 'F':
                        default:
                            d = new Conductor(IRON.n,IRON.k);
                            break;
                    }
                }
                else
                {
                    //parse ior
                    Spectrum etai;
                    Spectrum etat;
                    if(token[0]=='[') //cauchy
                    {
                        float bb,c,d;
                        val = strtok(token,"[], ");
                        bb = (float)atof(val);
                        val = strtok(NULL,"[], ");
                        c = (float)atof(val);
                        val = strtok(NULL,"[], ");
                        d = (float)atof(val);
                        etai = Spectrum(cauchyEq(bb,c,d));
                    }
                    else
                    {
                        float b1,b2,b3,c1,c2,c3;
                        val = strtok(token,"{}, ");
                        b1 = (float)atof(val);
                        val = strtok(NULL,"{}, ");
                        b2 = (float)atof(val);
                        val = strtok(NULL,"{}, ");
                        b3 = (float)atof(val);
                        val = strtok(NULL,"{}, ");
                        c1 = (float)atof(val);
                        val = strtok(NULL,"{}, ");
                        c2 = (float)atof(val);
                        val = strtok(NULL,"{}, ");
                        c3 = (float)atof(val);
                        etai = Spectrum(sellmeierEq(b1,b2,b3,c1,c2,c3));
                    }
                    
                    token = strtok_r(NULL," ",&stringpos);
                    if(token[0]=='[') //cauchy
                    {
                        float bb,c,d;
                        val = strtok(token,"[], ");
                        bb = (float)atof(val);
                        val = strtok(NULL,"[], ");
                        c = (float)atof(val);
                        val = strtok(NULL,"[], ");
                        d = (float)atof(val);
                        etat = Spectrum(cauchyEq(bb,c,d));
                    }
                    else
                    {
                        float b1,b2,b3,c1,c2,c3;
                        val = strtok(token,"{}, ");
                        b1 = (float)atof(val);
                        val = strtok(NULL,"{}, ");
                        b2 = (float)atof(val);
                        val = strtok(NULL,"{}, ");
                        b3 = (float)atof(val);
                        val = strtok(NULL,"{}, ");
                        c1 = (float)atof(val);
                        val = strtok(NULL,"{}, ");
                        c2 = (float)atof(val);
                        val = strtok(NULL,"{}, ");
                        c3 = (float)atof(val);
                        etat = Spectrum(sellmeierEq(b1,b2,b3,c1,c2,c3));
                    }
                    d = new Dielectric(etai,etat);
                }
                
                //parse distribution
                token = strtok_r(NULL," \n",&stringpos);
                if(strcmp(token,"blinn")==0)
                {
                    //parse exponent
                    token = strtok_r(NULL," \n",&stringpos);
                    const float exponent = clamp((float)atof(token),0,10000);
                    md = new Blinn(exponent);
                }
                else if (strcmp(token,"ggx")==0)
                {
                    token = strtok_r(NULL," \n",&stringpos);
                    const float ax = clamp((float)atof(token),0.f,1.f);
                    token = strtok_r(NULL," \n",&stringpos);
                    if(token != NULL)
                    {
                        const float ay = clamp((float)atof(token),0.f,1.f);
                        md = new GGXaniso(ax,ay);
                    }
                    else
                        md = new GGXiso(ax);
                    
                }
                else //beckmann
                {
                    token = strtok_r(NULL," \n",&stringpos);
                    const float a = clamp((float)atof(token),0.f,1.f);
                    md = new Beckmann(a);
                }
                Spectrum s(spec,false);
                addme = new MicrofacetR(s,md,d);
            }
            else //refraction glossy
            {
                token = strtok_r(NULL," \n",&stringpos);
                
                //parse color
                val = strtok(token,"(), "); //parse x
                r = (unsigned char)atoi(val);
                val = strtok(NULL,"(), "); //parse y
                g = (unsigned char)atoi(val);
                val = strtok(NULL,"(), "); //parse z
                b = (unsigned char)atoi(val);
                spec = ColorRGB(r,g,b);
                
                //parse ior
                token = strtok_r(NULL," \n",&stringpos);
                Spectrum etai;
                Spectrum etat;
                if(token[0]=='[') //cauchy
                {
                    float bb,c,d;
                    val = strtok(token,"[], ");
                    bb = (float)atof(val);
                    val = strtok(NULL,"[], ");
                    c = (float)atof(val);
                    val = strtok(NULL,"[], ");
                    d = (float)atof(val);
                    etai = Spectrum(cauchyEq(bb,c,d));
                }
                else
                {
                    float b1,b2,b3,c1,c2,c3;
                    val = strtok(token,"{}, ");
                    b1 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    b2 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    b3 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c1 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c2 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c3 = (float)atof(val);
                    etai = Spectrum(sellmeierEq(b1,b2,b3,c1,c2,c3));
                }
                
                token = strtok_r(NULL," ",&stringpos);
                if(token[0]=='[') //cauchy
                {
                    float bb,c,d;
                    val = strtok(token,"[], ");
                    bb = (float)atof(val);
                    val = strtok(NULL,"[], ");
                    c = (float)atof(val);
                    val = strtok(NULL,"[], ");
                    d = (float)atof(val);
                    etat = Spectrum(cauchyEq(bb,c,d));
                }
                else
                {
                    float b1,b2,b3,c1,c2,c3;
                    val = strtok(token,"{}, ");
                    b1 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    b2 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    b3 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c1 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c2 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c3 = (float)atof(val);
                    etat = Spectrum(sellmeierEq(b1,b2,b3,c1,c2,c3));
                }
                
                //parse distribution
                token = strtok_r(NULL," \n",&stringpos);
                if(strcmp(token,"blinn")==0)
                {
                    //parse exponent
                    token = strtok_r(NULL," \n",&stringpos);
                    const float exponent = clamp((float)atof(token),0,10000);
                    md = new Blinn(exponent);
                }
                else if (strcmp(token,"ggx")==0)
                {
                    token = strtok_r(NULL," \n",&stringpos);
                    const float ax = clamp((float)atof(token),0.f,1.f);
                    token = strtok_r(NULL," \n",&stringpos);
                    if(token != NULL)
                    {
                        const float ay = clamp((float)atof(token),0.f,1.f);
                        md = new GGXaniso(ax,ay);
                    }
                    else
                        md = new GGXiso(ax);
                    
                }
                else //beckmann
                {
                    token = strtok_r(NULL," \n",&stringpos);
                    const float a = clamp((float)atof(token),0.f,1.f);
                    md = new Beckmann(a);
                }
                Spectrum s(spec,false);
                addme = new MicrofacetT(s,md,etai,etat);
            }
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
            ColorRGB reflected(r,g,b);

            token = strtok_r(NULL," ",&stringpos);
            if(token[0]!='[' && token[0]!='{') //conductor
            {
                switch(token[0])
                {
                    case 'A':
                        if(token[1]=='u')
                            addme = new ConductorReflection(
                            Spectrum(reflected,false),GOLD.n,GOLD.k);
                        else if(token[1]=='g')
                            addme = new ConductorReflection(
                            Spectrum(reflected,false),SILVER.n,SILVER.k);
                        else
                            addme = new ConductorReflection(
                            Spectrum(reflected,false),ALUMINIUM.n,ALUMINIUM.k);
                        break;
                            
                    case 'C':
                    addme = new ConductorReflection(Spectrum(reflected,false),
                                                    COPPER.n,COPPER.k);break;
                    case 'H':
                    addme = new ConductorReflection(Spectrum(reflected,false),
                                                   MERCURY.n, MERCURY.k);break;
                    case 'P':
                        if(token[1]=='b')
                           addme = new ConductorReflection(
                                     Spectrum(reflected,false),LEAD.n,LEAD.k);
                        else
                            addme = new ConductorReflection(
                            Spectrum(reflected,false),PLATINUM.n,PLATINUM.k);
                        break;
                    case 'W':
                        addme=new ConductorReflection(Spectrum(reflected,false),
                                                TUNGSTEN.n, TUNGSTEN.k);break;
                    case 'F':
                    default:
                    addme = new ConductorReflection(Spectrum(reflected,false),
                                                        IRON.n,IRON.k);break;
                }
            }
            else //dielectric
            {
                Spectrum etai;
                Spectrum etat;
                if(token[0]=='[') //cauchy
                {
                    float bb,c,d;
                    val = strtok(token,"[], ");
                    bb = (float)atof(val);
                    val = strtok(NULL,"[], ");
                    c = (float)atof(val);
                    val = strtok(NULL,"[], ");
                    d = (float)atof(val);
                    etai = Spectrum(cauchyEq(bb,c,d));
                }
                else
                {
                    float b1,b2,b3,c1,c2,c3;
                    val = strtok(token,"{}, ");
                    b1 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    b2 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    b3 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c1 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c2 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c3 = (float)atof(val);
                    etai = Spectrum(sellmeierEq(b1,b2,b3,c1,c2,c3));
                }

                token = strtok_r(NULL," ",&stringpos);
                if(token[0]=='[') //cauchy
                {
                    float bb,c,d;
                    val = strtok(token,"[], ");
                    bb = (float)atof(val);
                    val = strtok(NULL,"[], ");
                    c = (float)atof(val);
                    val = strtok(NULL,"[], ");
                    d = (float)atof(val);
                    etat = Spectrum(cauchyEq(bb,c,d));
                }
                else
                {
                    float b1,b2,b3,c1,c2,c3;
                    val = strtok(token,"{}, ");
                    b1 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    b2 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    b3 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c1 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c2 = (float)atof(val);
                    val = strtok(NULL,"{}, ");
                    c3 = (float)atof(val);
                    etat = Spectrum(sellmeierEq(b1,b2,b3,c1,c2,c3));
                }

                addme = new DielectricReflection(Spectrum(reflected,false),
                                                 etai, etat);
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
            ColorRGB refracted(r,g,b);

            Spectrum etai;
            Spectrum etat;
            token = strtok_r(NULL," ",&stringpos); //parse ior incident
            if(token[0]=='[') //cauchy
            {
                float bb,c,d;
                val = strtok(token,"[], ");
                bb = (float)atof(val);
                val = strtok(NULL,"[], ");
                c = (float)atof(val);
                val = strtok(NULL,"[], ");
                d = (float)atof(val);
                etai = Spectrum(cauchyEq(bb,c,d));
            }
            else
            {
                float b1,b2,b3,c1,c2,c3;
                val = strtok(token,"{}, ");
                b1 = (float)atof(val);
                val = strtok(NULL,"{}, ");
                b2 = (float)atof(val);
                val = strtok(NULL,"{}, ");
                b3 = (float)atof(val);
                val = strtok(NULL,"{}, ");
                c1 = (float)atof(val);
                val = strtok(NULL,"{}, ");
                c2 = (float)atof(val);
                val = strtok(NULL,"{}, ");
                c3 = (float)atof(val);
                etai = Spectrum(sellmeierEq(b1,b2,b3,c1,c2,c3));
            }
            
            token = strtok_r(NULL," ",&stringpos); //parse ior transmitted
            if(token[0]=='[') //cauchy
            {
                float bb,c,d;
                val = strtok(token,"[], ");
                bb = (float)atof(val);
                val = strtok(NULL,"[], ");
                c = (float)atof(val);
                val = strtok(NULL,"[], ");
                d = (float)atof(val);
                etat = Spectrum(cauchyEq(bb,c,d));
            }
            else
            {
                float b1,b2,b3,c1,c2,c3;
                val = strtok(token,"{}, ");
                b1 = (float)atof(val);
                val = strtok(NULL,"{}, ");
                b2 = (float)atof(val);
                val = strtok(NULL,"{}, ");
                b3 = (float)atof(val);
                val = strtok(NULL,"{}, ");
                c1 = (float)atof(val);
                val = strtok(NULL,"{}, ");
                c2 = (float)atof(val);
                val = strtok(NULL,"{}, ");
                c3 = (float)atof(val);
                etat = Spectrum(sellmeierEq(b1,b2,b3,c1,c2,c3));
            }

            addme = new Refraction(Spectrum(refracted,false),etai,etat);
        }
        else
            return;
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
    char* pos;
    char* token = strtok_r(string," \n", &pos);
    if(strcmp(token,"asset:")==0)
    {
        std::string name(strtok_r(NULL," \n",&pos));
        token = strtok_r(NULL," \n",&pos);
        Shape* res;
        if(strcmp(token,"sphere")==0) //sdl sphere
            res = new Sphere();
        else if(strcmp(token, "box")==0)
            res = new Box();
        else
        {
            res = parseObj(token);
            Mesh* mesh = (Mesh*)res;
            //otherwise adding the mesh to the world will fail miserably
            mesh->finalize();
        }
        if(res!=NULL)
            map->insert(std::make_pair(name,out->scene->inheritShape(res)));
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
            Matrix4* m = new Matrix4();
            m->setIdentity();
            Matrix4 trans,rotx,roty,rotz,scale;

            //parse position
            token = strtok_r(NULL," ",&pos);//parse refracted color, rgb
            val = strtok(token,"(), "); //parse x
            x = (float)atof(val);
            val = strtok(NULL,"(), "); //parse y
            y = (float)atof(val);
            val = strtok(NULL,"(), "); //parse z
            z = (float)atof(val);
            trans.setTranslation(Vec3(x,y,z));

            token = strtok_r(NULL," ",&pos);//parse rotation
            val = strtok(token,"(), "); //parse x
            x = (float)atof(val);
            val = strtok(NULL,"(), "); //parse y
            y = (float)atof(val);
            val = strtok(NULL,"(), "); //parse z
            z = (float)atof(val);
            rotx.setRotateX(toRad(x));
            roty.setRotateY(toRad(y));
            rotz.setRotateZ(toRad(z));

            token = strtok_r(NULL," ",&pos);//parse translation
            val = strtok(token,"(), "); //parse x
            x = (float)atof(val);
            val = strtok(NULL,"(), "); //parse y
            y = (float)atof(val);
            val = strtok(NULL,"(), "); //parse z
            z = (float)atof(val);
            scale.setScale(Vec3(x,y,z));

            *m *= trans;
            rotz *= roty;
            rotz *= rotx;
            *m *= rotz;
            *m *= scale;

            //parse spectrum
            Spectrum emissive;
            token = strtok_r(NULL," ",&pos);
            if(token[0]=='(')//parse refracted color, rgb
            {
                unsigned char r,g,b;
                val = strtok(token,"(), "); //parse x
                r = (unsigned char)atoi(val);
                val = strtok(NULL,"(), "); //parse y
                g = (unsigned char)atoi(val);
                val = strtok(NULL,"(), "); //parse z
                b = (unsigned char)atoi(val);
                emissive = Spectrum(ColorRGB(r,g,b),true);
            }
            else //parse temperature, generate blackbody
                emissive = Spectrum(atoi(token));

            out->scene->addLight((unsigned int)got->second,m,emissive);
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
            Matrix4* m = new Matrix4();
            m->setIdentity();
            Matrix4 trans,rotx,roty,rotz,scale;

            //parse position
            token = strtok_r(NULL," ",&pos);//parse refracted color, rgb
            val = strtok(token,"(), "); //parse x
            x = (float)atof(val);
            val = strtok(NULL,"(), "); //parse y
            y = (float)atof(val);
            val = strtok(NULL,"(), "); //parse z
            z = (float)atof(val);
            trans.setTranslation(Vec3(x,y,z));

            token = strtok_r(NULL," ",&pos);//parse rotation
            val = strtok(token,"(), "); //parse x
            x = (float)atof(val);
            val = strtok(NULL,"(), "); //parse y
            y = (float)atof(val);
            val = strtok(NULL,"(), "); //parse z
            z = (float)atof(val);
            rotx.setRotateX(toRad(x));
            roty.setRotateY(toRad(y));
            rotz.setRotateZ(toRad(z));

            token = strtok_r(NULL," ",&pos);//parse translation
            val = strtok(token,"(), "); //parse x
            x = (float)atof(val);
            val = strtok(NULL,"(), "); //parse y
            y = (float)atof(val);
            val = strtok(NULL,"(), "); //parse z
            z = (float)atof(val);
            scale.setScale(Vec3(x,y,z));

            *m *= trans;
            rotz *= roty;
            rotz *= rotx;
            *m *= rotz;
            *m *= scale;

            out->scene->addAsset((unsigned int)got->second,m,mat);
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
    std::chrono::steady_clock::time_point a = std::chrono::steady_clock::now();
    int buf_size = 512;
    char* buf = (char*)malloc((size_t)buf_size);
    FILE* fin = fopen(filename,"r");
    if(fin!=NULL)
    {
        while(fgets(buf, buf_size, fin)!=NULL) //first pass
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
                    parseMaterial(buf);
                    break;
                case 'a':
                    parseShape(buf, &(Parser::shapeids), out);
                    break;
                default:
                    continue;
            }
        }
        fseek(fin,0,SEEK_SET);//restart from beginning of file
        while(fgets(buf, buf_size, fin)!=NULL)//second pass, world and lights
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
    {
        free(buf);
        Console.critical("Error opening input file");
    }
    using namespace std::chrono;
    steady_clock::time_point b = steady_clock::now();
    long long d = duration_cast<milliseconds>(b-a).count();
    char log[64];
    sprintf(log,MESSAGE_ENDED_PARSING,(int)d);
    Console.log(log,NULL);
}

/**
 * \endcond
 */
