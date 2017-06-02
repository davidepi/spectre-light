#include "camera.hpp"

Camera::Camera(const Point3* p, const Point3* t, const Vec3* u,
               int w, int h, const char* o) : film(w,h,o)
{
    camera2world.setInvLookAtLH(*p, *t, *u);
}

Camera::~Camera()
{
    
}
