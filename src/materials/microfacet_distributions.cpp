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
    float cos2 = fabsf(h->z)*fabsf(h->z);
    float inv_cos2 = 1.f/cos2;
    return inv_a2*INV_PI*inv_cos2*inv_cos2*exp(-((1-cos2)*inv_cos2)*inv_a2);
}
