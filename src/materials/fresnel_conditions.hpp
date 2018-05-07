//Created,   9 Jun 2017
//Last Edit  9 Nov 2017

/**
 *  \file fresnel_conditions.hpp
 *  \brief Implementation of the fresnel equations
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      23 Sep 2017
 *  \copyright GNU GPLv3
 */


#ifndef __FRESNEL_CONDITIONS_HPP__
#define __FRESNEL_CONDITIONS_HPP__

#include "utility/spectrum.hpp"
#include "utility/utility.hpp"

/**
 *  \class Fresnel fresnel_conditions.hpp
 *  \brief Fresnel conditions interface
 *
 *  Abstract class for the two types of fresnel equations: Conductor and
 *  Dielectric
 */
class Fresnel
{
public:

    /** \brief Evaluate the incident power reflected or transmitted
     *
     *  Given an angle, determines how much of the incoming light is reflected
     *  or transmitted
     *
     *  \param[in] cosin The angle between the two rays
     *  \return The amount of light reflected or transmitted
     */
    virtual Spectrum eval(float cosin) const = 0;

    //No need for virtual destructor...
    ///Default destructor
    virtual ~Fresnel() = default;
};


/**
 *  \class Conductor fresnel_conditions.hpp "materials/fresnel_conditions.hpp"
 *  \brief Fresnel equations for a conductive material
 *
 *  A class used to calculate the value of the fresnel equations in a conductive
 *  material, thus considering the absorbed light turned into heat
 */
class Conductor : public Fresnel
{
public:

    /** \brief Default constructor
     *
     *  Construct a conductive material with the given refraction index and
     *  absorption. Despite the fact that conductive materials do not transmit
     *  light, they absorb it, hence the needs for the index of refraction
     *
     *  \param[in] refraction Refraction index for the material
     *  \param[in] absorption The portion of spectrum absorbed
     */
    Conductor(const Spectrum& refraction, const Spectrum& absorption);

    /** \brief Evaluate the incident power reflected
     *
     *  Given an angle, determines how much of the incoming light is reflected,
     *  removing the one absorbed and turned into heat
     *
     *  \param[in] cosin The angle between the two rays
     *  \return The amount of light reflected
     */
    Spectrum eval(float cosin) const;

private:

    // ior
    const Spectrum refraction_index;

    //absorbed spectrum
    const Spectrum absorption;
};


/**
 *  \class Dielectric fresnel_conditions.hpp "materials/fresnel_conditions.hpp"
 *  \brief Fresnel equations for a dielectric material
 *
 *  A class used to calculate the value of the fresnel equations in a dielectric
 *  material
 */
class Dielectric : public Fresnel
{
public:

    /** \brief Default constructor
     *
     *  Construct a dielectric material with the given refraction index for
     *  incident and transmitted materials
     *
     *  \param[in] etai Refraction index for the incident ray
     *  \param[in] etat Refraction index for the transmitted ray
     */
    Dielectric(const Spectrum& etai, const Spectrum& etat);

    /** \brief Evaluate the incident power reflected or transmitted
     *
     *  Given an angle, determines how much of the incoming light is reflected.
     *  In case the ray is transmitted, return the amount of incoming light
     *  reflected, so the remaining of the original spectrum is the potion of
     *  light transmitted.
     *
     *  \note This amount is calculated only for the parameter set by \p chosen
     *
     *  \param[in] cosin The angle between the two rays
     *  \return The amount of light reflected, depending on the angle
     */
    Spectrum eval(float cosin) const;

    /** \brief Return the incident ior
     *
     *  \return the incident index of refraction
     */
    float get_eta_incident() const;

    /** \brief Return the transmitted ior
     *
     *  \return the transmitted index of refraction
     */
    float get_eta_transmitted() const;

private:

    //ior incident
    float eta_i;

    //ior transmitted
    float eta_t;
};

#endif

