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

void MultiBSDF::inherit_bdf(Bdf* addme, const Texture* spectrum,
                            const Bump* bump)
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
        MultiBSDF::diffuse[count] = spectrum;
    else
        //assuming default texture always exists and is SPECTRUM_ONE
        MultiBSDF::diffuse[count] = TexLib.get_dflt_diffuse();
    if(bump != NULL)
        MultiBSDF::bump[count] = bump;
    else
        MultiBSDF::bump[count] = TexLib.get_dflt_bump();
    count++;
}

Spectrum MultiBSDF::value(const Vec3* wo, const HitPoint* h, const Vec3* wi,
                          bool matchSpec) const
{
    char flags = matchSpec?FLAG_SPEC:0;
    if(wi->dot(h->geometric.n)*wo->dot(h->geometric.n)>0)//reflected ray
        flags |= FLAG_BRDF;
    else                                //transmitted ray
        flags |= FLAG_BTDF;
    Spectrum retval = SPECTRUM_BLACK;
    for(int i = 0; i<count; i++)
    {
        //add contribution only if matches refl/trans
        if(bdfs[i]->matches(flags))
        {
            bump[i]->bump(h);
            Vec3 wo_shading(wo->dot(h->geometric.dpdu), wo->dot(h->cross),
                            wo->dot(h->shading.n));
            Vec3 wi_shading(wi->dot(h->geometric.dpdu), wi->dot(h->cross),
                            wi->dot(h->shading.n));
            wo_shading.normalize();
            wi_shading.normalize();
            retval +=
                    bdfs[i]->value(&wo_shading, &wi_shading)*diffuse[i]->map(h);
        }
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

    //apply bump mapping
    bump[chosen]->bump(h);

    //transform to shading space
    Vec3 wo_shading(wo->dot(h->geometric.dpdu), wo->dot(h->cross), wo->dot(h->shading.n));
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
    wi->x = h->geometric.dpdu.x*tmpwi.x+h->cross.x*tmpwi.y+h->shading.n.x*tmpwi.z;
    wi->y = h->geometric.dpdu.y*tmpwi.x+h->cross.y*tmpwi.y+h->shading.n.y*tmpwi.z;
    wi->z = h->geometric.dpdu.z*tmpwi.x+h->cross.z*tmpwi.y+h->shading.n.z*tmpwi.z;

    wi->normalize();
    //if not specular, throw away retval and compute the value for the generated
    //pair of directions
    if(!matching[chosen]->is_specular())
    {
        *matchedSpec = false;
        char flags;
        retval = SPECTRUM_BLACK;
        *pdf = 0.f;
        if(wo->dot(h->geometric.n)*wi->dot(h->geometric.n)>0)
            flags = FLAG_BRDF;
        else
            flags = FLAG_BTDF;
        for(int i = 0; i<count; i++)
        {
            if(bdfs[i]->matches(flags))//add contribution only if matches
            {
                bump[i]->bump(h);
                wo_shading = Vec3(wo->dot(h->geometric.dpdu), wo->dot(h->cross),
                                  wo->dot(h->shading.n));
                wo_shading.normalize();
                retval += bdfs[i]->value(&wo_shading, &tmpwi)*
                          diffuse[chosen]->map(h);
                *pdf += bdfs[i]->pdf(&wo_shading, &tmpwi);
            }
        }
    }
    else
    {
        *matchedSpec = true;
        retval *= diffuse[chosen]->map(h);
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
    float pdf = 0.f;
    int matching = 0;
    for(int i = 0; i<count; ++i)
    {
        if(bdfs[i]->matches(flags))
        {
            matching++;
            bump[i]->bump(h);
            Vec3 wo_shading = Vec3(wo->dot(h->geometric.dpdu), wo->dot(h->cross),
                                   wo->dot(h->shading.n));
            Vec3 wi_shading(wi->dot(h->geometric.dpdu), wi->dot(h->cross),
                            wi->dot(h->shading.n));
            wo_shading.normalize();
            wi_shading.normalize();
            pdf += bdfs[i]->pdf(&wo_shading, &wi_shading);
        }
    }
    return matching>1?pdf/(float)matching:pdf; //prevent division by 0
}
