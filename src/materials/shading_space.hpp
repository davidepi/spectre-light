//Created,  22 Aug 2018
//Last Edit 22 Aug 2018

/**
 *  \file shading_space.hpp
 *  \brief Orthonormal basis used to represent the shading space
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 22 Aug 2018
 *  \copyright GNU GPLv3
 */


#ifndef __SHADING_SPACE_HPP__
#define __SHADING_SPACE_HPP__

#include "geometry/vec3.hpp"
#include "primitives/hit_point.hpp"

/**
 *  \brief Class representing the Shading space
 *
 *  The ShadingSpace class is an orthonormal basis, composed of three
 *  orthogonal unit vectors that is used to represent the shading space. This
 *  space is extensively used to simplify calculation of sin and cos in BxDF
 *  computations. The class exposes methods to tranform a vector from world
 *  space to shading space and vice versa.
 *
 *  Note that the three vector must be manually set.
 *
 *  \note This class ASSUMES the three vector are orthogonal and unit, and
 *  DOES NOT ENSURES it
 */
class ShadingSpace
{
public:

    /**
     *  \brief Default constructor
     */
    ShadingSpace() = default;

    /**
     *  \brief Initialize the ShadingSpace basis given the hit point
     *
     *  Given the result of an intersection, this method initialize the
     *  shading space by using the geometric results. This means that the
     *  shading space is not altered by any kind of texture displacement.
     *
     *  \param[in] hp The result of an intersection with a primitive
     */
    ShadingSpace(const HitPoint* hp);

    /**
     *  \brief Default destructor
     */
    ~ShadingSpace() = default;

    /**
     *  \brief Transforms a vector from shading space to world space
     *  \param[in] shading The input vector in shading space
     *  \return The vector in world space
     */
    Vec3 to_world(const Vec3& shading)const;

    /**
     *  \brief Transforms a vector from world space to shading space
     *  \param[in] world The input vector in world space
     *  \return The vector in shading space
     */
    Vec3 to_shading(const Vec3& world)const;

    /** The first vector. Usually dpdu */
    Vec3 s;

    /** The second vector. Usually calculated as a result of s and n */
    Vec3 t;

    /** The third vector. Usually the surface normal */
    Normal n;
};

#endif
