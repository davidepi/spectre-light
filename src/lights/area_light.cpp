#include "area_light.hpp"

AreaLight::AreaLight(Shape* sp, Matrix4* objToWorld, Color c)
: Asset(sp,objToWorld), c(c)
{
    AreaLight::area = sp->surface();
}

Color AreaLight::emissivePower()const
{
    return AreaLight::c * TWO_PI;
}

Color AreaLight::radiance(float r0, float r1, float r2, float r3,
                          const Point3* pos, Ray* out,float* pdf)const
{
    Normal n;
    out->origin = *pos;

    //generate random origin point of the emitted radiance in the surface of the
    //underlying model of the light
    AreaLight::model->getRandomPoint(r0,r1,&(out->origin),&n);

    //generate random direction
    float z = 1.f - 2.f * r0;
    float r = sqrtf(max(0.f,1.f-z*z));
    float phi = TWO_PI*r1;
    float x = r*cosf(phi);
    float y = r*sinf(phi);
    out->direction = Vec3(x,y,z);

    //if the dir is pointing on the opposite direction of the normal, flip it
    //because there is no emission in that direction
    if(out->direction.dot(n) < 0.f)
        out->direction *= -1.f;

    *pdf = 1.f/AreaLight::model->surface();
    return c;
}
