//Created,   6 May 2017
//Last Edit 10 Aug 2018

/**
 *  \file asset.hpp
 *  \brief     Wrapper of shape, texture and material
 *  \details   Containst the class that merge together a shape with its
 *             materials and textures
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      10 Aug 2018
 *  \copyright GNU GPLv3
 */


#ifndef __ASSET_HPP__
#define __ASSET_HPP__

#include "primitives/shape.hpp"
#include "materials/bdf.hpp"
#include "materials/material_library.hpp"
#include "textures/texture_image.hpp"

///Values under 128 are considered false when applying masking
#define THRESHOLD 128

/**
 *  \class Asset asset.hpp "primitives/asset.hpp"
 *  \brief A container for shapes, materials and textures
 *
 *  The asset class is a wrapper that merges a Shape, used to define the
 *  structure of the object, a Material, used to define the physical properties
 *  of the object, and a Texture.
 */
class Asset
{
public:

    /** \brief Construct an asset, given the underlying shape
     *
     *  \param[in] sp A pointer to the Shape wrapped in this class
     *  \param[in] transform The transformation matrix that will be applied to
     *  the shape
     *  \param[in] material_no The number of materials used in the Asset
     */
    Asset(const Shape* sp, const Matrix4& transform, unsigned char material_no);

    ///Default destructor
    virtual ~Asset();

    /** \brief Return the ID of this asset
     *
     *  \return A unsigned int representing the ID of this asset
     */
    unsigned int get_id() const;

    /** \brief Intersection of a Ray and this asset
     *
     *  Calls the intersection routine on the underlying shape.
     *  Check Shape::intersect
     *
     *  \param[in] ray_world A pointer to the ray used to perform the
     *  intersection
     *  \param[out] distance The distance of the point of intersection
     *  \param[out] h An HitPoint class containing information about the
     *  intersection point
     */
    bool intersect(const Ray* ray_world, float* distance, HitPoint* h) const;

    /** \brief Intersection of a Ray and the bounding box of the asset
     *
     *  Calls the intersection routine on the bounding box of this shape
     *
     *  \param[in] r A pointer to the ray used to perform the intersection
     *  \param[in] rp A pointer to the RayProperties struct, used for fast
     *                intersection
     *  \param[out] entry_point The entry point of the AABB
     *  \param[out] exit_point The exit point of the AABB
     */
    bool intersect_AABB(const Ray* r, const RayProperties* rp,
                        float* entry_point, float* exit_point) const;

    /** \brief Return a pointer to the AABB
     *
     *  Return a constant pointer to the axis aligned bounding box surrounding
     *  this asset. This AABB is in world space.
     *
     *  \return A pointer to the aabb surrounding this asset
     */
    const AABB* get_AABB() const;

    /** \brief Return true if this asset is a light
     *
     *  \return true if the asset is a light
     */
    virtual bool is_light() const;

    /** \brief Add a set of materials used by this Asset
     *
     *  More than the usage of this function it is important to understand the
     *  reason of it. In particular when considering Meshes where every triangle
     *  could have a different material. In this case:
     *  - Storing the material name for every triangle inside the Mesh and then
     *    perform a lookup in the hash map at each intersection would be too
     *    much computationally and memory expensive
     *  - Storing directly a pointer to the material inside each triangle would
     *    be too much memory expensive (8KB every 1K triangles in 64-bits
     *    systems)
     *  Moreover, both the previous solutions break instancing.
     *
     *  These problems are solved by keeping every material used in the Mesh
     *  into an array. Another array stores an unsigned char that acts as an
     *  offset of this array to find the corresponding material. With this
     *  method 1KB of data is used every 1K triangles + the actual size of the
     *  pointers (from 16 byte for a single material mesh up to 2K for mesh with
     *  255 materials)
     *
     *  This method is used to set the array of materials, and the array of
     *  associations: face_index-material
     *
     *  \warning This method does not allocate a bigger array if the index is
     *  outside the referenced area. The parser should take care of not writing
     *  outside the array bounds
     *
     *  \param[in] materials The array of materials used by this asset
     *  \param[in] material_len The length of the materials array
     *  \param[in] indexes An array where the ith entry is the offset of the
     *  materials array for the ith face
     */
    void set_materials(const Bsdf** materials, unsigned char material_len,
                       const unsigned char* indexes);

    /** \brief Return a pointer to the material
     *
     *  Return the material associated with the asset or the particular triangle
     *
     *  \param[in] ith_face The ith face of the mesh for which the material
     *  should be looked up. This can be found after performing an intersection,
     *  inside the HitPoint::index parameter
     *
     *  \return material A pointer to the material of the asset used by
     *  the face passed as parameter
     */
    const Bsdf* get_material(unsigned int ith_face) const;

    /**
     *  \brief Sets a Mask for this asset
     *
     *  Sets the Mask that will be used during rendering. The Mask is used to
     *  possibly invalidate a correct intersection
     *
     *  \param[in] m The mask that will be set
     */
    void set_mask(Mask m);

protected:

    ///Underlying model
    const Shape* model;

    ///ObjToWorld matrix
    Matrix4 objToWorld;

    ///WorldToObj matrix
    Matrix4 worldToObj;

private:

    //id of the asset
    const unsigned int id;

    //Bounding box
    AABB aabb;

    //Materials
    const Bsdf** materials;

    //index associating every face to every material
    unsigned char* materials_index;

    //mask used during intersections
    Mask mask;

};

#endif
