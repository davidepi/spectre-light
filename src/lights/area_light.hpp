//Created,  13 Jun 2017
//Last Edit  9 Jul 2017

/**
 *  \file area_light.hpp
 *  \brief     Definition of a light-emitting shape
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      9 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __AREA_LIGHT_HPP__
#define __AREA_LIGHT_HPP__

#include "color.hpp"
#include "asset.hpp"
#include "shape.hpp"

/**
 * \class AreaLight area_light.hpp "lights/area_light.hpp"
 * \brief A light-emitting shape
 *
 *  This class extends an Asset in order to transform it into a light. By 
 *  passing a Color the shape is treated as a light emitting shape
 */
class AreaLight : public Asset
{
public:

    /** \brief Default Constructor
     *
     *  Construct an object emitting light
     *
     *  \param[in] sp A pointer to the underlying shape
     *  \param[in] objToWorld A pointer to the matrix used to transform the
     *  light from object space to world space
     * \param[in] c The emitted light
     */
    AreaLight(Shape* sp, Matrix4* objToWorld, Color c);

    /** \brief Return the random radiance for a ray
     *
     *  Sample a random ray from the light and return the emitted radiance
     *  originated from that point
     *
     * \param[in] r0 A random number in the interval (0.0,1.0)
     * \param[in] r1 A random number in the interval (0.0,1.0)
     * \param[in] r2 A random number in the interval (0.0,1.0)
     * \param[in] r3 A random number in the interval (0.0,1.0)
     * \param[in] current_pos The current position of the viewer, i.e. the point
     * receiving the radiance from this light
     * \param[out] out The computed ray originating the radiance
     * \return The emitted radiance from the computed ray
     */
    Color radiance(float r0, float r1, float r2, float r3,
                   const Point3* current_pos, Ray* out)const;

    /** \brief Return the total emissive power over the surface
     * \return Emissive power over the surface, given constant radiance
     */
    Color emissivePower()const;
    
private:

    Color c;
    float area;
};

#endif
