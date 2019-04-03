//Created,  10 Jun 2017
//Last Edit 11 Apr 2018

/**
 *  \file refraction.hpp
 *  \brief Implementation of a BTDF
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      11 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __REFRACTION_HPP__
#define __REFRACTION_HPP__

#include "materials/bdf.hpp"

/**
 *  \class Refraction refraction.hpp "materials/refraction.hpp"
 *  \brief BTDF for a smooth surface
 *
 *  The Refraction class is a BTDF that models a smooth surface. This class is
 *  used to calculate the transmission of light inside an object
 */
class Refraction : public Bdf
{
public:

    /** \brief Default constructor
     *
     *  \param[in] eta_incident Refraction index for the incident material
     *  \param[in] eta_transmitted Refraction index for the transmitted material
     */
    Refraction(const Spectrum& eta_incident, const Spectrum& eta_transmitted);

    /** \brief NOOP
     *
     *  Refraction follows a delta distribution, so  this function returns
     *  always 0
     *
     *  \param[in] wo outgoing ray
     *  \param[in] wi incident ray
     *  \return 0
     */
    Spectrum value(const Vec3* wo, const Vec3* wi) const override;

    /** \brief Returns the value of the BTDF
     *
     *  Computes the transmitted vector, and the value of the BTDF for the pair
     *  of rays
     *
     *  \param[in] wo The outgoing direction
     *  \param[out] wi The incident direction
     *  \param[in] r0 A random float in the interval (0.0,1.0) used to choose
     *  among the wavelenghts the one to trace
     *  \param[in] r1 A random float in the interval (0.0,1.0) UNUSED
     *  \param[out] pdf The probability density function of the chosen point
     *  over the bdf hemisphere. Since the only valid pair of direction is
     *  generated, this method returns 1.0 as pdf
     *  \return The value of the BTDF
     */
    Spectrum sample_value(const Vec3* wo, Vec3* wi, float r0, float r1,
                          float* pdf) const override;

    /** \brief Return the probability density function for this bdf
     *
     *  Given a pair of vectors, return the pdf value for these directions. In
     *  other words the probability that another random sample will be equal to
     *  this one. Since this is a delta distribution, the probability that an
     *  arbitrary pair of direction is exactly equal to the specular one is 0.0f
     *
     *  \param[in] wo The outgoing direction
     *  \param[in] wi The incident direction
     *  \return 0
     */
    float pdf(const Vec3* wo, const Vec3* wi) const override;

private:

    float eta_i;
    float eta_t;
};

/** \brief Calculates the ior by using the Cauchy equation
 *
 *  This method uses the Cauchy equation to calculate a wavelenght-dependent
 *  index of refraction. The wavelenght is measured in micrometers, so the
 *  parameters must comply with this.
 *
 *  \param[in] B The B paramter of the Cauchy Equation
 *  \param[in] C The C paramter of the Cauchy Equation
 *  \param[in] D The D paramter of the Cauchy Equation
 *  \return The wavelenght dependent ior
 */
Spectrum cauchy(float B, float C, float D = 0);

/** \brief Calculates the ior by using the Sellmeier equation
 *
 *  This method uses the Sellmeier equation to calculate a wavelenght-dependent
 *  index of refraction. The wavelenght is measured in micrometers, so the
 *  parameters must comply with this.
 *
 *  \param[in] B1 The B1 paramter of the Sellmeier equation
 *  \param[in] B2 The B2 paramter of the Sellmeier equation
 *  \param[in] B3 The B3 paramter of the Sellmeier equation
 *  \param[in] C1 The C1 paramter of the Sellmeier equation
 *  \param[in] C2 The C2 paramter of the Sellmeier equation
 *  \param[in] C3 The C3 paramter of the Sellmeier equation
 *  \return The wavelenght dependent ior
 */
Spectrum sellmeier(float B1, float B2, float B3, float C1, float C2, float C3);

#endif

