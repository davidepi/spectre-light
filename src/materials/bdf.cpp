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

Color Bdf::df_s(const Vec3 *wo, Vec3 *wi) const
{
    return df(wo,wi);
}

Bsdf::Bsdf()
{
    Bsdf::count = 0;
}

Bsdf::~Bsdf()
{

}

void Bsdf::addBdf(const Bdf& addme)
{
#ifdef _LOW_LEVEL_CHECKS_
    if(count==_MAX_BDF_)
    {
        Console.severe("Cannot add more Bdfs");
        return;
    }
#endif
    Bsdf::bdfs[count++] = addme.clone();
}

Color Bsdf::df(const Vec3 *wo, const HitPoint* h, Vec3 *wi)const
{
    Vec3 wo_shading_space(wo->dot(h->right),wo->dot(h->cross),wo->dot(h->n));
    Vec3 wi_shading_space(wi->dot(h->right),wi->dot(h->cross),wi->dot(h->n));
    BdfFlags val;
    if(wi->dot(h->n)*wo->dot(h->n) > 0) //transmitted ray
        val = BTDF;
    else                                //reflected ray
        val = BRDF;
    Color retval;
    for(int i=0;i<count;i++)
    {
        if(bdfs[i].isType(val)) //add contribution only if matches refl/trans
            retval += bdfs[i].df(&wo_shading_space,&wi_shading_space);
    }
    return retval;
}

