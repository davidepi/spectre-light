//Created,  24 May 2017
//Last Edit  3 Jul 2017

/**
 *  \file camera.hpp
 *  \brief     Interface for the camera
 *  \details   An abstract class representing a generic camera in the space
 *  \author    Davide Pizzolotto
 *  \version   0.1
 *  \date      2 Jun 2017
 *  \copyright GNU GPLv3
 */


#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "cameras/image_output.hpp"
#include "samplers/sampler.hpp"
#include "geometry/matrix4.hpp"
#include "geometry/ray.hpp"

/**
 * \class Camera camera.hpp "cameras/camera.hpp"
 * \brief An interface for a generic camera
 *
 *  This class represents the implementation of a generic camera positioned
 *  in space. The positioning, reffered as "camera to world space" is done
 *  with the LookAt matrix. Other than the positioning, inside the class there
 *  is the film, an ImageOutput object used to store the rendered picture.
 *
 *  This class exposes a method called createRay, that must be overriden by
 *  the different types of camera that will be implemented
 */
class Camera
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
     */
    Camera(const Point3* position, const Point3* target, const Vec3* up,
           int width, int height);
    
    ///Default destructor
    virtual ~Camera();
    
    
    /** \brief Create a ray from a sample
     *
     *  Given a sample, generated by a sampler, in raster space, this methods
     *  create a ray in world space
     *
     *  \param[in] sample The given sample
     *  \param[out] ray   The output ray
     */
    virtual void createRay(Sample* sample, Ray* ray)const = 0;
    
protected:
        
    //Ray direction is define in camera space
    Matrix4 camera2world;
};

#endif
