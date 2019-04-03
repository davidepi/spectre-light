//Created,   7 Jun 2017
//Last Edit 11 Apr 2018

/**
 *  \file lambertian.hpp
 *  \brief     Lambertian BRDF
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      11 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __LAMBERTIAN_HPP__
#define __LAMBERTIAN_HPP__

#include "materials/bdf.hpp"

/**
 *  \class Lambertian lambertian.hpp "materials/lambertian.hpp"
 *  \brief BRDF for a perfectly diffuse smooth surface
 *
 *  The Lambertian is a BRDF that defines an ideal matte surface.
 *  For surfaces that better simulates a real world matte surface consider
 *  using the slower Oren-Nayar model defined in the OrenNayar class
 */
class Lambertian : public Bdf
{
public:

    /** \brief Default constructor
     *
     *  Generate a lambertian model with a white spectrum. This can be later
     *  mutiplied by the actual spectrum of the reflecting surface
     */
    Lambertian();

    /** \brief Return the value of the BRDF
     *
     *  Computes the value of the BRDF in the point, defining how the light is
     *  reflected or transmitted. This function returns the ratio of reflected
     *  radiance to the incident irradiance on the surface.
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wi The incident direction
     *  \return The value of the BxDF
     */
    Spectrum value(const Vec3* wo, const Vec3* wi) const override;

private:

    //scattered portion of spectrum
    const static Spectrum DIFFUSE;
};

#endif
