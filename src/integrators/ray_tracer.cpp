//author: Davide Pizzolotto
//license: GNU GPLv3

#include "ray_tracer.hpp"

Spectrum
direct_l(const Scene* sc, const HitPoint* hp, const Ray* r, Sampler* sam,
         OcclusionTester* ot, const Bsdf* mat, const Point3* point_s,
         const Normal* normal_s, const ShadingSpace* matrix)
{
    Spectrum L = SPECTRUM_BLACK;
    int nlights = sc->size_lights();
    if(hp->asset_h->is_light())
        if(dot(*normal_s, -r->direction)>0)
            L += ((AreaLight*)hp->asset_h)->emissive_spectrum();
    if(nlights>0)
    {
        float rand[6];
        sam->get_random_numbers(rand, 6);
        const Vec3 wo = normalize(-r->direction);
        Vec3 wi;
        //choose a light to sample
        int sampledlight = min((int)(rand[0]*nlights), nlights-1);
        const Light* light = sc->get_light(sampledlight);
        float lightpdf;
        float bsdfpdf;
        bool matchedSpec;
        float light_distance;

        //multiple importance sampling, light first
        Spectrum direct_l;
        direct_l = light->sample_visible_surface(rand[1], rand[2], point_s, &wi,
                                                 &lightpdf, &light_distance);
        if(lightpdf>0 && !direct_l.is_black())
        {
            Spectrum bsdf_f = mat->value(&wo, hp, &wi, matrix, false);
            Ray r2(*point_s, wi);
            if(!bsdf_f.is_black() && !ot->is_occluded(&r2, light_distance))
            {
                bsdfpdf = mat->pdf(&wo, hp, matrix, &wi, false);
                if(bsdfpdf>0)
                {
                    float weight = (lightpdf*lightpdf)/
                                   (lightpdf*lightpdf+bsdfpdf*bsdfpdf);
                    L += bsdf_f*direct_l*absdot(wi, *normal_s)*weight/
                         lightpdf;
                }
            }
        }

        //mip bsdf sampling
        //NULL is guaranteed not be used since the call will never be specular
        Spectrum bsdf_f = mat->sample_value(rand[3], rand[4], rand[5], &wo, hp,
                                            matrix, &wi, &bsdfpdf, false,
                                            &matchedSpec);
        if(bsdfpdf>0 && !bsdf_f.is_black())
        {
            float w = 1.f; //weight
            lightpdf = light->pdf(point_s, &wi);
            if(lightpdf == 0)
                return L; //no contribution from bsdf sampling
            w = (bsdfpdf*bsdfpdf)/(bsdfpdf*bsdfpdf+lightpdf*lightpdf);
            //here the shading point could lead to wrong intersections
            Ray r2(*point_s, wi);
            HitPoint h2;
            if(sc->k.intersect(&r2, &h2))
                //TODO: previously: if(h2.asset_h->get_id() == light->get_id())
                if((void*)h2.asset_h == (void*)light)
                    if(dot(h2.normal_h, -r2.direction)>0)
                    {
                        Spectrum rad = light->emissive_spectrum();
                        L += bsdf_f*rad*absdot(wi, *normal_s)*w/bsdfpdf;
                    }
        }
    }
    return L;
}
