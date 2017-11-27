//author: Davide Pizzolotto
//license: GNU GPLv3

#include "camera.hpp"

Camera::Camera(const Point3* p, const Point3* t, const Vec3* u,
               int, int)
{
    camera2world.setInvLookAtLH(*p, *t, *u);
}
