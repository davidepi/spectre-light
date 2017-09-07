#include "refraction.hpp"
Refraction::Refraction(const Spectrum& s, const Spectrum& etai,
                       const Spectrum& etat)
: Bdf(BdfFlags(BTDF|SPECULAR)),specular(s),eta_i(etai),eta_t(etat),d(etai.w[0],etat.w[0])
{
    //TODO: change dielectric class
}

Spectrum Refraction::df(const Vec3*, const Vec3*) const
{
    return SPECTRUM_BLACK;
}

Spectrum Refraction::df_s(const Vec3 *wo, Vec3 *wi, float r0, float,
                          float* pdf) const
{
    int sampled_spectrum = min((int)(r0*SPECTRUM_SAMPLES),SPECTRUM_SAMPLES-1);
    float ei = eta_i.w[sampled_spectrum];
    float et = eta_t.w[sampled_spectrum];

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
        return SPECTRUM_BLACK;
    //calculate transmitted ray
    float costransmitted = fromOutside?-sqrtf(1.f-sintransmitted2):
                                        sqrtf(1-sintransmitted2);
    wi->x = eta * -wo->x;
    wi->y = eta * -wo->y;
    wi->z = costransmitted;
    *pdf = 1.f/SPECTRUM_SAMPLES;
    
    //return BTDF
    Spectrum retval = SPECTRUM_BLACK;
    retval.w[sampled_spectrum] = SPECTRUM_WHITE.w[sampled_spectrum];
    retval.w[sampled_spectrum] -= d.eval(wi->z).w[sampled_spectrum];
    retval.w[sampled_spectrum] *= (ei*ei)/(et*et);
    retval.w[sampled_spectrum] *= specular.w[sampled_spectrum]/fabsf(wi->z);
    return retval;
}

float Refraction::pdf(const Vec3*, const Vec3*)const
{
    return 0.f;
}

Bdf* Refraction::clone()const
{
    Refraction* res = new Refraction(*this);
    return res;
}
