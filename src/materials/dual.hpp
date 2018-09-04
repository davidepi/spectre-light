//Created,  10 Aug 2018
//Last Edit 24 Aug 2018

/**
 *  \file dual.hpp
 *  \brief     DualBsdf class
 *  \details   Multi-material composed by two other materials
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      24 Aug 2018
 *  \copyright GNU GPLv3
 */


#ifndef __DUAL_HPP__
#define __DUAL_HPP__

#include "materials/bdf.hpp"
#include "materials/bsdf.hpp"
#include "textures/texture_image.hpp"
#include "textures/mask_boolean.hpp"

/**
 *  \brief Multi-material composed by two Bsdf
 *
 *  The DualBsdf class is the simplest multi-material. This class wraps
 *  together two BSDFs and a BooleanMask, and itself inherits from the Bsdf
 *  class. When the spectrum is computed, this class uses the provided mask
 *  in order to decide which material should contribute to the given point.
 *
 *  Note that this class differs from the MultiBSDF one: in the latter every
 *  Bdf contributes to the final result, while in this only the one chosen by
 *  the Mask is used
 */
class DualBsdf : public Bsdf
{
public:

    DualBsdf(const Bsdf* first, const Bsdf* second, const MaskBoolean& mask);

    /** \brief Return the value of the BSDF
     *
     *  Computes the value of the Bsdf in the point, defining how the light is
     *  reflected or transmitted. This function returns the ratio of reflected
     *  radiance to the incident irradiance on the surface. This value is
     *  determined by one of the Bsdf composing the DualBsdf, decided by the
     *  value of the BooleanMask.
     *
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[in] wiW The incident direction, in world space
     *  \param[in] matrix The matrix used to swap from world space to shading
     *  space
     *  \param[in] matchSpec True if specular Bdfs should be considered
     *  \return The value of the BSDF
     */
    Spectrum value(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                   const ShadingSpace* matrix, bool matchSpec) const override;

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
     *  \param[in] matrix The matrix used to swap from world space to shading
     *  space
     *  \param[out] wiW The incident direction, in world space
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere
     *  \param[in] matchSpec True if the method should match specular Bdfs
     *  \param[out] matchedSpec True if the method matched a specular Bdf
     *  \return A sampled value of the BSDF
     */
    Spectrum sample_value(float r0, float r1, float r2, const Vec3* woW,
                          const HitPoint* h, const ShadingSpace* matrix,
                          Vec3* wiW, float* pdf, bool matchSpec,
                          bool* matchedSpec) const override;

    /** \brief Return the probability density function for this bsdf
     *
     *  Given a pair of vectors, return the pdf value for these directions.
     *
     *  \param[in] woW The outgoing direction, in world space
     *  \param[in] h  The properties of the hit point
     *  \param[in] matrix The matrix used to swap from world space to shading
     *  space
     *  \param[in] wiW The incident direction, in world space
     *  \param[in] matchSpec True if the method should match specular Bdfs
     *  \return The pdf for this set of values
     */
    float pdf(const Vec3* woW, const HitPoint* h, const ShadingSpace* matrix,
              const Vec3* wiW, bool matchSpec) const override;

    /**
     *  \brief  Calculate the shading matrix for this material
     *
     * \param[in] hp The HitPoint that will be used for the shading matrix
     * computation
     * \param[out] matrix The shading matrix that will be generated
     * \param[out] normal The shading norma
     */
    void
    gen_shading_matrix(const HitPoint* hp, ShadingSpace* matrix,
                       Normal* normal) const override;

private:

    ///Mask used to decide which Bsdf should contribute
    const MaskBoolean mask;

    ///First Bsdf
    const Bsdf* first;

    ///Second Bsdf
    const Bsdf* second;
};


#endif
