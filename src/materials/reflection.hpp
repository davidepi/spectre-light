//Created,  10 Jun 2017
//Last Edit  2 Jul 2017

/**
 *  \file reflection.hpp
 *  \brief Specular reflective BRDF
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      2 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __REFLECTION_HPP__
#define __REFLECTION_HPP__

#include "bdf.hpp"
#include "fresnel_conditions.hpp"
#include "color.hpp"
#include "vec3.hpp"

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

    /** \brief Default Constructor
     *
     * \param[in] specular The spectrum of light reflected back
     * \param[in] fc Fresnel conditions used in the object (conductor or not)
     */
    Reflection(Color specular, FresnelConditions* fc);

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
     *  \param[in] wiincident ray
     *  \return 0
     */
    Color df(const Vec3* wo, const Vec3* wi)const;

    /** \brief Returns the value of the BRDF
     *
     *  Computes the incident vector, and the value of the BRDF for the pair
     *  of rays
     *
     *  \param[in] wo The outgoing direction
     *  \param[out] wi The incident direction
     *  \return The value of the BRDF
     */
    Color df_s(const Vec3* wo, Vec3* wi)const;

private:

    //scattered light
    Color specular;

    //fresnel term
    FresnelConditions* fc;
};


#endif
