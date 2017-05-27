#include "camera.hpp"

Camera::Camera(const Point3* p, const Point3* t, const Vec3* u,
               int w, int h, const char* o) : film(w,h,o)
{
    raster2world.setLookAtLH(*p, *t, *u);
}

Camera::~Camera()
{
    
}
