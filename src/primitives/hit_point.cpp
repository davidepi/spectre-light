//author: Davide Pizzolotto
//license: GNU GPLv3

#include "hit_point.hpp"

void calculate_differentials(HitPoint* hit, Ray* rx, Ray* ry)
{
    //ripped from pbrt
    //calculate intersection of differentials with plane
    float d = -dot(hit->geometric.n, Vec3(hit->point_h.x,
                                       hit->point_h.y,
                                       hit->point_h.z));
    Vec3 rxv = Vec3(rx->origin.x, rx->origin.y, rx->origin.z);
    Vec3 ryv = Vec3(ry->origin.x, ry->origin.y, ry->origin.z);
    float tx = -(dot(hit->geometric.n, rxv)+d);
    tx /= dot(hit->geometric.n, rx->direction);
    float ty = -(dot(hit->geometric.n, ryv)+d);
    ty /= dot(hit->geometric.n, ry->direction);
    Point3 px = rx->origin+(rx->direction*tx);
    Point3 py = ry->origin+(ry->direction*ty);
    //points differentials
    //    Vec3 dpdx = px-hit->point_h;
    //    Vec3 dpdy = py-hit->point_h;

    float nx = fabsf(hit->geometric.n.x);
    float ny = fabsf(hit->geometric.n.y);
    float nz = fabsf(hit->geometric.n.z);
    uint8_t axes0;
    uint8_t axes1;

    if(nx>ny && nx>nz)
    {
        axes0 = 1;
        axes1 = 2;
    }
    else if(ny>nz)
    {
        axes0 = 0;
        axes1 = 2;
    }
    else
    {
        axes0 = 0;
        axes1 = 1;
    }
    float a00 = hit->geometric.dpdu[axes0];
    float a01 = hit->geometric.dpdv[axes0];
    float a10 = hit->geometric.dpdu[axes1];
    float a11 = hit->geometric.dpdv[axes1];
    float bx0 = px[axes0]-hit->point_h[axes0];
    float bx1 = px[axes1]-hit->point_h[axes1];
    float by0 = py[axes0]-hit->point_h[axes0];
    float by1 = py[axes1]-hit->point_h[axes1];

    float det = a00*a11-a01*a10;
    if(fabsf(det)>1e-5f)
    {
        float invdet = 1.f/det;
        hit->du.x = (a11*bx0-a01*bx1)*invdet;
        hit->dv.x = (a00*bx1-a10*bx0)*invdet;
        hit->du.y = (a11*by0-a01*by1)*invdet;
        hit->dv.y = (a00*by1-a10*by0)*invdet;
        //check solutions
#ifdef DEBUG
        //after 1 hour of randomly generated values, this never happened
        //left just in case someday I'll find out a corner case that falls here
        if(std::isnan(hit->du.x) || std::isnan(hit->dv.x) ||
           std::isnan(hit->du.y) || std::isnan(hit->dv.y))
            throw "NaN differentials";
#endif

        hit->differentials = true;
    }
    else
        hit->differentials = false;
}
