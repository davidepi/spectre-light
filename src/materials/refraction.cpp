#include "refraction.hpp"

Refraction::Refraction(Color s, float etai, float etat)
        : Bdf(BdfFlags(BTDF|SPECULAR)), specular(s), d(etai,etat)
{
    eta_i = etai;
    eta_t = etat;
}

Color Refraction::df(const Vec3*, const Vec3*) const
{
    return Color();
}

Color Refraction::df_s(const Vec3 *wo, Vec3 *wi) const
{
    float ei = eta_i;
    float et = eta_t;
    bool fromOutside = wo->z > 0;
    if(!fromOutside)
        swap(&ei,&et);
    float sinincident2 = 1.f-(wo->z*wo->z);
    float eta = ei/et;
    float sintransmitted2 = eta*eta*sinincident2;
    if(sintransmitted2>=1)
        return Color();
    float costransmitted = fromOutside?sqrtf(max(0.f,1.f-sintransmitted2)):
                           -sqrtf(max(0.f,1-sintransmitted2));
    wi->x = eta * -wo->x;
    wi->y = eta * -wo->y;
    wi->z = costransmitted;
    return (Color(1)-d.eval(wo->z)) * (et*et)/(ei*ei) * specular/fabsf(wi->z);
}

Bdf* Refraction::clone()const
{
    Refraction* res = new Refraction(*this);
    return res;
}