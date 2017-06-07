#include "lambertian.hpp"
Lambertian::Lambertian(Color *scattered_spectrum) : Bdf(BRDF|DIFFUSE)
{
    diffuse = *scattered_spectrum;
}

Lambertian::~Lambertian()
{

}

Color Lambertian::df(const Vec3*, const Vec3* ) const
{
    //equally scattered in every direction
    return Lambertian::diffuse;
}