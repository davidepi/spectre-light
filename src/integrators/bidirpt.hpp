//Created,  23 Aug 2017
//Last Edit 28 Aug 2017

/**
 *  \file bidirpt.hpp
 *  \brief     LTE integrator that joins paths starting from light and camera
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      28 Aug 2017
 *  \copyright GNU GPLv3
 */


#ifndef __BIDIRPT_HPP__
#define __BIDIRPT_HPP__

#include "integrators/light_integrator.hpp"

class Bdpt : public LightIntegrator
{

public:
    Color radiance(const Scene* sc, const HitPoint* hp,
                   const Ray* r, Sampler* sam,OcclusionTester *ot)const;
};

#endif
