//Created,  19 Aug 2017
//Last Edit 19 Aug 2017

/**
 *  \file camera360.hpp
 *  \brief     A 360 camera
 *  \details   Create a camera for generating 360 panorama images
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      19 Aug 2017
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
     *  \param[in] position The position of the camera in the space
     *  \param[in] target   The target of the camera in the space
     *  \param[in] up       A normalized vector that represents the up direction
     *  of the camera
     *  \param[in] width    The width of the final image (resolution)
     *  \param[in] height   The height of the final image (resolution)
     */
    Camera360(const Point3* position, const Point3* target, const Vec3* up,
              int width, int height);

    /** \brief Create a ray from a sample
     *
     *  Given a sample, generated by a sampler, in raster space, this method
     *  creates a ray in world space
     *
     *  \param[in] sample The given sample
     *  \param[out] ray   The output ray
     */
    void createRay(Sample* sample, Ray* ray)const;

private:

    //inverse width of the image
    float invX;

    //inverse height of the image
    float invY;
};


#endif
