//author: Davide Pizzolotto
//license: GNU GPLv3

#include "scene.hpp"

Scene::Scene()
{
    Scene::assets_allocated = 1;
    Scene::lights_allocated = 1;
    Scene::asset_index = 0;
    Scene::light_index = 0;
    Scene::assets = new Asset*[Scene::assets_allocated];
    Scene::lights = new AreaLight*[Scene::lights_allocated];
}

Scene::~Scene()
{
    std::unordered_map<unsigned int,const Shape*>::iterator it;
    for(it=shapes.begin();it!=shapes.end();++it)
        delete it->second;
    shapes.clear();

    for(unsigned int i=0;i<Scene::asset_index;i++)
        delete Scene::assets[i];
    delete[] Scene::assets;

    //DO NOT DELETE individual lights. lights are just pointers owned in, the
    //assets array.
    //The light array is there just for faster lookup
    delete[] Scene::lights;
}

unsigned int Scene::inherit_shape(Shape *addme)
{
    shapes.insert(std::make_pair(addme->get_id(),addme));
    return addme->get_id();
}

unsigned int Scene::shapes_size()const
{
    return (unsigned int)shapes.size();
}

unsigned int Scene::assets_size()const
{
    return Scene::asset_index;
}

unsigned int Scene::lights_size()const
{
    return Scene::light_index;
}

const AreaLight*const* Scene::get_lights()const
{
    return (const AreaLight*const*)Scene::lights;
}

void Scene::inherit_asset(Asset* addme)
{
    Scene::assets[Scene::asset_index++] = addme;
    k.addAsset(addme);
}

void Scene::inherit_light(AreaLight* addme)
{
    Scene::assets[Scene::asset_index++] = addme;
    k.addAsset(addme);
}
