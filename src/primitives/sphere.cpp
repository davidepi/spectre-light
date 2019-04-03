//author: Davide Pizzolotto
//license: GNU GPLv3

#include "sphere.hpp"
#include "utility/console.hpp"
#include "utility/utility.hpp"
#include <cmath>

Sphere::Sphere(bool inverted) : inverted(inverted)
{

}

static inline void compute_uvs(const Point3* hit, HitPoint* ret)
{
    float phi = atan2f(hit->y, hit->x);
    if(phi<0)phi += TWO_PI;
    float theta = acosf(clamp(hit->z, -1.f, 1.f));
    constexpr const float thetamin = ONE_PI; //arccos(-1);
    constexpr const float thetamax = 0.f; //arccos(1);
    constexpr const float thetad = (thetamax-thetamin);
    constexpr const float inv_thetad = 1.f/thetad;
    float invzrad = 1.f/sqrtf(hit->x*hit->x+hit->y*hit->y);
    float cosphi = hit->x*invzrad;
    float sinphi = hit->y*invzrad;
    ret->uv = Point2(phi*INV_TWOPI, (theta-thetamin)*inv_thetad);
    ret->dpdu = Vec3(-TWO_PI*hit->y, TWO_PI*hit->x, 0);
    ret->dpdv = Vec3(hit->z*cosphi, hit->z*sinphi, -sinf(theta));
    ret->dpdv *= thetad;
}

AABB Sphere::compute_AABB() const
{
    const Point3 pmin(-1.f, -1.f, -1.f);
    const Point3 pmax(1.f, 1.f, 1.f);

    //who cares if pmin and pmax are stack-allocated, the AABB constructor is
    //going to copy them anyway
    return AABB(&pmin, &pmax);
}

AABB Sphere::compute_AABB(const Matrix4* transform) const
{
#ifdef DEBUG
    if(transform == NULL)
    {
        Console.severe(MESSAGE_WORLD_AABB_NULL_MATRIX);
        return AABB();
    }
#endif
    //rotation will broke if I don't transform every corner point of the AABB
    //as an example, rotate a 2D box by 90 deg and keep only the diagonal
    //vertices, then redraw the AABB given those vertices. Completely broken
    const Point3 p0 = *transform*Point3(-1, -1, -1);
    const Point3 p1 = *transform*Point3(1, -1, -1);
    const Point3 p2 = *transform*Point3(1, 1, -1);
    const Point3 p3 = *transform*Point3(-1, 1, -1);
    const Point3 p4 = *transform*Point3(-1, -1, 1);
    const Point3 p5 = *transform*Point3(1, -1, 1);
    const Point3 p6 = *transform*Point3(1, 1, 1);
    const Point3 p7 = *transform*Point3(-1, 1, 1);

    const Point3 pmi = min(
            min(min(min(min(min(min(p0, p1), p2), p3), p4), p5), p6), p7);
    const Point3 pma = max(
            max(max(max(max(max(max(p0, p1), p2), p3), p4), p5), p6), p7);

    return AABB(&pmi, &pma);
}

bool Sphere::intersect(const Ray* r, float* distance, HitPoint* hit,
                       const MaskBoolean* mask) const
{
#ifdef DEBUG
    if(*distance<SELF_INTERSECT_ERROR)
        Console.severe("Intersection distance < 0");
#endif
    const Vec3 originVec(r->origin.x, r->origin.y, r->origin.z);
    float a = r->direction.dot(r->direction);
    float b = 2*(r->direction.dot(originVec));
    float c = originVec.dot(originVec)-1.f;
    float sol1;
    float sol2;
    if(equation2(a, b, c, &sol1, &sol2))
    {
        if(sol2<sol1)
            swap(&sol1, &sol2);
        if(*distance<sol1)//better intersection already found
            return false;
        if(sol1<SELF_INTERSECT_ERROR) //intersection BEHIND origin
        {
            //sol2 behind origin or distance
            if(sol2<SELF_INTERSECT_ERROR || *distance<sol2)
                return false;               //already between sol1 and sol2
            else
            {
                //only second solution can be considered valid
                //write the valid one in the first and set second as NaN
                //NaN will be used to indicate the mask that this is invalid
                swap(&sol1, &sol2);
                sol2 = NAN;
            }
        }

        //tmp because I cannot overwrite until 100% sure the hit happened
        //here I need to generate uvs, and then test alpha masking
        HitPoint tmp;
        //intersection point BEFORE applying the shift if (x,y) == 0;
        //the shift is applied to avoid a 0-length dpdu
        Point3 hitp = r->apply(sol1);
        tmp.point_h = hitp;
        if(tmp.point_h.x == 0 && tmp.point_h.y == 0)//otherwise h->dpdu would be
            tmp.point_h.x = SELF_INTERSECT_ERROR;   //a 0 length vector
        tmp.du = hit->du;
        tmp.dv = hit->dv;
        tmp.differentials = hit->differentials;
        compute_uvs(&(tmp.point_h), &tmp);
        if(!mask->is_masked(&tmp))
        {
            //first hit is ok!
            *distance = sol1;
            hit->point_h = tmp.point_h;
            hit->uv = tmp.uv;
            hit->dpdu = tmp.dpdu;
            hit->dpdv = tmp.dpdv;
        }
        else if(!std::isnan(sol2))
        {
            //repeat the procedure with second hit, first was invalidated
            hitp = r->apply(sol2);
            tmp.point_h = hitp;
            if(tmp.point_h.x == 0 && tmp.point_h.y == 0)
                tmp.point_h.x = SELF_INTERSECT_ERROR;
            compute_uvs(&(tmp.point_h), &tmp);
            if(!mask->is_masked(&tmp))
            {
                //second hit is ok!
                *distance = sol2;
                hit->point_h = tmp.point_h;
                hit->uv = tmp.uv;
                hit->dpdu = tmp.dpdu;
                hit->dpdv = tmp.dpdv;
            }
            else //both hit were invalidated
                return false;
        }
        else //only viable solution invalidated
            return false;

        //hit happened, but normal should stay unpolluted (no shift)
        //otherwise normalization fucks everything up badly
        Vec3 normal(hitp.x, hitp.y, hitp.z);
        hit->normal_h = Normal(normal);
        hit->index = 0;
        if(inverted)
            hit->normal_h = -hit->normal_h;
        return true;
    }
    else
        return false;
}

float Sphere::surface() const
{
    return FOUR_PI;
}

float Sphere::surface(const Matrix4* transform) const
{
    Vec3 scale = transform->get_scale();
    const float val = scale.x;
    return FOUR_PI*val*val;
}

void Sphere::sample_point(float r0, float r1, const float*, Point3* p,
                          Normal* n) const
{
    float z = 1.f-2.f*r0;
    float r = sqrtf(max(0.f, 1.f-z*z));
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
