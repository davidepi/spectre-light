//author: Davide Pizzolotto
//license: GNU GPLv3

#include "fresnel_conditions.hpp"

Conductor::Conductor(const Spectrum& refraction, const Spectrum& absorption) :
refraction_index(refraction),absorption(absorption)
{

}

Spectrum Conductor::eval(float cosin)const
{
    //conductors have complex index of refraction where the imaginary part
    //is the "transmitted" (absorbed) part
    //eta_t can be rewritten as eta_t-i*k_t
    //reflected spectrum becomes
    //R = avg(Rparaller * Rparallel,Rperp * Rperp)

    Spectrum tmp = refraction_index*refraction_index+absorption*absorption;
    float cosinsq = cosin*cosin;
    Spectrum etacosin2 = refraction_index*(cosin*2.f);

    Spectrum rperpsq = (tmp-etacosin2+cosinsq)/(tmp+etacosin2+cosinsq);
    tmp*=cosinsq;
    Spectrum rparsq = (tmp-etacosin2+1)/(tmp+etacosin2+1);

    return (rperpsq+rparsq)/2.f;
}

Dielectric::Dielectric(const Spectrum& etai, const Spectrum& etat)
{
#ifdef SPECTRAL
    Dielectric::eta_i = 0;
    Dielectric::eta_t = 0;
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
    {
        eta_i+=etai.w[i];
        eta_t+=etat.w[i];
    }
    eta_i*=INV_SPECTRUM_SAMPLES;
    eta_t*=INV_SPECTRUM_SAMPLES;
#else
    Dielectric::eta_i = etai.w[0];
    Dielectric::eta_t = etat.w[0];
#endif
}

Spectrum Dielectric::eval(float cosin)const
{
    float ei;
    float et;
    float abscosthetai = cosin;
    if (cosin < 0) //exiting ray
    {
        ei = eta_t;
        et = eta_i;
        abscosthetai = -cosin;
    }
    else
    {
        ei = eta_i;
        et = eta_t;
        abscosthetai = cosin;
    }
    float sinthetat = (ei/et)*sqrtf(max(0.f, 1.f - abscosthetai*abscosthetai));
    if(sinthetat >= 1.f) //Total internal reflection
        return 1.f;
    else
    {
        float costhetat = sqrtf(max(0.f,1.f-sinthetat*sinthetat));
        float etatcosi = et*abscosthetai;
        float etaicosi = ei*abscosthetai;
        float etatcost = et*costhetat;
        float etaicost = ei*costhetat;

        float rperp = (etaicosi - etatcost) / (etaicosi + etatcost);
        float rpar  = (etatcosi - etaicost) / (etatcosi + etaicost);
        float retval = (rpar*rpar+rperp*rperp)/2.f;
        return Spectrum(retval);
    }
}

float Dielectric::get_eta_incident()const
{
    return Dielectric::eta_i;
}

float Dielectric::get_eta_transmitted()const
{
    return Dielectric::eta_t;
}

