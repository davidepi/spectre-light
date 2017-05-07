//Created,   6 May 2017
//Last Edit  6 May 2017

/**
 *  \file asset.hpp
 *  \brief     Wrapper of shape, texture and material
 *  \details   Containst the class that merge toghether a shape with its
 *             materials and textures
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      6 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __ASSET_HPP__
#define __ASSET_HPP__

#include "shape.hpp"

/**
 *  \class Asset asset.hpp "primitives/asset.hpp"
 *  \brief A container for shapes, materials and textures
 *
 *  The asset class is a wrapper that merge a Shape, used to define the
 *  structure of the object, a Material, used to define the physical properties
 *  of the object, and a Texture.
 */
class Asset
{
public:
    
    /** \brief Construct an asset, given the underlying shape
     *
     *  \param[in] sp A pointer to the Shape wrapped in this class
     */
    Asset(Shape* sp);
    
    ///Default destructor
    ~Asset();
    
    /** \brief Return the ID of this asset
     *  \return A unsigned int representing the ID of this asset
     */
    unsigned int getID();
    
    /** \brief Intersection of a Ray and this asset
     *
     *  Calls the intersection routine on the underlying shape.
     *  Check Shape::intersect
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[out] distance The distance of the point of intersection
     *  \param[out] error The maximum floating point error in the computation
     */
    bool intersect(const Ray* r,float* distance,float* error)const;
    
private:
    //underlying model
    Shape* model;
    //id of the asset
    const unsigned int id;
    //Material
    //Texture
};

#endif
