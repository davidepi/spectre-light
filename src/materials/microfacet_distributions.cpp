#include "microfacet_distributions.hpp"

float MicrofacetDist::G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const
{
    float cosh = fabsf(wh->z);
    float inv_dot = 1.f/absdot(*wo,*wh);
    float partial = 2*cosh*inv_dot;
    return min(1.f,min(partial*fabsf(wo->z),partial*fabsf(wi->z)));
}

Blinn::Blinn(float exponent)
{
    Blinn::exponent = exponent;
}

float Blinn::D(const Vec3* h)const
{
    return (exponent+2)*INV_TWOPI*powf(fabsf(h->z),Blinn::exponent);
}

void Blinn::sampleWh(const Vec3* wo,float r0,float r1,Vec3* wh)const
{
    float cost = powf(r0,(1.f/Blinn::exponent+1));
    float sint = sqrtf(1.f-cost*cost);
    float phi = r1*TWO_PI;
    *wh = Vec3(sint*cosf(phi),sint*sinf(phi),cost);
    if(wo->z*wh->z<0) *wh = -*wh;
}

float Blinn::pdf(const Vec3* wo, const Vec3* wh, const Vec3* wi)const
{
    float dotwoh = dot(*wo,*wh);
    if(dotwoh>0.f)
    {
        float cost = fabsf(wh->z);
        return ((Blinn::exponent+1)*powf(cost,exponent))/(FOUR_PI*2.f*dotwoh);
    }
    else
        return 0.f;
}

Beckmann::Beckmann(float roughness)
{
    Beckmann::inv_a = 1.f/roughness;
}

float Beckmann::D(const Vec3* h)const
{
    float cos2 = h->z*h->z;
    float inv_cos2 = 1.f/cos2;
    float inv_a2 = inv_a*inv_a;
    return inv_a2*INV_PI*inv_cos2*inv_cos2*exp((cos2-1.f)*inv_a2*inv_cos2);
}

float Beckmann::G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const
{
    return Beckmann::G1(wo)*Beckmann::G1(wi);
}

float Beckmann::G1(const Vec3* v)const
{
    float cos = fabsf(v->z);
    float c = cos*inv_a*(1.f/sqrtf(1.f-cos*cos));
    if(c>=1.6)
        return 1.f;
    else
        return (3.535f*c+2.181f*c*c)/(1+2.276*c+2.577*c*c);
        
}

GGXiso::GGXiso(float roughness)
{
    GGXiso::a2 = roughness*roughness;
}

float GGXiso::D(const Vec3 *h)const
{
    float squared_term = 1+(h->z*h->z)*(a2-1);
    squared_term*=squared_term;
    return a2*INV_PI*(1.f/squared_term);
}

float GGXiso::G(const Vec3 *wo, const Vec3 *wi, const Vec3 *wh)const
{
    return GGXiso::G1(wo)*GGXiso::G1(wi);
}

float GGXiso::G1(const Vec3* v)const
{
    float cos = v->z;
    return (2*cos)/(cos+sqrtf(a2+(1-a2)*cos*cos));
}

GGXaniso::GGXaniso(float ax, float ay)
{
    GGXaniso::inv_ax = 1.f/ax;
    GGXaniso::inv_ay = 1.f/ay;
}

float GGXaniso::D(const Vec3 *h)const
{
    float inv_cos2 = 1.f/(h->z*h->z);
    float sin2 = 1.f-(h->z*h->z);
    float inv_sin2 = 1.f/sin2;
    float tan2 = sin2*inv_cos2;
    //cosphi = h->x/sintheta due to the chose shading space
    float cosphi2 = h->x*h->x*inv_sin2;
    //cosphi = h->x/sintheta due to the chose shading space
    float sinphi2 = h->y*h->y*inv_sin2;
    
    float sq_term = 1+(((cosphi2*inv_ax*inv_ax)+(sinphi2*inv_ay*inv_ay))*tan2);
    sq_term*=sq_term;
    
    return INV_PI*inv_ax*inv_ay*inv_cos2*inv_cos2*(1.f/sq_term);
}

static inline float lambdaGGXaniso(const Vec3* v,float ax, float ay)
{
    float cos = v->z;
    float sin = sqrtf(1.f-cos*cos);
    float sin2 = sin*sin;
    float tan = fabsf(sin/cos);
    if(std::isinf(tan))
        return 0.f;
    float cos2phi = (v->x*v->x)/sin2;
    float sin2phi = (v->y*v->y)/sin2;
    float alpha = sqrtf(cos2phi*ax*ax+sin2phi*ay*ay);
    return (-1+sqrtf(1.f+(tan*tan*alpha*alpha)))*0.5f;
}

float GGXaniso::G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const
{
    //this one is taken from pbrtv3
    float ax = 1.f/inv_ax;
    float ay = 1.f/inv_ay;
    return 1.f/(1+lambdaGGXaniso(wo,ax,ay)+lambdaGGXaniso(wi,ax,ay));
}

void Beckmann::sampleWh(const Vec3 *wo, float r0, float r1, Vec3 *wh)const
{
    Console.critical("Uninplemented");
}

float Beckmann::pdf(const Vec3 *wo, const Vec3 *wh, const Vec3 *wi)const
{
    Console.critical("Uninplemented");
    return 0;
}

void GGXiso::sampleWh(const Vec3 *wo, float r0, float r1, Vec3 *wh)const
{
    Console.critical("Uninplemented");
}

float GGXiso::pdf(const Vec3 *wo, const Vec3 *wh, const Vec3 *wi)const
{
    Console.critical("Uninplemented");
    return 0;
}

void GGXaniso::sampleWh(const Vec3 *wo, float r0, float r1, Vec3 *wh)const
{
    Console.critical("Uninplemented");
}

float GGXaniso::pdf(const Vec3 *wo, const Vec3 *wh, const Vec3 *wi)const
{
    Console.critical("Uninplemented");
    return 0;
}
