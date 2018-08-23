//author: Davide Pizzolotto
//license: GNU GPLv3

#include "single_brdf.hpp"

SingleBRDF::SingleBRDF(const Bdf* bdf, const Texture* texture,
                       const Bump* bump)
{
    if(bdf->is_BRDF())
    {
        SingleBRDF::bdf = bdf;
    }
    else
    {
        Console.warning(MESSAGE_SINGLE_BRDF_WRONG);
        //this is deleted ANYWAY to prevent unintended behaviour.
        //the fact is that once passed to this function, addme is managed by
        //this class. This class refuses to add it, so it is instadeleted
        //and a default implementation used
        delete bdf;
        SingleBRDF::bdf = new Lambertian();
    }
    if(texture != NULL)
        SingleBRDF::diffuse = texture;
    else
        SingleBRDF::diffuse = TexLib.get_dflt_diffuse();
    if(bump != NULL)
        SingleBRDF::bump = bump;
    else
        SingleBRDF::bump = new Bump();
}

SingleBRDF::~SingleBRDF()
{
    delete SingleBRDF::bdf;
    delete SingleBRDF::bump;
}

Spectrum SingleBRDF::value(const Vec3* wo, const HitPoint* h, const Vec3* wi,
                           bool matchSpec) const
{
    char flags = matchSpec?FLAG_SPEC:0;
    Spectrum retval = SPECTRUM_BLACK;
    if(wi->dot(h->normal_h)*wo->dot(h->normal_h)>0)//reflected ray
        flags |= FLAG_BRDF;
    else                                //transmitted ray
        return retval;
    if(bdf->matches(flags))
    {
        ShadingSpace shading_matrix;
        bump->bump(h, &shading_matrix);
        Vec3 wo_shading = shading_matrix.to_shading(*wo);
        Vec3 wi_shading = shading_matrix.to_shading(*wi);
        retval = bdf->value(&wo_shading, &wi_shading);
        retval *= diffuse->map(h);
    }
    return retval;
}

Spectrum SingleBRDF::sample_value(float, float r1, float r2, const Vec3* wo,
                                  const HitPoint* h, Vec3* wi, float* pdf,
                                  bool matchSpec, bool* matchedSpec) const
{
    if(bdf->is_specular())
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
    ShadingSpace shading_matrix;
    bump->bump(h, &shading_matrix);
    Vec3 wo_shading = shading_matrix.to_shading(*wo);
    Vec3 wi_shading;
    Spectrum retval;
    retval = bdf->sample_value(&wo_shading, &wi_shading, r1, r2, pdf);
    wi_shading.normalize();
    *wi = shading_matrix.to_world(wi_shading);
    return retval*diffuse->map(h);
}

float SingleBRDF::pdf(const Vec3* wo, const HitPoint* h, const Vec3* wi,
                      bool matchSpec) const
{
    if(!matchSpec && bdf->is_specular())
        return 0.f;
    ShadingSpace shading_matrix;
    bump->bump(h, &shading_matrix);
    Vec3 wo_shading = shading_matrix.to_shading(*wo);
    Vec3 wi_shading = shading_matrix.to_shading(*wi);
    return bdf->pdf(&wo_shading, &wi_shading);
}
