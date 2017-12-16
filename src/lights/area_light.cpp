//author: Davide Pizzolotto
//license: GNU GPLv3

#include "area_light.hpp"

AreaLight::AreaLight(const Shape* sp, const Matrix4& objToWorld, const Spectrum& c)
: Asset(sp,objToWorld), c(c)
{
    //calculate the surface of the world-space object
    AreaLight::area = sp->surface(&objToWorld);
    
    //get the cumulative densities of the various faces of the light
    cd = (float*)malloc(sizeof(float)*sp->get_faces_number());
    sp->get_densities_array(&objToWorld, cd);
    
    AreaLight::invarea = 1.f/area;
}

AreaLight::~AreaLight()
{
    delete cd;
}

Spectrum AreaLight::emissiveSpectrum()const
{
    return AreaLight::c;
}

Spectrum AreaLight::radiance_e(float r0, float r1, Ray* out, float* pdf)const
{
    Normal n;

    //generate random origin point of the emitted radiance in the surface of the
    //underlying model of the light
    AreaLight::model->sample_point(r0,r1,cd,&(out->origin),&n);

    //generate random direction
    float z = 1.f - 2.f * r0;
    float r = sqrtf(max(0.f,1.f-z*z));
    float phi = TWO_PI*r1;
    float x = r*cosf(phi);
    float y = r*sinf(phi);
    out->direction = Vec3(x,y,z);

    //objspace to world space
    *out = AreaLight::objToWorld**out;

    //if the dir is pointing on the opposite direction of the normal, flip it
    //because there is no emission in that direction
    if(out->direction.dot(n) < 0.f)
        out->direction *= -1.f;

    *pdf = AreaLight::invarea * INV_TWOPI;
    return AreaLight::c;
}

Spectrum AreaLight::radiance_i(float r0, float r1, const Point3 *current_pos,
                            Vec3 *wi, float *pdf, float* distance) const
{
    Normal normal;
    Point3 light_point;
    Ray ray;
    ray.origin = worldToObj**current_pos;

    //generate random origin point of the emitted radiance in the surface of the
    //underlying model of the light
    AreaLight::model->sample_point(r0,r1,cd,&light_point,&normal);

    //in the next steps a ray originating from the current_pos and pointing to
    //the sampled point is tested against the light. This because if the sampled
    //point is on the backface, a point facing the current_pos is selected
    ray.direction = light_point-ray.origin;
    ray.direction.normalize();
    HitPoint hit;
    *distance = FLT_MAX;
    //will always succeed
    bool res=AreaLight::model->intersect(&ray,distance,&hit);
    //TODO: erase this after all the intersections are tried
    //just to be sure
    if(!res)
    {
        *pdf = 0;
        return SPECTRUM_BLACK;
    }
    light_point = ray.apply(*distance);
    normal = hit.normal_h;
    *wi = ray.direction;
    *pdf = (ray.origin.x-light_point.x)*(ray.origin.x-light_point.x)+
           (ray.origin.y-light_point.y)*(ray.origin.y-light_point.y)+
           (ray.origin.z-light_point.z)*(ray.origin.z-light_point.z);
    *pdf/=(absdot(normal,-(*wi))*AreaLight::area);
    if(std::isinf(*pdf))
    {
        *pdf = 0;
        return SPECTRUM_BLACK;
    }

    //convert wi to world space
    Spectrum retval;
    if(dot(normal,-(*wi))>0)
        retval = AreaLight::c;
    else
        retval = SPECTRUM_BLACK;

    *wi = AreaLight::objToWorld**wi;
    wi->normalize();
    return retval;
}

float AreaLight::pdf(const Point3* p, const Vec3* wi)const
{
    Ray ray;
    ray.origin = AreaLight::worldToObj * *p;
    ray.direction = AreaLight::worldToObj * *wi;
    HitPoint hit;
    float distance = FLT_MAX;
    //will always succeed
    bool res=AreaLight::model->intersect(&ray,&distance,&hit);
    if(!res)
        return 0;
    Point3 light_point = ray.apply(distance);
    float pdf = (ray.origin.x-light_point.x)*(ray.origin.x-light_point.x)+
                (ray.origin.y-light_point.y)*(ray.origin.y-light_point.y)+
                (ray.origin.z-light_point.z)*(ray.origin.z-light_point.z);
    pdf/=(absdot(hit.normal_h,-(ray.direction))*AreaLight::area);
    return pdf;
}

float AreaLight::pdf() const
{
    return AreaLight::invarea;
}

bool AreaLight::is_light()const
{
    return true;
}
