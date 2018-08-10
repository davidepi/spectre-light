#ifndef __SINGLE_BRDF_HPP__
#define __SINGLE_BRDF_HPP__

#include "materials/bdf.hpp"
#include "materials/bsdf.hpp"

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
     *  \param[in] inherited The Bdf that will be added
     *  \param[in] texture The texture that will be used to compute the
     *  spectrum of the Bsdf (otherwise every Bdf uses a white spectrum). If
     *  left empty, the default White texture will be used
     */
    SingleBRDF(const Bdf* inherited, const Texture* texture = NULL);

    ///Default destructor
    virtual ~SingleBRDF();

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
                   bool matchSpec) const override;

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
                          bool matchSpec, bool* matchedSpec) const override;

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
    float pdf(const Vec3* woW, const HitPoint* h, const Vec3* wiW,
              bool matchSpec) const override;

private:
    //Bdfs
    const Bdf* bdf;

    //Textures
    const Texture* texture;
};

#endif
