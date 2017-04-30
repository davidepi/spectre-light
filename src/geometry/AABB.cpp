#include "AABB.hpp"
AABB::AABB()
:bmin(INFINITY, INFINITY, INFINITY), bmax(-INFINITY,-INFINITY,-INFINITY)
{
    
}

AABB::AABB(const Point3 p)
: bmin(p.x, p.y, p.z), bmax(p.x, p.y, p.z)
{
    
}

AABB::AABB(const Point3* min, const Point3* max)
:bmin(min->x,min->y,min->z),bmax(max->x,max->y,max->z)
{
    
}

void AABB::expand(float value)
{
    AABB::bmin -= value;
    AABB::bmax += value;
}

void AABB::engulf(const Point3* p1)
{
    AABB::bmin = min((AABB::bmin),*p1);
    AABB::bmax = max((AABB::bmax),*p1);
}

void AABB::engulf(const AABB* aabb)
{
    AABB::bmin = min(AABB::bmin,aabb->bmin);
    AABB::bmax = max(AABB::bmax,aabb->bmax);
}

bool AABB::overlaps(const AABB* aabb)const
{
    bool x = (AABB::bmax.x >= aabb->bmin.x) && (AABB::bmin.x <= aabb->bmax.x);
    bool y = (AABB::bmax.y >= aabb->bmin.y) && (AABB::bmin.y <= aabb->bmax.y);
    bool z = (AABB::bmax.z >= aabb->bmin.z) && (AABB::bmin.z <= aabb->bmax.z);
    
    return x && y && z;
}

bool AABB::inside(const Point3* p)const
{
    return p->x >= AABB::bmin.x && p->x <= AABB::bmax.x &&
    p->y >= AABB::bmin.y && p->y <= AABB::bmax.y &&
    p->z >= AABB::bmin.z && p->z <= AABB::bmax.z;
}

float AABB::surface()const
{
    Vec3 diag = AABB::bmax - AABB::bmin;
    return 2.0f * (diag.x*diag.y + diag.x*diag.z + diag.y*diag.z);
}

float AABB::volume()const
{
    Vec3 diagonal = AABB::bmax - AABB::bmin;
    return diagonal.x * diagonal.y * diagonal.z;
}

int AABB::longest_axis()
{
    Vec3 diagonal = AABB::bmax - AABB::bmin;
    if(diagonal.x > diagonal.y && diagonal.x > diagonal.z)
        return 0;
    else if (diagonal.y > diagonal.z)
        return 1;
    else
        return 2;
}

//♥ ♥ ♥ Operators ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥

AABB AABB::operator+(const Point3& p)const
{
    Point3 minp = min(AABB::bmin,p);
    Point3 maxp = max(AABB::bmax,p);
    return AABB(&minp,&maxp);
}

AABB AABB::operator+(const AABB& aabb)const
{
    Point3 minp = min(AABB::bmin,aabb.bmin);
    Point3 maxp = max(AABB::bmax,aabb.bmax);
    
    return AABB(&minp,&maxp);
}

bool AABB::operator<(const AABB& a)const
{
    return AABB::volume() < a.volume();
}

bool AABB::operator>(const AABB& a)const
{
    return a < (*this);
}

bool AABB::operator<=(const AABB& a)const
{
    return !(a > *(this));
}

bool AABB::operator>=(const AABB& a)const
{
    return !(a < *(this));
}

bool AABB::operator==(const AABB& a)const
{
    return AABB::volume() == a.volume();
}

bool AABB::operator!=(const AABB &b)const
{
    return !(*(this)==b);
}

//♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥
