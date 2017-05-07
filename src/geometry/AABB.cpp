#include "AABB.hpp"
AABB::AABB() :bounds{Point3(INFINITY, INFINITY, INFINITY),
                     Point3(-INFINITY, -INFINITY, -INFINITY)}
{
    
}

AABB::AABB(const Point3 p)
: bounds{Point3(p.x, p.y, p.z), Point3(p.x, p.y, p.z)}
{
    
}

AABB::AABB(const Point3* min, const Point3* max)
:bounds{Point3(min->x, min->y, min->z), Point3(max->x, max->y, max->z)}
{
    
}

void AABB::expand(float value)
{
    AABB::bounds[0] -= value;
    AABB::bounds[1] += value;
}

void AABB::engulf(const Point3* p1)
{
    AABB::bounds[0] = min((AABB::bounds[0]),*p1);
    AABB::bounds[1] = max((AABB::bounds[1]),*p1);
}

void AABB::engulf(const AABB* aabb)
{
    AABB::bounds[0] = min(AABB::bounds[0],aabb->bounds[0]);
    AABB::bounds[1] = max(AABB::bounds[1],aabb->bounds[1]);
}

bool AABB::overlaps(const AABB* aabb)const
{
    bool x = (AABB::bounds[1].x >= aabb->bounds[0].x) &&
             (AABB::bounds[0].x <= aabb->bounds[1].x);
    bool y = (AABB::bounds[1].y >= aabb->bounds[0].y) &&
             (AABB::bounds[0].y <= aabb->bounds[1].y);
    bool z = (AABB::bounds[1].z >= aabb->bounds[0].z) &&
             (AABB::bounds[0].z <= aabb->bounds[1].z);
    
    return x && y && z;
}

bool AABB::inside(const Point3* p)const
{
    return p->x >= AABB::bounds[0].x && p->x <= AABB::bounds[1].x &&
           p->y >= AABB::bounds[0].y && p->y <= AABB::bounds[1].y &&
           p->z >= AABB::bounds[0].z && p->z <= AABB::bounds[1].z;
}

float AABB::surface()const
{
    Vec3 diag = AABB::bounds[1] - AABB::bounds[0];
    return 2.0f * (diag.x*diag.y + diag.x*diag.z + diag.y*diag.z);
}

float AABB::volume()const
{
    Vec3 diagonal = AABB::bounds[1] - AABB::bounds[0];
    return diagonal.x * diagonal.y * diagonal.z;
}

int AABB::longest_axis()
{
    Vec3 diagonal = AABB::bounds[1] - AABB::bounds[0];
    if(diagonal.x > diagonal.y && diagonal.x > diagonal.z)
        return 0;
    else if (diagonal.y > diagonal.z)
        return 1;
    else
        return 2;
}

bool AABB::intersect(const Ray* r, float* p1, float* p2)const
{
    float mint;
    float maxt;
    
    //x plane
    float invr = 1.0f/r->direction.x;
    float near = (AABB::bounds[0].x-r->origin.x) * invr;
    float far = (AABB::bounds[1].x-r->origin.x) * invr;
    if(near>far)
        swap(&near,&far);
    mint = near;
    maxt = far;
    if(mint>maxt)
        return false;
    
    //y plane
    invr = 1.0f/r->direction.y;
    near = (AABB::bounds[0].y-r->origin.y) * invr;
    far = (AABB::bounds[1].y-r->origin.y) * invr;
    if(near>far)
        swap(&near,&far);
    mint = near>mint?near:mint;
    maxt = far<maxt?far:maxt;
    if(mint>maxt)
        return false;
    
    //z plane
    invr = 1.0f/r->direction.z;
    near = (AABB::bounds[0].z-r->origin.z) * invr;
    far = (AABB::bounds[1].z-r->origin.z) * invr;
    if(near>far)
        swap(&near,&far);
    mint = near>mint?near:mint;
    maxt = far<maxt?far:maxt;
    if(mint>maxt)
        return false;
    if(!std::isnan(mint))
        *p1 = mint;
    if(!std::isnan(maxt))
        *p2 = maxt;
    return true;
}

bool AABB::intersect(const Ray* r, const RayProperties* p, float* p1, float* p2)
const
{
    float mint,maxt,minyt,maxyt;
    
    mint = (bounds[p->isXInvNeg].x - r->origin.x) * p->inverseX;
    maxt = (bounds[1-p->isXInvNeg].x - r->origin.x) * p->inverseX;
    minyt = (bounds[p->isYInvNeg].y - r->origin.y) * p->inverseY;
    maxyt = (bounds[1-p->isYInvNeg].y - r->origin.y) * p->inverseY;
    
    if(mint > maxyt || minyt > maxt)
        return false;
    if(minyt > mint)
        mint = minyt;
    if(maxyt < maxt)
        maxt = maxyt;
    
    minyt = (bounds[p->isZInvNeg].z - r->origin.z) * p->inverseZ;
    maxyt = (bounds[1-p->isZInvNeg].z - r->origin.z) * p->inverseZ;
    
    if(mint > maxyt || minyt > maxt)
        return false;
    if(minyt > mint)
        mint = minyt;
    if(maxyt < maxt)
        maxt = maxyt;
    *p1 = mint;
    *p2 = maxt;
    return true;
}


//♥ ♥ ♥ Operators ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥ ♥

AABB AABB::operator+(const Point3& p)const
{
    Point3 minp = min(AABB::bounds[0],p);
    Point3 maxp = max(AABB::bounds[1],p);
    return AABB(&minp,&maxp);
}

AABB AABB::operator+(const AABB& aabb)const
{
    Point3 minp = min(AABB::bounds[0],aabb.bounds[0]);
    Point3 maxp = max(AABB::bounds[1],aabb.bounds[1]);
    
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
