#include "asset.hpp"
unsigned static int _asset_ID_pool = 1;

Asset::Asset(Shape* sp, Matrix4* transform)
        :id(_asset_ID_pool++),aabb(sp->computeWorldAABB(transform))
{
    Asset::model = sp;
    Asset::objToWorld = transform;
    Asset::material = MtlLib.get("Default");

    transform->inverse(&(Asset::worldToObj));
}

Asset::~Asset()
{
    
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
        h->h = *objToWorld*h->h;
        //normal requires the inverse of the transformation. Since I want a
        //objToWorld, its inverse is a worldToObj
        h->n = transformNormal(h->n,&worldToObj);
        h->right = *objToWorld*h->right;
        h->n.normalize();
        h->right.normalize();
        h->cross = normalize(cross(Vec3(h->n),h->right));
    }
    return res;
}

bool Asset::intersectFast(const Ray* r, const RayProperties* rp,
                         float* p1, float* p2)const
{
    return aabb.intersect(r,rp,p1,p2);
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
