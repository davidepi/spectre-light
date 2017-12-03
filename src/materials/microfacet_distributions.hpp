//Created,  20 Sep 2017
//Last Edit 21 Nov 2017

/**
 *  \file microfacet_distributions.hpp
 *  \brief Microfacet distributions
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date  8 Nov 2017
 *  \copyright GNU GPLv3
 */

#ifndef __MICROFACET_DISTRIBUTION_HPP__
#define __MICROFACET_DISTRIBUTION_HPP__

#include "geometry/vec3.hpp"
#include "utility/utility.hpp"
#include "settings.h" //ONE_PI
#include <cmath> //isinf

/**
 *  \class MicrofacetDist microfacet_distributions.hpp
 *  \brief Interface used to represent microfacet distributions
 *
 *  The microfacet distribution class provides a method called \a D, that is
 *  used to compute the value of the microfacet distribution for a given half
 *  vector, and a method called \a G used for the geometric attenuation
 *  These values are required by the Cook-Torrance model and are used to know
 *  how the microfacets are distributed
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
     *  \return The value of the distribution term
     */
    virtual float D(const Vec3* h)const = 0;
    
    /** \brief The geometric attenuation G
     *
     *  Calculates the value of the geometric attenuation term, accounting the
     *  fact that some microfacets will not be visible. The geometric term is
     *  calculated by means of the Cook-Torrance formulation. For some kind of
     *  distribution the Smith's integral provides better results, for some
     *  other there is no closed form solution, for this reason this method is
     *  left here as a base, general implementation
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wi The incident direction
     *  \param[in] wh The halfway vector between wi and wo
     *  \return The value of the geometric attenuation term
     */
    virtual float G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const;
    
    /** \brief Find a random half vector
     *
     *  Given the outgoing direction and two random numbers, this method
     *  computes the half vector following the distribution and its
     *  pdf. Useful for importance sampling
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] r0 A random number in the interval [0.0,1.0]
     *  \param[in] r1 A random number in the interval [0.0,1.0]
     *  \param[out] wh The randomly chosen half vector
     */
    virtual void sample_wh(const Vec3* wo, float r0, float r1,
                          Vec3* wh)const = 0;
    
    /** \brief Find the pdf of two pairs of directions
     *
     *  Given an outgoing direction, an incident direction, and the half vector
     *  find the probability density function of chosing the incident direction
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wh The half vector between wi and wo
     *  \param[in] wi The incident direction
     *  \return The pdf
     */
    virtual float pdf(const Vec3* wo, const Vec3* wh, const Vec3* wi)const;
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
     *  \return The value of the distribution term
     */
    float D(const Vec3* h)const;
    
    /** \brief The geometric attenuation G
     *
     *  Calculates the value of the geometric attenuation term, by means of
     *  the Smith's integral. Thus, G(wi,wo) = G1(wi)G1(wo). For this particular
     *  microfacet distribution, the Smith's integral has no closed form
     *  solution. However, due to the similarities between the Beckmann
     *  distribution and this one, the Beckmann G1 formula is used also for this
     *  distribution
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wi The incident direction
     *  \param[in] wh The halfway vector between wi and wo
     *  \return The value of the geometric attenuation term
     */
    float G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const;
    
    /** \brief Find a random half vector
     *
     *  Given the outgoing direction and two random numbers, this method
     *  computes the half vector following the distribution and its
     *  pdf. Useful for importance sampling
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] r0 A random number in the interval [0.0,1.0]
     *  \param[in] r1 A random number in the interval [0.0,1.0]
     *  \param[out] wh The randomly chosen half vector
     */
    void sample_wh(const Vec3* wo, float r0, float r1, Vec3* wh)const;
    
    /** \brief Find the pdf of two pairs of directions
     *
     *  Given an outgoing direction, an incident direction, and the half vector
     *  find the probability density function of chosing the incident direction
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wh The half vector between wi and wo
     *  \param[in] wi The incident direction
     *  \return The pdf
     */
    float pdf(const Vec3* wo, const Vec3* wh, const Vec3* wi)const;
    
private:
    
    float G1(const Vec3* v)const;
    
    //exponent for the specular highlight
    float exponent;
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
    
    /** \brief Default constructor
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
     *  \return The value of the distribution term
     */
    float D(const Vec3* h)const;
    
    /** \brief The geometric attenuation G
     *
     *  Calculates the value of the geometric attenuation term, by means of
     *  the Smith's integral. Thus, G(wi,wo) = G1(wi)G1(wo)
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wi The incident direction
     *  \param[in] wh The halfway vector between wi and wo
     *  \return The value of the geometric attenuation term
     */
    float G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const;
    
    /** \brief Find a random half vector
     *
     *  Given the outgoing direction and two random numbers, this method
     *  computes the half vector following the distribution and its
     *  pdf. Useful for importance sampling
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] r0 A random number in the interval [0.0,1.0]
     *  \param[in] r1 A random number in the interval [0.0,1.0]
     *  \param[out] wh The randomly chosen half vector
     */
    void sample_wh(const Vec3* wo, float r0, float r1, Vec3* wh)const;
    
private:
    
    float G1(const Vec3* v)const;
    
    //alpha x
    float a;
};

/**
 *  \class GGXiso microfacet_distributions.hpp
 *  \brief Isotropic GGX distribution function
 *
 *  Sometimes called Trowbridge-Reitz, the GGX distribution fall of more slowly
 *  compared to the Beckmann one. It can be used to model in a better way
 *  metallic surfaces.
 *
 *  This particular implementation consider the GGX distribution as isotropic
 */
class GGXiso : public MicrofacetDist
{
public:
    
    /** \brief Default constructor
     *
     *  \param[in] roughness The roughness of the surface
     */
    GGXiso(float roughness);
    
    ///Default destructor
    ~GGXiso() = default;
    
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
     *  \return The value of the distribution term
     */
    float D(const Vec3* h)const;
    
    /** \brief The geometric attenuation G
     *
     *  Calculates the value of the geometric attenuation term, by means of
     *  the Smith's integral. Thus, G(wi,wo) = G1(wi)G1(wo)
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wi The incident direction
     *  \param[in] wh The halfway vector between wi and wo
     *  \return The value of the geometric attenuation term
     */
    float G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const;
    
    /** \brief Find a random half vector
     *
     *  Given the outgoing direction and two random numbers, this method
     *  computes the half vector following the distribution and its
     *  pdf. Useful for importance sampling
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] r0 A random number in the interval [0.0,1.0]
     *  \param[in] r1 A random number in the interval [0.0,1.0]
     *  \param[out] wh The randomly chosen half vector
     */
    void sample_wh(const Vec3* wo, float r0, float r1, Vec3* wh)const;
    
private:
    
    float G1(const Vec3* v)const;
    
    //squared roughness
    float a2;
};

/**
 *  \class GGXaniso microfacet_distributions.hpp
 *  \brief Anisotropic GGX distribution function
 *
 *  Exactly like the GGXiso class, but for anisotropic surfaces
 */
class GGXaniso : public MicrofacetDist
{
public:
    
    /** \brief Default constructor
     *
     *  \param[in] ax Alpha x value for the anisotropy
     *  \param[in] ay Alpha y value for the anisotropy
     */
    GGXaniso(float ax, float ay);
    
    ///Default destructor
    ~GGXaniso() = default;
    
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
     *  \return The value of the distribution term
     */
    float D(const Vec3* h)const;
    
    /** \brief The geometric attenuation G
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wi The incident direction
     *  \param[in] wh The halfway vector between wi and wo
     *  \return The value of the geometric attenuation term
     */
    float G(const Vec3* wo, const Vec3* wi, const Vec3* wh)const;
    
    /** \brief Find a random half vector
     *
     *  Given the outgoing direction and two random numbers, this method
     *  computes the half vector following the distribution and its
     *  pdf. Useful for importance sampling
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] r0 A random number in the interval [0.0,1.0]
     *  \param[in] r1 A random number in the interval [0.0,1.0]
     *  \param[out] wh The randomly chosen half vector
     */
    void sample_wh(const Vec3* wo, float r0, float r1, Vec3* wh)const;
    
private:
    
    //inverse of the alpha x
    float ax;
    
    //inverse of the alpha y
    float ay;
};

#endif
