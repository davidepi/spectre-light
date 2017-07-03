//Created,  10 Jun 2017
//Last Edit  2 Jul 2017

/**
 *  \file refraction.hpp
 *  \brief Implementation of a BTDF
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      2 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __REFRACTION_HPP__
#define __REFRACTION_HPP__

#include "bdf.hpp"
#include "color.hpp"
#include "vec3.hpp"
#include "fresnel_conditions.hpp"

/**
 *  \class Refraction refraction.hpp "materials/refraction.hpp"
 *  \brief BTDF for a smooth surface
 *
 *  The Refraction class is a BTDF that models a smooth surface. This class is
 *  used to calculate the transmission of light inside an object
 */
class Refraction : public Bdf
{
public:

    /** \brief Default constructor
     *
     *  \param[in] specular Scale factor for transmitted light
     *  \param[in] eta_incident Refraction index for the incident material
     *  \param[in] eta_transmitted Refraction index for the transmitted material
     */
    Refraction(Color specular, float eta_incident, float eta_transmitted);

    /** \brief Copy the BTDF
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
     *  Refraction follows a delta distribution, so  this function returns
     *  always 0
     *
     *  \param[in] wo outgoing ray
     *  \param[in] wi incident ray
     *  \return 0
     */
    Color df(const Vec3* wo, const Vec3* wi)const;

    /** \brief Returns the value of the BTDF
     *
     *  Computes the transmitted vector, and the value of the BTDF for the pair
     *  of rays
     *
     *  \param[in] wi The incident ray
     *  \param[out] wt The transmitted ray
     *  \return The value of the BTDF
     */
    Color df_s(const Vec3* wi, Vec3* wt)const;

private:

    //scale factor
    Color specular;

    //incident ior
    float eta_i;

    //transmitted ior
    float eta_t;

    //fresnel term
    Dielectric d;
};

#endif
