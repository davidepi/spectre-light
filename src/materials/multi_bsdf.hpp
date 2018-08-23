//Created,   10 Aug 2018
//Last Edit  20 Aug 2018

/**
 *  \file multi_bsdf.hpp
 *  \brief     Standard implementation of a material
 *  \details   A material composed of reflective and transmittive components
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      20 Aug 2018
 *  \copyright GNU GPLv3
 */


#ifndef __MULTI_BDF_HPP__
#define __MULTI_BDF_HPP__

#include "materials/bdf.hpp"
#include "materials/bsdf.hpp"
#include "materials/shading_space.hpp"
#include "materials/bump.hpp"

/**
 *  \brief Material wrapping multiple reflective or transmittive surfaces
 *
 *  The BSDF defines how the light scatters on a surface. This class is composed
 *  by several BRDF and BTDF that represent respectively how the light is
 *  reflected and transmitted. By combining these BxDFs it is possible to define
 *  how the light behaves when reaching the surface.
 *
 *  This is the standard implementation of a material.
 *
 *  \note A multi-material differs from this class: in this class every BDF
 *  component participates to the final result, where in a multi-material the
 *  actual BSDF defining the result is determined by a mask. Despite the
 *  similar names, a multi-material is one step above this class
 */
class MultiBSDF : public Bsdf
{
public:

    ///Default constructor
    MultiBSDF();

    ///Default destructor
    ~MultiBSDF() override;

    /** \brief Add the Bdf to the BSDF
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
     *  spectrum of the BSDF. If left empty, the default White texture will be
     *  used
     *  \param[in] bump The texture that will be used to compute the shading
     *  normal in the current point. If left empty, the default TextureBump
     *  will be used. The default TextureBump generates a shading normal
     *  equal to the geometric normal.
     *
     *  \warning The Bump will be deleted by this BSDF constructor. (The idea
     *  is that Bump are constructed by the Parses and managed by BxDFs)
     */
    void inherit_bdf(Bdf* addme, const Texture* spectrum = NULL,
                     const Bump* bump = NULL);

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
    Spectrum value(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                   bool matchSpec) const override;

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
    Spectrum sample_value(float r0, float r1, float r2, const Vec3* woW,
                          const HitPoint* h, Vec3* wiW, float* pdf,
                          bool matchSpec, bool* matchedSpec) const
    override;

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
    float pdf(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
              bool matchSpec) const override;

protected:

    //number of BxDFs
    unsigned char count;

    //BxDFs
    Bdf* bdfs[_MAX_BDF_];

    //Textures
    const Texture* diffuse[_MAX_BDF_];
    const Bump* bump[_MAX_BDF_];
};


#endif
