//Created,  22 Mar 2016
//Last Edit  3 May 2017

#ifndef __SPHERE_HPP__
#define __SPHERE_HPP__
#include "shape.hpp"

class Sphere : Shape
{
public:
    Sphere(float radius);
    Sphere(float radius, Matrix4* transformation);
    
    bool intersect(const Ray* r,float* distance,float* error)const;
    void recomputeAABB();
    AABB computeAABB()const;
    void obj2world();
    void world2obj();
    
private:
    Point3 centre;
    float radius;
};

#endif
