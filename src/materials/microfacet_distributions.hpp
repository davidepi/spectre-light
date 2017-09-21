//Created,  20 Sep 2017
//Last Edit 22 Sep 2017

/**
 *  \file microfacet_distributions.hpp
 *  \brief Microfacet models and distributions
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date  22 Sep 2017
 *  \copyright GNU GPLv3
 */


#ifndef __MICROFACET_HPP__
#define __MICROFACET_HPP__

#include "geometry/vec3.hpp"
#include <cmath>

/**
 *  \class MicrofacetDist microfacet_distributions.hpp
 *  \brief Interface used to represent microfacet distributions
 *
 *  The microfacet class provides a single method called \a d, that is used to
 *  compute the value of the microfacet distribution for a given half vector.
 *  This can be used in model such as the Cook-Torrance one
 */
class MicrofacetDist
{
public:
    
    ///Default constructor
    MicrofacetDist() = default;
    
    ///Default destructor
    virtual ~MicrofacetDist() = default;
    
    /** \brief The distribution term
     *
     *  Following the Torrance-Sparrow model and notation, this function 
     *  computes the value corresponding to the Distribution term of the
     *  equation. This indicates how microfacet values are distributed around
     *  the input vector
     *
     *  \param[in] h The half vector between light and view directions. The half
     *  vector is the vector laying exaclty in the middle between light and view
     *  vectors
     */
    virtual float d(const Vec3* h)const = 0;
};

/**
 *  \class Blinn microfacet_distributions.hpp
 *  \brief Blinn microfacet model
 *
 *  This microfacet distribution approximate the orientation of the microfacets
 *  with an exponential falloff passed to the constructor. The most common
 *  orientation is the one following the normal direction falling off following
 *  the exponent.
 *  Prefer Beckmann distribution over this one, this is left only as Legacy
 *
 *  This model represents an isotropic BRDF
 */
class Blinn : public MicrofacetDist
{
public:
    
    /** Default constructor
     *  
     *  \param[in] exponent Exponential falloff of the blinn microfacet model
     */
    Blinn(float exponent);
    
    ///Default destructor
    ~Blinn() = default;
    
    /** \brief The distribution term
     *
     *  Following the Torrance-Sparrow model and notation, this function
     *  computes the value corresponding to the Distribution term of the
     *  equation. This indicates how microfacet values are distributed around
     *  the input vector
     *
     *  \param[in] h The half vector between light and view directions. The half
     *  vector is the vector laying exaclty in the middle between light and view
     *  vectors
     */
    float d(const Vec3* h)const;
    
private:
    
    //exponent for the specular highlight
    float exponent;
};

/**
 *  \class Anisotropic microfacet_distributions.hpp
 *  \brief Anisotropic microfacet model
 *
 *  This distribution, based on a normalize version of Ashikhmin and Shirley
 *  is useful to represent anisotropic surfaces such as brushed metal, hairs,
 *  or some type of cloth
 *
 *  Since Beckmann distribution can also handle anisotropic values, prefer
 *  that one since it is physically correct. This one is left here only for
 *  Legacy purposes
 *
 */
class Anisotropic : public MicrofacetDist
{
    /** Default constructor
     *
     *  \param[in] x The exponent representing the highlight extent along the x
     *  axis
     *  \param[in] y The exponent representing the highlight extent along the y
     *  axis
     */
    Anisotropic(float x, float y);
    
    ///Default destructor
    ~Anisotropic() = default;
    
    /** \brief The distribution term
     *
     *  Following the Torrance-Sparrow model and notation, this function
     *  computes the value corresponding to the Distribution term of the
     *  equation. This indicates how microfacet values are distributed around
     *  the input vector
     *
     *  \param[in] h The half vector between light and view directions. The half
     *  vector is the vector laying exaclty in the middle between light and view
     *  vectors
     */
    float d(const Vec3* h)const;
    
private:
    
    //x exponent
    float x;
    
    //y exponent
    float y;
};

/**
 *  \class Beckmann microfacet_distributions.hpp
 *  \brief Beckmann microfacet model
 *
 *  General purpose distribution, in contrast to the Blinn-Phong model this one
 *  is physically correct. Only the isotropic version has been implemented.
 *  Should be the preferred distribution, excluding metal and/or anisotropic
 *  surfaces where GGX should be used
 */
class Beckmann : public MicrofacetDist
{
public:
    
    /** \brief Default isotropic constructor
     *
     *  Construct a Beckmann distribution for isotropic surfaces with the given
     *  roughness
     *
     *  \param[in] roughness The roughness of the surface
     */
    Beckmann(float roughness);
    
    ///Default destructor
    ~Beckmann() = default;
    
    /** \brief The distribution term
     *
     *  Following the Torrance-Sparrow model and notation, this function
     *  computes the value corresponding to the Distribution term of the
     *  equation. This indicates how microfacet values are distributed around
     *  the input vector
     *
     *  \param[in] h The half vector between light and view directions. The half
     *  vector is the vector laying exaclty in the middle between light and view
     *  vectors
     */
    float d(const Vec3* h)const;
    
private:
    
    // 1/(alpha x * alpha x)
    float inv_a2;
};

#endif
