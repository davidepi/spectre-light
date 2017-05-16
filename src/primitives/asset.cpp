#include "asset.hpp"

unsigned static int _asset_ID_pool = 1;

Asset::Asset(Shape* sp) : id(_asset_ID_pool++),aabb(sp->computeWorldAABB())
{
    Asset::model = sp;
}

bool Asset::intersect(const Ray *r, float *distance, float *error)const
{
    return Asset::model->intersect(r, distance, error);
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
