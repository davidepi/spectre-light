#include "fresnel_conditions.hpp"

FresnelConditions::~FresnelConditions()
{
    
}

Conductor::Conductor(const Spectrum& refraction, const Spectrum& absorption) :
refraction_index(refraction),absorption(absorption)
{

}

Spectrum Conductor::eval(float cosin, int)const
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

Dielectric::Dielectric(const Spectrum& refractioni, const Spectrum& refractiont)
{
    Dielectric::etai = refractioni;
    Dielectric::etat = refractiont;
}

Spectrum Dielectric::eval(float cosin, int c)const
{
    float ei = Dielectric::etai.w[c];
    float et = Dielectric::etat.w[c];
    float abscosthetai = cosin;
    if (cosin < 0) //exiting ray
    {
        swap(&ei, &et);
        abscosthetai = fabsf(cosin);
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
        Spectrum retval = SPECTRUM_BLACK;
        retval.w[c] = (rpar*rpar+rperp*rperp)/2.f;
        return retval;
    }
}
