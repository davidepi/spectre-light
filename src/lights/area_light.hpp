//Created,  13 Jun 2017
//Last Edit 13 Jun 2017

/**
 *  \file area_light.hpp
 *  \brief     Definition of a light-emitting shape
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      13 Jun 2017
 *  \copyright GNU GPLv3
 */


#ifndef __AREA_LIGHT_HPP__
#define __AREA_LIGHT_HPP__

#include "color.hpp"
#include "asset.hpp"
#include "shape.hpp"

/**
 * \class AreaLight area_light.hpp "lights/area_light.hpp"
 * \brief A light-emitting shape
 *
 *  This class extends an Asset in order to transform it into a light. By 
 *  passing a Color the shape is treated as a light emitting shape
 */
class AreaLight : public Asset
{
public:
    AreaLight(Shape* sp, Matrix4* objToWorld, Color c);
    void radiance()const;
    Color emissivePower()const;
    
private:
    Color c;
    float area;
};

#endif
