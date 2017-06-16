//Created,   6 May 2017
//Last Edit 15 Jun 2017

/**
 *  \file asset.hpp
 *  \brief     Wrapper of shape, texture and material
 *  \details   Containst the class that merge toghether a shape with its
 *             materials and textures
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      15 Jun 2017
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
    Asset(Shape* sp, Matrix4* transform);
    
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
     *  \param[out] h an HitPoint class containing information about the
     *  intersection point
     */
    bool intersect(const Ray* r,float* distance, HitPoint* h)const;
    
    /** \brief Intersection of a Ray and the bounding box of the asset
     *
     *  Calls the intersection routine on the bounding box of this shape
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[in] rp A pointer to the RayProperties struct, used for fast
     *                intersection
     *  \param[out] p1 The entry point of the AABB
     *  \param[out] p2 The exit point of the AABB
     */
    bool intersectFast(const Ray* r, const RayProperties* rp,
                       float* p1, float* p2)const;
    
    /** \brief Return a pointer to the AABB
     *
     *  Return a constant pointer to the axis aligned bounding box surrounding
     *  this asset
     *
     *  \return A pointer to the aabb surrounding this asset
     */
    const AABB* getAABB() const;
    
private:
    //underlying model
    Shape* model;

    //id of the asset
    const unsigned int id;

    //Bounding box
    AABB aabb;

    //Transformation
    Matrix4* transform;

    //Inverse transformation
    Matrix4 invTrans;

    //Material
    //Texture
};

#endif
