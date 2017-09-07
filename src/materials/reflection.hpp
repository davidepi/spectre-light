//Created,  10 Jun 2017
//Last Edit  7 Sep 2017

/**
 *  \file reflection.hpp
 *  \brief Specular reflective BRDF
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      7 Sep 2017
 *  \copyright GNU GPLv3
 */


#ifndef __REFLECTION_HPP__
#define __REFLECTION_HPP__

#include "materials/bdf.hpp"
#include "materials/fresnel_conditions.hpp"
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

    /** \brief Default Constructor for metallic material
     *
     *  \param[in] specular The spectrum of light reflected back
     *  \param[in] refraction The ior for the material. In a metallic material,
     *  index of refraction is different based on the wavelenght of light
     *  \param[in] absorption The amount of light absorbed by the material
     */
    Reflection(const Spectrum& specular, const Spectrum& refraction,
               const Spectrum& absorption, bool isMetal);

    ///Default destructor
    ~Reflection();

    /** \brief Copy the BRDF
     *
     *  Method used to copy this class
     *
     *  \warning The returned Bdf is heap allocated, and must be deallocated.
     *  Although this is really bad practice, it is the only possible
     *  implementation without using reference counting.
     *
     *  \return an heap allocated base pointer of the cloned class
     */
    Bdf* clone()const;

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
     *  \return The value of the BRDF for the pair of directions
     */
    Spectrum df_s(const Vec3 *wo, Vec3 *wi, float r0, float r1,
                  float* pdf)const;

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

private:

    //scattered light
    Spectrum specular;

    //fresnel term
    FresnelConditions* fc;
    
    //is conductor
    bool conductor;
};


#endif
