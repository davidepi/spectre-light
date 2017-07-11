//Created,   7 Jun 2017
//Last Edit  1 Jul 2017

/**
 *  \file lambertian.hpp
 *  \brief     Lambertian BRDF
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      1 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __LAMBERTIAN_HPP__
#define __LAMBERTIAN_HPP__

#include "settings.h"
#include "materials/bdf.hpp"
#include "utility/color.hpp"
#include "geometry/vec3.hpp"
#include "utility/console.hpp"

/**
 *  \class Lambertian lambertian.hpp "materials/lambertian.hpp"
 *  \brief BRDF for a perfectly diffuse smooth surface
 *
 *  The Lambertian is a BRDF that defines an ideal matte surface, with very 
 *  subtle roughness. For surfaces with a more pronounced roughness, consider 
 *  using the Oren-Nayar model defined in the OrenNayar class
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
    Lambertian(Color scattered_spectrum);

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
    Color df(const Vec3* wo, const Vec3* wi)const;

private:

    //scattered portion of spectrum
    Color diffuse;
};

#endif
