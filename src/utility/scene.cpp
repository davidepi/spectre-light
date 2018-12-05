//author: Davide Pizzolotto
//license: GNU GPLv3

#include "scene.hpp"

Scene::~Scene()
{
    for(auto& shape : shapes)
        delete shape.second;
    shapes.clear();

    for(auto& asset : assets)
        delete asset.second;
    assets.clear();

    //DO NOT DELETE area lights. lights are just pointers owned in, the
    //assets array.
    //The light array is there just for faster lookup.
    //This is the reason of the to_delete array for lights

    for(auto& lights_it : to_delete)
    {
        delete lights_it;
    }
    to_delete.clear();
}

void Scene::inherit_shape(const Shape* addme)
{
    //unordered map to check in O(1) if the shape is duplicate upon addition
    shapes.insert(std::make_pair(addme->get_id(), addme));
}

unsigned int Scene::size_shapes() const
{
    return (unsigned int)shapes.size();
}

void Scene::inherit_asset(const Asset* addme)
{
    //unordered map to check in O(1) if the asset is duplicate upon addition
    assets.insert(std::make_pair(addme->get_id(), addme));
    bound.engulf(addme->get_AABB());
    k.addAsset(addme);
}

unsigned int Scene::size_assets() const
{
    return (unsigned int)assets.size();
}

void Scene::inherit_arealight(const LightArea* addme)
{
    if(lights.size()<_MAX_LIGHTS_)
    {
        //usually I avoid auto keyword, but this iterator would be > 80 col
        auto insert_res = assets.insert(std::make_pair(addme->get_id(), addme));
        if(insert_res.second) //true if it was added
        {
            lights.push_back(addme);
            k.addAsset(addme);
        }
    }
    else
        Console.warning(MESSAGE_MAXLIGHTSNUMBER, _MAX_LIGHTS_);
}

void Scene::inherit_light(const Light* addme)
{
    if(lights.size()<_MAX_LIGHTS_)
    {
        lights.push_back(addme);
        to_delete.push_back(addme);
    }
    else
        Console.warning(MESSAGE_MAXLIGHTSNUMBER, _MAX_LIGHTS_);
}

unsigned int Scene::size_lights() const
{
    return (unsigned int)lights.size();
}

const Light* Scene::get_light(int index) const
{
    return lights[index];
}

float Scene::radius() const
{
    return bound.radius();
}

void Scene::inherit_sky(const LightSky* addme)
{
    inherit_light(addme);
    sky = addme;
}

Spectrum Scene::get_escaped_radiance(const Ray* ray) const
{
    if(sky != NULL)
        return sky->radiance_escaped(ray);
    else
        return {};
}
