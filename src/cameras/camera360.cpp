//author: Davide Pizzolotto
//license: GNU GPLv3

#include "camera360.hpp"

Camera360::Camera360(const Point3& pos, const Point3& target,
                     const Vec3& up, int width, int height)
        :Camera(pos, target, up, width, height)
{
    Camera360::invX = 1.f/width;
    Camera360::invY = 1.f/height;
}

void Camera360::create_single_ray(const Sample* sample, Point3* origin,
                                  Vec3* direction) const
{
    float theta = (float)ONE_PI*sample->posy*Camera360::invY;
    float phi = TWO_PI*sample->posx*Camera360::invX;

    *origin = camera2world*Point3(0, 0, 0);
    *direction = camera2world*Vec3(sinf(theta)*cosf(phi), cosf(theta),
                                   sinf(theta)*sinf(phi));
    direction->normalize();
}
