#include "lambertian.hpp"

Lambertian::Lambertian(Color scattered_spectrum) : Bdf(BdfFlags(BRDF|DIFFUSE)),
                                                   diffuse(scattered_spectrum)
{

}

Bdf* Lambertian::clone()const
{
    Lambertian* res = new Lambertian(*this);
    return res;
}

Color Lambertian::df(const Vec3*, const Vec3* ) const
{
    //equally scattered in every direction
    return Lambertian::diffuse*INV_PI;
}
