//Created,  23 Sep 2017
//Last Edit 26 Sep 2017

/**
 *  \file microfacet.hpp
 *  \brief Microfacet models
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date  26 Sep 2017
 *  \copyright GNU GPLv3
 */


#ifndef __MICROFACET_HPP__
#define __MICROFACET_HPP__

#include "materials/bdf.hpp"
#include "materials/microfacet_distributions.hpp"
#include "materials/fresnel_conditions.hpp"
#include "utility/spectrum.hpp"

/**
 *  \class MicrofacetR microfacet.hpp
 *  \brief Represent a class composed by reflective microfacets
 *
 *  The microfacetR class assumes that every microfacet composing the surface
 *  is made of a perfectly specular material. The values values passed to the
 *  constructor are used to tune the distribution of these microfacets and
 *  give different specular results. The underlying model is the Cook-Torrance
 *  one.
 */
class MicrofacetR : public Bdf
{
public:
    
    /** \brief Default constructor
     *
     *  \param[in] spe The reflected spectrum
     *  \param[in] f The fresnel term (Dielectric or Conductor) of this material
     *  \param[in] md The class used to know how the microfacets are distributed
     */
    MicrofacetR(Spectrum& spe, Fresnel* f, MicrofacetDist* md);
    
    ///Default destructor
    ~MicrofacetR();
    
    /** \brief Return the value of the Bdf
     *
     *  Computes the value of the Bdf in the point, defining how the light is
     *  reflected or transmitted. This function returns the ratio of reflected
     *  radiance to the incident irradiance on the surface.
     *
     *  \param[in] woS The outgoing direction, in shading space
     *  \param[in] wiS The incident direction, in shading space
     *  \return The value of the BxDF
     */
    Spectrum df(const Vec3* woS, const Vec3* wiS)const;
    
    /** \brief Returns the value of the BRDF
     *
     *  Computes the transmitted vector, and the value of the BRDF for the pair
     *  of rays
     *
     *  \param[in] woS The outgoing direction
     *  \param[out] wiS The incident direction
     *  \param[in] r0 A random float in the interval [0.0,1.0] used to sample
     *  the wi direction
     *  \param[in] r1 A random float in the interval [0.0,1.0] used to smaple
     *  the wi direction
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere
     *  \return The value of the BRDF
     */
    Spectrum df_s(const Vec3* woS, Vec3* wiS, float r0, float r1,
                  float* pdf, char* choose)const;
    
    /** \brief Return the probability density function for this BRDF
     *
     *  Given a pair of vectors, return the pdf value for these directions. In
     *  other words the probability that another random sample will be equal to
     *  this one
     *
     *  \param[in] woS The outgoing direction, in shading space
     *  \param[in] wiS The incident direction, in shading space
     *  \return The pdf for this set of values
     */
    float pdf(const Vec3* woS, const Vec3* wiS)const;
    
    
    
private:
    
    //fresnel term
    Fresnel* f;
    
    //microfacet distribution
    MicrofacetDist* md;
    
    //reflected spectrum
    Spectrum specular;
};

#endif
