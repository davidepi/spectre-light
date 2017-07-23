#include "ray_tracer.hpp"

Color RayTracer::radiance(const Scene* sc, const HitPoint* hp, const Ray* r,
                           Sampler* sam, OcclusionTester* ot)const
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
        Color directrad=light->radiance_i(rand[1],rand[2],&hp->h,&wi,&lightpdf,
                                          &light_distance);
        if(lightpdf > 0 && !directrad.isBlack())
        {
            Color bsdf_f = mat->df(&wo,hp,&wi);
            Ray r(hp->h,wi);
            if(!bsdf_f.isBlack() && !ot->isOccluded(&r,hp->hit,&light_distance))
            {
                bsdfpdf = mat->pdf(&wo,hp,&wi);
                float weight = (lightpdf*lightpdf)/(lightpdf*lightpdf+
                        bsdfpdf*bsdfpdf);
                L+=bsdf_f*directrad*absdot(wi,hp->n)*
                                    weight/lightpdf;
            }
        }

        //mip bsdf sampling
        Color bsdf_f = mat->df_s(rand[3],rand[4],rand[5],&wo,hp,&wi,&bsdfpdf);
        if(!bsdf_f.isBlack() && bsdfpdf>0)
        {
            lightpdf = light->pdf(&hp->h,&wi);
            float weight = (bsdfpdf*bsdfpdf)/(bsdfpdf*bsdfpdf+lightpdf*lightpdf);
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
    if(L.r>1)L.r=1;
    if(L.g>1)L.g=1;
    if(L.b>1)L.b=1;
    return L*nlights;
}