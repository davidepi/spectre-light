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
