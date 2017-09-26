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

Spectrum MicrofacetR::df_s(const Vec3* wo, Vec3* wi, float r0, float r1,
                           float* pdf, char*)const
{
    Vec3 wh;
    MicrofacetR::md->sampleWh(wo, r0, r1, &wh);
    *wi = reflect(*wo, wh);
    if(wo->z*wi->z < 0)
    {
        *pdf = 0;
        return SPECTRUM_BLACK;
    }
    *pdf = MicrofacetR::md->pdf(wo, &wh, wi);
    return MicrofacetR::df(wo, wi);
}

float MicrofacetR::pdf(const Vec3* woS, const Vec3* wiS)const
{
    if(woS->z*wiS->z < 0)
        return 0.f;
    Vec3 wh = *woS+*wiS;
    wh.normalize();
    if(wh.x!=0 || wh.y!=0 || wh.z != 0)
    {
        wh.normalize();
        return MicrofacetR::md->pdf(woS, &wh, wiS);
    }
    else
        return 0.f;
}
