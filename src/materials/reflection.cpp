#include "reflection.hpp"

Reflection::Reflection(Color specular, FresnelConditions* fc)
        : Bdf(BdfFlags(BRDF|SPECULAR)),specular(specular)
{
    Reflection::fc = fc;
}

Color Reflection::df(const Vec3*, const Vec3*) const
{
    return Color();
}

Color Reflection::df_s(const Vec3* wo, Vec3* wi) const
{
    //wi = wo * [-1 0 0 0]
    //          [0 -1 0 0]
    //          [0  0 1 0]
    //          [0  0 0 1]
    wi->x = -wo->x;
    wi->y = -wo->y;
    wi->z = wo->z;
    return fc->eval(wo->z)*specular*fabsf(wo->z);
}

Bdf* Reflection::clone()const
{
    Reflection* res = new Reflection(*this);
    return res;
}