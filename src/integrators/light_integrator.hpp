//Created,  15 Jul 2017
//Last Edit 15 Jul 2017

/**
 *  \file aabb.hpp
 *  \brief     Interface for rendering equation integrators
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      15 Jul 2017
 *  \copyright GNU GPLv3
 */


#ifndef __LIGHT_INTEGRATOR_HPP__
#define __LIGHT_INTEGRATOR_HPP__

#include "samplers/sampler.hpp"
#include "utility/scene.hpp"
#include "utility/color.hpp"
#include "primitives/shape.hpp"
#include "geometry/ray.hpp"

/**
 * \class LightIntegrator light_integrator.hpp
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
     *  The radiance method compute the arriving radiance at the film. This
     *  method requires as input the first intersection point found by
     *  intersecting a ray with the scene. Then it computes the radiance
     *  emitted by that point
     *
     *  \param[in] sc The rendered scene
     *  \param[in] hp The first intersection point
     *  \param[in] r The originating ray, generated from the camera
     *  \param[in] sam A sampler used to generate random numbers
     *  \return The radiance arriving at the film
     */
    virtual Color radiance(const Scene* sc, const HitPoint* hp,
                           const Ray* r, Sampler* sam)const = 0;
};


#endif
