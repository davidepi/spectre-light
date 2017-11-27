//author: Davide Pizzolotto
//license: GNU GPLv3

#include "lambertian.hpp"

Lambertian::Lambertian(const Spectrum& scattered_spectrum)
:Bdf(BdfFlags(BRDF|DIFFUSE)),diffuse(scattered_spectrum)
{
    Lambertian::diffuse*=INV_PI;
}

Bdf* Lambertian::clone()const
{
    Lambertian* res = new Lambertian(*this);
    return res;
}

Spectrum Lambertian::df(const Vec3*, const Vec3*)const
{
    //equally scattered in every direction
    return Lambertian::diffuse;
}
