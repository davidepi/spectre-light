#include "microfacet_distributions.hpp"

Blinn::Blinn(float exponent) : MicrofacetDist()
{
    Blinn::exponent = exponent;
}

float Blinn::d(const Vec3* h)const
{
    return (exponent+2)*INV_TWOPI*powf(fabsf(h->z),Blinn::exponent);
}

Anisotropic::Anisotropic(float x, float y) : MicrofacetDist()
{
    Anisotropic::x = x;
    Anisotropic::y = y;
}

float Anisotropic::d(const Vec3* h)const
{
    float cos = fabsf(h->z);
    float sin = 1.f-cos*cos;
    if(sin==0)
        return 0;
    float exp = (x*h->x*h->x+y*h->y*h->y)/sin;
    return sqrtf((x+2)*(y+2))*INV_TWOPI*powf(cos,exp);
}

Beckmann::Beckmann(float roughness)
{
    Beckmann::inv_a2 = 1.f/(roughness*roughness);
}

float Beckmann::d(const Vec3* h)const
{
    float cos2 = h->z*h->z;
    float inv_cos2 = 1.f/cos2;
    return inv_a2*INV_PI*inv_cos2*inv_cos2*exp((cos2-1.f)*inv_a2*inv_cos2);
}

GGXiso::GGXiso(float roughness)
{
    GGXiso::a2 = roughness*roughness;
}

float GGXiso::d(const Vec3 *h)const
{
    float squared_term = 1+(h->z*h->z)*(a2-1);
    squared_term*=squared_term;
    return a2*INV_PI*(1.f/squared_term);
}

GGXaniso::GGXaniso(float ax, float ay)
{
    GGXaniso::inv_ax = 1.f/ax;
    GGXaniso::inv_ay = 1.f/ay;
}

float GGXaniso::d(const Vec3 *h)const
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
