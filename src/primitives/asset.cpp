//author: Davide Pizzolotto
//license: GNU GPLv3

#include "asset.hpp"
unsigned static int _asset_ID_pool = 1;

Asset::Asset(const Shape* sp, const Matrix4& transform)
        :objToWorld(transform),id(_asset_ID_pool++),
         aabb(sp->compute_AABB(&transform))

{
    Asset::model = sp;
    Asset::material = MtlLib.get("Default");
    Asset::objToWorld.inverse(&(Asset::worldToObj));
}

unsigned int Asset::get_id()const
{
    return Asset::id;
}

bool Asset::intersect(const Ray* ray_obj,float* distance, HitPoint* hit)const
{

    //since intersection is performed in object_space, convert back the ray
    Ray ray_world = worldToObj**ray_obj;
    bool res = Asset::model->intersect(&ray_world, distance, hit);
    if(res)
    {
        //retransform back to world space
        hit->point_h = objToWorld*hit->point_h;
        //normal requires the inverse of the transformation. Since I want a
        //objToWorld, its inverse is a worldToObj
        hit->normal_h = transform_normal(hit->normal_h,&worldToObj);
        hit->right = objToWorld*hit->right;
        hit->normal_h.normalize();
        hit->right.normalize();
        hit->cross = normalize(cross(Vec3(hit->normal_h),hit->right));
    }
    return res;
}

bool Asset::intersect_AABB(const Ray* r, const RayProperties* rp,
                         float* entry_point, float* exit_point)const
{
    return aabb.intersect(r,rp,entry_point,exit_point);
}

const AABB* Asset::get_AABB()const
{
    return &(Asset::aabb);
}

void Asset::set_material(const Bsdf *material)
{
    Asset::material = material;
}

const Bsdf* Asset::get_material() const
{
    return Asset::material;
}

bool Asset::is_light() const
{
    return false;
}
