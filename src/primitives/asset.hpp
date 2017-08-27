//Created,   6 May 2017
//Last Edit 28 Jul 2017

/**
 *  \file asset.hpp
 *  \brief     Wrapper of shape, texture and material
 *  \details   Containst the class that merge toghether a shape with its
 *             materials and textures
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      28 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __ASSET_HPP__
#define __ASSET_HPP__

#include "primitives/shape.hpp"
#include "materials/bdf.hpp"
#include "materials/material_library.hpp"

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
    virtual ~Asset();
    
    /** \brief Return the ID of this asset
     *  \return A unsigned int representing the ID of this asset
     */
    unsigned int getID()const;
    
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

    /** \brief Set the material for the current asset
     *
     *  Set the material for the current asset. Note that the pointer will not
     *  be owned by the asset
     *
     *  \param[in] material The pointer of the material that will be associated
     *  with the current asset
     */
    void setMaterial(const Bsdf* material);

    /** \brief Return a pointer to the material
     *
     *  Return the material associated with the asset
     *
     *  \return material A pointer to the material of the asset
     */
    const Bsdf* getMaterial()const;

    /** \brief Return true if this asset is a light
     *
     *  \return true if the asset is a light
     */
    virtual bool isLight()const;
    
protected:

    //underlying model
    Shape* model;

    //ObjToWorld matrix
    Matrix4* objToWorld;

    //WorldToObj matrix
    Matrix4 worldToObj;

private:

    //id of the asset
    const unsigned int id;

    //Bounding box
    AABB aabb;

    //Material
    const Bsdf* material;

    //Texture
};

#endif
