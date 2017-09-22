#include "microfacet.hpp"

MicrofacetR::MicrofacetR(Spectrum& spe, Fresnel* f, MicrofacetDist* md)
: Bdf(BdfFlags(BRDF|GLOSSY)),specular(spe)
{
    MicrofacetR::f = f;
    MicrofacetR::md = md;
}

MicrofacetR::~MicrofacetR()
{
    delete MicrofacetR::f;
    delete MicrofacetR::md;
}

Spectrum MicrofacetR::df(const Vec3 *woS, const Vec3 *wiS)const
{
    float costwo = fabsf(woS->z); //cosThetaWo
    float costwi = fabsf(wiS->z); //cosThetaWi
    Vec3 wh = *woS+*wiS;
    //zero-length half vector or (incident or transmitted parallel to normal)
    if(costwo == 0 || costwi==0 || (wh.x==0 && wh.y==0 && wh.z==0))
        return SPECTRUM_BLACK;
    wh.normalize();
    float inv = 1.f/(4.f*costwo*costwi);
    return specular*md->D(&wh)*md->G(woS,wiS,&wh)*f->eval(dot(*wiS,wh))*inv;
}
