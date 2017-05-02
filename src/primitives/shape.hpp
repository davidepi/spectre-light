//Created,  25 Feb 2016
//Last Edit  2 May 2017

#ifndef __SHAPE_HPP_
#define __SHAPE_HPP_
#include "ray.hpp"
#include "matrix4.hpp"

class Shape;
class Shape
{
public:
    
    Shape();
    ~Shape();
    
    Matrix4* transformMatrix;
    
    unsigned int getID()const;
    virtual bool intersect(const Ray* r,float* distance,float* epsilon)const=0;
    virtual void computeAABB()const = 0;
    
private:
    const unsigned int id;
    AABB aabb;
};

#endif
