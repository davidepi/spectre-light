#include "bdf.hpp"
Bdf::Bdf(BdfFlags flags)
{
    Bdf::type = flags;
}

Bdf::~Bdf()
{

}

Color Bdf::df_s(const Vec3 *wo, Vec3 *wi) const
{
    return df(wo,wi);
}

Bsdf::Bsdf()
{
    Bsdf::count = 0;
}

void Bsdf::addBdf(Bdf addme)
{
#ifdef _LOW_LEVEL_CHECKS_
    if(count==_MAX_BDF_)
    {
        Console.severe("Cannot add more Bdfs");
        return;
    }
#endif
    Bsdf::bdfs[count++] = addme;
}

