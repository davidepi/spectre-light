#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "image_output.hpp"
#include "matrix4.hpp"
#include "ray.hpp"

class Camera
{
public:
    Camera(const Point3* position, const Point3* target, const Vec3* up,
           int width, int height, const char* filename);
    ~Camera();
    
    virtual void createRay(Sample* s, Ray* r)const = 0;
    
protected:
    Matrix4 raster2world;
    ImageOutput film;
};

#endif
