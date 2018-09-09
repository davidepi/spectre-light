//author: Davide Pizzolotto
//license: GNU GPLv3

#include "light_spot.hpp"

static inline float falloff(float cost, float coswidth, float cosfall)
{
    float retval;
    if (cost < coswidth)
        retval = 0.f;
    else if (cost > cosfall)
        retval = 1.f;
    else
    {
        retval = (cost - coswidth) / (cosfall - coswidth);
        retval *= retval*retval*retval;
    }
    return retval;
}

LightSpot::LightSpot(const Spectrum& intensity, const Matrix4& transform, float radius, float falloff_start) 
    :Light(intensity),light2world(transform)
{
    light_position = transform * Point3(0.f);
    const float RADIUS_RAD = radians(radius);
    const float FALLOFF_RAD = radians(falloff_start);
    transform.inverse(&world2light);
    cos_cone_width = 1.f / (1.f + RADIUS_RAD * RADIUS_RAD);
    cos_falloff_start = 1.f / (1.f + FALLOFF_RAD * FALLOFF_RAD);
}

Spectrum LightSpot::sample_surface(float r0, float r1, float r2, float r3, Ray * out, float * pdf) const
{
    out->origin = light_position;
    const float COST = (1.f - r0) + r0 * cos_cone_width;
    const float SINT = sqrtf(max(0.f, 1 - COST * COST));
    const float PHI = r1 * 2.f*ONE_PI;
    out->direction.x = SINT * cosf(PHI);
    out->direction.y = SINT * sinf(PHI);
    out->direction.z = COST;
    const float FALLOFF = falloff(out->direction.z, cos_cone_width, cos_falloff_start);
    out->direction = light2world * out->direction;
    out->direction.normalize();
    *pdf = INV_TWOPI * (1.f / (1.f - cos_cone_width));
    return c * FALLOFF;
}

Spectrum LightSpot::sample_visible_surface(float r0, float r1, const Point3 * position, Vec3 * wi, float * pdf, float * distance) const
{
    *wi = light_position - *position;
    *distance = wi->length();
    wi->normalize();
    Vec3 wiL = world2light * *wi;
    *pdf = 1.f;
    return c*falloff(wiL.z,cos_cone_width,cos_falloff_start) / (*distance**distance);
}

float LightSpot::pdf(const Ray*) const
{
    return INV_TWOPI * (1.f / (1.f - cos_cone_width));
}

float LightSpot::pdf(const Point3*, const Vec3*) const
{
    return 0.0f;
}

bool LightSpot::renderable() const
{
    return false;
}
