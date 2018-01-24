//author: Davide Pizzolotto
//license: GNU GPLv3

#include "microfacet_distributions.hpp"

float MicrofacetDist::pdf(const Vec3*, const Vec3* wh)const
{
    return this->D(wh)*fabsf(wh->z);
}

Blinn::Blinn(float exponent)
{
    Blinn::exponent = clamp(exponent,0.f,100000.f);
}

float Blinn::D(const Vec3* h)const
{
    //phong = 1/(pi*alpha2)*((h dot n)^(2/alpha2 - 2))
    //assuming exponent = 2/alpha2 - 2, the result is the following
    return (exponent+2)*INV_TWOPI*powf(fabsf(h->z),exponent);
}

float Blinn::G(const Vec3* wo, const Vec3* wi)const
{
    return Blinn::G1(wo)*Blinn::G1(wi);
}

float Blinn::G1(const Vec3* v)const
{
    const float cos = fabsf(v->z);
    if(cos==0)
        return 0;
    if(cos>=1) //fully visible
        return 1;
    const float sin = sqrtf(1-cos*cos);
    
    //value suggested by Walter et al. in
    //Microfacet Models for Refraction through Rough Surfaces
    //http://www.cs.cornell.edu/~srm/publications/EGSR07-btdf.pdf
    const float c = sqrtf(0.5f*Blinn::exponent+1)/(sin/cos);
    
    if(c>=1.6f)
        return 1.f;
    else
        return (3.535f*c+2.181f*c*c)/(1+2.276f*c+2.577f*c*c);
}

void Blinn::sample_wh(const Vec3* wo,float r0,float r1,Vec3* wh)const
{
    const float cost = powf(r0,(1.f/(Blinn::exponent+1)));
    const float sint = sqrtf(max(0.f,1.f-cost*cost));
    const float phi = r1*TWO_PI;
    *wh = Vec3(sint*cosf(phi),sint*sinf(phi),cost);
    if(wo->z*wh->z<0)
        *wh = -*wh;
}

float Blinn::pdf(const Vec3* wo, const Vec3* wh)const
{
    float dotwoh = dot(*wo,*wh);
    if(dotwoh>0.f)
    {
        const float cost = fabsf(wh->z);
        return ((Blinn::exponent+2)*powf(cost,exponent))/TWO_PI;
    }
    else
        return 0.f;
}

Beckmann::Beckmann(float roughness)
{
    Beckmann::a = clamp(roughness,0.f,1.f);
}

float Beckmann::D(const Vec3* h)const
{
    const float cost2 = h->z*h->z;
    const float sint2 = 1.f-cost2;
    if(cost2==0)
        return 0.f;
    const float a2 = Beckmann::a*Beckmann::a;
    const float exp = expf(-(sint2/cost2)/a2);
    return exp/(ONE_PI*cost2*cost2*a2)*exp;
}

float Beckmann::G(const Vec3* wo, const Vec3* wi)const
{
    return Beckmann::G1(wo)*Beckmann::G1(wi);
}

float Beckmann::G1(const Vec3* v)const
{
    const float cos = fabsf(v->z);
    if(cos==0)
        return 0;
    if(cos>=1) //fully visible
        return 1;
    const float c = cos/(sqrtf(max(0.f,1.f-cos*cos))*Beckmann::a);
    if(c>=1.6f)
        return 1.f;
    else
        return (3.535f*c+2.181f*c*c)/(1.f+2.276f*c+2.577f*c*c);
}

void Beckmann::sample_wh(const Vec3 *wo, float r0, float r1, Vec3 *wh)const
{
    //sampling algorithm for beckmann and GGX
    //https://agraphicsguy.wordpress.com/2015/11/01/sampling-microfacet-brdf
    //theta = arccos(1/sqrt(1-a2*log(1-r0)));
    const float l = log(1.f-r0);
    const float sqrt = 1.f-(Beckmann::a*Beckmann::a*l);
    const float cost = 1.f/sqrtf(sqrt);
    const float sint = sqrtf(1.f-cost*cost);
    const float phi = TWO_PI*r1;
    *wh = Vec3(sint*cosf(phi),sint*sinf(phi),cost);
    if(wo->z*wh->z<0)
        *wh = -*wh;
}

GGXiso::GGXiso(float roughness)
{
    roughness = clamp(roughness,0.f,1.f);
    GGXiso::a2 = roughness*roughness;
}

float GGXiso::D(const Vec3 *h)const
{
    if(h->z==0)
        return 0.f;
    const float cos2t = h->z*h->z;
    const float sin2t = max(0.f,1-cos2t);
    float sqr_term = a2+(sin2t/cos2t);
    sqr_term*=sqr_term;
    return a2/(sqr_term*cos2t*cos2t*ONE_PI);
}

float GGXiso::G(const Vec3 *wo, const Vec3 *wi)const
{
    return GGXiso::G1(wo)*GGXiso::G1(wi);
}

float GGXiso::G1(const Vec3* v)const
{
    const float cos2 = v->z*v->z;
    if(cos2==0)
        return 0.f;
    const float sin2 = max(0.f,1-cos2*cos2);
    return 2/(1+sqrtf(1+a2*sin2/cos2));
    
}

void GGXiso::sample_wh(const Vec3 *wo, float r0, float r1, Vec3 *wh)const
{
    const float cos2t = (1.f-r0)/(r0*(a2-1)+1);
    const float cost = sqrtf(max(0.f,cos2t));
    const float sint = sqrtf(max(0.f,1.f-cos2t));
    const float phi = TWO_PI*r1;
    *wh = Vec3(sint*cosf(phi),sint*sinf(phi),cost);
    if(wo->z*wh->z<0)
        *wh = -*wh;
}

GGXaniso::GGXaniso(float ax, float ay)
{
    GGXaniso::ax = ax;
    GGXaniso::ay = ay;
    GGXaniso::ax = clamp(GGXaniso::ax, 0.f, 1.f);
    GGXaniso::ay = clamp(GGXaniso::ay, 0.f, 1.f);
}

float GGXaniso::D(const Vec3 *h)const
{
    if(h->z==0)
        return 0.f;
    const float inv_cos2 = 1.f/(h->z*h->z);
    const float sin2 = max(0.f,1.f-(h->z*h->z));
    if(sin2==0)
        return 1.f;
    const float inv_sin2 = 1.f/sin2;
    const float tan2 = sin2*inv_cos2;
    const float inv_ax = 1.f/ax;
    const float inv_ay = 1.f/ay;
    //cosphi = h->x/sintheta due to the chosen shading space
    const float cosphi2 = h->x*h->x*inv_sin2;
    //sinphi = h->y/sintheta due to the chosen shading space
    const float sinphi2 = h->y*h->y*inv_sin2;
    
    float sq_term = 1+(((cosphi2*inv_ax*inv_ax)+(sinphi2*inv_ay*inv_ay))*tan2);
    sq_term*=sq_term;
    float res = INV_PI*inv_ax*inv_ay*inv_cos2*inv_cos2*(1.f/sq_term);
    return res;
}

static inline float lambdaGGXaniso(const Vec3* v,float ax, float ay)
{
    const float cos = v->z;
    const float sin = sqrtf(max(0.f,1.f-cos*cos));
    const float sin2 = sin*sin;
    const float tan = fabsf(sin/cos);
    if(std::isinf(tan))
        return 0.f;
   if(tan==0) //perpendicular = fully visible
       return 1.f;
    const float cos2phi = (v->x*v->x)/sin2;
    const float sin2phi = (v->y*v->y)/sin2;
    const float alpha = sqrtf(cos2phi*ax*ax+sin2phi*ay*ay);
    return (-1+sqrtf(1.f+(tan*tan*alpha*alpha)))*0.5f;
}

float GGXaniso::G(const Vec3* wo, const Vec3* wi)const
{
    //this one is taken from pbrtv3
    return 1.f/(1+lambdaGGXaniso(wo,ax,ay)+lambdaGGXaniso(wi,ax,ay));
}

void GGXaniso::sample_wh(const Vec3 *wo, float r0, float r1, Vec3 *wh)const
{
    //again, anisotropic equations are taken from pbrtv3
    float phi = atanf(ay/ax*tanf(TWO_PI*r1+.5f*ONE_PI));
    if(r1 > .5f)
        phi += ONE_PI;
    const float sinphi = sinf(phi);
    const float cosphi = cosf(phi);
    const float ax2 = ax * ax;
    const float ay2 = ay * ay;
    const float a2 = 1/(cosphi*cosphi/ax2+sinphi*sinphi/ay2);
    const float tantheta2 = a2*r0/(1-r0);
    const float cost = 1.f/sqrtf(1.f + tantheta2);
    const float sint = sqrtf(max(0.f,1.f-cost*cost));
    *wh = Vec3(sint*cosf(phi),sint*sinf(phi),cost);
    if(wo->z*wh->z<0)
        *wh = -*wh;
}
