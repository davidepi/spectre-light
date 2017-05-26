#include "orthographic_camera.hpp"

OrthographicCamera::OrthographicCamera(Vec3* p, int w, int h, const char* f)
: Camera(p,w,h,f)
{
    
}

OrthographicCamera::~OrthographicCamera()
{
    
}

void OrthographicCamera::createRay(Sample *s, Ray *r)
{
    
}
