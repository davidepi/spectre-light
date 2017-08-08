//
// Created by davide on 15/07/17.
//

#include "path_tracer.hpp"

Color PathTracer::radiance(const Scene* sc, const HitPoint* hp, const Ray* r,
                           Sampler* sam, OcclusionTester *ot)const
{
    Color power(1.0f);
    BdfFlags last = DIFFUSE;
    return l_rec(sc,hp,r,sam,&power,last,ot);
}

Color PathTracer::l_rec(const Scene *sc, const HitPoint *hp, const Ray *r,
                        Sampler *sam, Color *power, BdfFlags last,
                        OcclusionTester *ot) const
{
    Color retval(0.0);
    Vec3 wo = -r->direction;

    //if first hit is light or specular, use its emission
    if((r->ricochet==0 || last&SPECULAR!=0)
       && hp->hit->isLight() && dot(hp->n,wo)>0)
    {
        retval+=*power*((AreaLight *)hp->hit)->emissiveSpectrum();
    }

    //calculate direct lighting at point
    const Bsdf* mat = hp->hit->getMaterial();
    retval+=*power*direct_l(sc,hp,r,sam,ot);

    //random samples
    float rand[4];
    sam->getRandomNumbers(rand,4);

    //russian roulette
    if(r->ricochet>3 &&rand[0]<0.5f)
        return retval;
    if(r->ricochet==DEFAULT_BOUNCES)
        return retval;

    //sample next hit point
    Vec3 wi;
    float pdf;
    BdfFlags matched;
    Color f = mat->df_s(rand[1],rand[2],rand[3],&wo,hp,&wi,&pdf,BdfFlags(ALL),
    &matched);
    if(f.isBlack() || pdf==0)
        return retval;

    //calculate new power, new ray and new intersection point
    *power *= f*absdot(wi,hp->n)/pdf;
    Ray r2(hp->h,wi);
    r2.ricochet = r->ricochet+1;
    HitPoint h2;
    if(!sc->k.intersect(&r2,&h2))
        return retval; //ray out of scene, return now

    //recursive step
    return retval+l_rec(sc,&h2,&r2,sam,power,matched,ot);
}