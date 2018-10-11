//author: Davide Pizzolotto
//license: GNU GPLv3

#include "AABB.hpp"

AABB::AABB():bounds{Point3(INFINITY, INFINITY, INFINITY),
                    Point3(-INFINITY, -INFINITY, -INFINITY)}
{

}

AABB::AABB(const Point3& p)
        :bounds{Point3(p.x, p.y, p.z), Point3(p.x, p.y, p.z)}
{

}

AABB::AABB(const Point3* min, const Point3* max)
        :bounds{Point3(min->x, min->y, min->z), Point3(max->x, max->y, max->z)}
{

}

AABB::AABB(const Point3& min, const Point3& max)
        :bounds{Point3(min.x, min.y, min.z), Point3(max.x, max.y, max.z)}
{

}

void AABB::expand(float value)
{
    AABB::bounds[0] -= value;
    AABB::bounds[1] += value;
}

void AABB::engulf(const Point3* p1)
{
    AABB::bounds[0] = min((AABB::bounds[0]), *p1);
    AABB::bounds[1] = max((AABB::bounds[1]), *p1);
}

void AABB::engulf(const Point3& p1)
{
    AABB::bounds[0] = min((AABB::bounds[0]), p1);
    AABB::bounds[1] = max((AABB::bounds[1]), p1);
}

void AABB::engulf(const AABB* aabb)
{
    AABB::bounds[0] = min(AABB::bounds[0], aabb->bounds[0]);
    AABB::bounds[1] = max(AABB::bounds[1], aabb->bounds[1]);
}

void AABB::engulf(const AABB& aabb)
{
    AABB::bounds[0] = min(AABB::bounds[0], aabb.bounds[0]);
    AABB::bounds[1] = max(AABB::bounds[1], aabb.bounds[1]);
}

bool AABB::inside(const Point3* p) const
{
    return p->x>=AABB::bounds[0].x && p->x<=AABB::bounds[1].x &&
           p->y>=AABB::bounds[0].y && p->y<=AABB::bounds[1].y &&
           p->z>=AABB::bounds[0].z && p->z<=AABB::bounds[1].z;
}

float AABB::surface() const
{
    Vec3 diag = AABB::bounds[1]-AABB::bounds[0];
    return 2.0f*(diag.x*diag.y+diag.x*diag.z+diag.y*diag.z);
}

float AABB::volume() const
{
    Vec3 diagonal = AABB::bounds[1]-AABB::bounds[0];
    return diagonal.x*diagonal.y*diagonal.z;
}

char AABB::longest_axis() const
{
    Vec3 diagonal = AABB::bounds[1]-AABB::bounds[0];
    if(diagonal.x>=diagonal.y && diagonal.x>=diagonal.z)
        return 0;
    else if(diagonal.y>=diagonal.z)
        return 1;
    else
        return 2;
}

float AABB::radius() const
{
    return (AABB::center()-AABB::bounds[1]).length();
}

Point3 AABB::center() const
{
    return Point3((bounds[0].x+bounds[1].x)*0.5f,
                  (bounds[0].y+bounds[1].y)*0.5f,
                  (bounds[0].z+bounds[1].z)*0.5f);
}

bool AABB::intersect(const Ray* r, float* p1, float* p2) const
{
    float minxt, maxxt, minyt, maxyt, minzt, maxzt;
    float invx = 1.f/r->direction.x;
    float invy = 1.f/r->direction.y;
    float invz = 1.f/r->direction.z;
    if(r->direction.x>=0)
    {
        minxt = (bounds[0].x-r->origin.x)*invx;
        maxxt = (bounds[1].x-r->origin.x)*invx;
    }
    else
    {
        minxt = (bounds[1].x-r->origin.x)*invx;
        maxxt = (bounds[0].x-r->origin.x)*invx;
    }
    if(r->direction.y>=0)
    {
        minyt = (bounds[0].y-r->origin.y)*invy;
        maxyt = (bounds[1].y-r->origin.y)*invy;
    }
    else
    {
        minyt = (bounds[1].y-r->origin.y)*invy;
        maxyt = (bounds[0].y-r->origin.y)*invy;
    }

    if((minyt>maxxt) || (minxt>maxyt))
        return false;
    if(minyt>minxt)
        minxt = minyt;
    if(maxyt<maxxt)
        maxxt = maxyt;

    if(r->direction.z>=0)
    {
        minzt = (bounds[0].z-r->origin.z)*invz;
        maxzt = (bounds[1].z-r->origin.z)*invz;
    }
    else
    {
        minzt = (bounds[1].z-r->origin.z)*invz;
        maxzt = (bounds[0].z-r->origin.z)*invz;
    }

    if((minzt>maxxt) || (minxt>maxzt))
        return false;
    if(minzt>minxt)
        minxt = minzt;
    if(maxzt<maxxt)
        maxxt = maxzt;
    *p1 = minxt;
    *p2 = maxxt;
    return true;
}

bool AABB::intersect(const Ray* r, const RayProperties* p, float* p1, float* p2)
const
{
    float mint, maxt, minyt, maxyt;

    mint = (bounds[p->isXInvNeg].x-r->origin.x)*p->inverseX;
    maxt = (bounds[1-p->isXInvNeg].x-r->origin.x)*p->inverseX;
    minyt = (bounds[p->isYInvNeg].y-r->origin.y)*p->inverseY;
    maxyt = (bounds[1-p->isYInvNeg].y-r->origin.y)*p->inverseY;

    if(mint>maxyt || minyt>maxt)
        return false;
    if(minyt>mint)
        mint = minyt;
    if(maxyt<maxt)
        maxt = maxyt;

    minyt = (bounds[p->isZInvNeg].z-r->origin.z)*p->inverseZ;
    maxyt = (bounds[1-p->isZInvNeg].z-r->origin.z)*p->inverseZ;

    if(mint>maxyt || minyt>maxt)
        return false;
    if(minyt>mint)
        mint = minyt;
    if(maxyt<maxt)
        maxt = maxyt;
    *p1 = mint;
    *p2 = maxt;
    return true;
}


//------ Operators -------------------------------------------------------------

AABB AABB::operator+(const Point3& p) const
{
    Point3 minp = min(AABB::bounds[0], p);
    Point3 maxp = max(AABB::bounds[1], p);
    return AABB(&minp, &maxp);
}

AABB AABB::operator+(const AABB& aabb) const
{
    Point3 minp = min(AABB::bounds[0], aabb.bounds[0]);
    Point3 maxp = max(AABB::bounds[1], aabb.bounds[1]);

    return AABB(&minp, &maxp);
}

void AABB::operator+=(const Point3& p)
{
    AABB::bounds[0] = min((AABB::bounds[0]), p);
    AABB::bounds[1] = max((AABB::bounds[1]), p);
}

void AABB::operator+=(const AABB& aabb)
{
    AABB::bounds[0] = min(AABB::bounds[0], aabb.bounds[0]);
    AABB::bounds[1] = max(AABB::bounds[1], aabb.bounds[1]);
}

bool AABB::operator<(const AABB& a) const
{
    return AABB::surface()<a.surface();
}

bool AABB::operator>(const AABB& a) const
{
    return a<(*this);
}

bool AABB::operator<=(const AABB& a) const
{
    return !(a<*(this));
}

bool AABB::operator>=(const AABB& a) const
{
    return !(a>*(this));
}

bool AABB::operator==(const AABB& a) const
{
    return AABB::surface() == a.surface();
}

bool AABB::operator!=(const AABB& b) const
{
    return !(*(this) == b);
}

//------------------------------------------------------------------------------
