//author: Davide Pizzolotto
//license: GNU GPLv3

#include "asset.hpp"

unsigned static int _asset_ID_pool = 1;

Asset::Asset(const Shape* sp, const Matrix4& transform, unsigned char mat_no)
        :obj2world(transform), id(_asset_ID_pool++),
         aabb(sp->compute_AABB(&transform))
{
    Asset::model = sp;
    Asset::materials = (const Bsdf**)malloc(sizeof(Bsdf*)*(mat_no+1));
    Asset::materials_index = (unsigned char*)malloc(sp->get_faces_number());
    Asset::obj2world.inverse(&(Asset::world2obj));
}

unsigned int Asset::get_id() const
{
    return Asset::id;
}

Asset::~Asset()
{
    free(materials);
    free(materials_index);
}

bool
Asset::intersect(const Ray* ray_world, float* distance, HitPoint* hit) const
{
    //since intersection is performed in object_space, convert back the ray
    Ray ray_obj = world2obj**ray_world;
    //keep old_value in case the hit is invalidated by the mask
    bool res = Asset::model->intersect(&ray_obj, distance, hit, &mask);
    if(res)
    {
        //retransform back to world space
        hit->point_h = obj2world*hit->point_h;
        //normal requires the inverse of the transformation. Since I want a
        //obj2world, its inverse is a world2obj
        hit->normal_h = transform_normal(hit->normal_h, &world2obj);
        hit->dpdu = obj2world*hit->dpdu;
        hit->dpdv = obj2world*hit->dpdv;
        hit->normal_h.normalize();
        hit->dpdu.normalize();
        hit->dpdv.normalize();
    }
    return res;
}

bool Asset::intersect_AABB(const Ray* r, const RayProperties* rp,
                           float* entry_point, float* exit_point) const
{
    return aabb.intersect(r, rp, entry_point, exit_point);
}

const AABB* Asset::get_AABB() const
{
    return &(Asset::aabb);
}

bool Asset::is_light() const
{
    return false;
}

void Asset::set_materials(const Bsdf** mats, unsigned char mats_len,
                          const unsigned char* indexes)
{
    free(materials);
    materials = (const Bsdf**)malloc(sizeof(Bsdf*)*mats_len);
    memcpy(materials, mats, sizeof(Bsdf*)*mats_len);
    memcpy(materials_index, indexes, (size_t)model->get_faces_number());
}

const Bsdf* Asset::get_material(unsigned int index) const
{
    return Asset::materials[materials_index[index]];
}

void Asset::set_mask(const MaskBoolean& m)
{
    Asset::mask = m;
}
