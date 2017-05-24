#include "camera.hpp"

Camera::Camera(Vec3* pos, int w, int h, const char* o) : position(*pos),
film(w,h,o)
{
    
}

Camera::~Camera()
{
    
}
