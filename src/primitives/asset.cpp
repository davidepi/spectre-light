//author: Davide Pizzolotto
//license: GNU GPLv3

#include "asset.hpp"
unsigned static int _asset_ID_pool = 1;

Asset::Asset(Shape* sp, Matrix4* transform)
        :objToWorld(*transform),id(_asset_ID_pool++),
         aabb(sp->compute_AABB(transform))

{
    Asset::model = sp;
    Asset::material = MtlLib.get("Default");
    Asset::objToWorld.inverse(&(Asset::worldToObj));
}

unsigned int Asset::getID()const
{
    return Asset::id;
}

bool Asset::intersect(const Ray* r,float* distance, HitPoint* h)const
{

    //since intersection is performed in object_space, convert back the ray
    Ray r2 = worldToObj**r;
    bool res = Asset::model->intersect(&r2, distance, h);
    if(res)
    {
        //retransform back to world space
        h->point_h = objToWorld*h->point_h;
        //normal requires the inverse of the transformation. Since I want a
        //objToWorld, its inverse is a worldToObj
        h->normal_h = transform_normal(h->normal_h,&worldToObj);
        h->right = objToWorld*h->right;
        h->normal_h.normalize();
        h->right.normalize();
        h->cross = normalize(cross(Vec3(h->normal_h),h->right));
    }
    return res;
}

bool Asset::intersectAABB(const Ray* r, const RayProperties* rp,
                         float* entry_point, float* exit_point)const
{
    return aabb.intersect(r,rp,entry_point,exit_point);
}

const AABB* Asset::getAABB()const
{
    return &(Asset::aabb);
}

void Asset::setMaterial(const Bsdf *material)
{
    Asset::material = material;
}

const Bsdf* Asset::getMaterial() const
{
    return Asset::material;
}

bool Asset::isLight() const
{
    return false;
}
