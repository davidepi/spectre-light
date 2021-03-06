//author: Davide Pizzolotto
//license: GNU GPLv3

#include "reflection.hpp"

Reflection::Reflection():Bdf(FLAG_BRDF | FLAG_SPEC)
{

}

Spectrum Reflection::value(const Vec3*, const Vec3*) const
{
    return SPECTRUM_BLACK;
}

float Reflection::pdf(const Vec3*, const Vec3*) const
{
    return 0.f;
}

ConductorReflection::ConductorReflection(const Spectrum& refraction,
                                         const Spectrum& absorption)
        :ior(refraction), fresnel((ior*ior)+(absorption*absorption))
{
}

DielectricReflection::DielectricReflection(const Spectrum& ior_i,
                                           const Spectrum& ior_t)
{
#ifdef SPECTRAL
    DielectricReflection::eta_i = 0;
    DielectricReflection::eta_t = 0;
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
    {
        eta_i+=ior_i.w[i];
        eta_t+=ior_t.w[i];
    }
    eta_i*=INV_SPECTRUM_SAMPLES;
    eta_t*=INV_SPECTRUM_SAMPLES;
#else
    eta_i = ior_i.w[0];
    eta_t = ior_t.w[0];
#endif
}

Spectrum ConductorReflection::sample_value(const Vec3* wo, Vec3* wi,
                                           float, float, float* pdf) const
{
    //wi = wo * [-1 0 0 0]
    //          [0 -1 0 0]
    //          [0  0 1 0]
    //          [0  0 0 1]
    wi->x = -wo->x;
    wi->y = -wo->y;
    wi->z = wo->z;
    float cosinsq = wo->z*wo->z;
    Spectrum eval;
    Spectrum etacosin2 = ior*(wo->z*2.f);
    Spectrum rperpsq = (fresnel-etacosin2+cosinsq)/(fresnel+etacosin2+cosinsq);
    Spectrum tmp = fresnel*cosinsq;
    Spectrum rparsq = (tmp-etacosin2+1)/(tmp+etacosin2+1);
    eval = (rperpsq+rparsq)/2.f;
    *pdf = 1.f;
    return eval/fabsf(wo->z);
}

Spectrum DielectricReflection::sample_value(const Vec3* wo, Vec3* wi,
                                            float, float, float* pdf) const
{
    wi->x = -wo->x;
    wi->y = -wo->y;
    wi->z = wo->z;
    *pdf = 1.f;
    float ei;
    float et;
    float abscosthetai = wo->z;
    if(wo->z<=0) //exiting ray
    {
        ei = eta_t;
        et = eta_i;
        abscosthetai = fabsf(wo->z);
    }
    else
    {
        ei = eta_i;
        et = eta_t;
    }
    float sinthetat = (ei/et)*sqrtf(max(0.f, 1.f-abscosthetai*abscosthetai));
    float eval;
    if(sinthetat>1.f)
        eval = 1.f;
    else
    {
        float costhetat = sqrtf(max(0.f, 1.f-sinthetat*sinthetat));
        float etatcosi = et*abscosthetai;
        float etaicosi = ei*abscosthetai;
        float etatcost = et*costhetat;
        float etaicost = ei*costhetat;

        float rperp = (etaicosi-etatcost)/(etaicosi+etatcost);
        float rpar = (etatcosi-etaicost)/(etatcosi+etaicost);
        eval = (rpar*rpar+rperp*rperp)/2.f;
        eval /= fabsf(wo->z);
    }
    return eval;
}

