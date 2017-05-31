//Created,  28 May 2017
//Last Edit 31 May 2017

/**
 *  \file perspective_camera.hpp
 *  \brief     A perspective
 *  \details   Create a camera for generating perspective images
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      31 May 2017
 *  \copyright GNU GPLv3
 */


#ifndef __PERSPECTIVE_CAMERA_HPP__
#define __PERSPECTIVE_CAMERA_HPP__

#include "camera.hpp"
#include "point3.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "sampler.hpp"

/**
 *  \class PerspectiveCamera
 *  \brief A camera generating a perspective projection
 *
 *  This class represents a camera which produces images exhibiting perspective
 *  projection. In this projection every object becomes smaller, the farther it
 *  is from the camera
 *
 *  The near plane and far plane of the viewing frustum used by this camera
 *  are set to 0.0 and 1000.0 respectively
 */
class PerspectiveCamera : public Camera
{
public:
    
    /** \brief Default constructor
     *
     *  \param[in] position The position of the camera in the space
     *  \param[in] target   The target of the camera in the space
     *  \param[in] up       A normalized vector that represents the up direction
     *  of the camera
     *  \param[in] width    The width of the final image (resolution)
     *  \param[in] height   The height of the final image (resolution)
     *  \param[in] filename The name of the file that will be stored onto the
     *  disk
     *  \param[in] fov The angle of view in radians
     */
    PerspectiveCamera(const Point3* position,const Point3* target,
                       const Vec3* up, int width, int height,
                       const char* filename, float fov);
    
    ///Default destructor
    ~PerspectiveCamera();
    
    /** \brief Create a ray from a sample
     *
     *  Given a sample, generated by a sampler, in raster space, this methods
     *  create a ray in world space
     *
     *  \param[in] sample The given sample
     *  \param[out] ray   The output ray
     */
    void createRay(Sample* sample, Ray* ray)const;
};

#endif
