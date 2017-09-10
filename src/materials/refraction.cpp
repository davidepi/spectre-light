#include "refraction.hpp"
Refraction::Refraction(const Spectrum& s, const Spectrum& etai,
                       const Spectrum& etat)
: Bdf(BdfFlags(BTDF|SPECULAR)),specular(s),eta_i(etai),eta_t(etat),d(etai,etat)
{

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
    retval.w[sampled_spectrum] -=
                            d.eval(wi->z,sampled_spectrum).w[sampled_spectrum];
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

Spectrum cauchyEq(float B, float C, float D)
{
#ifdef SPECTRAL
    Spectrum retval;
#else
    float ior = 0;
#endif

    float current_wavelength = SPECTRUM_START*1E-3f;
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
    {
        float c = C/(current_wavelength*current_wavelength);
        float d = D/powf(current_wavelength,4);
#ifdef SPECTRAL
        retval.w[i] = B + c + d;
#else
        ior += B + c + d;
#endif
        current_wavelength += SPECTRUM_INTERVAL*1E-3f;
    }
#ifdef SPECTRAL
    return retval;
#else
    return Spectrum(ior*INV_SPECTRUM_SAMPLES);
#endif

}

Spectrum sellmeierEq(float B1,float B2,float B3,float C1,float C2,float C3)
{
#ifdef SPECTRAL
    Spectrum retval;
#else
    float ior = 0;
#endif
    float current_wavelength = SPECTRUM_START*1E-3f;
    float p1,p2,p3;
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
    {
        p1 = (B1*current_wavelength*current_wavelength) /
             (current_wavelength*current_wavelength-C1);
        p2 = (B2*current_wavelength*current_wavelength) /
             (current_wavelength*current_wavelength-C2);
        p3 = (B3*current_wavelength*current_wavelength) /
             (current_wavelength*current_wavelength-C3);
#ifdef SPECTRAL
        retval.w[i] = 1 + p1 + p2 + p3;
#else
        ior+= 1 + p1 + p2 + p3;
#endif
        current_wavelength += SPECTRUM_INTERVAL*1E-3f;
    }
#ifdef SPECTRAL
    return retval;
#else
    return Spectrum(ior*INV_SPECTRUM_SAMPLES);
#endif
}
