//Created,   9 Jun 2017
//Last Edit 11 Apr 2018

/**
 *  \file oren_nayar.hpp
 *  \brief     Oren-Nayar microfacet BRDF
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      11 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __OREN_NAYAR_HPP__
#define __OREN_NAYAR_HPP__

#include "materials/bdf.hpp"


/**
 *  \class OrenNayar oren_nayar.hpp "materials/oren_nayar.hpp"
 *  \brief BRDF for a perfectly diffuse rough surface
 *
 *  The Oren-Nayar model is a BRDF that defines a diffuse surface.
 *  In constrast to the Lambertian model, this one is able to weight the
 *  roughness of a surface.
 */
class OrenNayar : public Bdf
{
public:

    /** \brief Default constructor
     *
     *  Construct an Oren-Nayar distribution with the given colour and roughness
     *
     *  \param[in] sigma The value of roughness, where 0 is equal to the
     *  Lambertian model
     */
    OrenNayar(float sigma);

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

    const static Spectrum DIFFUSE;

    //Pre-computed A term
    float A;

    //Pre-computed B term
    float B;
};


#endif

