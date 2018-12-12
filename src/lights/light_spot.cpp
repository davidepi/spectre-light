//author: Davide Pizzolotto
//license: GNU GPLv3

#include "light_spot.hpp"

static inline float falloff(float cost, float cosinner, float costotal)
{
    float retval;
    if(cost<costotal)
        retval = 0.f;
    else if(cost>cosinner)
        retval = 1.f;
    else
    {
        retval = (cost-costotal)/(cosinner-costotal);
        retval *= retval*retval*retval;
    }
    return retval;
}

LightSpot::LightSpot(const Spectrum& intensity, const Matrix4& transform,
                     float radius_inner, float radius_outer)
        :Light(intensity), light2world(transform)
{
    light_position = transform*Point3(0.f);
    transform.inverse(&world2light);
    if(radius_inner == radius_outer) //same radius could generate inf values
        radius_outer += 1e-5f;
    else if(radius_outer<radius_inner)
        swap(&radius_outer, &radius_inner);
    //if radius is the tan, then the found cos is only half of the required one
    const float TAN2H_OUTER = radius_outer*radius_outer;
    const float TAN2H_INNER = radius_inner*radius_inner;
    const float COS2H_OUTER = 1.f/(1.f+TAN2H_OUTER);
    const float COS2H_INNER = 1.f/(1.f+TAN2H_INNER);
    cos_outer = 2*COS2H_OUTER-1.f;
    cos_inner = 2*COS2H_INNER-1.f;
}

Spectrum LightSpot::sample_surface(float r0, float r1, float, float, Ray* out,
                                   float* pdf) const
{
    out->origin = light_position;
    const float COST = (1.f-r0)+r0*cos_outer;
    const float SINT = sqrtf(max(0.f, 1-COST*COST));
    const float PHI = r1*2.f*ONE_PI;
    out->direction.x = SINT*cosf(PHI);
    out->direction.y = SINT*sinf(PHI);
    out->direction.z = COST;
    const float FALLOFF = falloff(out->direction.z,
                                  cos_inner, cos_outer);
    out->direction = light2world*out->direction;
    out->direction.normalize();
    *pdf = INV_TWOPI*(1.f/(1.f-cos_outer));
    return c*FALLOFF;
}

Spectrum LightSpot::sample_visible_surface(float, float,
                                           const Point3* positionW, Vec3* wiW,
                                           float* pdf, float* distance) const
{
    *wiW = light_position-*positionW;
    const float DISTANCE2 =
            (light_position.x-positionW->x)*(light_position.x-positionW->x)+
            (light_position.y-positionW->y)*(light_position.y-positionW->y)+
            (light_position.z-positionW->z)*(light_position.z-positionW->z);
    *distance = sqrtf(DISTANCE2);
    wiW->normalize();
    Vec3 wiL = world2light**wiW;
    *pdf = 1.f;
    const float FALLOFF = falloff(wiL.z, cos_inner, cos_outer);
    return c*FALLOFF/DISTANCE2;
}

float LightSpot::pdf(const Ray*) const
{
    return INV_TWOPI*(1.f/(1.f-cos_outer));
}

float LightSpot::pdf(const Point3*, const Vec3*) const
{
    return 0.0f;
}

bool LightSpot::renderable() const
{
    return false;
}
