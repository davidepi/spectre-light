//author: Davide Pizzolotto
//license: GNU GPLv3

#include "ray_tracer.hpp"

Spectrum RayTracer::radiance(const Scene *sc, const HitPoint *hp, const Ray *r,
                          Sampler *sam, OcclusionTester *ot) const
{
    Spectrum direct = direct_l(sc,hp,r,sam,ot)*sc->lights_size();
    //specular reflection
    if(r->ricochet < DEFAULT_BOUNCES) //ensure termination
    {
        direct+=spec_l(sc,hp,r,sam,ot,BdfFlags(BRDF),this);
        direct+=spec_l(sc,hp,r,sam,ot,BdfFlags(BTDF),this);
    }
    return direct;
}

Spectrum direct_l(const Scene* sc, const HitPoint* hp, const Ray* r,
                  Sampler* sam, OcclusionTester* ot)
{
    Spectrum L(0);
    int nlights = sc->lights_size();
    const AreaLight*const* lights = sc->get_lights();
    if(hp->asset_h->is_light())
        if(dot(hp->normal_h,-r->direction)>0)
            L+=((AreaLight *) hp->asset_h)->emissiveSpectrum();
    if(nlights>0)
    {
        float rand[6];
        sam->get_random_numbers(rand,6);
        const Vec3 wo = -r->direction;
        Vec3 wi;
        //choose a light to sample
        int sampledlight = min((int)(rand[0]*nlights),nlights-1);
        const AreaLight* light = lights[sampledlight];
        const Bsdf* mat = hp->asset_h->get_material();
        float lightpdf;
        float bsdfpdf;
        BdfFlags flags((BdfFlags)(ALL&~SPECULAR));
        BdfFlags sampled_val;
        float light_distance;

        //multiple importance sampling, light first
        Spectrum directrad=light->radiance_i(rand[1],rand[2],&hp->point_h,&wi,
                                             &lightpdf,&light_distance);
        if(lightpdf > 0 && !directrad.is_black())
        {
            Spectrum bsdf_f = mat->value(&wo,hp,&wi,flags);
            Ray r2(hp->point_h,wi);
            if(!bsdf_f.is_black() && !ot->is_occluded(&r2,light_distance))
            {
                bsdfpdf = mat->pdf(&wo,hp,&wi,flags);
                if(bsdfpdf>0)
                {
                    float weight = (lightpdf*lightpdf)/(lightpdf*lightpdf+
                                                        bsdfpdf*bsdfpdf);
                    L+=bsdf_f*directrad*absdot(wi,hp->normal_h)*weight/lightpdf;
                }
            }
        }

        //mip bsdf sampling
        //NULL is guaranteed not be used since the call will never be specular
        Spectrum bsdf_f = mat->sample_value(rand[3],rand[4],rand[5],&wo,hp,
                                            &wi,&bsdfpdf,flags,&sampled_val);
        if(bsdfpdf>0 && !bsdf_f.is_black())
        {
            float w = 1.f; //weight
            //if((sampled_val&SPECULAR)==0) //if not specular -> 100% guaranteed
            //{
                lightpdf = light->pdf(&hp->point_h, &wi);
                if(lightpdf == 0)
                    return L; //no contribution from bsdf sampling
                w = (bsdfpdf*bsdfpdf)/(bsdfpdf*bsdfpdf+lightpdf*lightpdf);
            //}
            Ray r2(hp->point_h,wi);
            HitPoint h2;
            if(sc->k.intersect(&r2,&h2))
                if(h2.asset_h->get_id() == light->get_id())
                    if(dot(h2.normal_h,-r2.direction)>0)
                    {
                        Spectrum rad = light->emissiveSpectrum();
                        L += bsdf_f * rad * absdot(wi, hp->normal_h) * w / bsdfpdf;
                    }
        }
    }
    return L;
}

Spectrum spec_l(const Scene* s, const HitPoint* hp, const Ray* r, Sampler* sam,
             OcclusionTester* ot, BdfFlags ref,const LightIntegrator* i)
{
    Vec3 wo = normalize(-r->direction);
    Vec3 wi;
    float rand[3];
    float bsdfpdf;
    sam->get_random_numbers(rand,3);
    const Bsdf* mat = hp->asset_h->get_material();
    BdfFlags sampled_val;
    BdfFlags sampleme = BdfFlags((ref&(BRDF|BTDF))|SPECULAR);
    Spectrum bsdf_f = mat->sample_value(rand[0], rand[1], rand[2], &wo, hp, &wi,
                       &bsdfpdf,sampleme,&sampled_val);
    
    if(bsdfpdf==1.f && !bsdf_f.is_black())
    {
        float adot = absdot(wi, hp->normal_h);
        if(adot != 0)
        {
            Spectrum reflr_rad;
            Ray r2(hp->point_h,wi); //new ray to trace
            r2.ricochet=r->ricochet+1;
            HitPoint h2;
            if(s->k.intersect(&r2,&h2)) //if intersection is found
                reflr_rad = i->radiance(s,&h2,&r2,sam,ot);
            return bsdf_f*reflr_rad*adot;
        }
        else
            return SPECTRUM_BLACK;
    }
    else
        return SPECTRUM_BLACK;
}
