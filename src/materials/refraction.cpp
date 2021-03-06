//author: Davide Pizzolotto
//license: GNU GPLv3

#include "refraction.hpp"

Refraction::Refraction(const Spectrum& etai, const Spectrum& etat)
        :Bdf(FLAG_BTDF | FLAG_SPEC)
{
#ifdef SPECTRAL
    Refraction::eta_i = 0;
    Refraction::eta_t = 0;
    for(int i=0;i<SPECTRUM_SAMPLES;i++)
    {
        eta_i+=etai.w[i];
        eta_t+=etat.w[i];
    }
    eta_i*=INV_SPECTRUM_SAMPLES;
    eta_t*=INV_SPECTRUM_SAMPLES;
#else
    eta_i = etai.w[0];
    eta_t = etat.w[0];
#endif
}

Spectrum Refraction::value(const Vec3*, const Vec3*) const
{
    return SPECTRUM_BLACK;
}

Spectrum Refraction::sample_value(const Vec3* wo, Vec3* wi, float, float,
                                  float* pdf) const
{
    float ei;
    float et;

    //check if the incident ray is coming from outside the object or not
    //normal is (0,0,1) so z > 0 = coming from outside
    bool fromOutside = wo->z>0;
    float eval;
    float abscosincident = wo->z;
    if(!fromOutside) //swaps the index, since I assume ei is for the outside
    {

        ei = Refraction::eta_t;
        et = Refraction::eta_i;
        abscosincident = fabsf(abscosincident);
    }
    else
    {
        ei = Refraction::eta_i;
        et = Refraction::eta_t;
    }

    //calculate transmitted direction
    float sinincident2 = 1.f-(wo->z*wo->z);
    float eta = ei/et;
    float sintransmitted2 = eta*eta*sinincident2;
    //total internal reflection
    if(sintransmitted2>=1)
    {
        *pdf = 0.f;
        return SPECTRUM_BLACK;
    }

    //transmitted angle
    float costhetat = sqrtf(1.f-sintransmitted2);

    //costhetat accounting the fact that is generated inside the object
    float costransmitted = fromOutside?-costhetat:costhetat;

    //calculate transmitted ray
    wi->x = eta*-wo->x;
    wi->y = eta*-wo->y;
    wi->z = costransmitted;
    *pdf = 1.f;

    float etatcosi = et*abscosincident;
    float etaicosi = ei*abscosincident;
    float etatcost = et*costhetat;
    float etaicost = ei*costhetat;
    float rperp = (etaicosi-etatcost)/(etaicosi+etatcost);
    float rpar = (etatcosi-etaicost)/(etatcosi+etaicost);
    eval = 1.f-((rpar*rpar+rperp*rperp)/2.f); //refracted part

    eval *= (ei*ei)/(et*et);
    eval /= fabsf(wi->z);

    return eval;
}

float Refraction::pdf(const Vec3*, const Vec3*) const
{
    return 0.f;
}

Spectrum cauchy(float B, float C, float D)
{
#ifdef SPECTRAL
    Spectrum retval;
#else
    float ior = 0;
#endif

    float current_wavelength = SPECTRUM_START*1E-3f;
    for(int i = 0; i<SPECTRUM_SAMPLES; i++)
    {
        float c = C/(current_wavelength*current_wavelength);
        float d = D/powf(current_wavelength, 4);
#ifdef SPECTRAL
        retval.w[i] = B + c + d;
#else
        ior += B+c+d;
#endif
        current_wavelength += SPECTRUM_INTERVAL*1E-3f;
    }
#ifdef SPECTRAL
    return retval;
#else
    return Spectrum(ior*INV_SPECTRUM_SAMPLES);
#endif

}

Spectrum sellmeier(float B1, float B2, float B3, float C1, float C2, float C3)
{
#ifdef SPECTRAL
    Spectrum retval;
#else
    float ior = 0;
#endif
    float current_wavelength = SPECTRUM_START*1E-3f;
    float p1, p2, p3;
    for(int i = 0; i<SPECTRUM_SAMPLES; i++)
    {
        float wavelength_squared = current_wavelength*current_wavelength;
        p1 = (B1*wavelength_squared)/(wavelength_squared-C1);
        p2 = (B2*wavelength_squared)/(wavelength_squared-C2);
        p3 = (B3*wavelength_squared)/(wavelength_squared-C3);
#ifdef SPECTRAL
        retval.w[i] = sqrtf(1 + p1 + p2 + p3);
#else
        ior += sqrtf(1+p1+p2+p3);
#endif
        current_wavelength += SPECTRUM_INTERVAL*1E-3f;
    }
#ifdef SPECTRAL
    return retval;
#else
    return Spectrum(ior*INV_SPECTRUM_SAMPLES);
#endif
}

