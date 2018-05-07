//Created,  15 Jul 2017
//Last Edit 18 Mar 2018

/**
 *  \file ray_tracer.hpp
 *  \brief     Direct lighting integrator
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      14 Sep 2017
 *  \copyright GNU GPLv3
 */


#ifndef __RAY_TRACER_HPP__
#define __RAY_TRACER_HPP__

#include "utility/spectrum.hpp"
#include "utility/scene.hpp"
#include "primitives/shape.hpp"
#include "samplers/sampler.hpp"
#include "utility/occlusion_tester.hpp"

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
 */
Spectrum direct_l(const Scene *sc, const HitPoint *hp,
                  const Ray *r, Sampler *sam, OcclusionTester *ot);

#endif
