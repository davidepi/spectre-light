//Created,  15 Jul 2017
//Last Edit 23 Jul 2017

/**
 *  \file light_integrator.hpp
 *  \brief     Interface for rendering equation integrators
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      23 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __LIGHT_INTEGRATOR_HPP__
#define __LIGHT_INTEGRATOR_HPP__

#include "samplers/sampler.hpp"
#include "utility/scene.hpp"
#include "utility/color.hpp"
#include "utility/spectrum.hpp"
#include "primitives/shape.hpp"
#include "geometry/ray.hpp"
#include "utility/occlusion_tester.hpp"

/**
 *  \class LightIntegrator light_integrator.hpp
 * \brief The interface for rendering equation integrators
 *
 *  The integrator class is just an interface that exposes the radiance method,
 *  used by subclasses to determine the radiance arriving at the image film.
 *  Every rendering equation solver, such as path tracer or mlt, should
 *  implement this method
 */
class LightIntegrator
{
public:

    /** \brief Determine the radiance arriving at a point
     *
     *  The radiance method computes the arriving radiance at the film. This
     *  method requires as input the first intersection point found by
     *  intersecting a ray with the scene. Then it computes the radiance
     *  emitted by that point
     *
     *  \param[in] scene The rendered scene
     *  \param[in] hit The first intersection point
     *  \param[in] ray The originating ray, generated from the camera
     *  \param[in] sampler A sampler used to generate random numbers
     *  \param[in] visibility Class used in order to test the occlusion. It is
     *  passed here to keep trace of cached assets between various call of this
     *  function
     *  \return The radiance arriving at the film
     */
    virtual Spectrum radiance(const Scene* scene, const HitPoint* hit,
                              const Ray* ray, Sampler* sampler,
                              OcclusionTester* visibility)const = 0;

    ///Default destructor
    virtual ~LightIntegrator(){};
};

#endif
