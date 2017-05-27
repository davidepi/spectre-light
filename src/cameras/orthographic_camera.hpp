#ifndef __ORTHOGRAPHIC_CAMERA_HPP__
#define __ORTHOGRAPHIC_CAMERA_HPP__

#include "camera.hpp"

class OrthographicCamera : public Camera
{
public:
    
    OrthographicCamera(const Point3* position,const Point3* target,
                       const Vec3* up, int width, int height,
                       const char* filename, const float bounds[4]);
    ~OrthographicCamera();
    void createRay(Sample* s, Ray* r)const;
};

#endif
