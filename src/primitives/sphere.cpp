#include "sphere.hpp"
Sphere::Sphere(float rad) :Shape()
{
    Sphere::radius = rad;
}

AABB Sphere::computeAABB()const
{
    const Point3 pmin(-Sphere::radius,-Sphere::radius,-Sphere::radius);
    const Point3 pmax( Sphere::radius, Sphere::radius, Sphere::radius);
    
    //who cares if pmin and pmax are stack-allocated, the AABB constructor is
    //going to copy them anyway
    return AABB(&pmin, &pmax);
}

AABB Sphere::computeWorldAABB(const Matrix4* transform)const
{
#ifdef _LOW_LEVEL_CHECKS_
    if(transform==NULL)
    {
        Console.severe(
        "Trying to generate a world-space AABB with a NULL matrix");
        return AABB();
    }
#endif
    const Point3 pmin = *transform * Point3(-Sphere::radius,
                                                  -Sphere::radius,
                                                  -Sphere::radius);
    const Point3 pmax = *transform * Point3(Sphere::radius,
                                                  Sphere::radius,
                                                  Sphere::radius);
    
    return AABB(&pmin, &pmax);
}

bool Sphere::intersect(const Ray* r,float* distance, HitPoint* h)const
{
    const Vec3 tmp(r->origin.x,r->origin.y,r->origin.z);
    float a = r->direction.dot(r->direction);
    float b = 2*(r->direction.dot(tmp));
    float c = tmp.dot(tmp) - (Sphere::radius*Sphere::radius);
    float sol1;
    float sol2;
    if(equation2(a,b,c,&sol1,&sol2))
    {
        if(sol2<sol1)
            swap(&sol1,&sol2);
        
        if(sol1>r->maxext || sol2<r->minext)
            return false;
        *distance = sol1;
        if(sol1<r->minext) //intersection BEHIND origin
        {
            *distance = sol2;
            if(*distance>r->maxext) //both intersections behind origin
                return false;
        }
        h->h = r->apply(*distance);
        Vec3 normal(h->h.z,h->h.y,h->h.z);
        normal.normalize();
        h->n = Normal(normal);
        h->sp = this;
        return true;
    }
    else
        return false;
}

float Sphere::surface()const
{
    return 4.0f*(float)M_PI*Sphere::radius*Sphere::radius;
}
