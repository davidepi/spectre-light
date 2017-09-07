#include "reflection.hpp"

Reflection::Reflection(const Spectrum& specular, const Spectrum& ior1,
                       const Spectrum& ior2, bool conductor)
    : Bdf(BdfFlags(BRDF|SPECULAR)),specular(specular),conductor(conductor)
{
    if(conductor)
        Reflection::fc = new Conductor(ior1,ior2);
    else
        Reflection::fc = new Dielectric(ior1,ior2);
}

Reflection::~Reflection()
{
    delete Reflection::fc;
}

Spectrum Reflection::df(const Vec3*, const Vec3*) const
{
    return SPECTRUM_BLACK;
}

Spectrum Reflection::df_s(const Vec3 *wo, Vec3 *wi, float r0, float,
                          float* pdf) const
{
    //wi = wo * [-1 0 0 0]
    //          [0 -1 0 0]
    //          [0  0 1 0]
    //          [0  0 0 1]
    wi->x = -wo->x;
    wi->y = -wo->y;
    wi->z = wo->z;
    int chosen = 0;
    if(conductor)
        *pdf = 1.f;
    else
    {
        *pdf = 1.f/SPECTRUM_SAMPLES;
        chosen = min((int)(r0*SPECTRUM_SAMPLES),SPECTRUM_SAMPLES-1);
    }
    return fc->eval(wo->z,chosen)*specular/fabsf(wo->z);
}

float Reflection::pdf(const Vec3*, const Vec3*)const
{
    return 0.f;
}

Bdf* Reflection::clone()const
{
    Reflection* res = new Reflection(*this);
    return res;
}
