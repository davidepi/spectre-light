#ifndef __MESH_HPP__
#define __MESH_HPP__

#include "primitives/shape.hpp"
#include "primitives/triangle.hpp"
#include "geometry/matrix4.hpp"
#include "geometry/point3.hpp"
#include "geometry/vec3.hpp"
#include "geometry/AABB.hpp"
#include "utility/console.hpp"

class Mesh : public Shape
{
public:
    Mesh(unsigned int size);
    ~Mesh();
    void addTriangle(const Vertex* a, const Vertex* b, const Vertex* c);
    void addTriangle(const Point3* a, const Point3* b, const Point3* c,
                     const Normal* n);
    void finalize();
    bool intersect(const Ray* r,float* distance, HitPoint* h)const;
    AABB computeAABB()const;
    AABB computeWorldAABB(const Matrix4* trans)const;
    float surface()const;
    void getRandomPoint(float r, float r1, Point3* p, Normal* n)const;

//private:
    Triangle* tris;
    AABB aabb;
    unsigned int count;
    unsigned int alloc;
    float area;
};

#endif