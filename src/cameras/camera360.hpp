//Created,  19 Aug 2017
//Last Edit 14 May 2018

/**
 *  \file camera360.hpp
 *  \brief     A 360 camera
 *  \details   Create a camera for generating 360 panorama images
 *  \author    Davide Pizzolotto
 *  \version   0.2
 *  \date      14 May 2018
 *  \copyright GNU GPLv3
 */


#ifndef __CAMERA360_HPP__
#define __CAMERA360_HPP__

#include "cameras/camera.hpp"
#include "settings.h"

/**
 *  \class Camera360
 *  \brief Model for an omni-directional camera
 *
 *  This class represents a camera which produces 360 degrees panorama images.
 *  The type of images produced by this camera represent the sphere all around
 *  the camera position with a mercator projection
 */
class Camera360 : public Camera
{
public:

    /** \brief Construct a camera in the space
     *
     *  Construct a camera given the position, the target and the up vector.
     *  The up vector represents a vector pointing upward from the center of the
     *  camera, used to orientate/tilt it. Moreover this constructor requires
     *  also the width and height of the final image
     *
     *  Since a 360 camera does not have a target, the "target" parameter will
     *  be used to determine the center of the generated image
     *
     *  \param[in] position The position of the camera in world space
     *  \param[in] target The target of the camera in world space
     *  \param[in] up A normalized vector that represents the up direction of
     *  the camera
     *  \param[in] width The width of the final image (resolution)
     *  \param[in] height The height of the final image (resolution)
     */
    Camera360(const Point3& position, const Point3& target, const Vec3& up,
              int width, int height);

private:

    ///Like create_ray but generates single <origin,direction> pairs
    void create_single_ray(const Sample* sample, Point3* orig,
                           Vec3* dir) const override;

    //inverse width of the image
    float invX;

    //inverse height of the image
    float invY;
};

#endif
