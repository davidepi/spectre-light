#include "sphere.hpp"
Sphere::Sphere(float rad) :Shape()
{
    Sphere::radius = rad;
}

Sphere::Sphere(float rad, Matrix4* m) :Shape()
{
    Sphere::radius = rad;
    Shape::transformMatrix = m;
}

AABB Sphere::computeAABB()const
{
    const Point3 pmin(-Sphere::radius,-Sphere::radius,-Sphere::radius);
    const Point3 pmax( Sphere::radius, Sphere::radius, Sphere::radius);
    
    //who cares if pmin and pmax are stack-allocated, the AABB constructor is
    //going to copy them anyway
    return AABB(&pmin, &pmax);
}

AABB Sphere::computeWorldAABB()const
{
#ifdef _LOW_LEVEL_CHECKS_
    if(transformMatrix==NULL)
    {
        Console.severe(
        "Trying to generate a world-space AABB with a NULL matrix");
        return AABB();
    }
#endif
    const Point3 pmin = *transformMatrix * Point3(-Sphere::radius,
                                                  -Sphere::radius,
                                                  -Sphere::radius);
    const Point3 pmax = *transformMatrix * Point3(Sphere::radius,
                                                  Sphere::radius,
                                                  Sphere::radius);
    
    return AABB(&pmin, &pmax);
}

void Sphere::obj2world()
{
#ifdef _LOW_LEVEL_CHECKS_
    if(transformMatrix==NULL)
    {
        Console.severe(
        "Trying to convert a sphere to world-space with a NULL matrix");
        return;
    }
#endif
    Sphere::centre = Point3(Sphere::transformMatrix->m03,
                            Sphere::transformMatrix->m13,
                            Sphere::transformMatrix->m23);
    Sphere::radius *= Vec3(Sphere::transformMatrix->m00,
                           Sphere::transformMatrix->m10,
                           Sphere::transformMatrix->m20).length();
}

void Sphere::world2obj()
{
#ifdef _LOW_LEVEL_CHECKS_
    if(transformMatrix==NULL)
    {
        Console.severe(
        "Trying to convert a sphere to object-space with a NULL matrix");
        return;
    }
#endif
    Sphere::centre = Point3();
    Sphere::radius /= Vec3(Sphere::transformMatrix->m00,
                           Sphere::transformMatrix->m10,
                           Sphere::transformMatrix->m20).length();
}

bool Sphere::intersect(const Ray *r, float *distance, float *error)const
{
    const Vec3 tmp = r->origin - Sphere::centre;
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
        *error = 5e-4f**distance; //this line of code is stealed from pbrt :^)
        return true;
    }
    else
        return false;
}

float Sphere::surface()const
{
    return 4.0f*(float)M_PI*Sphere::radius*Sphere::radius;
}
