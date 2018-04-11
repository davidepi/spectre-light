//author: Davide Pizzolotto
//license: GNU GPLv3

#include "bdf.hpp"
#include "materials/lambertian.hpp"
Bdf::Bdf(char flags)
{
    Bdf::type = flags;
}

char Bdf::get_flags()const
{
    return Bdf::type;
}

Spectrum Bdf::sample_value(const Vec3 *wo, Vec3 *wi, float r0, float r1,
                           float* pdf)const
{
    //sample x,y points on the hemisphere, shirley's method maybe's better
    float t = TWO_PI * r0;
    float r = sqrtf(r1);
    wi->x = r * cosf(t);
    wi->y = r * sinf(t);
    wi->z = sqrtf(max(0.f,1.f-wi->x*wi->x-wi->y*wi->y));
    //if the wo was flipped, flip also wi
    if(wo->z < 0) wi->z *= -1.f;
    *pdf = fabsf(wi->z)*INV_PI;
    return value(wo,wi);
}
float Bdf::pdf(const Vec3* wo, const Vec3* wi)const
{
    //default pdf is cos(theta)/pi
    return wo->z*wi->z>0?fabsf(wi->z)*INV_PI:0.f;
}

Bsdf::Bsdf()
{
    Bsdf::count = 0;
}

Bsdf::~Bsdf()
{
    for(int i=0;i<count;i++)
        delete Bsdf::bdfs[i];
}

void Bsdf::inherit_bdf(Bdf* addme)
{
#ifdef DEBUG
    if(count==_MAX_BDF_)
    {
        Console.severe("Cannot add more Bdfs");
        return;
    }
#endif
    Bsdf::bdfs[count++] = addme;
}

Spectrum Bsdf::value(const Vec3 *wo, const HitPoint* h, const Vec3 *wi,
                     bool matchSpec)const
{
    char flags = matchSpec?FLAG_SPEC:0;
    Vec3 wo_shading(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->normal_h));
    Vec3 wi_shading(wi->dot(h->right),wi->dot(h->cross),wi->dot(h->normal_h));
    if(wi->dot(h->normal_h)*wo->dot(h->normal_h) > 0)//reflected ray
        flags |= FLAG_BRDF;
    else                                //transmitted ray
        flags |= FLAG_BTDF;
    Spectrum retval = SPECTRUM_BLACK;
    wo_shading.normalize();
    wi_shading.normalize();
    for(int i=0;i<count;i++)
    {
        //add contribution only if matches refl/trans
        if(bdfs[i]->matches(flags))
            retval += bdfs[i]->value(&wo_shading,&wi_shading);
    }
    return retval;
}

Spectrum Bsdf::sample_value(float r0, float r1, float r2, const Vec3* wo,
                            const HitPoint* h, Vec3* wi, float* pdf,
                            bool matchSpec, bool* matchedSpec)const
{
    //this could be skipped with an ad-hoc method but... it will loop 2-3 times
    //at max...
    int matchcount = 0;
    Bdf* matching[_MAX_BDF_];
    if(!matchSpec)
    {
        for(int i=0;i<Bsdf::count;i++)
            if (!(Bsdf::bdfs[i]->is_specular()))
                matching[matchcount++] = bdfs[i];
        if(matchcount==0)
        {
            //otherwise it will access invalid array positions
            *pdf=0.f;
            return SPECTRUM_BLACK;
        }
    }
    else
    {
        for(int i=0;i<Bsdf::count;i++)
                matching[matchcount++] = bdfs[i];
    }
    
    int chosen = (int)(r0 * matchcount);
    if(chosen == matchcount) //out of array
        chosen--;
    
    //transform to shading space
    Vec3 wo_shading(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->normal_h));
    wo_shading.normalize();
    Vec3 tmpwi;
    
    //I don't care about the result, but I need to generate the &wi vector
    Spectrum retval;
    retval=matching[chosen]->sample_value(&wo_shading, &tmpwi,r1,r2,pdf);
    if(tmpwi.length()==0) //total internal reflection
    {
        *pdf = 0.f;
        return SPECTRUM_BLACK;
    }
    else
        tmpwi.normalize();
    
    //transform incident ray to world space
    wi->x = h->right.x*tmpwi.x + h->cross.x * tmpwi.y + h->normal_h.x * tmpwi.z;
    wi->y = h->right.y*tmpwi.x + h->cross.y * tmpwi.y + h->normal_h.y * tmpwi.z;
    wi->z = h->right.z*tmpwi.x + h->cross.z * tmpwi.y + h->normal_h.z * tmpwi.z;
    
    wi->normalize();
    //if not specular, throw away retval and compute the value for the generated
    //pair of directions
    if(!matching[chosen]->is_specular())
    {
        *matchedSpec = false;
        char flags;
        retval = SPECTRUM_BLACK;
        *pdf = 0.f;
        if (wo->dot(h->normal_h) * wi->dot(h->normal_h) > 0)
            flags = FLAG_BRDF;
        else
            flags = FLAG_BTDF;
        for (int i = 0; i < count; i++)
        {
            if (bdfs[i]->matches(flags))//add contribution only if matches
            {
                retval += bdfs[i]->value(&wo_shading, &tmpwi);
                *pdf+= bdfs[i]->pdf(&wo_shading, &tmpwi);
            }
        }
    }
    else
    {
        *matchedSpec = true;
    }
    if(matchcount==0)
        throw "ouch";
    *pdf/=(float)matchcount;
    return retval;
}

float Bsdf::pdf(const Vec3* wo,  const HitPoint* h, const Vec3* wi,
                bool matchSpec)const
{
    if(Bsdf::count == 0)
        return 0.f;
    char flags = matchSpec?FLAG_BRDF|FLAG_BTDF|FLAG_SPEC:FLAG_BRDF|FLAG_BTDF;
    Vec3 wo_shading(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->normal_h));
    Vec3 wi_shading(wi->dot(h->right),wi->dot(h->cross),wi->dot(h->normal_h));
    wo_shading.normalize();
    wi_shading.normalize();
    float pdf = 0.f;
    int matching = 0;
    for(int i = 0; i < count; ++i)
    {
        if(bdfs[i]->matches(flags))
        {
            matching++;
            pdf += bdfs[i]->pdf(&wo_shading, &wi_shading);
        }
    }
    return matching>1?pdf/(float)matching:pdf; //prevent division by 0
}

SingleBRDF::SingleBRDF()
{
    //used as a fallback if the inherit_bdf passes in an illegal value.
    //not the best course of action, but these methods will be called at startup
    //time
    SingleBRDF::reflection = (Bdf*)new Lambertian();
    //to avoid SEGFAULT, default texture is completely white
    SingleBRDF::diffuse = TexLib.get("Default");
}

SingleBRDF::~SingleBRDF()
{
    delete SingleBRDF::reflection;
}

void SingleBRDF::inherit_bdf(Bdf* addme)
{
    if(addme->is_BRDF())
    {
        delete SingleBRDF::reflection;
        SingleBRDF::reflection = addme;
    }
    else
    {
        Console.warning(MESSAGE_SINGLE_BRDF_WRONG);
        //this is deleted ANYWAY to prevent leaks.
        //the fact is that once passed to this function, addme is managed by
        //this class. This class refuses to add it, so it is instadeleted
        delete addme;
    }
}

void SingleBRDF::add_diffuse_texture(const char *name)
{
    SingleBRDF::diffuse = TexLib.get(name);
    if(SingleBRDF::diffuse==NULL)
    {
        char* errormsg = (char*)malloc(sizeof(char)*strlen(name)+1+
                                       strlen(MESSAGE_TEXTURE_NOT_FOUND));
        sprintf(errormsg, MESSAGE_TEXTURE_NOT_FOUND, name);
        Console.warning(errormsg);
        free(errormsg);
    }
}

Spectrum SingleBRDF::value(const Vec3 *wo, const HitPoint* h, const Vec3 *wi,
                           bool matchSpec)const
{
    char flags = matchSpec?FLAG_SPEC:0;
    Spectrum retval = SPECTRUM_BLACK;
    if(wi->dot(h->normal_h)*wo->dot(h->normal_h) > 0)//reflected ray
        flags |= FLAG_BRDF;
    else                                //transmitted ray
        return retval;
    Vec3 wo_shading(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->normal_h));
    Vec3 wi_shading(wi->dot(h->right),wi->dot(h->cross),wi->dot(h->normal_h));
    wo_shading.normalize();
    wi_shading.normalize();
    if(reflection->matches(flags))
    {
        retval = reflection->value(&wo_shading,&wi_shading);
        retval *= diffuse->map(h->u, h->v);
    }
    return retval;
}

Spectrum SingleBRDF::sample_value(float, float r1, float r2, const Vec3* wo,
                                  const HitPoint* h, Vec3* wi, float* pdf,
                                  bool matchSpec, bool* matchedSpec)const
{
    if(reflection->is_specular())
    {
        *matchedSpec = true;
        if(!matchSpec)
        {
            *pdf = 0.f;
            return SPECTRUM_BLACK;
        }
    }
    else
        *matchedSpec = false;
    Vec3 wo_shading(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->normal_h));
    wo_shading.normalize();
    Vec3 tmpwi;
    Spectrum retval;
    retval=reflection->sample_value(&wo_shading, &tmpwi,r1,r2,pdf);
    tmpwi.normalize();
    wi->x = h->right.x*tmpwi.x + h->cross.x * tmpwi.y + h->normal_h.x * tmpwi.z;
    wi->y = h->right.y*tmpwi.x + h->cross.y * tmpwi.y + h->normal_h.y * tmpwi.z;
    wi->z = h->right.z*tmpwi.x + h->cross.z * tmpwi.y + h->normal_h.z * tmpwi.z;
    wi->normalize();
    return retval*diffuse->map(h->u, h->v);
}

float SingleBRDF::pdf(const Vec3* wo,  const HitPoint* h, const Vec3* wi,
                      bool matchSpec)const
{
    if(!matchSpec && reflection->is_specular())
        return 0.f;
    Vec3 wo_shading(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->normal_h));
    Vec3 wi_shading(wi->dot(h->right),wi->dot(h->cross),wi->dot(h->normal_h));
    wo_shading.normalize();
    wi_shading.normalize();
    float pdf = 0.f;
    pdf = reflection->pdf(&wo_shading, &wi_shading);
    return pdf;
}
