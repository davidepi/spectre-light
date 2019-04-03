//author: Davide Pizzolotto
//license: GNU GPLv3

#include "bdf.hpp"
#include "materials/lambertian.hpp"
#include "primitives/shape.hpp"
#include "utility/console.hpp"
#include "textures/texture.hpp"
#include "textures/texture_library.hpp"
#include <cstring> //error msg
#include <cstdlib> //malloc error msg

Bdf::Bdf(char flags)
{
    Bdf::type = flags;
}

char Bdf::get_flags() const
{
    return Bdf::type;
}

Spectrum Bdf::sample_value(const Vec3* wo, Vec3* wi, float r0, float r1,
                           float* pdf) const
{
    //sample x,y points on the hemisphere, shirley's method maybe's better
    float t = TWO_PI*r0;
    float r = sqrtf(r1);
    wi->x = r*cosf(t);
    wi->y = r*sinf(t);
    wi->z = sqrtf(max(0.f, 1.f-wi->x*wi->x-wi->y*wi->y));
    //if the wo was flipped, flip also wi
    if(wo->z<0) wi->z *= -1.f;
    *pdf = fabsf(wi->z)*INV_PI;
    return value(wo, wi);
}

float Bdf::pdf(const Vec3* wo, const Vec3* wi) const
{
    //default pdf is cos(theta)/pi
    return wo->z*wi->z>0?fabsf(wi->z)*INV_PI:0.f;
}
