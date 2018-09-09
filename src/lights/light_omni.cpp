//author: Davide Pizzolotto
//license: GNU GPLv3

#include "light_omni.hpp"

LightOmni::LightOmni(Spectrum intensity, const Matrix4& transform)
        :Light(intensity)
{
    light_position = transform*Point3(0.f);
}

Spectrum
LightOmni::sample_surface(float r0, float r1, float, float, Ray* out,
                          float* pdf) const
{
    out->origin = light_position;
    const float cost = 1.f-2.f*r0;
    const float sint = sqrtf(max(0.f, 1-cost*cost));
    const float phi = 2.f*ONE_PI*r1;
    out->direction.x = sint*cosf(phi);
    out->direction.y = sint*sinf(phi);
    out->direction.z = cost;
    *pdf = INV_FOURPI;
    return c;
}

Spectrum
LightOmni::sample_visible_surface(float, float, const Point3* position,
                                  Vec3* wi, float* pdf, float* distance) const
{
    *wi = light_position-*position;
    *distance = wi->length();
    wi->normalize();
    *pdf = 1.f;
    return c/(*distance**distance);
}

float LightOmni::pdf(const Ray*) const
{
    return INV_FOURPI;
}

float LightOmni::pdf(const Point3*, const Vec3*) const
{
    return 0.f;
}

bool LightOmni::renderable() const
{
    return false;
}
