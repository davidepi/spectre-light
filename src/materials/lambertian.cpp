//author: Davide Pizzolotto
//license: GNU GPLv3

#include "lambertian.hpp"

//need to construct the SPECTRUM_ONE here since the static vars in the spectrum
//file is not guaranteed to be initialized before this
const Spectrum Lambertian::DIFFUSE = Spectrum(
        {
                1.f, 1.f, 1.f, 1.f,
                1.f, 1.f, 1.f, 1.f,
                1.f, 1.f, 1.f, 1.f,
                1.f, 1.f, 1.f, 1.f
        })*INV_PI;

Lambertian::Lambertian():Bdf(FLAG_BRDF)
{

}

Spectrum Lambertian::value(const Vec3*, const Vec3*) const
{
    //equally scattered in every direction
    return Lambertian::DIFFUSE;
}
