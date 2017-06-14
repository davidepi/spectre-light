#include "box.hpp"

Box::Box() : edges(1,1,1)
{
    
}

Box::Box(Vec3 e) : edges(e)
{

}

AABB Box::computeAABB()const
{
    const Point3 min(0,0,0);
    const Point3 max(Box::edges.x,Box::edges.y,Box::edges.z);
    return AABB(&min,&max);
}

AABB Box::computeWorldAABB(const Matrix4* transform)const
{
#ifdef _LOW_LEVEL_CHECKS_
    if(transform==NULL)
    {
        Console.severe(
        "Trying to generate a world-space AABB with a NULL matrix");
        return AABB();
    }
#endif
    const Point3 pmin=*transform*Point3();
    const Point3 pmax=*transform*Point3(Box::edges.x,Box::edges.y,Box::edges.z);
    
    return AABB(&pmin, &pmax);
}

float Box::surface()const
{
    float la = 2*(edges.x+edges.z)*(edges.y); //lateral surface = perimeter * heigth
    return la+2*edges.x*edges.z;
}

bool Box::intersect(const Ray* r,float* distance,HitPoint* h)const
{
    Point3 top(edges.x,edges.y,edges.z);
    float mint;
    float maxt;
    
    //x plane
    float invr = 1.0f/r->direction.x;
    float near = (-r->origin.x) * invr;
    float far = (top.x-r->origin.x) * invr;
    if(near>far)
        swap(&near,&far);
    mint = near;
    maxt = far;
    if(mint>maxt)
        return false;
    
    //y plane
    invr = 1.0f/r->direction.y;
    near = (-r->origin.y) * invr;
    far = (top.y-r->origin.y) * invr;
    if(near>far)
        swap(&near,&far);
    mint = near>mint?near:mint;
    maxt = far<maxt?far:maxt;
    if(mint>maxt)
        return false;
    
    //z plane
    invr = 1.0f/r->direction.z;
    near = (-r->origin.z) * invr;
    far = (top.z-r->origin.z) * invr;
    if(near>far)
        swap(&near,&far);
    mint = near>mint?near:mint;
    maxt = far<maxt?far:maxt;
    if(mint>maxt)
        return false;
    *distance = min(mint,maxt);
    h->h = r->apply(*distance);
    h->sp = this;

    //calculate normal
    Point3 centre(edges.x/2.f,edges.y/2.f,edges.z/2.f);
    Vec3 offset = h->h - centre;
    Vec3 normal = ((int)(offset.x/centre.x),
                    (int)(offset.y/centre.y),
                    (int)(offset.z/centre.z));

    normal.normalize();
    h->n = Normal(normal);

    return true;

}
