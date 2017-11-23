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
    float inv = 4.f*costwo*costwi;
    return specular*md->D(&wh)*md->G(woS,wiS,&wh)*f->eval(dot(*wiS,wh))/inv;
}

Spectrum MicrofacetR::df_s(const Vec3* wo, Vec3* wi, float r0, float r1,
                           float* pdf)const
{
    Vec3 wh;
    MicrofacetR::md->sampleWh(wo, r0, r1, &wh);
    wh.normalize();
    *wi = -reflect(*wo, wh);
    wi->normalize();
    if(wo->z*wi->z < 0)
    {
        *pdf = 0;
        return SPECTRUM_BLACK;
    }
    //4.f*dot(woS,wh); is the transformation from pdf wrt half vector
    //to pdf wrt incident vector
    *pdf = MicrofacetR::md->pdf(wo, &wh, wi)/(4.f*dot(*wo,wh));
    if(pdf==0)
        return SPECTRUM_BLACK;
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
        //4.f*dot(woS,wh); is the transformation from pdf wrt half vector
        //to pdf wrt incident vector
        return MicrofacetR::md->pdf(woS, &wh, wiS)/(4.f*dot(*woS,wh));
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
    if(wh.x==0 && wh.y==0 && wh.z==0)
        return SPECTRUM_BLACK;
    wh.normalize();
    if(wh.z<0)
        wh = -wh;
    float dotwoh = dot(*woS,wh);
    float dotwih = dot(*wiS,wh);
    //abs are made at the end. Every value is always positive in the formula
    float up= etao*etao*md->D(&wh)*md->G(woS,wiS,&wh)*dotwoh*dotwih;
    if(up==0) //avoid calculating fresnel term
    {
        return SPECTRUM_BLACK;
    }
    float denom = etao*dotwoh+etai*dotwih;
    denom*=denom;
    denom*=costwo*costwi;
    return  specular * (SPECTRUM_ONE-d.eval(dotwih)) * fabsf(up/denom);
}

Spectrum MicrofacetT::df_s(const Vec3* woS, Vec3* wiS, float r0, float r1,
                            float* pdf)const
{
    Vec3 wh;
    if(woS->z == 0)
    {
        *pdf = 0.f;
        return SPECTRUM_BLACK;
    }
    MicrofacetT::md->sampleWh(woS, r0, r1, &wh);
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
    
    //-woS because the vector is pointing outside
    *wiS = refract(-*woS, wh, etao/etai);
    if(wiS->x==0 && wiS->y==0 && wiS->z==0) //Total internal reflection
    {
        *pdf = 0;
        return SPECTRUM_BLACK;
    }
    const float dotwoh = dot(*woS,wh);
    float jacobian = etao*etao*fabsf(dotwoh);
    const float jacobian_denom = (etai*dot(*wiS,wh)+etao*dotwoh);
    jacobian/=jacobian_denom*jacobian_denom;
    wiS->normalize();
    *pdf = MicrofacetT::md->pdf(woS, &wh, wiS)*jacobian;
    return MicrofacetT::df(woS,wiS);
}

float MicrofacetT::pdf(const Vec3* woS, const Vec3* wiS)const
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
    Vec3 wh = -*wiS*etai-*woS*etao;
    if(wh.x==0 && wh.y==0 && wh.z==0)
        return 0.f;
    wh.normalize();
    const float dotwoh = dot(*woS,wh);
    float jacobian = etao*etao*fabsf(dotwoh);
    const float jacobian_denom = (etai*dot(*wiS,wh)+etao*dotwoh);
    jacobian/=jacobian_denom*jacobian_denom;
    return MicrofacetT::md->pdf(woS, &wh, wiS)*jacobian;
}
