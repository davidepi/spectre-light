//Created,  28 May 2017
//Last Edit 14 May 2018

/**
 *  \file camera_perspective.hpp
 *  \brief     A perspective camera
 *  \details   A camera for generating perspective images
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      14 May 2018
 *  \copyright GNU GPLv3
 */


#ifndef __CAMERA_PERSPECTIVE_HPP__
#define __CAMERA_PERSPECTIVE_HPP__

#include "cameras/camera.hpp"
#include "geometry/point3.hpp"
#include "geometry/vec3.hpp"
#include "geometry/ray.hpp"
#include "samplers/sampler.hpp"

///Value used by the parser to know the camera type is `perspective`
#define SPECTRE_CAMERA_PERSPECTIVE 1

/**
 *  \class CameraPerspective
 *  \brief A camera generating a perspective projection
 *
 *  This class represents a camera which produces images exhibiting perspective
 *  projection. In this projection every object becomes smaller, the farther it
 *  is from the camera
 *
 *  The near plane and far plane of the viewing frustum used by this camera
 *  are set to 0.0 and 1000.0 respectively
 */
class CameraPerspective : public Camera
{
public:

    /** \brief Default constructor
     *
     *  \param[in] position The position of the camera in world space
     *  \param[in] target   The target of the camera in world space
     *  \param[in] up A normalized vector that represents the up direction of
     *  the camera
     *  \param[in] width The width of the final image (resolution)
     *  \param[in] height The height of the final image (resolution)
     *  \param[in] fov The angle of view in radians
     */
    CameraPerspective(const Point3* position, const Point3* target,
                      const Vec3* up, int width, int height, float fov);

private:

    ///Like create_ray but generates single <origin,direction> pairs
    void create_single_ray(const Sample* sample, Point3* orig, Vec3* dir) const;

    ///The matrix used to transform from raster space to camera space
    Matrix4 raster2camera;
};

#endif
