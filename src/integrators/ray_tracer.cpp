#include "ray_tracer.hpp"

Color RayTracer::radiance(const Scene *sc, const HitPoint *hp, const Ray *r,
                          Sampler *sam, OcclusionTester *ot) const
{
    Color direct = direct_l(sc,hp,r,sam,ot)*sc->lightSize();
    //specular reflection
    if(r->ricochet < DEFAULT_BOUNCES) //ensure termination
    {
        direct+=spec_l(sc,hp,r,sam,ot,BdfFlags(BRDF),this);
        direct+=spec_l(sc,hp,r,sam,ot,BdfFlags(BTDF),this);
    }
    return direct;
}

Color direct_l(const Scene* sc, const HitPoint* hp, const Ray* r, Sampler* sam,
               OcclusionTester* ot)
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
        BdfFlags flags((BdfFlags)(ALL&~SPECULAR));
        BdfFlags sampled_val;
        float light_distance;

        //multiple importance sampling, light first
        Color directrad=light->radiance_i(rand[1],rand[2],&hp->h,&wi,
                                          &lightpdf,&light_distance);
        if(lightpdf > 0 && !directrad.isBlack())
        {
            Color bsdf_f = mat->df(&wo,hp,&wi,flags);
            Ray r(hp->h,wi);
            if(!bsdf_f.isBlack() && !ot->isOccluded(&r,&light_distance))
            {
                bsdfpdf = mat->pdf(&wo,hp,&wi,flags);
                float weight = (lightpdf*lightpdf)/(lightpdf*lightpdf+
                        bsdfpdf*bsdfpdf);
                L+=bsdf_f*directrad*absdot(wi,hp->n)*weight/lightpdf;
            }
        }

        //mip bsdf sampling
        Color bsdf_f = mat->df_s(rand[3],rand[4],rand[5],&wo,hp,&wi,&bsdfpdf,
                                 flags,&sampled_val);
        if(bsdfpdf>0 && !bsdf_f.isBlack())
        {
            float w = 1.f; //weight
            //if((sampled_val&SPECULAR)==0) //if not specular -> 100% guaranteed
            //{
                lightpdf = light->pdf(&hp->h, &wi);
                if(lightpdf == 0)
                    return L; //no contribution from bsdf sampling
                w = (bsdfpdf*bsdfpdf)/(bsdfpdf*bsdfpdf+lightpdf*lightpdf);
            //}
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

Color spec_l(const Scene* s, const HitPoint* hp, const Ray* r, Sampler* sam,
             OcclusionTester* ot, BdfFlags ref,const LightIntegrator* i)
{
    Vec3 wo = -r->direction;
    Vec3 wi;
    float rand[3];
    float bsdfpdf;
    sam->getRandomNumbers(rand,3);
    const Bsdf* mat = hp->hit->getMaterial();
    BdfFlags sampled_val;
    BdfFlags sampleme = BdfFlags((ref&(BRDF|BTDF))|SPECULAR);
    Color bsdf_f = mat->df_s(rand[0], rand[1], rand[2], &wo, hp, &wi,
                       &bsdfpdf,sampleme,&sampled_val);
    float adot = absdot(wi, hp->n);
    if(bsdfpdf == 1.f && !bsdf_f.isBlack() && adot != 0)
    {
        Color reflr_rad;
        Ray r2(hp->h,wi); //new ray to trace
        r2.ricochet=r->ricochet+1;
        HitPoint h2;
        if(s->k.intersect(&r2,&h2)) //if intersection is found
            reflr_rad = i->radiance(s,&h2,&r2,sam,ot);
        return bsdf_f*reflr_rad*adot;
    }
    else
        return Color();
}