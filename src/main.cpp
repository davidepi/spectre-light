//Just for testing purposes
#include "settings.h"
#include "utility.hpp"
#include "AABB.hpp"
#include "point3.hpp"
#include "ray.hpp"
#include "matrix4.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "shape.hpp"
#include "asset.hpp"
#include "box.hpp"
#include "sphere.hpp"
int main()
{
    Point3 pmin(0,0,0), pmax(1,1,1);
    AABB a(&pmin,&pmax);
    Ray r(Point3(0.5,0,0.5),Vec3(1,0,0));
    RayProperties rp;
    rp.inverseX = 1.0f/r.direction.x;
    rp.inverseY = 1.0f/r.direction.y;
    rp.inverseZ = 1.0f/r.direction.z;
    rp.isXInvNeg = rp.inverseX<0;
    rp.isYInvNeg = rp.inverseY<0;
    rp.isZInvNeg = rp.inverseZ<0;
    return 0;
}
