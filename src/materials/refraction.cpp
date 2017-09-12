#include "refraction.hpp"
#ifdef DISPERSION
Refraction::Refraction(const Spectrum& s, const Spectrum& etai,
                       const Spectrum& etat)
: Bdf(BdfFlags(BTDF|SPECULAR)),specular(s),eta_i(etai),eta_t(etat)
{

}
#else
Refraction::Refraction(const Spectrum& s, const Spectrum& etai,
                       const Spectrum& etat)
: Bdf(BdfFlags(BTDF|SPECULAR)),specular(s)
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
#endif

Spectrum Refraction::df(const Vec3*, const Vec3*) const
{
    return SPECTRUM_BLACK;
}

Spectrum Refraction::df_s(const Vec3 *wo, Vec3 *wi, float r0, float,
                          float* pdf,char* choose) const
{
#ifdef DISPERSION
    if(*choose==-1)
        *choose = (char)min((int)(r0*SPECTRUM_SAMPLES),SPECTRUM_SAMPLES-1);
#endif
    float ei;
    float et;

    //check if the incident ray is coming from outside the object or not
    //normal is (0,0,1) so z > 0 = coming from outside
    bool fromOutside = wo->z > 0;
    float eval;
    float abscosincident = wo->z;
    if(!fromOutside) //swaps the index, since I assume ei is for the outside
    {
#ifdef DISPERSION
        ei = Refraction::eta_t.w[*choose];
        et = Refraction::eta_i.w[*choose];
#else
        ei = Refraction::eta_t;
        et = Refraction::eta_i;
#endif
        abscosincident = fabsf(abscosincident);
    }
    else
    {
#ifdef DISPERSION
        ei = Refraction::eta_i.w[*choose];
        et = Refraction::eta_t.w[*choose];
#else
        ei = Refraction::eta_i;
        et = Refraction::eta_t;
#endif
    }

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
    *pdf = 1.f;

    float etatcosi = et*abscosincident;
    float etaicosi = ei*abscosincident;
    float etatcost = et*costransmitted;
    float etaicost = ei*costransmitted;
    float rperp = (etaicosi - etatcost) / (etaicosi + etatcost);
    float rpar  = (etatcosi - etaicost) / (etatcosi + etaicost);
    eval = 1.f-(rpar*rpar+rperp*rperp)/2.f;
    
    //return BTDF
    Spectrum retval(eval);
    retval *= (ei*ei)/(et*et);
    retval *= specular/fabsf(wi->z);
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
