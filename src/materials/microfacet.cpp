//author: Davide Pizzolotto
//license: GNU GPLv3

#include "microfacet.hpp"

MicrofacetR::MicrofacetR(const MicrofacetDist* distribution,
                         const Fresnel* fresnel)
        :Bdf(FLAG_BRDF)
{
    MicrofacetR::fresnel = fresnel;
    MicrofacetR::distribution = distribution;
}

MicrofacetR::~MicrofacetR()
{
    delete MicrofacetR::fresnel;
    delete MicrofacetR::distribution;
}

Spectrum MicrofacetR::value(const Vec3* woS, const Vec3* wiS) const
{
    if(woS->z*wiS->z<0)//different hemispheres
        return SPECTRUM_BLACK;
    float costwo = fabsf(woS->z); //cosThetaWo
    float costwi = fabsf(wiS->z); //cosThetaWi
    Vec3 wh = *woS+*wiS;
    //zero-length half vector or (incident or transmitted parallel to normal)
    if(costwo == 0 || costwi == 0 || (wh.x == 0 && wh.y == 0 && wh.z == 0))
        return SPECTRUM_BLACK;
    wh.normalize();
    float inv = 4.f*costwo*costwi;
    return fresnel->eval(dot(*wiS, wh))*distribution->D(&wh)*
           distribution->G(woS, wiS)/inv;
}

Spectrum MicrofacetR::sample_value(const Vec3* wo, Vec3* wi, float r0, float r1,
                                   float* pdf) const
{
    Vec3 wh;
    MicrofacetR::distribution->sample_wh(wo, r0, r1, &wh);
    wh.normalize();
    *wi = -reflect(*wo, wh);
    wi->normalize();
    if(wo->z*wi->z<0)
    {
        *pdf = 0;
        return SPECTRUM_BLACK;
    }
    //4.f*dot(woS,wh); is the transformation from pdf wrt half vector
    //(returned by the function) to pdf wrt incident vector.
    *pdf = MicrofacetR::distribution->pdf(wo, &wh)/(4.f*dot(*wo, wh));
    return MicrofacetR::value(wo, wi);
}

float MicrofacetR::pdf(const Vec3* woS, const Vec3* wiS) const
{
    if(woS->z*wiS->z<0)
        return 0.f;
    Vec3 wh = *woS+*wiS;
//    if(wh.x==0 && wh.y==0 && wh.z == 0) //impossible
//        return 0.f;
    wh.normalize();
    //4.f*dot(woS,wh); is the transformation from pdf wrt half vector
    //to pdf wrt incident vector
    return MicrofacetR::distribution->pdf(woS, &wh)/(4.f*dot(*woS, wh));
}

MicrofacetT::MicrofacetT(const MicrofacetDist* md,
                         const Spectrum& etai, const Spectrum& etat)
        :Bdf(FLAG_BTDF), fresnel_diel(etai, etat)
{
    MicrofacetT::distribution = md;
    MicrofacetT::eta_i = fresnel_diel.get_eta_incident();
    MicrofacetT::eta_t = fresnel_diel.get_eta_transmitted();
}

MicrofacetT::~MicrofacetT()
{
    delete distribution;
}

Spectrum MicrofacetT::value(const Vec3* woS, const Vec3* wiS) const
{
    if(woS->z*wiS->z>0)
        return SPECTRUM_BLACK;
    float costwo = woS->z;
    float costwi = wiS->z;
    if(costwo == 0 || costwi == 0)
        return SPECTRUM_BLACK;
    float etao;
    float etai;
    if(costwo>0)
    {
        etao = eta_i;
        etai = eta_t;
    }
    else
    {
        etao = eta_t;
        etai = eta_i;
    }
    Vec3 wh = -*woS*etao-*wiS*etai;
    if(wh.x == 0 && wh.y == 0 && wh.z == 0)
        return SPECTRUM_BLACK;
    wh.normalize();
    if(wh.z<0)
        wh = -wh;
    float dotwoh = dot(*woS, wh);
    float dotwih = dot(*wiS, wh);
    //abs are made at the end. Every value is always positive in the formula
    float up = etao*etao*distribution->D(&wh)*distribution->G(woS, wiS)*
               dotwoh*dotwih;
    if(flt_equal(up, 0.f)) //avoid calculating fresnel term
    {
        return SPECTRUM_BLACK;
    }
    float denom = etao*dotwoh+etai*dotwih;
    denom *= denom;
    denom *= costwo*costwi;
    return (SPECTRUM_ONE-fresnel_diel.eval(dotwih))*fabsf(up/denom);
}

Spectrum MicrofacetT::sample_value(const Vec3* woS, Vec3* wiS, float r0,
                                   float r1, float* pdf) const
{
    Vec3 wh;
    if(woS->z == 0)
    {
        *pdf = 0.f;
        return SPECTRUM_BLACK;
    }
    MicrofacetT::distribution->sample_wh(woS, r0, r1, &wh);
    wh.normalize();
    //refracted ray
    float etao;
    float etai;
    if(woS->z>0)
    {
        etao = eta_i;
        etai = eta_t;
    }
    else
    {
        etao = eta_t;
        etai = eta_i;
    }
    *wiS = refract(*woS, wh, etao/etai);
    if(wiS->x == 0 && wiS->y == 0 && wiS->z == 0) //Total internal reflection
    {
        *pdf = 0;
        return SPECTRUM_BLACK;
    }
    const float dotwoh = dot(*woS, wh);
    float jacobian = etao*etao*fabsf(dotwoh);
    const float jacobian_denom = (etai*dot(*wiS, wh)+etao*dotwoh);
    jacobian /= jacobian_denom*jacobian_denom;
    wiS->normalize();
    *pdf = MicrofacetT::distribution->pdf(woS, &wh)*jacobian;
    return MicrofacetT::value(woS, wiS);
}

float MicrofacetT::pdf(const Vec3* woS, const Vec3* wiS) const
{
    if(woS->z*wiS->z>0)
        return 0;
    float etao;
    float etai;
    if(woS->z>0)
    {
        etao = eta_i;
        etai = eta_t;
    }
    else
    {
        etao = eta_t;
        etai = eta_i;
    }
    Vec3 wh = -*woS*etao-*wiS*etai;
    if(wh.x == 0 && wh.y == 0 && wh.z == 0)
        return 0.f;
    wh.normalize();
    const float dotwoh = dot(*woS, wh);
    float jacobian = etao*etao*fabsf(dotwoh);
    const float jacobian_denom = (etai*dot(*wiS, wh)+etao*dotwoh);
    jacobian /= jacobian_denom*jacobian_denom;
    return MicrofacetT::distribution->pdf(woS, &wh)*jacobian;
}

