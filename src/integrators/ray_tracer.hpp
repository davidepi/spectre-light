//
// Created by davide on 15/07/17.
//

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

class RayTracer : public LightIntegrator
{
    Color radiance(const Scene* sc, const HitPoint* hp,
                   const Ray* r, Sampler* sam)const;
};


#endif
