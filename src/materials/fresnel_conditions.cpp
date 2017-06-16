#include "fresnel_conditions.hpp"

Conductor::Conductor(Color refraction, Color absorption) :
refraction_index(refraction),absorption(absorption)
{

}

Color Conductor::eval(float cosin)const
{
    //conductors have complex index of refraction where the imaginary part
    //is the "transmitted" (absorbed) part
    //eta_t can be rewritten as eta_t-i*k_t
    //reflected spectrum becomes
    //R = avg(Rparaller * Rparallel,Rperp * Rperp)

    Color tmp = refraction_index*refraction_index+absorption*absorption;
    Color cosinsq = cosin*cosin;
    Color etacosin2 = refraction_index*(cosin*2.f);

    Color rperpsq = (tmp-etacosin2+cosinsq)/(tmp+etacosin2+cosinsq);
    tmp*=cosinsq;
    Color rparsq = (tmp-etacosin2+1)/(tmp+etacosin2+1);

    return (rperpsq+rparsq)/2.f;
}

Dielectric::Dielectric(float refractioni, float refractiont)
{
    Dielectric::etai = refractioni;
    Dielectric::etat = refractiont;
}

Dielectric::~Dielectric()
{

}

Color Dielectric::eval(float cosin)const
{
    float ei = Dielectric::etai;
    float et = Dielectric::etat;
    if (cosin < 0) //exiting ray
        swap(&ei, &et);
    float sintheta = ei / et * sqrtf(max(0.f, 1.f - cosin * cosin));
    if(sintheta >= 1.f) //Total internal reflection
        return 1.f;
    else
    {
        float costheta = sqrtf(max(0.f,1.f-sintheta*sintheta));
        float cosabsin = fabsf(cosin);
        float etatcosi = et*cosabsin;
        float etaicosi = ei*cosabsin;
        float etatcost = et*costheta;
        float etaicost = ei*costheta;

        float rperp = (etaicosi - etatcost) / (etaicosi + etatcost);
        float rpar  = (etatcosi - etaicost) / (etatcosi + etaicost);
        return Color((rpar*rpar+rperp*rperp)/2.f);
    }
}