//Created,  10 Jun 2017
//Last Edit 11 Apr 2018

/**
 *  \file reflection.hpp
 *  \brief Specular reflective BRDF
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      11 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __REFLECTION_HPP__
#define __REFLECTION_HPP__

#include "materials/bdf.hpp"
#include "utility/color.hpp"
#include "utility/spectrum.hpp"
#include "geometry/vec3.hpp"

/**
 *  \class Reflection reflection.hpp "materials/reflection.hpp"
 *  \brief BRDF for a smooth mirror-like reflection
 *
 *  The Reflection class is a BRDF that models a smooth surface, exhibiting
 *  specular, mirror-like reflection.
 *  To exhibit such an effect, every light beam is reflected with the same
 *  angle
 */
class Reflection : public Bdf
{
public:

    /** \brief Default Constructor for perfectly specular reflective material
     *
     */
    explicit Reflection();

    /** \brief NOOP
     *
     *  Since specular reflection exhist only for a single pair of ray, the
     *  BRDF follows a delta distribution, and this function returns always 0
     *
     *  \param[in] wo outgoing ray
     *  \param[in] wi incident ray
     *  \return 0
     */
    Spectrum value(const Vec3* wo, const Vec3* wi) const;

    /** \brief Returns the value of the BRDF
     *
     *  Computes the incident vector, and the value of the BRDF for the pair
     *  of rays
     *
     *  \param[in] wo The outgoing direction
     *  \param[out] wi The incident direction
     *  \param[in] r0 A random float in the interval (0.0,1.0) UNUSED
     *  \param[in] r1 A random float in the interval (0.0,1.0) UNUSED
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere. This is a delta distribution, but this method
     *  generates the only possible pair of directions, so the pdf is 1.0
     *  \return The value of the BRDF for the pair of directions
     */
    virtual Spectrum sample_value(const Vec3* wo, Vec3* wi, float r0, float r1,
                                  float* pdf) const = 0;

    /** \brief Return the probability density function for this bdf
     *
     *  Given a pair of vectors, return the pdf value for these directions. In
     *  other words the probability that another random sample will be equal to
     *  this one. Since this is a delta distribution, given a random pair of
     *  directions, the probability of obtaining these directions is 0
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wi The incident direction
     *  \return 0
     */
    float pdf(const Vec3* wo, const Vec3* wi) const;
};

/**
 *  \class ConductorReflection reflection.hpp "materials/reflection.hpp"
 *  \brief BRDF for a smooth mirror-like reflection
 *
 *  Reflection class used when the reflecting surface is a conductor. Avoids
 *  allocating a Conductor class by embedding everything into a single method
 */
class ConductorReflection : public Reflection
{
public:

    /** \brief Default Constructor for metallic material
     *
     *  \param[in] refraction The index of refraction of the material if isMetal
     *  is true. The incident index of refraction otherwise.
     *  \param[in] absorption The amount of light absorbed by the material if
     */
    ConductorReflection(const Spectrum& refraction, const Spectrum& absorption);

    /** \brief Returns the value of the BRDF
     *
     *  Computes the incident vector, and the value of the BRDF for the pair
     *  of rays
     *
     *  \param[in] wo The outgoing direction
     *  \param[out] wi The incident direction
     *  \param[in] r0 A random float in the interval (0.0,1.0) UNUSED
     *  \param[in] r1 A random float in the interval (0.0,1.0) UNUSED
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere. This is a delta distribution, but this method
     *  generates the only possible pair of directions, so the pdf is 1.0
     *  \return The value of the BRDF for the pair of directions
     */
    Spectrum sample_value(const Vec3* wo, Vec3* wi, float r0, float r1,
                          float* pdf) const;

private:
    const Spectrum ior;
    const Spectrum fresnel;
};

/**
 *  \class DielectricReflection reflection.hpp "materials/reflection.hpp"
 *  \brief BRDF for a smooth mirror-like reflection
 *
 *  Reflection class used when the reflecting surface is a dielectric. Avoids
 *  allocating a Dielectric class by embedding everything into a single method
 */
class DielectricReflection : public Reflection
{
public:
    /** \brief Default Constructor for dielectric material
     *
     *  \param[in] ior_i The incident index of refraction
     *  \param[in] ior_t The transmitted index of refraction
     */
    DielectricReflection(const Spectrum& ior_i, const Spectrum& ior_t);

    /** \brief Returns the value of the BRDF
     *
     *  Computes the incident vector, and the value of the BRDF for the pair
     *  of rays
     *
     *  \param[in] wo The outgoing direction
     *  \param[out] wi The incident direction
     *  \param[in] r0 A random float in the interval (0.0,1.0) UNUSED
     *  \param[in] r1 A random float in the interval (0.0,1.0) UNUSED
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere. This is a delta distribution, but this method
     *  generates the only possible pair of directions, so the pdf is 1.0
     *  \return The value of the BRDF for the pair of directions
     */
    Spectrum sample_value(const Vec3* wo, Vec3* wi, float r0, float r1,
                          float* pdf) const;

private:
    float eta_i;
    float eta_t;
};

#endif

