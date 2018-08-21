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
        SingleBRDF::bump = TexLib.get_dflt_bump();
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
    if(wi->dot(h->geometric.n)*wo->dot(h->geometric.n)>0)//reflected ray
        flags |= FLAG_BRDF;
    else                                //transmitted ray
        return retval;
    if(bdf->matches(flags))
    {
        bump->bump(h);
        Vec3 wo_shading(wo->dot(h->geometric.dpdu), wo->dot(h->cross),
                        wo->dot(h->shading.n));
        Vec3 wi_shading(wi->dot(h->geometric.dpdu), wi->dot(h->cross),
                        wi->dot(h->shading.n));
        wo_shading.normalize();
        wi_shading.normalize();
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
    bump->bump(h);
    Vec3 wo_shading(wo->dot(h->geometric.dpdu), wo->dot(h->cross), wo->dot(h->shading.n));
    wo_shading.normalize();
    Vec3 tmpwi;
    Spectrum retval;
    retval = bdf->sample_value(&wo_shading, &tmpwi, r1, r2, pdf);
    tmpwi.normalize();
    wi->x = h->geometric.dpdu.x*tmpwi.x+h->cross.x*tmpwi.y+h->shading.n.x*tmpwi.z;
    wi->y = h->geometric.dpdu.y*tmpwi.x+h->cross.y*tmpwi.y+h->shading.n.y*tmpwi.z;
    wi->z = h->geometric.dpdu.z*tmpwi.x+h->cross.z*tmpwi.y+h->shading.n.z*tmpwi.z;
    wi->normalize();
    return retval*diffuse->map(h);
}

float SingleBRDF::pdf(const Vec3* wo, const HitPoint* h, const Vec3* wi,
                      bool matchSpec) const
{
    if(!matchSpec && bdf->is_specular())
        return 0.f;
    bump->bump(h);
    Vec3 wo_shading(wo->dot(h->geometric.dpdu), wo->dot(h->cross), wo->dot(h->shading.n));
    Vec3 wi_shading(wi->dot(h->geometric.dpdu), wi->dot(h->cross), wi->dot(h->shading.n));
    wo_shading.normalize();
    wi_shading.normalize();
    float pdf;
    pdf = bdf->pdf(&wo_shading, &wi_shading);
    return pdf;
}
