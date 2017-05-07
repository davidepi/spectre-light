#include "box.hpp"

Box::Box() : Shape(),fbl(0,0,0),fbr(1,0,0),ftl(0,1,0),bbl(0,0,1)
{
    
}

Box::Box(Vec3* e, Matrix4* t) : Shape(),fbl(0,0,0),fbr(e->x,0,0),ftl(0,0,e->y),
bbl(0,0,e->z)
{
    transformMatrix = t;
}

Box::Box(Point3* b, Vec3* e, Matrix4* t) : Shape(),fbl(*b),
fbr(b->x+e->x,b->y,b->z),ftl(b->x,b->y+e->y,b->z),bbl(b->x,b->y,b->z+e->z)
{
    transformMatrix = t;
}

void Box::recomputeAABB()
{
    const Point3 max(Box::fbr.x,Box::ftl.y,Box::bbl.z);
    Box::aabb = AABB(&(Box::fbl),&max);
}

AABB Box::computeAABB()const
{
    const Point3 max(Box::fbr.x,Box::ftl.y,Box::bbl.z);
    return AABB(&(Box::fbl),&max);
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
    warning("No rotation supported for now");
#ifdef _LOW_LEVEL_CHECKS_
    if(transformMatrix==NULL)
    {
        severe("Trying to convert a box to world-space with a NULL matrix");
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
    warning("No rotation supported for now");
#ifdef _LOW_LEVEL_CHECKS_
    if(transformMatrix==NULL)
    {
        severe("Trying to convert a box to world-space with a NULL matrix");
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
    Point3 top(fbr.x,ftl.y,bbl.z);
    float mint;
    float maxt;
    
    //x plane
    float invr = 1.0f/r->direction.x;
    float near = (fbl.x-r->origin.x) * invr;
    float far = (top.x-r->origin.x) * invr;
    if(near>far)
        swap(&near,&far);
    mint = near;
    maxt = far;
    if(mint>maxt)
        return false;
    
    //y plane
    invr = 1.0f/r->direction.y;
    near = (fbl.y-r->origin.y) * invr;
    far = (top.y-r->origin.y) * invr;
    if(near>far)
        swap(&near,&far);
    mint = near>mint?near:mint;
    maxt = far<maxt?far:maxt;
    if(mint>maxt)
        return false;
    
    //z plane
    invr = 1.0f/r->direction.z;
    near = (fbl.z-r->origin.z) * invr;
    far = (top.z-r->origin.z) * invr;
    if(near>far)
        swap(&near,&far);
    mint = near>mint?near:mint;
    maxt = far<maxt?far:maxt;
    if(mint>maxt)
        return false;
    *distance = min(mint,maxt);
    *error = 0; //TODO: since this method will be replaced for now this is a
                //placeholder
    return true;

}
