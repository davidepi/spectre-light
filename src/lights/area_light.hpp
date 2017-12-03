//Created,  13 Jun 2017
//Last Edit 26 Nov 2017

/**
 *  \file area_light.hpp
 *  \brief     Definition of a light-emitting shape
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      26 Nov 2017
 *  \copyright GNU GPLv3
 */


#ifndef __AREA_LIGHT_HPP__
#define __AREA_LIGHT_HPP__

#include "utility/spectrum.hpp"
#include "primitives/asset.hpp"
#include "primitives/shape.hpp"
#include <cmath> //isinf

/**
 * \class AreaLight area_light.hpp "lights/area_light.hpp"
 * \brief A light-emitting shape
 *
 *  This class extends an Asset in order to transform it into a light. By 
 *  passing a Color or Spectrum the shape is treated as a light emitting shape
 */
class AreaLight : public Asset
{
public:

    /** \brief Default Constructor
     *
     *  Construct an object emitting light
     *
     *  \param[in] shape A pointer to the underlying shape
     *  \param[in] objToWorld A pointer to the matrix used to transform the
     *  light from object space to world space
     *  \param[in] c The emitted light
     */
    AreaLight(Shape* shape, Matrix4* objToWorld, const Spectrum& c);
    
    ///Default destructor
    virtual ~AreaLight();

    /** \brief Return the radiance for a random ray
     *
     *  Sample a random ray from the light and return the emitted radiance
     *  originated from that point
     *
     *  \param[in] r0 A random number in the interval (0.0,1.0)
     *  \param[in] r1 A random number in the interval (0.0,1.0)
     *  \param[out] out The computed ray originating the radiance, in world
     *  space units
     *  \param[out] pdf The probability density function of the chosen point
     *  over the light
     *  \return The emitted radiance from the computed ray
     *  \sa radiance_i
     */
    Spectrum radiance_e(float r0, float r1, Ray* out, float* pdf)const;

    /** \brief Generate the incident vector and return the radiance
     *
     *  Given a point in the scene, compute the incident direction pointing
     *  towards the light and compute the radiance arriving at that point.
     *  This method assume that there are no occluding objects between the light
     *  and the point
     *
     *  \param[in] r0 A random number in the interval (0.0,1.0)
     *  \param[in] r1 A random number in the interval (0.0,1.0)
     *  \param[in] current_pos The current position of the viewer, i.e the point
     *  receiving the radiance from this light
     *  \param[out] wi The computed incident direction
     *  \param[out] pdf The probability density function of the chosen point
     *  over the light
     *  \param[out] distance The distance of the light from the position
     *  \return The emitted radiance from the computed ray
     *  \sa radiance_e
     */
    Spectrum radiance_i(float r0, float r1, const Point3* current_pos, Vec3* wi,
                     float* pdf, float* distance)const;

    /** \brief Return the light spectrum emitted
     *  \return The emitted light spectrum
     */
    Spectrum emissiveSpectrum()const;

    /** \brief Return true if this asset is a light
     *
     *  \return true
     */
    bool isLight()const;

    /** \brief Return the probability density function for this light
     *
     *  \return The pdf for this light
     *  \sa radiance_e()
     */
    float pdf()const;

    /** \brief Return the probability density function for this light
     *
     *  \param[in] p The origin point
     *  \param[in] wi The incident vector
     *  \return The pdf for this light
     *  \sa radiance_i()
     */
    float pdf(const Point3* p, const Vec3* wi)const;

    
private:
    
    //Emissive spectrum of the light
    Spectrum c;
    
    //area of the light
    float area;
    
    //inverse area of the light
    float invarea;
    
    //contains the cumulative area for every face of the underlying shape
    float* cd;
};

#endif
