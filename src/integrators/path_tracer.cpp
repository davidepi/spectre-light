//author: Davide Pizzolotto
//license: GNU GPLv3

#include "path_tracer.hpp"

Spectrum PathTracer::radiance(const Scene* sc, const HitPoint* hp, const Ray* r,
                              Sampler* sam, OcclusionTester* ot) const
{
    Spectrum power = SPECTRUM_ONE;
    return l_rec(sc, hp, r, sam, &power, false, ot);
}

Spectrum PathTracer::l_rec(const Scene* sc, const HitPoint* hp, const Ray* r,
                           Sampler* sam, Spectrum* power, bool last_spec,
                           OcclusionTester* ot) const
{
    float rrprob = 1.f;
    Spectrum retval = SPECTRUM_BLACK;
    Vec3 wo = -r->direction;
    wo.normalize();
    //calculate direct lighting at point
    const Bsdf* mat = hp->asset_h->get_material(hp->index);
    ShadingSpace matrix;
    Normal n;
    Point3 p = hp->point_h;
    mat->gen_shading_matrix(hp, &matrix, &n);

    //if first hit is light or specular, use its emission
    if((r->ricochet == 0 || last_spec)
       && hp->asset_h->is_light() && dot(n, wo)>0)
        retval += *power*((LightArea*)hp->asset_h)->emissive_spectrum();

    Spectrum direct = direct_l(sc, hp, r, sam, ot, mat, &p, &n, &matrix);
    retval += *power*direct;

    //random samples
    float rand[4];
    sam->get_random_numbers(rand, 4);

    //russian roulette
    if(r->ricochet>3)
    {
        float term = min(power->luminance(), 0.5f);
        if(rand[0]<term)
            return retval;
        else
            rrprob = term; //survived russian roulette, need to cut down contrib
    }
    if(r->ricochet == DEFAULT_BOUNCES)
        return retval;

    //sample next hit point
    Vec3 wi;
    float pdf;
    bool matchedSpec;
    Spectrum f = mat->sample_value(rand[1], rand[2], rand[3], &wo, hp, &matrix,
                                   &wi, &pdf, true, &matchedSpec);
    if(pdf == 0 || f.is_black())
        return retval;
    float adot = absdot(wi, n);
    //calculate new power, new ray and new intersection point
    *power *= f*adot/pdf*rrprob;
    Ray r2(p, wi);
    r2.ricochet = (unsigned char)(r->ricochet+1);
    HitPoint h2;
    h2.differentials = false;

    //recursive step
    Spectrum rec;
    //TODO: check this one, not sure if it is correct or should be multiplied
    // by the *power value
    if(!sc->k.intersect(&r2, &h2))
        rec = sc->get_escaped_radiance(&r2); //ray out of scene, return now
    else
        rec = l_rec(sc, &h2, &r2, sam, power, matchedSpec, ot);

    retval += rec;
    return retval;
}
