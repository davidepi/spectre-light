//Created,  20 Sep 2017
//Last Edit 20 Sep 2017

/**
 *  \file microfacet.hpp
 *  \brief Microfacet distributions
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date  20 Sep 2017
 *  \copyright GNU GPLv3
 */


#ifndef __MICROFACET_HPP__
#define __MICROFACET_HPP__

#include "geometry/vec3.hpp"
#include <cmath>

/**
 *  \class Microfacet microfacet.hpp "materials/microfacet.hpp"
 *  \brief Interface used to represent microfacet distributions
 *
 *  The microfacet class provides a single method called \a d, that is used to
 *  compute the value of the microfacet distribution for a given half vector.
 *  This can be used in model such as the Cook-Torrance one
 */
class Microfacet
{
public:
    
    ///Default constructor
    Microfacet() = default;
    
    ///Default destructor
    virtual ~Microfacet() = default;
    
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
 *  \class Blinn microfacet.hpp "materials/microfacet.hpp"
 *  \brief Blinn microfacet model
 *
 *  This microfacet model approximate the orientation of the microfacets with 
 *  an exponential falloff passed to the constructor. The most common 
 *  orientation is the one following the normal direction falling off following
 *  the exponent
 *
 *  This model represents an isotropic BRDF
 */
class Blinn : public Microfacet
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
     *  Following the Cook-Torrance model and notation, this function computes
     *  the value corresponding to the Distribution term of the equation. This
     *  indicates how microfacet values are distributed around the input vector
     *
     *  \param[in] h The half vector between light and view directions. The half
     *  vector is the vector laying exaclty in the middle between light and view
     *  vectors
     */
    float d(const Vec3* h)const;
    
private:
    
    float exponent;
};

#endif
