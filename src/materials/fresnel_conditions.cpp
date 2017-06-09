#include "fresnel_conditions.hpp"

Conductor::Conductor(float refraction, float absorption)
{
    Conductor::refraction_index = refraction;
    Conductor::absorption = absorption;
}

Color Conductor::eval(float cosin)
{
    //conductors have complex index of refraction where the imaginary part
    //is the "transmitted" (absorbed) part
    //eta_t can be rewritten as eta_t-i*k_t
    //reflected spectrum becomes
    //R = avg(Rparaller * Rparallel,Rperp * Rperp)

    float tmp = refraction_index*refraction_index+absorption*absorption;
    float cosinsq = cosin*cosin;
    float etacosin2 = 2.f*refraction_index*cosin;

    float rperpsq = (tmp-etacosin2+cosinsq)/(tmp+etacosin2+cosinsq);
    tmp*=cosinsq;
    float rparsq = (tmp-etacosin2+1)/(tmp+etacosin2+1);

    return (rperpsq+rparsq)/2.f;
}