
//Created,   16 Jun 2017
//Last Edit  11 Apr 2018

/**
 *  \file bdf.hpp
 *  \brief     Contains Bdf and Bsdf classes
 *  \details   Basic classes for material definitions
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      11 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __BDF_HPP__
#define __BDF_HPP__

#include "primitives/shape.hpp"
#include "utility/spectrum.hpp"
#include "geometry/vec3.hpp"
#include "utility/console.hpp"
#include "textures/texture.hpp"
#include "textures/texture_library.hpp"
#include <cstring> //error msg
#include <cstdlib> //malloc error msg

#define FLAG_BRDF 0x1
#define FLAG_BTDF 0x2
#define FLAG_SPEC 0x4

/**
 *  \class Bdf bdf.hpp "materials/bdf.hpp"
 *  \brief Component of the Bsdf class
 *
 *  The bdf class can represent either a BRDF or a BTDF. It is a fundamental
 *  component of the Bsdf class, describing how the light is reflected at a
 *  surface.
 *  Note that every Bdf produces a Greyscale spectrum. Then the Bsdf class is
 *  responsible of chosing the right texture to module the results of Bdfs
 */
class Bdf
{
public:

    /** \brief Default constructor
     *
     *  \param[in] flags The flags of the Bdf, used to distinguish between BRDF
     *  or BTDF
     */
    Bdf(char flags);

    ///Default destructor
    virtual ~Bdf() = default;

    /** \brief Return the value of the Bdf
     *
     *  Compute the value of the Bdf in the point, defining how the light is
     *  reflected or transmitted. This function returns the ratio of reflected
     *  radiance to the incident irradiance on the surface.
     *
     *  \param[in] woS The outgoing direction, in shading space
     *  \param[in] wiS The incident direction, in shading space
     *  \return The value of the BxDF
     *  \sa sample_value(const Vec3* woS, Vec3* wiS)const
     */
    virtual Spectrum value(const Vec3* woS, const Vec3* wiS) const = 0;

    /** \brief Return the value of the Bdf
     *
     *  This method is like the value one, but it first samples a direction
     *  using importance sampling. Then the value is computed exactly like the
     *  other method. The sampled direction is the incident one.
     *
     *  The default implementation of this method samples randomly on the
     *  hemisphere of the normal
     *
     *  \param[in] woS The outgoing direction, in shading space
     *  \param[out] wiS The incident direction, in shading space
     *  \param[in] r0 A random float in the interval (0.0,1.0)
     *  \param[in] r1 A random float in the interval (0.0,1.0)
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere
     *  \return The value of the Bdf for the pair of direction
     *  \sa value(const Vec3* woS, const Vec3* wiS)const
     */
    virtual Spectrum
    sample_value(const Vec3* woS, Vec3* wiS, float r0, float r1,
                 float* pdf) const;

    /** \brief Return the probability density function for this bdf
     *
     *  Given a pair of vectors, return the pdf value for these directions
     *
     *  \param[in] woS The outgoing direction, in shading space
     *  \param[in] wiS The incident direction, in shading space
     *  \return The pdf for this set of values
     */
    virtual float pdf(const Vec3* woS, const Vec3* wiS) const;

    ///Return true if the flags of this Bdf are a subset of the input ones
    inline bool matches(char flags) const
    {
        return (type & flags) == type;
    }

    ///Return true if the Bdf is a BRDF
    inline bool is_BRDF() const
    {
        return type & FLAG_BRDF;
    }

    ///Return true if the Bdf is a BTDF
    inline bool is_BTDF() const
    {
        return type & FLAG_BTDF;
    }

    ///Return true if the Bdf is specular
    inline bool is_specular() const
    {
        return type & FLAG_SPEC;
    }

    /** \brief Returns the flags associated with this Bdf
     *
     *  \return The flags representing the type of Bdf
     */
    char get_flags() const;

private:

    //the type of the bdf
    char type;
};

#endif

