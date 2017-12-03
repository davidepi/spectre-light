//author: Davide Pizzolotto
//license: GNU GPLv3

#include "camera.hpp"

Camera::Camera(const Point3* pos, const Point3* target, const Vec3* up,
               int, int)
{
    camera2world.setInvLookAtLH(*pos, *target, *up);
}
