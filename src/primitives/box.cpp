#include "box.hpp"

Box::Box() : Shape(),fbl(0,0,0),fbr(1,0,0),ftl(0,1,0),bbl(0,0,1)
{
    
}

Box::Box(Vec3* e, Matrix4* t) : Shape(),fbl(0,0,0),fbr(e->x,0,0),ftl(0,e->y,0),
bbl(0,0,e->z)
{
    transformMatrix = t;
}

Box::Box(Point3* b, Vec3* e, Matrix4* t) : Shape(),fbl(*b),
fbr(b->x+e->x,b->y,b->z),ftl(b->x,b->y+e->y,b->z),bbl(b->x,b->y,b->z+e->z)
{
    transformMatrix = t;
}

AABB Box::computeAABB()const
{
    const Point3 max(Box::fbr.x,Box::ftl.y,Box::bbl.z);
    return AABB(&(Box::fbl),&max);
}

AABB Box::computeWorldAABB()const
{
#ifdef _LOW_LEVEL_CHECKS_
    if(transformMatrix==NULL)
    {
        Console.severe(
        "Trying to generate a world-space AABB with a NULL matrix");
        return AABB();
    }
#endif
    const Point3 pmin=*transformMatrix*Box::fbl;
    const Point3 pmax=*transformMatrix*Point3(Box::fbr.x,Box::ftl.y,Box::bbl.z);
    
    return AABB(&pmin, &pmax);
}

float Box::surface()const
{
    float xe = fbr.x-fbl.x; //x edge
    float ze = bbl.z-fbl.z; //z edge
    float la = 2*(xe+ze)*(ftl.y-fbl.y); //lateral surface = perimeter * heigth
    return la+2*xe*ze;
}

void Box::obj2world()
{
    Console.warning("No rotation supported for now");
#ifdef _LOW_LEVEL_CHECKS_
    if(transformMatrix==NULL)
    {
        Console.severe("Trying to convert a box to world-space with a NULL matrix");
        return;
    }
#endif
    Box::fbl = (*transformMatrix)*Box::fbl;
    Box::fbr = (*transformMatrix)*Box::fbr;
    Box::ftl = (*transformMatrix)*Box::ftl;
    Box::bbl = (*transformMatrix)*Box::bbl;
}

void Box::world2obj()
{
    Console.warning("No rotation supported for now");
#ifdef _LOW_LEVEL_CHECKS_
    if(transformMatrix==NULL)
    {
        Console.severe("Trying to convert a box to world-space with a NULL matrix");
        return;
    }
#endif
    Matrix4 inv;
    transformMatrix->inverse(&inv);
    Box::fbl = inv*Box::fbl;
    Box::fbr = inv*Box::fbr;
    Box::ftl = inv*Box::ftl;
    Box::bbl = inv*Box::bbl;
}

bool Box::intersect(const Ray* r,float* distance,float* error)const
{
//    Point3 btr(fbr.x,ftl.y,bbl.z);
//    
//    float minxt, maxxt, minyt, maxyt, minzt, maxzt;
//    float invx = 1.f/r->direction.x;
//    float invy = 1.f/r->direction.y;
//    float invz = 1.f/r->direction.z;
//    if(r->direction.x >= 0)
//    {
//        minxt = (fbl.x - r->origin.x) * invx;
//        maxxt = (fbr.x - r->origin.x) * invx;
//    }
//    else
//    {
//        minxt = (fbr.x - r->origin.x) * invx;
//        maxxt = (fbl.x - r->origin.x) * invx;
//    }
//    if(r->direction.y >= 0)
//    {
//        minyt = (fbl.y - r->origin.y) * invy;
//        maxyt = (ftl.y - r->origin.y) * invy;
//    }
//    else
//    {
//        minyt = (ftl.y - r->origin.y) * invy;
//        maxyt = (fbl.y - r->origin.y) * invy;
//    }
//    
//    if((minxt > maxyt) || (minyt > maxxt))
//        return false;
//    if(minyt > minxt)
//        minxt = minyt;
//    if(maxyt < maxxt)
//        maxxt = maxyt;
//    
//    if(r->direction.z >= 0)
//    {
//        minzt = (fbl.z - r->origin.z) * invz;
//        maxzt = (bbl.z - r->origin.z) * invz;
//    }
//    else
//    {
//        minzt = (bbl.z - r->origin.z) * invz;
//        maxzt = (fbl.z - r->origin.z) * invz;
//    }
//    
//    if((minxt > maxzt) || (minzt > maxxt))
//        return false;
//    else
    return true; //this is equal to the AABB
}
