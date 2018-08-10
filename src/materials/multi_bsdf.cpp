//author: Davide Pizzolotto
//license: GNU GPLv3

#include "multi_bsdf.hpp"

MultiBSDF::MultiBSDF()
{
    MultiBSDF::count = 0;
}

MultiBSDF::~MultiBSDF()
{
    for(int i = 0; i<count; i++)
        delete MultiBSDF::bdfs[i];
}

void MultiBSDF::inherit_bdf(Bdf* addme, const Texture* spectrum)
{
#ifdef DEBUG
    if(count == _MAX_BDF_)
    {
        Console.severe("Cannot add more Bdfs");
        return;
    }
#endif
    MultiBSDF::bdfs[count] = addme;
    if(spectrum != NULL)
        MultiBSDF::textures[count] = spectrum;
    else
        //assuming default texture always exists and is SPECTRUM_ONE
        MultiBSDF::textures[count] = TexLib.get_default();
    count++;
}

Spectrum MultiBSDF::value(const Vec3* wo, const HitPoint* h, const Vec3* wi,
                          bool matchSpec) const
{
    char flags = matchSpec?FLAG_SPEC:0;
    Vec3 wo_shading(wo->dot(h->dpdu), wo->dot(h->cross), wo->dot(h->normal_h));
    Vec3 wi_shading(wi->dot(h->dpdu), wi->dot(h->cross), wi->dot(h->normal_h));
    if(wi->dot(h->normal_h)*wo->dot(h->normal_h)>0)//reflected ray
        flags |= FLAG_BRDF;
    else                                //transmitted ray
        flags |= FLAG_BTDF;
    Spectrum retval = SPECTRUM_BLACK;
    wo_shading.normalize();
    wi_shading.normalize();
    for(int i = 0; i<count; i++)
    {
        //add contribution only if matches refl/trans
        if(bdfs[i]->matches(flags))
            retval += bdfs[i]->value(&wo_shading, &wi_shading)*
                      textures[i]->map(h);
    }
    return retval;
}

Spectrum MultiBSDF::sample_value(float r0, float r1, float r2, const Vec3* wo,
                                 const HitPoint* h, Vec3* wi, float* pdf,
                                 bool matchSpec, bool* matchedSpec) const
{
    //this could be skipped with an ad-hoc method but... it will loop 2-3 times
    //at max...
    int matchcount = 0;
    Bdf* matching[_MAX_BDF_];
    if(!matchSpec)
    {
        for(int i = 0; i<MultiBSDF::count; i++)
            if(!(MultiBSDF::bdfs[i]->is_specular()))
                matching[matchcount++] = bdfs[i];
        if(matchcount == 0)
        {
            //otherwise it will access invalid array positions
            *pdf = 0.f;
            return SPECTRUM_BLACK;
        }
    }
    else
    {
        for(int i = 0; i<MultiBSDF::count; i++)
            matching[matchcount++] = bdfs[i];
    }

    int chosen = (int)(r0*matchcount);
    if(chosen == matchcount) //out of array
        chosen--;

    //transform to shading space
    Vec3 wo_shading(wo->dot(h->dpdu), wo->dot(h->cross), wo->dot(h->normal_h));
    wo_shading.normalize();
    Vec3 tmpwi;

    //I don't care about the result, but I need to generate the &wi vector
    Spectrum retval;
    //texture computation is done after the if. Because if this is not specular
    //the result is thrown away
    retval = matching[chosen]->sample_value(&wo_shading, &tmpwi, r1, r2, pdf);
    if(tmpwi.length() == 0) //total internal reflection
    {
        *pdf = 0.f;
        return SPECTRUM_BLACK;
    }
    else
        tmpwi.normalize();

    //transform incident ray to world space
    wi->x = h->dpdu.x*tmpwi.x+h->cross.x*tmpwi.y+h->normal_h.x*tmpwi.z;
    wi->y = h->dpdu.y*tmpwi.x+h->cross.y*tmpwi.y+h->normal_h.y*tmpwi.z;
    wi->z = h->dpdu.z*tmpwi.x+h->cross.z*tmpwi.y+h->normal_h.z*tmpwi.z;

    wi->normalize();
    //if not specular, throw away retval and compute the value for the generated
    //pair of directions
    if(!matching[chosen]->is_specular())
    {
        *matchedSpec = false;
        char flags;
        retval = SPECTRUM_BLACK;
        *pdf = 0.f;
        if(wo->dot(h->normal_h)*wi->dot(h->normal_h)>0)
            flags = FLAG_BRDF;
        else
            flags = FLAG_BTDF;
        for(int i = 0; i<count; i++)
        {
            if(bdfs[i]->matches(flags))//add contribution only if matches
            {
                retval += bdfs[i]->value(&wo_shading, &tmpwi)*
                          textures[chosen]->map(h);
                *pdf += bdfs[i]->pdf(&wo_shading, &tmpwi);
            }
        }
    }
    else
    {
        *matchedSpec = true;
        retval *= textures[chosen]->map(h);
    }
    if(matchcount>1)
        *pdf /= (float)matchcount;
    return retval;
}

float MultiBSDF::pdf(const Vec3* wo, const HitPoint* h, const Vec3* wi,
                     bool matchSpec) const
{
    if(MultiBSDF::count == 0)
        return 0.f;
    char flags = matchSpec?FLAG_BRDF | FLAG_BTDF | FLAG_SPEC:FLAG_BRDF |
                                                             FLAG_BTDF;
    Vec3 wo_shading(wo->dot(h->dpdu), wo->dot(h->cross), wo->dot(h->normal_h));
    Vec3 wi_shading(wi->dot(h->dpdu), wi->dot(h->cross), wi->dot(h->normal_h));
    wo_shading.normalize();
    wi_shading.normalize();
    float pdf = 0.f;
    int matching = 0;
    for(int i = 0; i<count; ++i)
    {
        if(bdfs[i]->matches(flags))
        {
            matching++;
            pdf += bdfs[i]->pdf(&wo_shading, &wi_shading);
        }
    }
    return matching>1?pdf/(float)matching:pdf; //prevent division by 0
}
