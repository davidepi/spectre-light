//Created,  26 May 2017
//Last Edit 14 May 2018

/**
 *  \file camera_orthographic.hpp
 *  \brief     An orthographic camera
 *  \details   A camera used to generate orthographic images
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      14 May 2018
 *  \copyright GNU GPLv3
 */


#ifndef __CAMERA_ORTHOGRAPHIC_HPP__
#define __CAMERA_ORTHOGRAPHIC_HPP__

#include "cameras/camera.hpp"
#include "geometry/point3.hpp"
#include "geometry/vec3.hpp"
#include "geometry/ray.hpp"
#include "samplers/sampler.hpp"

///Value used by the parser to know the camera type is `orthographic`
#define SPECTRE_CAMERA_ORTHOGRAPHIC 0

/**
 *  \class CameraOrthographic
 *  \brief A camera generating an orthographic projection
 *
 *  This class represents a camera which produces images exhibiting orthographic
 *  projection. In this projection every projection line is orthogonal to the
 *  system and it does not exhibit perspective.
 *
 *  The near plane and far plane of the viewing frustum used by this camera
 *  are set to 0.0 and 1.0 respectively
 */
class CameraOrthographic : public Camera
{
public:

    /** \brief Construct the camera
     *
     *  \param[in] position The position of the camera in world space
     *  \param[in] target The target of the camera in world space
     *  \param[in] up A normalized vector that represents the up direction of 
     *  the camera
     *  \param[in] width The width of the final image (resolution)
     *  \param[in] height The height of the final image (resolution)
     */
    CameraOrthographic(const Point3* position, const Point3* target,
                       const Vec3* up, int width, int height);

private:

    ///Like create_ray but generates single <origin,direction> pairs
    void create_single_ray(const Sample* sample, Point3* orig, Vec3* dir) const;

    //The matrix used to transform from raster space to world space
    Matrix4 raster2world;
};

#endif
