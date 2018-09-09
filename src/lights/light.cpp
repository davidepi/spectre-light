//author: Davide Pizzolotto
//license: GNU GPLv3

#include "light.hpp"

Light::Light(const Spectrum& intensity):c(intensity)
{}

Spectrum Light::emissive_spectrum() const
{
    return c;
}
