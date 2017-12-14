//author: Davide Pizzolotto
//license: GNU GPLv3

#include "sphere.hpp"

AABB Sphere::compute_AABB()const
{
    const Point3 pmin(-1.f,-1.f,-1.f);
    const Point3 pmax(1.f, 1.f, 1.f);
    
    //who cares if pmin and pmax are stack-allocated, the AABB constructor is
    //going to copy them anyway
    return AABB(&pmin, &pmax);
}

AABB Sphere::compute_AABB(const Matrix4* transform)const
{
#ifdef DEBUG
    if(transform==NULL)
    {
        Console.severe(MESSAGE_WORLD_AABB_NULL_MATRIX);
        return AABB();
    }
#endif
    //rotation will broke if I don't transform every corner point of the AABB
    //as an example, rotate a 2D box by 90 deg and keep only the diagonal
    //vertices, then redraw the AABB given those vertices. Completely broken
    const Point3 p0=*transform*Point3(-1,-1,-1);
    const Point3 p1=*transform*Point3(1,-1,-1);
    const Point3 p2=*transform*Point3(1,1,-1);
    const Point3 p3=*transform*Point3(-1,1,-1);
    const Point3 p4=*transform*Point3(-1,-1,1);
    const Point3 p5=*transform*Point3(1,-1,1);
    const Point3 p6=*transform*Point3(1,1,1);
    const Point3 p7=*transform*Point3(-1,1,1);
    
    const Point3 pmi=min(min(min(min(min(min(min(p0,p1),p2),p3),p4),p5),p6),p7);
    const Point3 pma=max(max(max(max(max(max(max(p0,p1),p2),p3),p4),p5),p6),p7);
    
    return AABB(&pmi,&pma);
}

bool Sphere::intersect(const Ray* r,float* distance, HitPoint* hit)const
{
#ifdef DEBUG
    Console.severe(*distance<SELF_INTERSECT_ERROR,"Intersection distance < 0");
#endif
    const Vec3 tmp(r->origin.x,r->origin.y,r->origin.z);
    float a = r->direction.dot(r->direction);
    float b = 2*(r->direction.dot(tmp));
    float c = tmp.dot(tmp) - 1.f;
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
        hit->point_h = r->apply(*distance);
        Vec3 normal(hit->point_h.x, hit->point_h.y, hit->point_h.z);
        hit->normal_h = Normal(normal);
        if(hit->point_h.x == 0 && hit->point_h.y == 0)//otherwise h->right
        {                                             //would be a 0
            hit->point_h.x = SELF_INTERSECT_ERROR; //-length vector
        }
        hit->right = Vec3(-TWO_PI * hit->point_h.y,TWO_PI * hit->point_h.x,0);
        return true;
    }
    else
        return false;
}

float Sphere::surface()const
{
    return FOUR_PI;
}

float Sphere::surface(const Matrix4* transform)const
{
    Vec3 scale = transform->get_scale();
    const float val = scale.x;
    return FOUR_PI*val*val;
}

void Sphere::sample_point(float r0, float r1, const float*, Point3* p,
                            Normal* n)const
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
