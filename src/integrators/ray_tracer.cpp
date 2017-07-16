#include "ray_tracer.hpp"

Color RayTracer::radiance(const Scene* sc, const HitPoint* hp, const Ray* r,
                           Sampler* sam)const
{
    Color L;
    int nlights = sc->lightSize();
    const AreaLight*const* lights = sc->getLights();
    if(hp->hit->isLight())
        if(dot(hp->n,-r->direction)>0)
            L+=((AreaLight *) hp->hit)->emissiveSpectrum();
    if(L.r ==1 && L.g==1 &&L.b==1)
    {
        volatile int i=0;
    }
    if(nlights>0)
    {
        float rand[8];
        sam->getRandomNumbers(rand,8);
        const Vec3 wo = -r->direction;
        Color retval;
        //choose a light to sample
        int sampledlight = min((int)(rand[0]*nlights),nlights-1);
        const AreaLight* light = lights[sampledlight];
        float lightpdf;
        float bsdfpdf;
        Ray lightray;

        //multiple importance sampling, light first
        Color directrad = light->radiance(rand[1],rand[2],rand[3],rand[4],
                                          &hp->h,&lightray,&lightpdf);
        const Bsdf* mat = hp->hit->getMaterial();
        if(lightpdf > 0 && !directrad.isBlack())
        {
            Color bsdf_f = mat->df(&wo,hp,&lightray.direction);
            OcclusionTester ot(sc);
            if(!bsdf_f.isBlack())// && !ot.isOccluded(&lightray,hp->hit))
            {
                bsdfpdf = mat->pdf(&wo,hp,&lightray.direction);
                float weight = (lightpdf*lightpdf)/(lightpdf*lightpdf-
                        bsdfpdf*bsdfpdf);
                L+=bsdf_f*directrad*absdot(lightray.direction,hp->n)*
                                    weight/lightpdf;
            }
        }

        //mip bsdf sampling
        Vec3 wi;
        Color bsdf_f = mat->df_s(rand[5],rand[6],rand[7],&wo,hp,&wi,&bsdfpdf);
        if(!bsdf_f.isBlack() && bsdfpdf>0)
        {
            lightpdf = light->pdf();
            float weight = (bsdfpdf*bsdfpdf)/(bsdfpdf*bsdfpdf-lightpdf*lightpdf);
            Ray r2(hp->h,wi);
            HitPoint h2;
            Color rad;
            if(sc->k.intersect(&r2,&h2))
                if(h2.hit->getID() == light->getID())
                    if(dot(h2.n,-r2.direction)>0)
                        rad=light->emissiveSpectrum();
            if(!rad.isBlack())
                L+=bsdf_f*rad*absdot(wi,hp->n)*weight/bsdfpdf;

        }
    }
    return L*nlights;
}