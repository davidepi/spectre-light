#include "scene.hpp"

Scene::Scene()
{
    Scene::shapes_allocated = 1;
    Scene::assets_allocated = 1;
    Scene::shape_index = 0;
    Scene::asset_index = 0;
    Scene::shapes = new Shape*[Scene::shapes_allocated];
    Scene::assets = new Asset*[Scene::shapes_allocated];
}

Scene::~Scene()
{
    for(int i=0;i<shapes_allocated;i++)
        delete Scene::shapes[i];
    delete[] Scene::shapes;

    for(int i=0;i<assets_allocated;i++)
        delete Scene::assets[i];
    delete[] Scene::assets;
}

void Scene::inheritShape(Shape *addme)
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
}

bool Scene::addAsset(int shapeid, Matrix4* transformMatrix)
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

            Scene::assets[Scene::asset_index++]= new Asset(Scene::shapes[i],
                                                           transformMatrix);
            k.addAsset(Scene::assets[Scene::asset_index-1]); //add to kdtree
            return true;
        }
    }

    return false; //shape not found, nothing added
}