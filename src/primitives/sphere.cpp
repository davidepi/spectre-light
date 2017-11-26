#include "sphere.hpp"
Sphere::Sphere(float rad) :Shape()
{
#ifdef _LOW_LEVEL_CHECKS_
    Console.severe(rad <= 0,MESSAGE_DEGENERATE_SPHERE);
#endif
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
        Console.severe(MESSAGE_WORLD_AABB_NULL_MATRIX);
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
#ifdef _LOW_LEVEL_CHECKS_
    Console.severe(*distance<SELF_INTERSECT_ERROR,"Intersection distance < 0");
#endif
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
        if(*distance < sol1)//better intersection already found
            return false;
        if(sol1<SELF_INTERSECT_ERROR) //intersection BEHIND origin
        {
            //sol2 behind origin or distance
            if (sol2<SELF_INTERSECT_ERROR || *distance < sol2)
                return false;               //already between sol1 and sol2
            else
                *distance = sol2;
        }
        else
            *distance = sol1;
        if(h!=NULL)
        {
            h->h = r->apply(*distance);
            Vec3 normal(h->h.x, h->h.y, h->h.z);
            h->n = Normal(normal);
            if (h->h.x == 0 && h->h.y == 0)    //otherwise h->right would be a 0
                h->h.x = SELF_INTERSECT_ERROR; //-length vector
            h->right = Vec3(-TWO_PI * h->h.y, TWO_PI * h->h.x, 0);
        }
        return true;
    }
    else
        return false;
}

float Sphere::surface()const
{
    return FOUR_PI*Sphere::radius*Sphere::radius;
}

float Sphere::surface(const Matrix4* transform)const
{
    Vec3 scale = transform->extractScale();
    const float val = (scale.x+scale.y+scale.z)/3.f;
    const float radius = Sphere::radius*val;
    return FOUR_PI*radius*radius;
}

void Sphere::getRandomPoint(float r0, float r1, Point3* p, Normal* n)const
{
    float z = 1.f - 2.f * r0;
    float r = sqrtf(max(0.f,1.f-z*z));
    float phi = TWO_PI*r1;
    float x = r*cosf(phi);
    float y = r*sinf(phi);
    p->x = x;
    p->y = y;
    p->z = z;
    n->x = x;
    n->y = y;
    n->z = z;
}
