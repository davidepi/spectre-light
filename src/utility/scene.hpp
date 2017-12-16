//Created,  29 Jun 2017
//Last Edit 16 Dec 2017

/**
 *  \file scene.hpp
 *  \brief     Class enclosing a scene
 *  \details   Agglomerate of Assets composing a scene, and the kdtree to
 *             intersect them
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      16 Dec 2017
 *  \copyright GNU GPLv3
 */


#ifndef __SCENE_HPP__
#define __SCENE_HPP__

#include "accelerators/kdtree.hpp"
#include "primitives/asset.hpp"
#include "geometry/matrix4.hpp"
#include "utility/utility.hpp"
#include "utility/console.hpp"
#include "lights/area_light.hpp"

/**
 *  \class Scene scene.hpp "utility/scene.hpp"
 *  \brief Implementation of a collection of shapes
 *
 *  The scene class is a collection of shapes representing the scene that will
 *  be rendered. This is composed by Asset classes and a KdTree class used for
 *  fast intersection.
 *
 *
 *  \warning The scene class is responsible for the lifecycle of the shapes and
 *  assets inside it, so the shapes added with the Scene::inheritShape() are
 *  INHERITED and therefore MUST NOT be deallocated manually
 */
class Scene
{
public:

    ///Default constructor
    Scene();

    ///Default destructor
    ~Scene();

    ///Preserve rule of three
    Scene& operator=(Scene const&) = delete;

    ///Preserve rule of three
    Scene(Scene const&) = delete;

    ///The KdTree used to perform fast intersections on the scene
    KdTree k;

    /** \brief Add a Shape to the scene
     *
     *  Given a pointer to a shape, the scene inherits its ownership and use it
     *  for subsequent addAsset calls
     *
     *  \param[in] addme The shape that will be added to the Scene
     *  \return The added shape id
     */
    int inheritShape(Shape* addme);

    /** \brief Given a shape id and a matrix, create an asset with those
     *
     *  \param[in] shapeid The id of the shape, already inherited by the scene
     *  \param[in] transform The transform matrix for the asset
     *  \param[in] material The material for the asset. If NULL the material
     *  will remain the default one
     *  \return the added assets id. 0 if nothing was added
     */
    unsigned int addAsset(unsigned int shapeid, const Matrix4& transform,
                          const Bsdf* material = NULL);

    /** \brief Given a shapeid and a matrix, create a light with those
     *
     *  \param[in] shapeid The id of the shape, already inherited by the scene
     *  \param[in] transform The transform matrix for the light
     *  \param[in] c The emissive spectrum of the light
     *  \return the added light id. Since a light is essentially an asset, this
     *  is an asset id. 0 if nothing was added
     */
    unsigned int addLight(unsigned int shapeid, const Matrix4& transform,
                          const Spectrum& c);

    /** \brief Return the number of lights in the scene
     * \return The number of lights in the scene
     */
    int lightSize()const;

    /** \brief  Return the array of lights in the scene
     * \return The array of lights in the scene
     */
    const AreaLight* const* getLights()const;

private:

    //Array of shape pointers
    Shape** shapes;

    //size of shape pointers array
    int shapes_allocated;

    //next insertion index in the shape pointers array
    int shape_index;

    //Array of asset pointers
    Asset** assets;

    //size of asset pointers array
    int assets_allocated;

    //next insertion index in the asset pointers array
    int asset_index;

    //Array of light pointers
    AreaLight** lights;

    //size of light pointers array
    int lights_allocated;

    //next insertion index in the asset pointers array
    int light_index;

};


#endif
