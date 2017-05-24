#ifndef __CAMERA_HPP__
#define __CAMERA_HPP__

#include "image_output.hpp"
#include "vec3.hpp"
#include "ray.hpp"

class Camera
{
public:
    Camera(Vec3* position, int width, int height, const char* filename);
    ~Camera();
    
    virtual void createRay(Sample* s, Ray* r)const = 0;
    
protected:
    Vec3 position;
    ImageOutput film;
};

#endif
