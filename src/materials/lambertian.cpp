#include "lambertian.hpp"
Lambertian::Lambertian(Color *scattered_spectrum) : Bdf(BdfFlags(BRDF|DIFFUSE))
{
    diffuse = *scattered_spectrum;
}

Lambertian::~Lambertian()
{

}

Color Lambertian::df(const Vec3*, const Vec3* ) const
{
    //equally scattered in every direction
    Color ret;
    ret.r = Lambertian::diffuse.r * INV_PI;
    ret.g = Lambertian::diffuse.g * INV_PI;
    ret.b = Lambertian::diffuse.b * INV_PI;
    return ret;
}