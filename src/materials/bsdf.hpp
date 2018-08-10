//Created,   16 Jun 2017
//Last Edit  11 Apr 2018

/**
 *  \file bdf.hpp
 *  \brief     Contains Bsdf class
 *  \details   Material interface
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      11 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __BSDF_HPP__
#define __BSDF_HPP__

#include "utility/spectrum.hpp"
#include "geometry/vec3.hpp"
#include "utility/console.hpp"
#include "textures/texture.hpp"
#include "textures/texture_library.hpp"
#include <cstring> //error msg
#include <cstdlib> //malloc error msg

/**
 *  \class Bsdf bdf.hpp "materials/bdf.hpp"
 *  \brief Interface used to define a material
 *
 *  The BSDF defines how the light scatters on a surface. This class exposes
 *  some method useful to know how a light ray behaves in world space and the
 *  actual spectrum returned by the interaction with a surface.
 *
 *  A BSDF is actually the definition of a material.
 *  However, this class is just an interface. The MultiBSDF class wraps
 *  together these methods with the actual underlying components of the
 *  material (BRDFs and BTDFs)
 */
class Bsdf
{
public:

    ///Default destructor
    virtual ~Bsdf() = default;

    /** \brief Return the value of the BSDF
     *
     *  Computes the value of the Bsdf in the point, defining how the light is
     *  reflected or transmitted. This function returns the ratio of reflected
     *  radiance to the incident irradiance on the surface. This value is
     *  determined by the BRDFs and BTDFs encompassed in the BSDF
     *
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[in] wiW The incident direction, in world space
     *  \param[in] matchSpec True if specular Bdfs should be considered
     *  \return The value of the BSDF
     */
    virtual Spectrum value(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                           bool matchSpec) const = 0;

    /** \brief Return the value of the BSDF
     *
     *  Similar to the value method, this one sample a single direction and
     *  returns the light reflected or transmitted in that direction. The random
     *  incident ray is updated in the \p wi member
     *
     *  \param[in] r0 A random float in the interval (0.0,1.0)
     *  \param[in] r1 A random float in the interval (0.0,1.0)
     *  \param[in] r2 A random float in the interval (0.0,1.0)
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[out] wiW The incident direction, in world space
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere
     *  \param[in] matchSpec True if the method should match specular Bdfs
     *  \param[out] matchedSpec True if the method matched a specular Bdf
     *  \return A sampled value of the BSDF
     */
    virtual Spectrum sample_value(float r0, float r1, float r2, const Vec3* woW,
                                  const HitPoint* h, Vec3* wiW, float* pdf,
                                  bool matchSpec, bool* matchedSpec) const = 0;

    /** \brief Return the probability density function for this bsdf
     *
     *  Given a pair of vectors, return the pdf value for these directions.
     *
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[in] wiW The incident direction, in world space
     *  \param[in] matchSpec True if the method should match specular Bdfs
     *  \return The pdf for this set of values
     */
    virtual float pdf(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                      bool matchSpec) const = 0;
};

#endif
