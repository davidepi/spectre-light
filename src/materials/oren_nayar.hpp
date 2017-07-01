//Created,   9 Jun 2017
//Last Edit  1 Jul 2017

/**
 *  \file oren_nayar.hpp
 *  \brief     Oren-Nayar microfacet BRDF
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      1 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __OREN_NAYAR_HPP__
#define __OREN_NAYAR_HPP__


#include "bdf.hpp"
#include "color.hpp"
#include "vec3.hpp"

/**
 *  \class OrenNayar oren_nayar.hpp "materials/oren_nayar.hpp"
 *  \brief Component of the Bsdf class
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
     *  \param[in] diffuse The scattered portion of light
     *  \param[in] sigma The value of roughness, where 0 is equal to the
     *  Lambertian model
     */
    OrenNayar(Color diffuse, float sigma);

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

    //Scattered portion of light
    Color diffuse;

    //Pre-computed A term
    float A;

    //Pre-computed B term
    float B;
};


#endif
