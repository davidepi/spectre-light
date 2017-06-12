#include "asset.hpp"

unsigned static int _asset_ID_pool = 1;

Asset::Asset(Shape* sp, Matrix4* transform)
        :id(_asset_ID_pool++),aabb(sp->computeWorldAABB(transform))
{
    Asset::model = sp;
    Asset::transform = transform;
    transform->inverse(&(Asset::invTrans));
}

unsigned int Asset::getID()
{
    return Asset::id;
}

bool Asset::intersect(const Ray* r,float* distance, HitPoint* h)const
{

    //since intersection is performed in object_space, convert back the ray
    Ray r2 = invTrans**r;
    return Asset::model->intersect(&r2, distance, h);
}

bool Asset::intersectFast(const Ray* r, const RayProperties* rp,
                         float* p1, float* p2)const
{
    return aabb.intersect(r,rp,p1,p2);
}

Asset::~Asset()
{
    
}

const AABB* Asset::getAABB()const
{
    return &(Asset::aabb);
}
