#include "bdf.hpp"
Bdf::Bdf(BdfFlags flags)
{
    Bdf::type = flags;
}

Bdf::~Bdf()
{

}

BdfFlags Bdf::getFlags() const
{
    return Bdf::type;
}

Color Bdf::df_s(const Vec3 *wo, Vec3 *wi, float r0, float r1, float* pdf)const
{
    //sample x,y points on the hemisphere, shirley's method maybe's better
    float t = TWO_PI * r0;
    float r = sqrtf(r1);
    wi->x = r * cosf(t);
    wi->y = r * cosf(t);
    wi->z = sqrtf(max(0.f,1.f-wi->x*wi->x-wi->y*wi->y));
    //if the wo was flipped, flip also wi
    if(wo->z < 0) wi->z *= -1.f;
    *pdf = fabsf(wi->z)*INV_PI;
    return df(wo,wi);
}
float Bdf::pdf(const Vec3* wo, const Vec3* wi)const
{
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

void Bsdf::addBdf(const Bdf* addme)
{
#ifdef _LOW_LEVEL_CHECKS_
    if(count==_MAX_BDF_)
    {
        Console.severe("Cannot add more Bdfs");
        return;
    }
#endif
    Bsdf::bdfs[count++] = addme->clone();
}

Color Bsdf::df(const Vec3 *wo, const HitPoint* h, const Vec3 *wi,
               BdfFlags val)const
{
    Vec3 wo_shading_space(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->n));
    Vec3 wi_shading_space(wi->dot(h->right),wi->dot(h->cross),wi->dot(h->n));
    if(wi_shading_space.dot(h->n)*wo_shading_space.dot(h->n) > 0)//reflected ray
        val = (BdfFlags)(val & ~BTDF);
    else                                //transmitted ray
        val = (BdfFlags)(val & ~BRDF);
    Color retval;
    for(int i=0;i<count;i++)
    {
        if(bdfs[i]->isType(val)) //add contribution only if matches refl/trans
            retval += bdfs[i]->df(&wo_shading_space,&wi_shading_space);
    }
    return retval;
}

Color Bsdf::df_s(float r0, float r1, float r2, const Vec3* wo,
                 const HitPoint* h, Vec3* wi, float* pdf, BdfFlags matchme)const
{
    if(Bsdf::count == 0)
    {
        *pdf = 0.f;
        return Color(); //otherwise it will access invalid array positions
    }

    int matchcount = 0;
    Bdf* matching[_MAX_BDF_];
    for(int i=0;i<Bsdf::count;i++)
        if(Bsdf::bdfs[i]->isType(matchme))
        {
            matching[matchcount++]=bdfs[i];
        }

    int chosen = (int)(r0 * matchcount);
    if(chosen == matchcount) //out of array
        chosen--;

    //transform to shading space
    Vec3 wo_shading_space(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->n));
    Vec3 tmpwi;

    //I don't care about the result, but I need to generate the &wi vector
    //TODO: gained efficiency by creating an ad-hoc method?
    Color retval=matching[chosen]->df_s(&wo_shading_space, &tmpwi, r1, r2, pdf);

    //if not specular, throw away retval and compute the value for the generated
    //pair of directions
    if((matchme & SPECULAR)==0)
    {
        retval = Color();
        BdfFlags val = matching[chosen]->getFlags();//val now is a subset of
        char nummatching = 1;                       //matchme
        if (tmpwi.dot(h->n) * wo_shading_space.dot(h->n) > 0)
            val = (BdfFlags)(val & ~BTDF);
        else
            val = (BdfFlags)(val & ~BRDF);
        for (int i = 0; i < count; i++)
        {

            if (bdfs[i]->isType(val))//add contribution only if matches
            {
                retval += bdfs[i]->df(&wo_shading_space, &tmpwi);
                if(bdfs[i]!=matching[chosen])
                    *pdf += bdfs[i]->pdf(&wo_shading_space, &tmpwi);
                nummatching++;
            }
        }
        if(nummatching>1) //most of times this will be 1. Division is expensive
            *pdf /= nummatching;
    }

    //transform incident ray to world space
    wi->x = h->right.x*tmpwi.x + h->cross.x * tmpwi.y + h->n.x * tmpwi.z;
    wi->x = h->right.y*tmpwi.x + h->cross.y * tmpwi.y + h->n.y * tmpwi.z;
    wi->x = h->right.z*tmpwi.x + h->cross.z * tmpwi.y + h->n.z * tmpwi.z;

    return retval;
}

float Bsdf::pdf(const Vec3* wo,  const HitPoint* h, const Vec3* wi)const
{
    if(Bsdf::count == 0)
        return 0.f;
    Vec3 wo_shading_space(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->n));
    Vec3 wi_shading_space(wi->dot(h->right),wi->dot(h->cross),wi->dot(h->n));
    float pdf = 0.f;
    int matching = 0;
    for (int i = 0; i < count; ++i)
    {
        matching++;
        pdf += bdfs[i]->pdf(&wo_shading_space, &wi_shading_space);
    }
    if(matching>0)
        return pdf/(float)matching;
    else
        return 0.f;
}
