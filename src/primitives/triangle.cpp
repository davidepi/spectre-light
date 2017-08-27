#include "triangle.hpp"

Triangle::Triangle()
{

}

Triangle::Triangle(Vertex v0, Vertex v1, Vertex v2) : a(v0), b(v1), c(v2)
{

}

AABB Triangle::computeAABB()const
{
    Point3 pmin(min(min(a.p.x,b.p.x),c.p.x),
                min(min(a.p.y,b.p.y),c.p.y),
                min(min(a.p.z,b.p.z),c.p.z));

    Point3 pmax(max(max(a.p.x,b.p.x),c.p.x),
                max(max(a.p.y,b.p.y),c.p.y),
                max(max(a.p.z,b.p.z),c.p.z));

    //who cares if pmin and pmax are stack-allocated, the AABB constructor is
    //going to copy them anyway
    return AABB(&pmin, &pmax);
}

AABB Triangle::computeWorldAABB(const Matrix4* transform)const
{
#ifdef _LOW_LEVEL_CHECKS_
    if(transform==NULL)
    {
        Console.severe(MESSAGE_WORLD_AABB_NULL_MATRIX);
        return AABB();
    }
#endif
    Point3 pmin(min(min(a.p.x,b.p.x),c.p.x),
                min(min(a.p.y,b.p.y),c.p.y),
                min(min(a.p.z,b.p.z),c.p.z));

    Point3 pmax(max(max(a.p.x,b.p.x),c.p.x),
                max(max(a.p.y,b.p.y),c.p.y),
                max(max(a.p.z,b.p.z),c.p.z));

    pmin = *transform*pmin;
    pmax = *transform*pmax;

    return AABB(&pmin, &pmax);
}

float Triangle::surface()const
{
    return 0.5f*cross(b.p-a.p,c.p-a.p).length();
}

void Triangle::getRandomPoint(float r0, float r1, Point3* p, Normal* n)const
{
    float sq = sqrtf(r0);
    float u = 1.f-sq;
    float v = r1*sq;
    float w = 1.f-u-v;

    p->x = u*a.p.x+v*b.p.x+w*c.p.x;
    p->y = u*a.p.y+v*b.p.y+w*c.p.y;
    p->z = u*a.p.z+v*b.p.z+w*c.p.z;

    *n = Normal(cross(b.p-a.p,c.p-a.p));
    n->normalize();
}

bool Triangle::intersect(const Ray *r, float *distance, HitPoint *h)const
{

    Vec3 ba = b.p-a.p;
    Vec3 ca = c.p-a.p;
    Vec3 pv = r->direction.cross(ca);
    float det = pv.dot(ba);
    if(det==0) //ray parallel to the triangle
        return false;

    float invdet = 1.f/det;
    Vec3 tv = r->origin - a.p;
    float u = pv.dot(tv) * invdet;
    if(u<0.f || u>1.f)//constraints are u,v>=0 & u+v<=1 so if u>1 I can exit now
        return false;

    Vec3 qv = tv.cross(ba);
    float v = r->direction.dot(qv) * invdet;
    if(v<0.f || u+v>1.f)
        return false;

    float dist = ca.dot(qv)*invdet;
    if(dist<SELF_INTERSECT_ERROR || dist > *distance)
        return false;

    *distance = dist;
    float w = 1.f-u-v;
    h->h=r->apply(dist); //compute hit point

    //compute normal in the point, given normals in the vertices
    h->n = a.n*w+b.n*u+c.n*v;//TODO: change this after uv mapping implementation

    //compute default shading vector TODO: change also this after uv map impl
    h->right.x = b.p.x-a.p.x;
    h->right.y = b.p.y-a.p.y;
    h->right.z = b.p.z-a.p.z;

    h->cross = cross(Vec3(h->n),h->right);
    h->right = cross(Vec3(h->n),h->cross); //adjust right vector
    return true;
}
