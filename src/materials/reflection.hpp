//Created,  10 Jun 2017
//Last Edit 15 Sep 2017

/**
 *  \file reflection.hpp
 *  \brief Specular reflective BRDF
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      15 Sep 2017
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
     *  \param[in] specular The spectrum of light reflected back
     */
    explicit Reflection(const Spectrum& specular);

    /** \brief NOOP
     *
     *  Since specular reflection exhist only for a single pair of ray, the
     *  BRDF follows a delta distribution, and this function returns always 0
     *
     *  \param[in] wo outgoing ray
     *  \param[in] wi incident ray
     *  \return 0
     */
    Spectrum df(const Vec3* wo, const Vec3* wi)const;

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
     *  \param[in,out] choose Used for the dispersion to choose the wavelength
     *  sample
     *  \return The value of the BRDF for the pair of directions
     */
    virtual Spectrum df_s(const Vec3 *wo, Vec3 *wi, float r0, float r1,
                  float* pdf, char* chosen)const = 0;

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
    float pdf(const Vec3* wo, const Vec3* wi)const;

protected:

    //scattered light
    Spectrum specular;
};

class ConductorReflection : public Reflection
{
public:
    
    /** \brief Default Constructor for metallic material
     *
     *  \param[in] specular The spectrum of light reflected back
     *  \param[in] refraction The index of refraction of the material if isMetal
     *  is true. The incident index of refraction otherwise.
     *  \param[in] absorption The amount of light absorbed by the material if
     */
    ConductorReflection(const Spectrum& specular, const Spectrum& refraction,
                        const Spectrum& absorption);
    
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
     *  \param[in,out] choose Used for the dispersion to choose the wavelength
     *  sample
     *  \return The value of the BRDF for the pair of directions
     */
    Spectrum df_s(const Vec3 *wo, Vec3 *wi, float r0, float r1,
                  float* pdf, char* chosen)const;
private:
    Spectrum fresnel;
    Spectrum ior;
};

class DielectricReflection : public Reflection
{
public:
    /** \brief Default Constructor for dielectric material
     *
     *  \param[in] specular The spectrum of light reflected back
     *  \param[in] ior_i The incident index of refraction
     *  \param[in] ior_t The transmitted index of refraction
     */
    DielectricReflection(const Spectrum& specular, const Spectrum& ior_i,
                         const Spectrum& ior_t);
    
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
     *  \param[in,out] choose Used for the dispersion to choose the wavelength
     *  sample
     *  \return The value of the BRDF for the pair of directions
     */
    Spectrum df_s(const Vec3 *wo, Vec3 *wi, float r0, float r1,
                  float* pdf, char* choose)const;
private:
#ifdef DISPERSION
    Spectrum eta_i;
    Spectrum eta_t;
#else
    float eta_i;
    float eta_t;
#endif
};

#endif
