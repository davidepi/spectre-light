#include "reflection.hpp"

Reflection::Reflection(const Spectrum& specular)
    : Bdf(BdfFlags(BRDF|SPECULAR)),specular(specular)
{
    
}

Spectrum Reflection::df(const Vec3*, const Vec3*) const
{
    return SPECTRUM_BLACK;
}

float Reflection::pdf(const Vec3*, const Vec3*)const
{
    return 0.f;
}

ConductorReflection::ConductorReflection(const Spectrum& specular,
                                         const Spectrum& refraction,
                                         const Spectrum& absorption)
: Reflection(specular),ior(refraction)
{
    fresnel = (ior*ior)+(absorption*absorption);
}

#ifdef DISPERSION
DielectricReflection::DielectricReflection(const Spectrum& specular,
                                           const Spectrum& ior_i,
                                           const Spectrum& ior_t)
: Reflection(specular),eta_i(ior_i),eta_t(ior_t)
{
    //validator class guarantees no DISPERSION without SPECTRAL
}
#else
DielectricReflection::DielectricReflection(const Spectrum& specular,
                                           const Spectrum& ior_i,
                                           const Spectrum& ior_t)
: Reflection(specular)
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
#endif

Spectrum ConductorReflection::df_s(const Vec3 *wo, Vec3 *wi, float, float,
                                   float* pdf, char* choose)const
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
    *pdf=1.f;
    return eval*specular/fabsf(wo->z);
}

Spectrum DielectricReflection::df_s(const Vec3 *wo, Vec3 *wi, float, float,
                                    float* pdf, char* choose)const
{
    wi->x = -wo->x;
    wi->y = -wo->y;
    wi->z = wo->z;
    *pdf = 1.f;
#ifdef DISPERSION
    const Spectrum* ei;
    const Spectrum* et;
    float abscosthetai = wo->z;
    if (wo->z < 0) //exiting ray
    {
        ei = &eta_t;
        et = &eta_i;
        abscosthetai = fabsf(wo->z);
    }
    else
    {
        ei = &eta_i;
        et = &eta_t;
    }
    Spectrum sinthetat = (*ei / *et);
    sinthetat *= sqrtf(max(0.f, 1.f - abscosthetai*abscosthetai));
    
    Spectrum costhetat;
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
    {
        if(sinthetat.w[i]>1)
            sinthetat.w[i] = 1.f;
        costhetat.w[i] = sqrtf(max(0.f,1.f-sinthetat.w[i]*sinthetat.w[i]));
    }
    
    Spectrum etatcosi = *et*abscosthetai;
    Spectrum etaicosi = *ei*abscosthetai;
    Spectrum etatcost = *et*costhetat;
    Spectrum etaicost = *ei*costhetat;
        
    Spectrum rperp = (etaicosi - etatcost) / (etaicosi + etatcost);
    Spectrum rpar  = (etatcosi - etaicost) / (etatcosi + etaicost);
    Spectrum eval = (rpar*rpar+rperp*rperp)/2.f;
    eval /= fabsf(wo->z)
#else
    float ei;
    float et;
    float abscosthetai = wo->z;
    if (wo->z < 0) //exiting ray
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
    float sinthetat = (ei/et)* sqrtf(max(0.f, 1.f - abscosthetai*abscosthetai));
    float eval;
    if(sinthetat>1.f)
        eval = 1.f;
    else
    {
        float costhetat = sqrtf(max(0.f, 1.f - sinthetat * sinthetat));
        float etatcosi = et * abscosthetai;
        float etaicosi = ei * abscosthetai;
        float etatcost = et * costhetat;
        float etaicost = ei * costhetat;

        float rperp = (etaicosi - etatcost) / (etaicosi + etatcost);
        float rpar = (etatcosi - etaicost) / (etatcosi + etaicost);
        eval = (rpar * rpar + rperp * rperp) / 2.f;
        eval /= fabsf(wo->z);
    }
#endif
    return specular*eval;
}
