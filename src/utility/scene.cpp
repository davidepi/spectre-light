#include "scene.hpp"

Scene::Scene()
{
    Scene::shapes_allocated = 1;
    Scene::assets_allocated = 1;
    Scene::lights_allocated = 1;
    Scene::shape_index = 0;
    Scene::asset_index = 0;
    Scene::light_index = 0;
    Scene::shapes = new Shape*[Scene::shapes_allocated];
    Scene::assets = new Asset*[Scene::assets_allocated];
    Scene::lights = new AreaLight*[Scene::lights_allocated];
}

Scene::~Scene()
{
    for(int i=0;i<shapes_allocated;i++)
        delete Scene::shapes[i];
    delete[] Scene::shapes;

    for(int i=0;i<assets_allocated;i++)
        delete Scene::assets[i];
    delete[] Scene::assets;

    delete[] Scene::lights;
    //DO NOT DELETE individual lights. lights are a subclass of assets, the
    //array is there just for faster lookup
}

int Scene::inheritShape(Shape *addme)
{
    if(Scene::shapes_allocated == Scene::shape_index) //array full, doubles it
    {
        if (Scene::shape_index == _MAX_ASSETS_)
            Console.warning(MESSAGE_MAXASSETNUMBER);
        else
        {
            Shape **tmp = Scene::shapes;
            Scene::shapes_allocated = max(Scene::shapes_allocated << 1,
                                          _MAX_ASSETS_);
            Scene::shapes = new Shape*[Scene::shapes_allocated];
            memcpy(Scene::shapes,tmp,Scene::shape_index*sizeof(Shape*));
            delete[] tmp;
        }
    }

    Scene::shapes[Scene::shape_index++] = addme; //add shape
    return  addme->getID();
}

int Scene::addAsset(int shapeid, Matrix4* transformMatrix,const Bsdf* material)
{
    //complexity O(n), could be O(1), but who cares, this is done in the setup
    for(int i=0;i<Scene::shape_index;i++)
    {
        if(Scene::shapes[i]->getID() == shapeid) //found the shape
        {
            if(Scene::assets_allocated == Scene::asset_index) //array full
            {
                if (Scene::asset_index == _MAX_ASSETS_)
                    Console.warning(MESSAGE_MAXASSETNUMBER);
                else
                {
                    Asset **tmp = Scene::assets;
                    Scene::assets_allocated = max(Scene::assets_allocated << 1,
                                                  _MAX_ASSETS_);
                    Scene::assets = new Asset*[Scene::assets_allocated];
                    memcpy(Scene::assets,tmp,Scene::asset_index*sizeof(Asset*));
                    delete[] tmp;
                }


            }

            Asset* addme = new Asset(Scene::shapes[i], transformMatrix);
            if(material!=NULL)
                addme->setMaterial(material);
            Scene::assets[Scene::asset_index++] = addme;
            k.addAsset(addme); //add to kdtree
            return addme->getID();
        }
    }

    return 0; //shape not found, nothing added
}

int Scene::addLight(int shapeid, Matrix4* transform, Color c)
{
    AreaLight* addme = NULL;
    int retval = 0;

    //complexity O(n), could be O(1), but who cares, this is done in the setup
    for(int i=0;i<Scene::shape_index;i++)
    {
        if(Scene::shapes[i]->getID() == shapeid) //found the shape
        {
            if(Scene::assets_allocated == Scene::asset_index) //array full
            {
                if (Scene::asset_index == _MAX_ASSETS_)
                    Console.warning(MESSAGE_MAXASSETNUMBER);
                else
                {
                    Asset **tmp = Scene::assets;
                    Scene::assets_allocated = max(Scene::assets_allocated << 1,
                                                  _MAX_ASSETS_);
                    Scene::assets = new Asset*[Scene::assets_allocated];
                    memcpy(Scene::assets,tmp,Scene::asset_index*sizeof(Asset*));
                    delete[] tmp;
                }


            }

            addme=new AreaLight(Scene::shapes[i], transform,c);
            Scene::assets[Scene::asset_index++] = (Asset*)addme;
            k.addAsset(addme); //add to kdtree
            retval = addme->getID();
        }
    }

    if(addme!=NULL) //add the light also to the lights array
    {
        if(Scene::lights_allocated == Scene::light_index)//array full
        {
            if (Scene::light_index == _MAX_ASSETS_)
                Console.warning(MESSAGE_MAXASSETNUMBER);
            else
            {
                AreaLight **tmp = Scene::lights;
                Scene::lights_allocated = max(Scene::lights_allocated << 1,
                                              _MAX_ASSETS_);
                Scene::lights = new AreaLight*[Scene::lights_allocated];
                memcpy(Scene::lights,tmp,Scene::light_index*sizeof(AreaLight*));
                delete[] tmp;
            }
        }

        Scene::lights[Scene::light_index++] = addme;
    }

    return retval;
}

int Scene::lightSize()const
{
    return Scene::light_index;
}

const AreaLight*const* Scene::getLights()const
{
    return (const AreaLight*const*)Scene::lights;
}
