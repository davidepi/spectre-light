//Created,   7 Jun 2017
//Last Edit  1 Jul 2017

/**
 *  \file lambertian.hpp
 *  \brief     Lambertian BRDF
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      1 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __LAMBERTIAN_HPP__
#define __LAMBERTIAN_HPP__

#include "settings.h"
#include "materials/bdf.hpp"
#include "utility/spectrum.hpp"
#include "geometry/vec3.hpp"
#include "utility/console.hpp"

/**
 *  \class Lambertian lambertian.hpp "materials/lambertian.hpp"
 *  \brief BRDF for a perfectly diffuse smooth surface
 *
 *  The Lambertian is a BRDF that defines an ideal matte surface.
 *  For surfaces that reflects better a real world matter surface consider
 *  using the slower Oren-Nayar model defined in the OrenNayar class
 */
class Lambertian : public Bdf
{
public:

    /** \brief Default constructor
     *
     *  Generate a lambertian model with the given color
     *
     *  \param[in] scattered_spectrum The portion of light scattered by the BRDF
     */
    Lambertian(const Spectrum& scattered_spectrum);

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
    Spectrum value(const Vec3* wo, const Vec3* wi)const;

private:

    //scattered portion of spectrum
    const Spectrum diffuse;
};

#endif
