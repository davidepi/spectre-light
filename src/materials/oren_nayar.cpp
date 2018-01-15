//author: Davide Pizzolotto
//license: GNU GPLv3

#include "oren_nayar.hpp"

OrenNayar::OrenNayar(const Spectrum& diffuse, float sigma)
:Bdf(BdfFlags(BRDF|DIFFUSE)),diffuse(diffuse)
{
    OrenNayar::diffuse*=INV_PI;
    float sigma2 = sigma*sigma;
    OrenNayar::A = 1.f - (sigma2/(2*(sigma2+0.33f)));
    OrenNayar::B = (0.45f*sigma2)/(sigma2+0.09f);
}

Spectrum OrenNayar::value(const Vec3 *wout, const Vec3 *wincident) const
{
    float costhetain = wincident->z;
    float costhetaout = wout->z;
    float abscosthetain = fabsf(costhetain);
    float abscosthetaout = fabsf(costhetaout);
    float sinthetain = sqrtf(max(0.f,1.f-costhetain*costhetain));
    float sinthetaout = sqrtf(max(0.f,1.f-costhetaout*costhetaout));

    //cos(phiin - phiout) = cos(phiin)*cos(phiout)+sin(phiin)*sin(phiout)
    float maxcos = 0.0f;
    if(sinthetain>0.f && sinthetaout>0.f) //cos(phiin - phiout) positive
    {
        float cosphiin, cosphiout, sinphiin, sinphiout;
        cosphiin = clamp(wincident->x/sinthetain,-1.f,1.f);
        cosphiout = clamp(wout->x/sinthetaout,-1.f,1.f);
        sinphiin = max(0.f,sqrtf(1.f - cosphiin * cosphiin));
        sinphiout = max(0.f,sqrtf(1.f - cosphiout * cosphiout));
        maxcos = max(0.0f, cosphiin * cosphiout + sinphiin * sinphiout);
    }
    else
        return OrenNayar::diffuse*A;

    float sinalpha, tanbeta;
    if(abscosthetain>abscosthetaout)
    {
        sinalpha = sinthetaout;
        tanbeta = sinthetain/abscosthetain;
    }
    else
    {
        sinalpha = sinthetain;
        tanbeta = sinthetaout/abscosthetaout;
    }

    //diffuse/pi * (A+B*max[0,cos(phiin-phiout)]*sinalpha*tanbeta)
    return OrenNayar::diffuse * (A+B*maxcos*sinalpha*tanbeta);
}

