//
// Created by davide on 15/07/17.
//


#include "ray_tracer.hpp"

Color RayTracer::radiance(const Scene* sc, const HitPoint* hp, const Ray* r,
                           Sampler* sam)const
{
    Color L;
    int nlights = sc->lightSize();
    const AreaLight*const* lights = sc->getLights();
    if(nlights>0)
    {
        float rand[5];
        sam->getRandomNumbers(rand,5);
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
                float weigth = (lightpdf*lightpdf)/(lightpdf*lightpdf-
                        bsdfpdf*bsdfpdf);
                L+=bsdf_f*directrad*absdot(lightray.direction,hp->n)*
                                    weigth/lightpdf;
            }
        }
    }
    return L*nlights;
}