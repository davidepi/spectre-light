//author: Davide Pizzolotto
//license: GNU GPLv3

#include "light_spot.hpp"

static inline float falloff(float cost, float coswidth, float cosfall)
{
    float retval;
    if(cost<coswidth)
        retval = 0.f;
    else if(cost>cosfall)
        retval = 1.f;
    else
    {
        retval = (cost-coswidth)/(cosfall-coswidth);
        retval *= retval*retval*retval;
    }
    return retval;
}

LightSpot::LightSpot(const Spectrum& intensity, const Matrix4& transform,
                     float radius, float falloff_start):Light(intensity),
                                                        light2world(transform)
{
    light_position = transform*Point3(0.f);
    transform.inverse(&world2light);
    //if radius is the tan, then the found cos is only half of the required one
    const float COS_HALF = 1.f/(1.f+radius*radius);
    const float FOFF_HALF = 1.f/(1.f+falloff_start*falloff_start);
    cos_cone_width = 2*COS_HALF*COS_HALF-1.f;
    cos_falloff_start = 2*FOFF_HALF*FOFF_HALF-1.f;
}

Spectrum LightSpot::sample_surface(float r0, float r1, float, float, Ray* out,
                                   float* pdf) const
{
    out->origin = light_position;
    const float COST = (1.f-r0)+r0*cos_cone_width;
    const float SINT = sqrtf(max(0.f, 1-COST*COST));
    const float PHI = r1*2.f*ONE_PI;
    out->direction.x = SINT*cosf(PHI);
    out->direction.y = SINT*sinf(PHI);
    out->direction.z = COST;
    const float FALLOFF = falloff(out->direction.z, cos_cone_width,
                                  cos_falloff_start);
    out->direction = light2world*out->direction;
    out->direction.normalize();
    *pdf = INV_TWOPI*(1.f/(1.f-cos_cone_width));
    return c*FALLOFF;
}

Spectrum LightSpot::sample_visible_surface(float, float, const Point3* position,
                                           Vec3* wi, float* pdf,
                                           float* distance) const
{
    *wi = light_position-*position;
    const float DISTANCE2 =
            (light_position.x-position->x)*(light_position.x-position->x)+
            (light_position.y-position->y)*(light_position.y-position->y)+
            (light_position.z-position->z)*(light_position.z-position->z);
    *distance = sqrtf(DISTANCE2);
    wi->normalize();
    Vec3 wiL = world2light**wi;
    *pdf = 1.f;
    return c*falloff(wiL.z, cos_cone_width, cos_falloff_start)/DISTANCE2;
}

float LightSpot::pdf(const Ray*) const
{
    return INV_TWOPI*(1.f/(1.f-cos_cone_width));
}

float LightSpot::pdf(const Point3*, const Vec3*) const
{
    return 0.0f;
}

bool LightSpot::renderable() const
{
    return false;
}
