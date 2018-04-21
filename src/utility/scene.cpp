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

    delete[] Scene::lights;
    //DO NOT DELETE individual lights. lights are just pointers owned in, the
    //assets array.
    //The light array is there just for faster lookup
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

unsigned int Scene::add_asset(unsigned int shapeid, const Matrix4& transformMat,
                             const Bsdf* material)
{
    //shape exists
    if(shapes.count(shapeid))
    {
        if(Scene::assets_allocated == Scene::asset_index) //array full
        {
            if(Scene::asset_index!=_MAX_ASSETS_)
            {
                Asset **tmp = Scene::assets;
                Scene::assets_allocated = min(Scene::assets_allocated << 1,
                                              _MAX_ASSETS_);
                Scene::assets = new Asset*[Scene::assets_allocated];
                memcpy(Scene::assets,tmp,Scene::asset_index*sizeof(Asset*));
                delete[] tmp;
            }
            else //max number of assets reached
            {
                Console.warning(MESSAGE_MAXASSETNUMBER);
                return 0;
            }
        }
        Asset* addme = new Asset(shapes[shapeid], transformMat, 1);
        if(material!=NULL)
            addme->set_material(material,1);
        Scene::assets[Scene::asset_index++] = addme;
        k.addAsset(addme); //add to kdtree
        return addme->get_id();
    }
    else
        return 0; //shape not found, nothing added
}

unsigned int Scene::assets_size()const
{
    return Scene::asset_index;
}

unsigned int Scene::add_light(unsigned int shapeid, const Matrix4& transform,
                             const Spectrum& c)
{
    AreaLight* addme = NULL;
    unsigned int retval = 0;
    unsigned int asset_array_index = UINT_MAX;
    if(shapes.count(shapeid))
    {
        if(Scene::assets_allocated == Scene::asset_index) //array full
        {
            if(Scene::asset_index!=_MAX_ASSETS_)
            {
                Asset **tmp = Scene::assets;
                Scene::assets_allocated = min(Scene::assets_allocated << 1,
                                              _MAX_ASSETS_);
                Scene::assets = new Asset*[Scene::assets_allocated];
                memcpy(Scene::assets,tmp,Scene::asset_index*sizeof(Asset*));
                delete[] tmp;
            }
            else //max number of assets reached
            {
                Console.warning(MESSAGE_MAXASSETNUMBER);
                return 0;
            }
        }
        //reserve the index
        asset_array_index = Scene::asset_index++;
    }
    else
        return 0; //shape not found, nothing added

    //add the light also to the lights array.
    //once here the asset_array_index will ALWAYS be initialized
    if(Scene::lights_allocated == Scene::light_index)//array full
    {
        if(Scene::light_index != _MAX_LIGHTS_)
        {
            AreaLight **tmp = Scene::lights;
            Scene::lights_allocated = min(Scene::lights_allocated << 1,
                                          _MAX_LIGHTS_);
            Scene::lights = new AreaLight*[Scene::lights_allocated];
            memcpy(Scene::lights,tmp,Scene::light_index*sizeof(AreaLight*));
            delete[] tmp;
        }
        else
        {
            Console.warning(MESSAGE_MAXASSETNUMBER);
            //remove reserved index
            Scene::asset_index--;
            return 0;
        }
    }
    addme = new AreaLight(shapes[shapeid], transform,c);
    Scene::assets[asset_array_index] = (Asset*)addme;
    Scene::lights[Scene::light_index++] = addme;
    k.addAsset(addme); //add to kdtree
    retval = addme->get_id();

    return retval;
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
