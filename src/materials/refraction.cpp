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

Color Refraction::df_s(const Vec3 *wo, Vec3 *wi, float, float, float* pdf) const
{
    float ei = eta_i;
    float et = eta_t;

    //check if the incident ray is coming from outside the object or not
    //normal is (0,0,1) so z > 0 = coming from outside
    bool fromOutside = wo->z > 0;
    if(!fromOutside) //swaps the index, since I assume ei is for the outside
        swap(&ei,&et);

    //calculate transmitted direction
    float sinincident2 = 1.f-(wo->z*wo->z);
    float eta = ei/et;
    float sintransmitted2 = eta*eta*sinincident2;
    //total internal reflection
    if(sintransmitted2>=1)
        return Color();
    //calculate transmitted ray
    float costransmitted = fromOutside?sqrtf(max(0.f,1.f-sintransmitted2)):
                           -sqrtf(max(0.f,1-sintransmitted2));
    wi->x = eta * -wo->x;
    wi->y = eta * -wo->y;
    wi->z = costransmitted;
    *pdf = 1.f;
    //return BTDF
    return (Color(1)-d.eval(wo->z)) * (et*et)/(ei*ei) * specular/fabsf(wi->z);
}

float Refraction::pdf(const Vec3* wo, const Vec3* wi)const
{
    return 1.f;
}

Bdf* Refraction::clone()const
{
    Refraction* res = new Refraction(*this);
    return res;
}