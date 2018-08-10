//
// Created by davide on 10/08/18.
//

#ifndef __MULTI_BDF_HPP__
#define __MULTI_BDF_HPP__

#include "materials/bdf.hpp"
#include "materials/bsdf.hpp"

class MultiBSDF : public Bsdf
{
public:

    ///Default constructor
    MultiBSDF();

    ///Default destructor
    virtual ~MultiBSDF();

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
    void inherit_bdf(Bdf* addme, const Texture* spectrum = NULL);

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
                           bool matchSpec) const;

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
                                  bool matchSpec, bool* matchedSpec) const;

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
    virtual float pdf(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
                      bool matchSpec) const;

protected:

    //number of Bdfs
    unsigned char count;

    //Bdfs
    Bdf* bdfs[_MAX_BDF_];

    //Textures
    const Texture* textures[_MAX_BDF_];
};


#endif
