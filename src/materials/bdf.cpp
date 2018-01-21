//author: Davide Pizzolotto
//license: GNU GPLv3

#include "bdf.hpp"
Bdf::Bdf(BdfFlags flags)
{
    Bdf::type = flags;
}

BdfFlags Bdf::get_flags() const
{
    return Bdf::type;
}

Spectrum Bdf::sample_value(const Vec3 *wo, Vec3 *wi, float r0, float r1,
                   float* pdf)const
{
    //sample x,y points on the hemisphere, shirley's method maybe's better
    float t = TWO_PI * r0;
    float r = sqrtf(r1);
    wi->x = r * cosf(t);
    wi->y = r * sinf(t);
    wi->z = sqrtf(max(0.f,1.f-wi->x*wi->x-wi->y*wi->y));
    //if the wo was flipped, flip also wi
    if(wo->z < 0) wi->z *= -1.f;
    *pdf = fabsf(wi->z)*INV_PI;
    return value(wo,wi);
}
float Bdf::pdf(const Vec3* wo, const Vec3* wi)const
{
    //default pdf is cos(theta)/pi
    return wo->z*wi->z>0?fabsf(wi->z)*INV_PI:0.f;
}

Bsdf::Bsdf()
{
    Bsdf::count = 0;
}

Bsdf::~Bsdf()
{
    for(int i=0;i<count;i++)
        delete Bsdf::bdfs[i];
}

void Bsdf::inherit_bdf(Bdf* addme)
{
#ifdef DEBUG
    if(count==_MAX_BDF_)
    {
        Console.severe("Cannot add more Bdfs");
        return;
    }
#endif
    Bsdf::bdfs[count++] = addme;
}

Spectrum Bsdf::value(const Vec3 *wo, const HitPoint* h, const Vec3 *wi,
                  BdfFlags val)const
{
    Vec3 wo_shading_space(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->normal_h));
    Vec3 wi_shading_space(wi->dot(h->right),wi->dot(h->cross),wi->dot(h->normal_h));
    if(wi->dot(h->normal_h)*wo->dot(h->normal_h) > 0)//reflected ray
        val = (BdfFlags)(val & ~BTDF);
    else                                //transmitted ray
        val = (BdfFlags)(val & ~BRDF);
    Spectrum retval = SPECTRUM_BLACK;
    wo_shading_space.normalize();
    wi_shading_space.normalize();
    for(int i=0;i<count;i++)
    {
        if(bdfs[i]->is_type(val)) //add contribution only if matches refl/trans
            retval += bdfs[i]->value(&wo_shading_space,&wi_shading_space);
    }
    return retval;
}

Spectrum Bsdf::sample_value(float r0, float r1, float r2, const Vec3* wo,
                    const HitPoint* h, Vec3* wi, float* pdf,
                    BdfFlags matchme, BdfFlags* val)const
{
    int matchcount = 0;
    Bdf* matching[_MAX_BDF_];
    for(int i=0;i<Bsdf::count;i++)
        if (Bsdf::bdfs[i]->is_type(matchme))
            matching[matchcount++] = bdfs[i];

    if(matchcount==0)
    {
        *pdf = 0.f;
        return SPECTRUM_BLACK;//otherwise it will access invalid array positions
    }
    int chosen = (int)(r0 * matchcount);
    if(chosen == matchcount) //out of array
        chosen--;

    //transform to shading space
    Vec3 wo_shading_space(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->normal_h));
    Vec3 tmpwi;

    //I don't care about the result, but I need to generate the &wi vector
    //TODO: gained efficiency by creating an ad-hoc method?
    Spectrum retval;
    retval=matching[chosen]->sample_value(&wo_shading_space, &tmpwi,r1,r2,pdf);

    //transform incident ray to world space
    wi->x = h->right.x*tmpwi.x + h->cross.x * tmpwi.y + h->normal_h.x * tmpwi.z;
    wi->y = h->right.y*tmpwi.x + h->cross.y * tmpwi.y + h->normal_h.y * tmpwi.z;
    wi->z = h->right.z*tmpwi.x + h->cross.z * tmpwi.y + h->normal_h.z * tmpwi.z;

    *val = matching[chosen]->get_flags();//val now is a subset of matchme
    if(wi->length()==0)
    {
        *pdf = 0.f;
        return SPECTRUM_BLACK;
    }
    else
    {
        wo_shading_space.normalize();
        tmpwi.normalize();
        wi->normalize();
    }
    //if not specular, throw away retval and compute the value for the generated
    //pair of directions
    if((*val & SPECULAR)==0)
    {
        retval = SPECTRUM_BLACK;
        if (wo->dot(h->normal_h) * wi->dot(h->normal_h) > 0)
            *val = (BdfFlags)(*val & ~BTDF);
        else
            *val = (BdfFlags)(*val & ~BRDF);
        for (int i = 0; i < count; i++)
        {
            if (bdfs[i]->is_type(*val))//add contribution only if matches
                retval += bdfs[i]->value(&wo_shading_space, &tmpwi);
            if(bdfs[i]!=matching[chosen] && bdfs[i]->is_type(matchme))
                *pdf+= bdfs[i]->pdf(&wo_shading_space, &tmpwi);
        }
    }
    if(matchcount>1)
        *pdf/=matchcount;
    return retval;
}

float Bsdf::pdf(const Vec3* wo,  const HitPoint* h, const Vec3* wi,
                BdfFlags m)const
{
    if(Bsdf::count == 0)
        return 0.f;
    Vec3 wo_shading_space(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->normal_h));
    Vec3 wi_shading_space(wi->dot(h->right),wi->dot(h->cross),wi->dot(h->normal_h));
    wo_shading_space.normalize();
    wi_shading_space.normalize();
    float pdf = 0.f;
    int matching = 0;
    for (int i = 0; i < count; ++i)
    {
        if(bdfs[i]->is_type(m))
        {
            matching++;
            pdf += bdfs[i]->pdf(&wo_shading_space, &wi_shading_space);
        }
    }
    if(matching>0)
        return pdf/(float)matching;
    else
        return 0.f;
}

