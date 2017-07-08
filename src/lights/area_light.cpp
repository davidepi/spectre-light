#include "area_light.hpp"

AreaLight::AreaLight(Shape* sp, Matrix4* objToWorld, Color c)
: Asset(sp,objToWorld), c(c)
{
    AreaLight::area = sp->surface();
}

Color AreaLight::emissivePower()const
{
    return AreaLight::c * 2.f * M_PI;
}
