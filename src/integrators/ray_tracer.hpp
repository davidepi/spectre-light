//Created,  15 Jul 2017
//Last Edit 30 Jul 2017

/**
 *  \file ray_tracer.hpp
 *  \brief     Direct lighting integrator
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      30 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __RAY_TRACER_HPP__
#define __RAY_TRACER_HPP__

#include "integrators/light_integrator.hpp"
#include "samplers/sampler.hpp"
#include "utility/scene.hpp"
#include "utility/color.hpp"
#include "primitives/shape.hpp"
#include "lights/area_light.hpp"
#include "utility/occlusion_tester.hpp"
#include "settings.h"

/**
 * \class RayTracer ray_tracer.hpp
 * \brief Rendering equation solver, accounting for direct lighting only
 *
 *  This class computes the radiance arriving at a point, accounting for
 *  direct lighting only. The point, called "hitpoint" from now on,
 *  has to be supplied when calling the radiance function exposed by the
 *  LightIntegrator superclass. Then the implementation of the function does the
 *  following things:
 *  - first it generates a random sample on a random light, and tries to reach
 *  that sample from the hitpoint. If there are no occlusion, the radiance is
 *  weighted and added to the output.
 *  - then it tries to generate a random direction on the hemisphere of the
 *  hitpoint, according to the specified BSDF, and tries to reach another
 *  random point on the light. If not occluded also this sample is weighted and
 *  added to the output.
 */
class RayTracer : public LightIntegrator
{
    /** \brief Determine the radiance arriving at a point
     *
     *  The radiance method compute the arriving radiance at the film. This
     *  method requires as input the first intersection point found by
     *  intersecting a ray with the scene. Then it computes the radiance
     *  emitted by that point.
     *
     *  This method is a wrapper for the direct_l one, and accounts for direct
     *  illumination only
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
    Color radiance(const Scene* sc, const HitPoint* hp,
                   const Ray* r, Sampler* sam, OcclusionTester* ot)const;
};

/** \brief Determine the radiance arriving at a point
 *
 *  Determine the radiance arriving directly at a point, accounting only
 *  non-specular brdfs/btdfs
 *
 *  \param[in] sc The rendered scene
 *  \param[in] hp The first intersection point
 *  \param[in] r The originating ray, generated from the camera
 *  \param[in] sam A sampler used to generate random numbers
 *  \param[in] ot Class used in order to test the occlusion. It is passed
 *  here to keep trace of cached assets between various call of this
 *  function
 *  \return The radiance arriving at the film
 *  \sa RayTracer::radiance
 */
Color direct_l(const Scene *sc, const HitPoint *hp,
               const Ray *r, Sampler *sam, OcclusionTester *ot);

/** \brief Determine the radiance arriving at a point
 *
 *  Determine the radiance arriving directly at a point, accounting only
 *  specular reflection or refraction
 *
 *  \param[in] sc The rendered scene
 *  \param[in] hp The first intersection point
 *  \param[in] r The originating ray, generated from the camera
 *  \param[in] sam A sampler used to generate random numbers
 *  \param[in] ot Class used in order to test the occlusion. It is passed
 *  here to keep trace of cached assets between various call of this
 *  function
 *  \param[in] ref BRDF for specular reflection, BTDF for specular
 *  refraction
 *  \param[in] i Since this function needs to compute the radiance arriving
 *  through a specular direction, the integrator used to calla the radiance()
 *  function is passed here
 *  \return The radiance arriving at the film
 */
Color spec_l(const Scene *sc, const HitPoint *hp, const Ray *r,
                   Sampler *sam, OcclusionTester *ot, BdfFlags ref,
                   const LightIntegrator* i);

#endif
