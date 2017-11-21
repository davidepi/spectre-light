#include "camera360.hpp"

Camera360::Camera360(const Point3* p,const Point3* t,
                     const Vec3* u, int w, int h) : Camera(p,t,u,w,h)
{
    Camera360::invX = 1.f/w;
    Camera360::invY = 1.f/h;
}

void Camera360::createRay(Sample *s, Ray *r)const
{
    float t = (float)ONE_PI * s->posy * Camera360::invY;
    float p = TWO_PI * s->posx * Camera360::invX;

    r->origin = camera2world * Point3(0,0,0);
    r->direction = camera2world * Vec3(sinf(t)*cosf(p),cosf(t),sinf(t)*sinf(p));
    r->direction.normalize();
}
