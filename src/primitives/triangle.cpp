//author: Davide Pizzolotto
//license: GNU GPLv3

#include "triangle.hpp"

Triangle::Triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
        :a(v0), b(v1), c(v2)
{

}

AABB Triangle::compute_AABB() const
{
    Point3 pmin(min(min(a.p, b.p), c.p));
    Point3 pmax(max(max(a.p, b.p), c.p));

    //who cares if pmin and pmax are stack-allocated, the AABB constructor is
    //going to copy them anyway
    return AABB(&pmin, &pmax);
}

AABB Triangle::compute_AABB(const Matrix4* transform) const
{
#ifdef DEBUG
    if(transform == NULL)
    {
        Console.severe(MESSAGE_WORLD_AABB_NULL_MATRIX);
        return AABB();
    }
#endif
    const Point3 p0 = *transform*a.p;
    const Point3 p1 = *transform*b.p;
    const Point3 p2 = *transform*c.p;

    Point3 pmin(min(min(p0, p1), p2));
    Point3 pmax(max(max(p0, p1), p2));

    return AABB(pmin, pmax);
}

float Triangle::surface() const
{
    return 0.5f*cross(b.p-a.p, c.p-a.p).length();
}

float Triangle::surface(const Matrix4* transform) const
{
    const Vec3 scale = transform->get_scale();
    const Point3 point_a(a.p.x*scale.x, a.p.y*scale.y, a.p.z*scale.z);
    const Point3 point_b(b.p.x*scale.x, b.p.y*scale.y, b.p.z*scale.z);
    const Point3 point_c(c.p.x*scale.x, c.p.y*scale.y, c.p.z*scale.z);
    return 0.5f*cross(point_b-point_a, point_c-point_a).length();
}

bool Triangle::intersect(const Ray* r, float* distance, HitPoint* h,
                         const MaskBoolean* mask) const
{
    //recap since this method has become pretty cryptic
    // a,b,c = triangle vertices
    // p,t,n = point, texture coordinate and normal for the vertex
    //u,v = intersection point uv values
    //h->uv = intersection point uv values, accounting for the original
    // user-defined values
    const Vec3 ba = b.p-a.p;
    const Vec3 ca = c.p-a.p;
    const Vec3 pv = r->direction.cross(ca);
    float det = pv.dot(ba);
    if(det == 0) //ray parallel to the triangle
        return false;

    float invdet = 1.f/det;
    const Vec3 tv = r->origin-a.p;
    float u = pv.dot(tv)*invdet;
    if(u<0.f || u>1.f) //origin position and dir inclination
        return false; //constraints are u,v>=0 & u+v<=1 so if u>1 I can exit now

    const Vec3 qv = tv.cross(ba);
    float v = r->direction.dot(qv)*invdet;
    if(v<0.f || u+v>1.f) //I could hit with this origin, but the direction
        return false;    //betrays me

    float dist = ca.dot(qv)*invdet;
    if(dist<SELF_INTERSECT_ERROR || dist>*distance)
        return false;

    //hit now dependes only on masking
    //determines UV values
    const float w = 1.f-u-v;
    const float delta[2][2] = {{a.t[0]-c.t[0], b.t[0]-c.t[0]},
                               {a.t[1]-c.t[1], b.t[1]-c.t[1]}};
    const float uvdet = delta[0][0]*delta[1][1]-delta[0][1]*delta[1][0];
    //TODO: handle degenerate UVs (uvdet == 0)
    const float invuvdet = 1.f/uvdet;
    const Vec3 ac = a.p-c.p;
    const Vec3 bc = b.p-c.p;
    //tmp is necessary because I cannot overwrite original "h" if there's not
    //intersection. (here intersection could be invalidated by mask)
    HitPoint tmp;
    tmp.dpdu = (ac*delta[1][1]-bc*delta[1][0])*invuvdet;
    tmp.dpdv = (bc*delta[0][0]-ac*delta[0][1])*invuvdet;
    tmp.uv.x = w*a.t.x+u*b.t.x+v*c.t.x;
    tmp.uv.y = w*a.t.y+u*b.t.y+v*c.t.y;
    tmp.du = h->du;
    tmp.dv = h->du;
    tmp.differentials = h->differentials;
    if(!mask->is_masked(&tmp))
    {
        //not masked -> copy uv and dpdu, dpdv
        h->dpdu = tmp.dpdu;
        h->dpdv = tmp.dpdv;
        h->uv = tmp.uv;
    }
    else
        return false;

    // from here it is a guaranteed hit
    *distance = dist;
    h->point_h = r->apply(dist);
    //compute normal in the point, given normals in the vertices
    h->normal_g = a.n*w+b.n*u+c.n*v;
    h->cross = cross(Vec3(h->normal_g), h->dpdu);
    return true;
}

void Triangle::sample_point(float r0, float r1, const float*, Point3* p,
                            Normal* n) const
{
    r0 = max(0.f, r0); //to avoid NaNs due to flt precision
    float sq = sqrtf(r0);
    float u = 1.f-sq;
    float v = r1*sq;
    float w = 1.f-u-v;

    p->x = u*a.p.x+v*b.p.x+w*c.p.x;
    p->y = u*a.p.y+v*b.p.y+w*c.p.y;
    p->z = u*a.p.z+v*b.p.z+w*c.p.z;

    *n = Normal(cross(b.p-a.p, c.p-a.p));
    n->normalize();
}
