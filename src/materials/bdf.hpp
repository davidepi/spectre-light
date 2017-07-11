//Created,   16 Jun 2017
//Last Edit   1 Jul 2017

/**
 *  \file bdf.hpp
 *  \brief     Contains Bdf and Bsdf classes
 *  \details   Basic classes for material definitions
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      1 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __BDF_HPP__
#define __BDF_HPP__

#include "primitives/shape.hpp"
#include "utility/color.hpp"
#include "geometry/vec3.hpp"
#include "utility/console.hpp"

///Type of Bdf
enum BdfFlags {BRDF = 0x1, BTDF = 0x2, DIFFUSE = 0x4, SPECULAR = 0x8};

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
     *  \param flags The flag of the Bdf, used to distinguish between BRDF or
     *  BTDF
     */
    Bdf(BdfFlags flags);

    ///Default destructor
    virtual ~Bdf();

    /** \brief Copy the Bdf and its eventual derived class
     *
     *  Method used to copy this class, or its derived version, when only the
     *  base pointer is available
     *
     *  \warning The returned Bdf is heap allocated, and must be deallocated.
     *  Although this is really bad practice, it is the only possible
     *  implementation without using reference counting.
     *
     *  \return an heap allocated pointer of the cloned class
     */
    virtual Bdf* clone()const = 0;

    /** \brief Return the value of the Bdf
     *
     *  Computes the value of the Bdf in the point, defining how the light is
     *  reflected or transmitted. This function returns the ratio of reflected
     *  radiance to the incident irradiance on the surface.
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wi The incident direction
     *  \return The value of the BxDF
     *  \sa df_s(const Vec3* wo, Vec3* wi)const
     */
    virtual Color df(const Vec3* wo, const Vec3* wi)const = 0;

    /** \brief Return the value of the Bdf
     *
     *  This method is like the df one, but it is used in case of delta
     *  ditributions, for example when light is reflected from a single outgoing
     *  direction to a single incident direction.
     *
     *  This methods computes the incident direction, given the outgoing
     *  direction and computes the value of the Bdf for these one.
     *
     *  In case the distribution is not a delta one, this method sample a single
     *  incident direction by using importance sampling
     *
     *  \param[in] wo The outgoing direction
     *  \param[out] wi The incident direction
     *  \param[in] r0 A random float in the interval (0.0,1.0)
     *  \param[in] r1 A random float in the interval (0.0,1.0)
     *  \return The value of the Bdf for the pair of direction
     *  \sa df(const Vec3* wo, const Vec3* wi)const
     */
    virtual Color df_s(const Vec3* wo, Vec3* wi, float r0, float r1)const;

    /** \brief Returns the flags associated with this Bdf
     *  \return The flags representing the type of Bdf
     */
    BdfFlags getFlags()const;

    /** \brief Check if the Bdf is of the given type
     *
     *  Provided a type of Bdf as argument, this function returns true if the
     *  Bdf is of the given type
     *
     * \param[in] f The type of the Bdf
     * \return true if the Bdf is of the given type
     */
    inline bool isType(BdfFlags f)
    {
        return type & f;
    }

private:

    //the type of the bdf
    BdfFlags type;
};


/**
 *  \class Bsdf bdf.hpp "materials/bdf.hpp"
 *  \brief Wrapper for several Bdf
 *
 *  The BSDF defines how the light scatter on a surface. This class is composed
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
     *  Copy the given Bdf and adds it to this Bsdf. This means that the value
     *  of the Bdf will be taken in consideration when evaluating the Bsdf
     *
     *  \param[in] addme The Bdf that will be added
     */
    void addBdf(const Bdf* addme);

    /** \brief Return the value of the BSDF
     *
     *  Computes the value of the Bsdf in the point, defining how the light is
     *  reflected or transmitted. This function returns the ratio of reflected
     *  radiance to the incident irradiance on the surface. This value is
     *  determined by the BRDFs and BTDFs encompassed in the BSDF
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] h  The properties of the hit point
     *  \param[in] wi The incident direction
     *  \return The value of the BSDF
     */
    Color df(const Vec3* wo, const HitPoint* h, const Vec3* wi)const;

    /** \brief Return the value of the BSDF
     *
     *  Similar to the df method, this one sample a single direction and returns
     *  the light reflected or transmitted in that direction. The random
     *  incident ray is updated in the \p wi member
     *
     *  \param[in] r0 A random float in the interval (0.0,1.0)
     *  \param[in] r1 A random float in the interval (0.0,1.0)
     *  \param[in] r2 A random float in the interval (0.0,1.0)
     *  \param[in] wo The outgoing direction
     *  \param[in] h  The properties of the hit point
     *  \param[out] wi The incident direction
     *  \return A sampled value of the BSDF
     */
    Color df_s(float r0, float r1, float r2, const Vec3* wo, const HitPoint* h,
               Vec3* wi)const;
private:

    //number of Bdfs
    char count;

    //Bdfs
    Bdf* bdfs[_MAX_BDF_];
};

#endif
