//author: Davide Pizzolotto
//license: GNU GPLv3

#include "camera360.hpp"

Camera360::Camera360(const Point3* pos,const Point3* target,
                     const Vec3* up, int width, int height)
:Camera(pos,target,up,width,height)
{
    Camera360::invX = 1.f/width;
    Camera360::invY = 1.f/height;
}

void Camera360::createRay(Sample* sample, Ray* ray)const
{
    float theta = (float)ONE_PI * sample->posy * Camera360::invY;
    float phi = TWO_PI * sample->posx * Camera360::invX;

    ray->origin = camera2world * Point3(0,0,0);
    ray->direction = camera2world * Vec3(sinf(theta)*cosf(phi),cosf(theta),
                                         sinf(theta)*sinf(phi));
    ray->direction.normalize();
}
