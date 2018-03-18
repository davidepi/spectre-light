//author: Davide Pizzolotto
//license: GNU GPLv3

#include "lambertian.hpp"

Lambertian::Lambertian(const Spectrum& scattered_spectrum)
:Bdf(FLAG_BRDF),diffuse(scattered_spectrum*INV_PI)
{
    
}

Spectrum Lambertian::value(const Vec3*, const Vec3*)const
{
    //equally scattered in every direction
    return Lambertian::diffuse;
}
