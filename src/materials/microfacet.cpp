#include "microfacet.hpp"

MicrofacetR::MicrofacetR(Spectrum& spe, MicrofacetDist* md, Fresnel* f)
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

Spectrum MicrofacetR::df(const Vec3* woS, const Vec3* wiS)const
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
    wh.normalize();
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
    if(wh.x!=0 || wh.y!=0 || wh.z != 0)
    {
        wh.normalize();
        return MicrofacetR::md->pdf(woS, &wh, wiS);
    }
    else
        return 0.f;
}

MicrofacetT::MicrofacetT(Spectrum& spe, MicrofacetDist* md,
                         Spectrum& etai, Spectrum& etat)
: Bdf(BdfFlags(BTDF|GLOSSY)), specular(spe), d(etai,etat)
{
    MicrofacetT::md = md;
    MicrofacetT::eta_i = d.getEtaIncident();
    MicrofacetT::eta_t = d.getEtaTransmitted();
}

MicrofacetT::~MicrofacetT()
{
    delete md;
}

Spectrum MicrofacetT::df(const Vec3* woS, const Vec3* wiS)const
{
    if(woS->z*wiS->z>0)
        return SPECTRUM_BLACK;
    float costwo = woS->z;
    float costwi = wiS->z;
    if(costwo == 0 || costwi == 0)
        return SPECTRUM_BLACK;
    float eta;
    if(costwo>0)
        eta = eta_t/eta_i;
    else
        eta = eta_i/eta_t;
    
    Vec3 wh = *woS+(*wiS*eta);
    if(wh.x==0 && wh.y==0 && wh.z==0)
        return SPECTRUM_BLACK;
    wh.normalize();
    if(wh.z<0) wh = -wh;
    float dotwoh = dot(*woS,wh);
    float dotwih = dot(*wiS,wh);
    
    float up= eta*eta*md->D(&wh)*md->G(woS,wiS,&wh)*fabsf(dotwoh)*fabsf(dotwih);
    if(up<1E-3) //avoid calculating fresnel term
        return SPECTRUM_BLACK;
    float denom = dotwoh+eta*dotwih;
    denom*=denom;
    denom*= costwo*costwi;
    
    return  specular * (SPECTRUM_ONE-d.eval(dotwoh)) * fabsf(up/denom);
}

Spectrum MicrofacetT::df_s(const Vec3* woS, Vec3* wiS, float r0, float r1,
                            float* pdf, char* choose)const
{
    Vec3 wh;
    MicrofacetT::md->sampleWh(woS, r0, r1, &wh);
    //refracted ray
    float eta;
    if(woS->z>0)
        eta = eta_t/eta_i;
    else
        eta = eta_i/eta_t;
    float costi = dot(wh,*woS);
    float sin2ti = 1.f-costi*costi;
    float sin2tt = eta*eta*sin2ti;
    if(sin2tt>=1)
    {
        *pdf = 0.f;
        return SPECTRUM_BLACK;
    }
    float costt = sqrtf(1.f-sin2tt);
    *wiS = -*woS*eta+wh*(eta*costi-costt);
    //
    float dotwoh = dot(*woS,wh);
    float dotwih = dot(*wiS,wh);
    float inv = dotwoh+eta*dotwih;
    inv *= inv;
    float term = fabsf((eta*eta*dotwih)/inv);
    *pdf = MicrofacetT::md->pdf(woS, &wh, wiS)*term;
    return MicrofacetT::df(woS,wiS);
}

float MicrofacetT::pdf(const Vec3* woS, const Vec3* wiS)const
{
    if(woS->z*wiS->z>0)
        return 0;
    float eta;
    if(woS->z>0)
        eta = eta_t/eta_i;
    else
        eta = eta_i/eta_t;
    Vec3 wh = (*woS+*wiS*eta);
    if(wh.x==0 && wh.y==0 && wh.z==0)
        return 0.f;
    wh.normalize();
    float dotwoh = dot(*woS,wh);
    float dotwih = dot(*wiS,wh);
    float inv = dotwoh+eta*dotwih;
    inv*=inv;
    float term = fabsf((eta*eta*dotwih)/inv);
    return MicrofacetT::md->pdf(woS, &wh, wiS)*term;
}
