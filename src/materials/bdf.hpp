//Created,   16 Jun 2017
//Last Edit  11 Apr 2018

/**
 *  \file bdf.hpp
 *  \brief     Contains Bdf and Bsdf classes
 *  \details   Basic classes for material definitions
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      11 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __BDF_HPP__
#define __BDF_HPP__

#include "primitives/shape.hpp"
#include "utility/spectrum.hpp"
#include "geometry/vec3.hpp"
#include "utility/console.hpp"
#include "textures/texture.hpp"
#include "textures/texture_library.hpp"
#include <cstring> //error msg
#include <cstdlib> //malloc error msg

#define FLAG_BRDF 0x1
#define FLAG_BTDF 0x2
#define FLAG_SPEC 0x4

/**
 *  \class Bdf bdf.hpp "materials/bdf.hpp"
 *  \brief Component of the Bsdf class
 *
 *  The bdf class can represent either a BRDF or a BTDF. It is a fundamental
 *  component of the Bsdf class, describing how the light is reflected at a
 *  surface.
 *  Note that every Bdf produces a Greyscale spectrum. Then the Bsdf class is
 *  responsible of chosing the right texture to module the results of Bdfs
 */
class Bdf
{
public:

    /** \brief Default constructor
     *
     *  \param[in] flags The flags of the Bdf, used to distinguish between BRDF
     *  or BTDF
     */
    Bdf(char flags);

    ///Default destructor
    virtual ~Bdf() = default;

    /** \brief Return the value of the Bdf
     *
     *  Compute the value of the Bdf in the point, defining how the light is
     *  reflected or transmitted. This function returns the ratio of reflected
     *  radiance to the incident irradiance on the surface.
     *
     *  \param[in] woS The outgoing direction, in shading space
     *  \param[in] wiS The incident direction, in shading space
     *  \return The value of the BxDF
     *  \sa sample_value(const Vec3* woS, Vec3* wiS)const
     */
    virtual Spectrum value(const Vec3* woS, const Vec3* wiS)const = 0;

    /** \brief Return the value of the Bdf
     *
     *  This method is like the value one, but it first samples a direction
     *  using importance sampling. Then the value is computed exactly like the
     *  other method. The sampled direction is the incident one.
     *
     *  The default implementation of this method samples randomly on the
     *  hemisphere of the normal
     *
     *  \param[in] woS The outgoing direction, in shading space
     *  \param[out] wiS The incident direction, in shading space
     *  \param[in] r0 A random float in the interval (0.0,1.0)
     *  \param[in] r1 A random float in the interval (0.0,1.0)
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere
     *  \return The value of the Bdf for the pair of direction
     *  \sa value(const Vec3* woS, const Vec3* wiS)const
     */
    virtual Spectrum sample_value(const Vec3* woS, Vec3* wiS, float r0,float r1,
                                  float* pdf)const;

    /** \brief Return the probability density function for this bdf
     *
     *  Given a pair of vectors, return the pdf value for these directions
     *
     *  \param[in] woS The outgoing direction, in shading space
     *  \param[in] wiS The incident direction, in shading space
     *  \return The pdf for this set of values
     */
    virtual float pdf(const Vec3* woS, const Vec3* wiS)const;
    
    ///Return true if the flags of this Bdf are a subset of the input ones
    inline bool matches(char flags)const
    {
        return (type & flags) == type;
    }
    
    ///Return true if the Bdf is a BRDF
    inline bool is_BRDF()const
    {
        return type & FLAG_BRDF;
    }
    
    ///Return true if the Bdf is a BTDF
    inline bool is_BTDF()const
    {
        return type & FLAG_BTDF;
    }
    
    ///Return true if the Bdf is specular
    inline bool is_specular()const
    {
        return type & FLAG_SPEC;
    }

    /** \brief Returns the flags associated with this Bdf
     *
     *  \return The flags representing the type of Bdf
     */
    char get_flags()const;

private:

    //the type of the bdf
    char type;
};


/**
 *  \class Bsdf bdf.hpp "materials/bdf.hpp"
 *  \brief Wrapper for several Bdf
 *
 *  The BSDF defines how the light scatters on a surface. This class is composed
 *  by several BRDF and BTDF that represent respectively how the light is
 *  reflected and transmitted. By combining these Bdfs it is possible to define
 *  how the light behaves when reaching the surface
 */
class Bsdf
{
public:

    ///Default constructor
    Bsdf();

    ///Default destructor
    virtual ~Bsdf();

    /** \brief Add the Bdf to the Bsdf
     *
     *  Inherit the ownership of the given Bdf and adds it to this Bsdf.
     *  This means that the value of the Bdf will be taken in consideration when
     *  evaluating the Bsdf
     *
     *  \warning Since this method inherits the pointer and take care of its
     *  deallocations, inheriting the same pointer twice will cause a double
     *  free at destruction time
     *
     *  \param[in] addme The Bdf that will be added
     *  \param[in] spectrum The texture that will be used to compute the
     *  spectrum of the Bsdf. If left empty, the default White texture will be
     *  used
     */
    virtual void inherit_bdf(Bdf* addme, Texture* spectrum = NULL);

    /** \brief Return the value of the BSDF
     *
     *  Computes the value of the Bsdf in the point, defining how the light is
     *  reflected or transmitted. This function returns the ratio of reflected
     *  radiance to the incident irradiance on the surface. This value is
     *  determined by the BRDFs and BTDFs encompassed in the BSDF
     *
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[in] wiW The incident direction, in world space
     *  \param[in] matchSpec True if specular Bdfs should be considered
     *  \return The value of the BSDF
     */
    virtual Spectrum value(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                           bool matchSpec)const;

    /** \brief Return the value of the BSDF
     *
     *  Similar to the value method, this one sample a single direction and
     *  returns the light reflected or transmitted in that direction. The random
     *  incident ray is updated in the \p wi member
     *
     *  \param[in] r0 A random float in the interval (0.0,1.0)
     *  \param[in] r1 A random float in the interval (0.0,1.0)
     *  \param[in] r2 A random float in the interval (0.0,1.0)
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[out] wiW The incident direction, in world space
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere
     *  \param[in] matchSpec True if the method should match specular Bdfs
     *  \param[out] matchedSpec True if the method matched a specular Bdf
     *  \return A sampled value of the BSDF
     */
    virtual Spectrum sample_value(float r0, float r1, float r2, const Vec3* woW,
                                  const HitPoint* h, Vec3* wiW, float* pdf,
                                  bool matchSpec, bool* matchedSpec)const;

    /** \brief Return the probability density function for this bsdf
     *
     *  Given a pair of vectors, return the pdf value for these directions.
     *
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[in] wiW The incident direction, in world space
     *  \param[in] matchSpec True if the method should match specular Bdfs
     *  \return The pdf for this set of values
     */
    virtual float pdf(const Vec3* woW,  const HitPoint* h, const Vec3* wiW,
                      bool matchSpec)const;

protected:

    //number of Bdfs
    unsigned char count;

    //Bdfs
    Bdf* bdfs[_MAX_BDF_];
    
    //Textures
    const Texture* textures[_MAX_BDF_];
};

/**
 *  \class SingleBRDF bdf.hpp "materials/bdf.hpp"
 *  \brief Wrapper for a single BRDF
 *
 *  The SingleBRDF class is a simplified version of the BSDF one. It encloses a
 *  single Bdf class exhibiting only reflectivity, and it is used to simplify
 *  the computation of matte surfaces. Note that it is not possible to add a
 *  single BTDF.
 */
class SingleBRDF : public Bsdf
{
public:
    
    ///Default constructor
    SingleBRDF();
    
    ///Default destructor
    virtual ~SingleBRDF();
    
    /** \brief Add the BRDF to this Bsdf
     *
     *  Inherit the ownership of the given BRDF and adds it to this Bsdf.
     *  If a BTDF is passed as input, a white lambertian surface will be added
     *  instead, since BTDF are not supported by this class. To used BTDFs one
     *  should use the generic Bsdf class
     *
     *  \warning Since this method inherits the pointer and take care of its
     *  deallocations, inheriting the same pointer twice will cause a double
     *  free at destruction time
     *
     *  \param[in] addme The Bdf that will be added
     *  \param[in] texture The texture that will be used to compute the
     *  spectrum of the Bsdf (otherwise every Bdf uses a white spectrum). If
     *  left empty, the default White texture will be used
     */
    void inherit_bdf(Bdf* addme, Texture* texture = NULL);
    
    /** \brief Return the value of the BSDF
     *
     *  Computes the value of the enclosed BRDF in the point, defining how the
     *  light is reflected.
     *
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[in] wiW The incident direction, in world space
     *  \param[in] matchSpec True if the method should consider specular BRDFs
     *  \return The value of the BSDF
     */
    Spectrum value(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                   bool matchSpec)const;
    
    /** \brief Return the value of the BRDF
     *
     *  Similar to the value method, this one sample a single direction and
     *  returns the light reflected in that direction. The random incident ray
     *  is updated in the \p wi member
     *
     *  \param[in] r0 A random float in the interval (0.0,1.0)
     *  \param[in] r1 A random float in the interval (0.0,1.0)
     *  \param[in] r2 A random float in the interval (0.0,1.0)
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[out] wiW The incident direction, in world space
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere
     *  \param[in] matchSpec True if the method should consider specular BRDFs
     *  \param[out] matchedSpec True if the method considered specular BRDFs
     *  \return A sampled value of the BSDF
     */
    Spectrum sample_value(float r0, float r1, float r2, const Vec3* woW,
                          const HitPoint* h, Vec3* wiW, float* pdf,
                          bool matchSpec, bool* matchedSpec)const;
    
    /** \brief Return the probability density function for this BRDF
     *
     *  Given a pair of vectors, return the pdf value for these directions.
     *
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[in] wiW The incident direction, in world space
     *  \param[in] matchSpec True if the method should consider specular BRDFs
     *  \return The pdf for this set of values
     */
    virtual float pdf(const Vec3* woW,  const HitPoint* h, const Vec3* wiW,
                      bool matchSpec)const;
};

#endif

