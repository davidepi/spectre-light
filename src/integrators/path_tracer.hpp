//Created,  15 Jul 2017
//Last Edit 18 Mar 2018

/**
 *  \file path_tracer.hpp
 *  \brief     LTE integrator
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      18 Mar 2018
 *  \copyright GNU GPLv3
 */


#ifndef __PATH_TRACER_HPP__
#define __PATH_TRACER_HPP__

#include "integrators/light_integrator.hpp"
#include "samplers/sampler.hpp"
#include "utility/scene.hpp"
#include "utility/color.hpp"
#include "utility/spectrum.hpp"
#include "primitives/shape.hpp"
#include "lights/area_light.hpp"
#include "utility/occlusion_tester.hpp"
#include "settings.h"
#include "integrators/ray_tracer.hpp"

/**
 * \class PathTracer path_tracer.hpp
 * \brief Rendering equation solver, accounting for direct lighting and GI
 *
 *  This class computes the radiance arriving at a point, accounting for
 *  direct and indirect lighting. The point, called "hitpoint" from now on,
 *  has to be supplied when calling the radiance function exposed by the
 *  LightIntegrator superclass.
 *  The implementation of the radiance method calculates the direct radiance
 *  arriving at a point, then recursively it finds another point to which this
 *  radiance is reflected. After 3 bounces there is a 50% probability that the
 *  path is terminated due to russian roulette.
 */
class PathTracer : public LightIntegrator
{
    /** \brief Determines the radiance arriving at a point
     *
     *  The radiance method compute the arriving radiance at the film. This
     *  method requires as input the first intersection point found by
     *  intersecting a ray with the scene. Then it computes the radiance
     *  arriving from that point.
     *
     *  \param[in] sc The rendered scene
     *  \param[in] hp The first intersection point
     *  \param[in] r The originating ray, generated from the camera
     *  \param[in] sam A sampler used to generate random numbers
     *  \param[in] ot Class used in order to test the occlusion. It is passed
     *  here to keep trace of cached assets between various call of this
     *  function
     *  \return The radiance arriving at the film
     */
    Spectrum radiance(const Scene* sc, const HitPoint* hp,
                      const Ray* r, Sampler* sam,OcclusionTester *ot)const;

private:

    //recursive function for the radiance computation
    Spectrum l_rec(const Scene* sc, const HitPoint* hp,
                   const Ray* r, Sampler* sam, Spectrum* power, bool last_spec,
                   OcclusionTester *ot)const;
};

#endif
