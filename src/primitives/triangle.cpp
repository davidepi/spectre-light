//author: Davide Pizzolotto
//license: GNU GPLv3

#include "triangle.hpp"

Triangle::Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
        :a(v0), b(v1), c(v2)
{
    
}

AABB Triangle::compute_AABB()const
{
    Point3 pmin(min(min(a.p,b.p),c.p));
    Point3 pmax(max(max(a.p,b.p),c.p));

    //who cares if pmin and pmax are stack-allocated, the AABB constructor is
    //going to copy them anyway
    return AABB(&pmin, &pmax);
}

AABB Triangle::compute_AABB(const Matrix4* transform)const
{
#ifdef DEBUG
    if(transform==NULL)
    {
        Console.severe(MESSAGE_WORLD_AABB_NULL_MATRIX);
        return AABB();
    }
#endif
    const Point3 p0 = *transform*a.p;
    const Point3 p1 = *transform*b.p;
    const Point3 p2 = *transform*c.p;

    Point3 pmin(min(min(p0,p1),p2));
    Point3 pmax(max(max(p0,p1),p2));

    return AABB(pmin, pmax);
}

float Triangle::surface()const
{
    return 0.5f*cross(b.p-a.p,c.p-a.p).length();
}

float Triangle::surface(const Matrix4* transform)const
{
    const Vec3 scale = transform->get_scale();
    const Point3 point_a(a.p.x*scale.x,a.p.y*scale.y,a.p.z*scale.z);
    const Point3 point_b(b.p.x*scale.x,b.p.y*scale.y,b.p.z*scale.z);
    const Point3 point_c(c.p.x*scale.x,c.p.y*scale.y,c.p.z*scale.z);
    return 0.5f*cross(point_b-point_a,point_c-point_a).length();
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
    if(u<0.f || u>1.f) //origin position and dir inclination
        return false; //constraints are u,v>=0 & u+v<=1 so if u>1 I can exit now

    Vec3 qv = tv.cross(ba);
    float v = r->direction.dot(qv) * invdet;
    if(v<0.f || u+v>1.f) //I could hit with this origin, but the direction
        return false;    //betrays me

    float dist = ca.dot(qv)*invdet;
    if(dist<SELF_INTERSECT_ERROR || dist > *distance)
        return false;

    *distance = dist;
    float w = 1.f-u-v;
    h->point_h=r->apply(dist); //compute hit point

    //compute normal in the point, given normals in the vertices
    //TODO: change this after uv mapping implementation
    h->normal_h = a.n*w+b.n*u+c.n*v;

    //compute default shading vector
    //TODO: change also this after uv map impl
    h->right.x = b.p.x-a.p.x;
    h->right.y = b.p.y-a.p.y;
    h->right.z = b.p.z-a.p.z;

    h->cross = cross(Vec3(h->normal_h),h->right);
    h->right = cross(Vec3(h->normal_h),h->cross); //adjust right vector
    return true;
}

void Triangle::sample_point(float r0, float r1, const float*, Point3* p,
                            Normal* n)const
{
    r0 = max(0.f,r0); //to avoid NaNs due to flt precision
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
