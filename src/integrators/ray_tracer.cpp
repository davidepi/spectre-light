#include "ray_tracer.hpp"

Color RayTracer::radiance(const Scene *sc, const HitPoint *hp, const Ray *r,
                          Sampler *sam, OcclusionTester *ot) const
{
    return RayTracer::direct_l(sc,hp,r,sam,ot)*sc->lightSize();
}

Color RayTracer::direct_l(const Scene* sc, const HitPoint* hp, const Ray* r,
                           Sampler* sam, OcclusionTester* ot)const
{
    Color L;
    int nlights = sc->lightSize();
    const AreaLight*const* lights = sc->getLights();
    if(hp->hit->isLight())
        if(dot(hp->n,-r->direction)>0)
            L+=((AreaLight *) hp->hit)->emissiveSpectrum();
    if(nlights>0)
    {
        float rand[6];
        sam->getRandomNumbers(rand,6);
        const Vec3 wo = -r->direction;
        Vec3 wi;
        Color retval;
        //choose a light to sample
        int sampledlight = min((int)(rand[0]*nlights),nlights-1);
        const AreaLight* light = lights[sampledlight];
        const Bsdf* mat = hp->hit->getMaterial();
        float lightpdf;
        float bsdfpdf;

        float light_distance;
        //multiple importance sampling, light first
        Color directrad=light->radiance_i(rand[1],rand[2],&hp->h,&wi,
                                          &lightpdf,&light_distance);
        if(lightpdf > 0 && !directrad.isBlack())
        {
            Color bsdf_f = mat->df(&wo,hp,&wi,BdfFlags(ALL));
            Ray r(hp->h,wi);
            if(!bsdf_f.isBlack() && !ot->isOccluded(&r,&light_distance))
            {
                bsdfpdf = mat->pdf(&wo,hp,&wi);
                float weight = (lightpdf*lightpdf)/(lightpdf*lightpdf+
                        bsdfpdf*bsdfpdf);
                L+=bsdf_f*directrad*absdot(wi,hp->n)*
                                    weight/lightpdf;
            }
        }

        //mip bsdf sampling
        Color bsdf_f = mat->df_s(rand[3],rand[4],rand[5],&wo,hp,&wi,&bsdfpdf,
                                 BdfFlags(ALL));
        if(!bsdf_f.isBlack() && bsdfpdf>0)
        {
            float w = 1.f; //weight
            //if not specular
                lightpdf = light->pdf(&hp->h,&wi);
                if(lightpdf==0)
                    return L; //no contribution from bsdf sampling
                else
                    w=(bsdfpdf*bsdfpdf)/(bsdfpdf*bsdfpdf+lightpdf*lightpdf);
            //endif

            Ray r2(hp->h,wi);
            HitPoint h2;
            Color rad;
            if(sc->k.intersect(&r2,&h2))
                if(h2.hit->getID() == light->getID())
                    if(dot(h2.n,-r2.direction)>0)
                        rad=light->emissiveSpectrum();
            if(!rad.isBlack())
                L+=bsdf_f*rad*absdot(wi,hp->n)*w/bsdfpdf;

        }
    }
    return L;
}