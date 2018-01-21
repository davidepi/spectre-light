//Created,   16 Jun 2017
//Last Edit  21 Jan 2018

/**
 *  \file bdf.hpp
 *  \brief     Contains Bdf and Bsdf classes
 *  \details   Basic classes for material definitions
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      21 Jan 2018
 *  \copyright GNU GPLv3
 */


#ifndef __BDF_HPP__
#define __BDF_HPP__

#include "primitives/shape.hpp"
#include "utility/spectrum.hpp"
#include "geometry/vec3.hpp"
#include "utility/console.hpp"

///Type of Bdf
enum BdfFlags {BRDF = 0x1, BTDF = 0x2, DIFFUSE = 0x4, SPECULAR = 0x8,
                GLOSSY = 0x10, ALL = BRDF | BTDF | DIFFUSE | SPECULAR | GLOSSY};

/**
 *  \class Bdf bdf.hpp "materials/bdf.hpp"
 *  \brief Component of the Bsdf class
 *
 *  The bdf class can represent either a BRDF or a BTDF. It is a fundamental
 *  component of the Bsdf class, describing how the light is reflected at a
 *  surface.
 */
class Bdf
{
public:

    /** \brief Default constructor
     *
     *  \param[in] flags The flags of the Bdf, used to distinguish between BRDF
     *  or BTDF
     */
    Bdf(BdfFlags flags);

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

    /** \brief Returns the flags associated with this Bdf
     *
     *  \return The flags representing the type of Bdf
     */
    BdfFlags get_flags()const;

    /** \brief Check if the Bdf is of the given type
     *
     *  Provided a type of Bdf as argument, this function returns true if the
     *  Bdf is of the given type. It is not necessary that the Bdf
     *  satisfies all the flags passe in input, but the input flags
     *  must be a superset of the Bdf in order to return true
     *
     * \param[in] f The type of the Bdf
     * \return true if the Bdf is a subset of the input type
     */
    inline bool is_type(BdfFlags f)
    {
        //without `== type` would match subflags
        //for example type=BRDF|SPECULAR f=SPECULAR would be true
        //the wanted behaviour is the opposite.
        return (type & f) == type;
    }

private:

    //the type of the bdf
    BdfFlags type;
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
    ~Bsdf();

    /** \brief Add the Bdf to the Bsdf
     *
     *  Inherit the ownership of the given Bdf and adds it to this Bsdf.
     *  This means that the value of the Bdf will be taken in consideration when
     *  evaluating the Bsdf
     *
     *  \param[in] addme The Bdf that will be added
     */
    void inherit_bdf(Bdf* addme);

    /** \brief Return the value of the BSDF
     *
     *  Computes the value of the Bsdf in the point, defining how the light is
     *  reflected or transmitted. This function returns the ratio of reflected
     *  radiance to the incident irradiance on the surface. This value is
     *  determined by the BRDFs and BTDFs encompassed in the BSDF
     *
     *  \warning Since this method inherits the pointer and take care of its
     *  deallocations, inheriting the same pointer twice will cause a double
     *  free at destruction time
     *
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[in] wiW The incident direction, in world space
     *  \param[in] matchme The types of bdfs to consider when computing radiance
     *  \return The value of the BSDF
     */
    Spectrum value(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                BdfFlags matchme)const;

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
     *  \param[in] matchme The types of bdfs to consider when computing radiance
     *  \param[out] matched The bdfs matched with the sampling
     *  \return A sampled value of the BSDF
     */
    Spectrum sample_value(float r0, float r1, float r2, const Vec3* woW,
                          const HitPoint* h, Vec3* wiW, float* pdf,
                          BdfFlags matchme, BdfFlags* matched)
    const;

    /** \brief Return the probability density function for this bsdf
     *
     *  Given a pair of vectors, return the pdf value for these directions.
     *
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[in] wiW The incident direction, in world space
     *  \param[in] matchme The types of bdfs to consider when computing the pdf
     *  \return The pdf for this set of values
     */
    float pdf(const Vec3* woW,  const HitPoint* h, const Vec3* wiW,
              BdfFlags matchme)const;

private:

    //number of Bdfs
    unsigned char count;

    //Bdfs
    Bdf* bdfs[_MAX_BDF_];
};

#endif

