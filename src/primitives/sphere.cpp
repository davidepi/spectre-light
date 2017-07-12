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
        Vec3 normal(h->h.x,h->h.y,h->h.z);
        h->n = Normal(normal);
        if(h->h.x==0 && h->h.y==0) //particular case
            h->right = Vec3(0,1,0);
        else
            h->right = Vec3(-TWO_PI*h->h.y,TWO_PI*h->h.x,0);
        return true;
    }
    else
        return false;
}

float Sphere::surface()const
{
    return FOUR_PI*Sphere::radius*Sphere::radius;
}

void Sphere::getRandomPoint(float r0, float r1, Point3* p, Normal* n)const
{
    if(p->x*p->x+p->y*p->y+p->z*p->z - radius*radius < 0.000005f)
    {
        //point inside sphere, sample uniformly
        float z = 1.f - 2.f * r0; //height of the sample, supposing radius 1
        float r = sqrtf(max(0.f,1.f-z*z));
        float phi = TWO_PI*r1; //partial sphere to consider
        float x = r*cosf(phi);
        float y = r*sinf(phi);
        p->x = x;
        p->y = y;
        p->z = z;
        n->x = -x; //negative because the point is inside, so the normal points
        n->y = -y; //inside
        n->z = -z;
    }
    else
    {
       //point outside sphere, sample only visible hemisphere
//       Vec3 pc(-p->x,-p->y,-p->z); //direction from point to sphere centre
        //TODO: for now I'm just sampling uniformly on the whole sphere
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
}
