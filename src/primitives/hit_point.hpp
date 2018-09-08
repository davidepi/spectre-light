//Created,  19 Aug 2018
//Last Edit 19 Aug 2018

/**
 *  \file hit_point.hpp
 *  \brief     Struct holding several information about the hit point
 *  \details   Details of the hit point saved into this struct
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      19 Aug 2018
 *  \copyright GNU GPLv3
 */


#ifndef __HIT_POINT_HPP__
#define __HIT_POINT_HPP__

#include "geometry/point3.hpp"
#include "geometry/vec3.hpp"
#include "geometry/point2.hpp"
#include "geometry/ray.hpp"

//HitPoint struct needs Asset and Asset needs HitPoint. Forward declaration.
class Asset;

///Struct containing the data of the intersection between a Ray and a Shape
struct HitPoint
{
    ///The hit point in world space
    Point3 point_h;

    ///The geometric normal of the hit point in world space
    Normal normal_h;

    ///Differential of hit point, varying the x coordinate on the surface
    Vec3 dpdu;

    ///Differential of hit point, varying the y coordinate on the surface
    Vec3 dpdv;

    ///Hit asset
    const Asset* asset_h;

    ///index of the hit triangle (0 if the asset is not a mesh)
    unsigned int index;

    ///Mapping coordinate u of the point, used for texture mapping
    Point2 uv;

    ///Holds values dudx and dudy, differentials of the u parameter
    Vec2 du;

    ///Holds values dvdx and dvdy, differentials of the v parameter
    Vec2 dv;

    //true if the values du and dv are set
    bool differentials;
};

void calculate_differentials(HitPoint* hp, Ray* rx, Ray* ry);

#endif
