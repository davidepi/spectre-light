#ifndef __PERSPECTIVE_CAMERA_HPP__
#define __PERSPECTIVE_CAMERA_HPP__

#include "camera.hpp"

class PerspectiveCamera : public Camera
{
public:
    
    PerspectiveCamera(const Point3* position,const Point3* target,
                       const Vec3* up, int width, int height,
                       const char* filename, const float bounds[4], float fov);
    ~PerspectiveCamera();
    void createRay(Sample* s, Ray* r)const;
};

#endif
