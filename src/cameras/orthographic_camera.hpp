#ifndef __ORTHOGRAPHIC_CAMERA_HPP__
#define __ORTHOGRAPHIC_CAMERA_HPP__

#include "camera.hpp"

class OrthographicCamera : public Camera
{
public:
    
    OrthographicCamera(Vec3* position, int width, int height,
                       const char* filename);
    ~OrthographicCamera();
    void createRay(Sample* s, Ray* r);
};

#endif
