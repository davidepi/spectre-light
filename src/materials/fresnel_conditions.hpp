//Created,   9 Jun 2017
//Last Edit  2 Jul 2017

/**
 *  \file fresnel_conditions.hpp
 *  \brief Implementation of the fresnel equations
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      2 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __FRESNEL_CONDITIONS_HPP__
#define __FRESNEL_CONDITIONS_HPP__

#include "utility/color.hpp"
#include "utility/utility.hpp"

/**
 *  \class FresnelConditions fresnel_conditions.hpp
 *  \brief Fresnel conditions interface
 *
 *  Abstract class for the two types of fresnel equations: Conductor and
 *  Dielectric
 */
class FresnelConditions
{
public:

    /** \brief Evaluate the incident power reflected or transmitted
     *
     *  Given an angle, determines how much of the incoming light is reflected
     *  or transmitted
     *
     *  \param cosin The angle between the two rays
     *  \return The amount of light reflected or transmitted
     */
    virtual Color eval(float cosin)const = 0;
};


/**
 *  \class Conductor fresnel_conditions.hpp "materials/fresnel_conditions.hpp"
 *  \brief Fresnel equations for a conductive material
 *
 *  A class used to calculate the value of the fresnel equations in a conductive
 *  material, thus considering the absorbed light turned into heat
 */
class Conductor : public FresnelConditions
{
public:

    /** \brief Default constructor
     *
     *  Construct a conductive material with the given refraction index and
     *  absorption. Despite the fact that conductive materials do not transmit
     *  light, they absorb it, hence the needs for the index of refraction
     *
     *  \param refraction Refraction index for the material
     *  \param absorption The portion of spectrum absorbed
     */
    Conductor(Color refraction, Color absorption);

    /** \brief Evaluate the incident power reflected
     *
     *  Given an angle, determines how much of the incoming light is reflected,
     *  removing the one absorbed and turned into heat
     *
     *  \param cosin The angle between the two rays
     *  \return The amount of light reflected
     */
    Color eval(float cosin)const;

private:

    // ior
    Color refraction_index;

    //absorbed spectrum
    Color absorption;
};


/**
 *  \class Dielectric fresnel_conditions.hpp "materials/fresnel_conditions.hpp"
 *  \brief Fresnel equations for a dielectric material
 *
 *  A class used to calculate the value of the fresnel equations in a dielectric
 *  material
 */
class Dielectric : public FresnelConditions
{
public:

    /** \brief Default constructor
     *
     *  Construct a dielectric material with the given refraction index for
     *  incident and transmitted materials
     *
     *  \param refractioni Refraction index for the incident ray
     *  \param refractiont Refraction index for the transmitted ray
     */
    Dielectric(float refractioni, float refractiont);

    /** \brief Evaluate the incident power reflected or transmitted
     *
     *  Given an angle, determines how much of the incoming light is reflected.
     *  In case the ray is transmitted, return the amount of incoming light
     *  transmitted
     *
     *  \param cosin The angle between the two rays
     *  \return The amount of light reflected or transmitted, depending on the
     *  angle
     */
    Color eval(float cosin)const;

private:

    //ior incident
    float etai;

    //ior transmitted
    float etat;
};

#endif
