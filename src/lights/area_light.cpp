#include "area_light.hpp"

AreaLight::AreaLight(Shape* sp, Matrix4* objToWorld, Color c)
: Asset(sp,objToWorld), c(c)
{
    AreaLight::area = sp->surface();
    AreaLight::invarea = 1.f/area;
}

Color AreaLight::emissivePower()const
{
    return AreaLight::c * TWO_PI;
}

Color AreaLight::emissiveSpectrum()const
{
    return AreaLight::c;
}

Color AreaLight::radiance_e(float r0, float r1, Ray* out, float* pdf)const
{
    Normal n;

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

    //objspace to world space
    *out = *AreaLight::objToWorld**out;

    //if the dir is pointing on the opposite direction of the normal, flip it
    //because there is no emission in that direction
    if(out->direction.dot(n) < 0.f)
        out->direction *= -1.f;

    *pdf = AreaLight::invarea * INV_TWOPI;
    return AreaLight::c;
}

Color AreaLight::radiance_i(float r0, float r1, const Point3 *current_pos,
                            Vec3 *wi, float *pdf) const
{
    Normal n;
    Point3 p;
    Ray r;
    r.origin = worldToObj**current_pos;

    //generate random origin point of the emitted radiance in the surface of the
    //underlying model of the light
    AreaLight::model->getRandomPoint(r0,r1,&p,&n);

    //in the next steps a ray originating from the current_pos and pointing to
    //the sampled point is tested against the light. This because if the sampled
    //point is on the backface, a point facing the current_pos is selected
    r.direction = p-r.origin;
    r.direction.normalize();
    HitPoint hp;
    float distance = FLT_MAX;
    bool res=AreaLight::model->intersect(&r,&distance,&hp);//will always succeed
#ifdef _LOW_LEVEL_CHECKS_
    //TODO: erase this after all the intersections are tried
    //just to be sure
    if(!res)
    {
        AreaLight::model->intersect(&r,&distance,&hp); //the error happens when
        //the light is tangent to the sphere
        return Color();
    }
#endif
    p = r.apply(distance);
    n = hp.n;
    *wi = r.direction;

    *pdf = (r.origin.x-p.x)*(r.origin.x-p.x)+(r.origin.y-p.y)*(r.origin.y-p.y)+
           (r.origin.z-p.z)*(r.origin.z-p.z);
    *pdf/=(absdot(n,-(*wi))*AreaLight::area);

    //convert wi to world space
    Color retval;
    if(dot(n,-(*wi))>0) //TODO:probably can be removed
        retval = AreaLight::c;

    *wi = *AreaLight::objToWorld**wi;
    wi->normalize();
    return retval;
}

float AreaLight::pdf(const Point3* p, const Vec3* wi)const
{
    Ray r;
    r.origin = AreaLight::worldToObj * *p;
    r.direction = AreaLight::worldToObj * *wi;
    HitPoint hp;
    float distance = FLT_MAX;
    bool res=AreaLight::model->intersect(&r,&distance,&hp);//will always succeed
#ifdef _LOW_LEVEL_CHECKS_
    //TODO: erase this after all the intersections are tried
    //just to be sure
    if(!res)
        return 0;
#endif
    Point3 ps = r.apply(distance);
    float pdf = (r.origin.x-ps.x)*(r.origin.x-ps.x)+(r.origin.y-ps.y)*
                (r.origin.y-ps.y)+(r.origin.z-ps.z)*(r.origin.z-ps.z);
    pdf/=(absdot(hp.n,-(*wi))*AreaLight::area);
    return pdf;
}

float AreaLight::pdf() const
{
    return AreaLight::invarea;
}

bool AreaLight::isLight()const
{
    return true;
}
