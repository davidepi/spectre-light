#include "asset.hpp"

unsigned static int _asset_ID_pool = 1;

Asset::Asset(Shape* sp) : id(_asset_ID_pool++)
{
    Asset::model = sp;
}

bool Asset::intersect(const Ray *r, float *distance, float *error)const
{
    return Asset::model->intersect(r, distance, error);
}
