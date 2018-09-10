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
    const float COST = 1.f-2.f*r0;
    out->origin = light_position;
    const float SINT = sqrtf(max(0.f, 1-COST*COST));
    const float PHI = 2.f*ONE_PI*r1;
    out->direction.x = SINT*cosf(PHI);
    out->direction.y = SINT*sinf(PHI);
    out->direction.z = COST;
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
