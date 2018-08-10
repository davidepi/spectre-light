//author: Davide Pizzolotto
//license: GNU GPLv3

#include "asset.hpp"

unsigned static int _asset_ID_pool = 1;

Asset::Asset(const Shape* sp, const Matrix4& transform, unsigned char mat_no)
        :objToWorld(transform), id(_asset_ID_pool++),
         aabb(sp->compute_AABB(&transform))
{
    Asset::model = sp;
    Asset::materials = (const Bsdf**)malloc(sizeof(Bsdf*)*(mat_no+1));
    Asset::materials_index = (unsigned char*)malloc(sp->get_faces_number());
    Asset::objToWorld.inverse(&(Asset::worldToObj));
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
    Ray ray_obj = worldToObj**ray_world;
    //keep old_value in case the hit is invalidated by the mask
    float previous_distance = *distance;
    HitPoint previous_hit = *hit;
    bool res = Asset::model->intersect(&ray_obj, distance, hit);
    if(res)
    {
        //retransform back to world space
        hit->point_h = objToWorld*hit->point_h;
        //normal requires the inverse of the transformation. Since I want a
        //objToWorld, its inverse is a worldToObj
        hit->normal_h = transform_normal(hit->normal_h, &worldToObj);
        hit->dpdu = objToWorld*hit->dpdu;
        hit->dpdv = objToWorld*hit->dpdv;
        hit->normal_h.normalize();
        hit->dpdu.normalize();
        hit->dpdv.normalize();
        hit->cross = normalize(cross(Vec3(hit->normal_h), hit->dpdu));
        if(mask.map != NULL)
        {
            bool mask_val = mask.map->map_channel(hit, mask.channel)>=THRESHOLD;
            if((!mask_val || mask.inverted) && (mask_val || !mask.inverted))
            {
                //hit invalidated, restore previous distance
                *distance = previous_distance;
                *hit = previous_hit;
                res = false;
            }
        }
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

void Asset::set_mask(Mask m)
{
    Asset::mask = m;
}
