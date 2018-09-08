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
        MultiBSDF::diffuse[count] = spectrum;
    else
        //assuming default texture always exists and is SPECTRUM_ONE
        MultiBSDF::diffuse[count] = TexLib.get_dflt_texture();
    count++;
}

Spectrum MultiBSDF::value(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                          const ShadingSpace* matrix, bool matchSpec) const
{
    char flags = matchSpec?FLAG_SPEC:0;
    if(wiW->dot(h->normal_h)*woW->dot(h->normal_h)>0)//reflected ray
        flags |= FLAG_BRDF;
    else                                //transmitted ray
        flags |= FLAG_BTDF;
    Spectrum retval = SPECTRUM_BLACK;
    Vec3 wo_shading = matrix->to_shading(*woW);
    Vec3 wi_shading = matrix->to_shading(*wiW);
    for(int i = 0; i<count; i++)
    {
        //add contribution only if matches refl/trans
        if(bdfs[i]->matches(flags))
            retval +=
                    bdfs[i]->value(&wo_shading, &wi_shading)*diffuse[i]->map(h);
    }
    return retval;
}

Spectrum MultiBSDF::sample_value(float r0, float r1, float r2, const Vec3* woW,
                                 const HitPoint* h, const ShadingSpace* matrix,
                                 Vec3* wiW, float* pdf, bool matchSpec,
                                 bool* matchedSpec) const
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
    Vec3 wo_shading = matrix->to_shading(*woW);
    Vec3 wi_shading;

    //I don't care about the result, but I need to generate the &wi vector
    Spectrum retval;
    //texture computation is done after the if. Because if this is not specular
    //the result is thrown away
    retval = matching[chosen]->sample_value(&wo_shading, &wi_shading, r1, r2,
                                            pdf);
    if(wi_shading.length() == 0) //total internal reflection
    {
        *pdf = 0.f;
        return SPECTRUM_BLACK;
    }
    else
        wi_shading.normalize();

    //transform incident ray to world space
    *wiW = matrix->to_world(wi_shading);
    //if not specular, throw away retval and compute the value for the generated
    //pair of directions
    if(!matching[chosen]->is_specular())
    {
        *matchedSpec = false;
        char flags;
        retval = SPECTRUM_BLACK;
        *pdf = 0.f;
        if(woW->dot(h->normal_h)*wiW->dot(h->normal_h)>0)
            flags = FLAG_BRDF;
        else
            flags = FLAG_BTDF;
        for(int i = 0; i<count; i++)
        {
            if(bdfs[i]->matches(flags))//add contribution only if matches
            {
                retval += bdfs[i]->value(&wo_shading, &wi_shading)*
                          diffuse[chosen]->map(h);
                *pdf += bdfs[i]->pdf(&wo_shading, &wi_shading);
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

float
MultiBSDF::pdf(const Vec3* woW, const HitPoint*, const ShadingSpace* matrix,
               const Vec3* wiW, bool matchSpec) const
{
    if(MultiBSDF::count == 0)
        return 0.f;
    char flags = matchSpec?FLAG_BRDF | FLAG_BTDF | FLAG_SPEC:FLAG_BRDF |
                                                             FLAG_BTDF;
    float pdf = 0.f;
    int matching = 0;
    Vec3 wo_shading = matrix->to_shading(*woW);
    Vec3 wi_shading = matrix->to_shading(*wiW);
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
