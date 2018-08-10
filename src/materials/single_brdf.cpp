//author: Davide Pizzolotto
//license: GNU GPLv3

#include "single_brdf.hpp"

SingleBRDF::SingleBRDF(const Bdf* bdf, const Texture* texture)
{
    if(bdf->is_BRDF())
    {
        SingleBRDF::bdf = bdf;
        if(texture != NULL)
            SingleBRDF::texture = texture;
        else
            SingleBRDF::texture = TexLib.get_default();
    }
    else
    {
        Console.warning(MESSAGE_SINGLE_BRDF_WRONG);
        //this is deleted ANYWAY to prevent leaks.
        //the fact is that once passed to this function, addme is managed by
        //this class. This class refuses to add it, so it is instadeleted
        delete bdf;
    }
}

SingleBRDF::~SingleBRDF()
{
    delete SingleBRDF::bdf;
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
    Vec3 wo_shading(wo->dot(h->dpdu), wo->dot(h->cross), wo->dot(h->normal_h));
    Vec3 wi_shading(wi->dot(h->dpdu), wi->dot(h->cross), wi->dot(h->normal_h));
    wo_shading.normalize();
    wi_shading.normalize();
    if(bdf->matches(flags))
    {
        retval = bdf->value(&wo_shading, &wi_shading);
        retval *= texture->map(h);
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
    Vec3 wo_shading(wo->dot(h->dpdu), wo->dot(h->cross), wo->dot(h->normal_h));
    wo_shading.normalize();
    Vec3 tmpwi;
    Spectrum retval;
    retval = bdf->sample_value(&wo_shading, &tmpwi, r1, r2, pdf);
    tmpwi.normalize();
    wi->x = h->dpdu.x*tmpwi.x+h->cross.x*tmpwi.y+h->normal_h.x*tmpwi.z;
    wi->y = h->dpdu.y*tmpwi.x+h->cross.y*tmpwi.y+h->normal_h.y*tmpwi.z;
    wi->z = h->dpdu.z*tmpwi.x+h->cross.z*tmpwi.y+h->normal_h.z*tmpwi.z;
    wi->normalize();
    return retval*texture->map(h);
}

float SingleBRDF::pdf(const Vec3* wo, const HitPoint* h, const Vec3* wi,
                      bool matchSpec) const
{
    if(!matchSpec && bdf->is_specular())
        return 0.f;
    Vec3 wo_shading(wo->dot(h->dpdu), wo->dot(h->cross), wo->dot(h->normal_h));
    Vec3 wi_shading(wi->dot(h->dpdu), wi->dot(h->cross), wi->dot(h->normal_h));
    wo_shading.normalize();
    wi_shading.normalize();
    float pdf;
    pdf = bdf->pdf(&wo_shading, &wi_shading);
    return pdf;
}
