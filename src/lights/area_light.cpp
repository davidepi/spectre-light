#include "area_light.hpp"

AreaLight::AreaLight(Shape* sp, Color c) : Asset(sp), c(c)
{
    AreaLight::area = sp->surface();
}

Color AreaLight::emissivePower()const
{
    return AreaLight::c * 2.f * M_PI;
}
