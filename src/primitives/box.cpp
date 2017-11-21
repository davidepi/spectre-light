#include "box.hpp"

Box::Box() : edges(1,1,1)
{
    
}

Box::Box(Vec3 e) : edges(e)
{
#ifdef _LOW_LEVEL_CHECKS_
        Console.severe(e.x==0 || e.y==0 || e.z==0,MESSAGE_DEGENERATE_BOX);
#endif
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
        Console.severe(MESSAGE_WORLD_AABB_NULL_MATRIX);
        return AABB();
    }
#endif
    const Point3 pmin=*transform*Point3();
    const Point3 pmax=*transform*Point3(Box::edges.x,Box::edges.y,Box::edges.z);
    
    return AABB(min(pmin,pmax),max(pmin,pmax));
}

float Box::surface()const
{
    float la = 2*(edges.x+edges.z)*(edges.y);//lateral surface= perimeter*heigth
    return la+2*edges.x*edges.z;
}

bool Box::intersect(const Ray* r,float* distance,HitPoint* h)const
{

    Point3 top(edges.x,edges.y,edges.z);
    float mint;
    float maxt;
    char axis = 0; //used for normal identification
    
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
    if(near > mint)
    {
        mint = near;
        axis = 1;
    }
    maxt = far<maxt?far:maxt;
    if(mint>maxt)
        return false;
    
    //z plane
    invr = 1.0f/r->direction.z;
    near = (-r->origin.z) * invr;
    far = (top.z-r->origin.z) * invr;
    if(near>far)
        swap(&near,&far);
    if(near > mint)
    {
        mint = near;
        axis = 2;
    }
    maxt = far<maxt?far:maxt;
    if(mint>maxt)
        return false;
    float tmpdistance;
    if(mint>SELF_INTERSECT_ERROR)
        tmpdistance = mint;
    else if(maxt>SELF_INTERSECT_ERROR)
        tmpdistance = maxt;
    else
        return false;
    if(tmpdistance>*distance)
        return false;
    else
        *distance = tmpdistance;
    h->h = r->apply(*distance);
    h->n = Normal();
    h->n[axis] = 1;
    h->n[axis]*=sign(h->h[axis]);
    if(h->n.z!=0)
        h->right = Vec3(h->n.z,0,0);
    else
        h->right = Vec3(-h->n.y,h->n.x,0);
    return true;
}

void Box::getRandomPoint(float r0, float r1, Point3* p, Normal* n)const
{
    /*
      frn bck top btm lft rgt
     |---|---|---|---|---|---|
     | y | y | z | z | y | y |
     |---|---|---|---|---|---|
       x   x   x   x   z   z
     */
    float res = lerp(r0,0,edges.x*4+edges.z*2);
    if(res<edges.x)
    {
        //front
        p->x=res;
        p->y = lerp(r1,0,edges.y);
        p->z = 0;
        n->x = 0;
        n->y = 0;
        n->z = -1;
    }
    else if(res<2*edges.x)
    {
        //back
        p->x=res-edges.x;
        p->y = lerp(r1,0,edges.y);
        p->z = edges.z;
        n->x = 0;
        n->y = 0;
        n->z = 1;
    }
    else if(res<3*edges.x)
    {
        //top
        p->x = res-2*edges.x;
        p->y = edges.y;
        p->z = lerp(r1,0,edges.z);
        n->x = 0;
        n->y = 1;
        n->z = 0;
    }
    else if(res<4*edges.x)
    {
        //bottom
        p->x = res-3*edges.x;
        p->y = 0;
        p->z = lerp(r1,0,edges.z);
        n->x = 0;
        n->y = -1;
        n->z = 0;
    }
    else if(res<(4*edges.x+edges.z))
    {
        //left
        p->x = 0;
        p->y = lerp(r1,0,edges.y);
        p->z = res-4*edges.x;
        n->x = -1;
        n->y = 0;
        n->z = 0;
    }
    else
    {
        //right
        p->x = edges.x;
        p->y = lerp(r1,0,edges.y);
        p->z = res-4*edges.x-edges.z;
        n->x = 1;
        n->y = 0;
        n->z = 0;
    }
}
