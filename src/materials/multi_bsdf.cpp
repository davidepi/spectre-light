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
    if(wi->dot(h->normal_h)*wo->dot(h->normal_h)>0)//reflected ray
        flags |= FLAG_BRDF;
    else                                //transmitted ray
        flags |= FLAG_BTDF;
    Spectrum retval = SPECTRUM_BLACK;
    ShadingSpace shading_matrix;
    for(int i = 0; i<count; i++)
    {
        //add contribution only if matches refl/trans
        if(bdfs[i]->matches(flags))
        {
            bump[i]->bump(h, &shading_matrix);
            Vec3 wo_shading = shading_matrix.to_shading(*wo);
            Vec3 wi_shading = shading_matrix.to_shading(*wi);
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
    ShadingSpace shading_matrix;
    bump[chosen]->bump(h, &shading_matrix);

    //transform to shading space
    Vec3 wo_shading = shading_matrix.to_shading(*wo);
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
    *wi = shading_matrix.to_world(wi_shading);
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
                bump[i]->bump(h, &shading_matrix);
                wo_shading = shading_matrix.to_shading(*wo);
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

float MultiBSDF::pdf(const Vec3* wo, const HitPoint* h, const Vec3* wi,
                     bool matchSpec) const
{
    if(MultiBSDF::count == 0)
        return 0.f;
    char flags = matchSpec?FLAG_BRDF | FLAG_BTDF | FLAG_SPEC:FLAG_BRDF |
                                                             FLAG_BTDF;
    float pdf = 0.f;
    int matching = 0;
    ShadingSpace shading_matrix;
    for(int i = 0; i<count; ++i)
    {
        if(bdfs[i]->matches(flags))
        {
            matching++;
            bump[i]->bump(h, &shading_matrix);
            Vec3 wo_shading = shading_matrix.to_shading(*wo);
            Vec3 wi_shading = shading_matrix.to_shading(*wi);
            pdf += bdfs[i]->pdf(&wo_shading, &wi_shading);
        }
    }
    return matching>1?pdf/(float)matching:pdf; //prevent division by 0
}
