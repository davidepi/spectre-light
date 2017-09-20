#include "microfacet.hpp"

Blinn::Blinn(float exponent) : Microfacet()
{
    Blinn::exponent = exponent;
}

float Blinn::d(const Vec3* h)const
{
    return (exponent+2)*INV_TWOPI*powf(fabsf(h->z),Blinn::exponent);
}
