//Just for testing purposes
#include "utility.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "point3.hpp"
#include "matrix4.hpp"
#include "AABB.hpp"
int main()
{
    Vec2 v2(0,1);
    Vec3 v3(v2,-1);
    Point3 p1(0,0,0);
    Point3 p2(1,1,1);
    Matrix4 m;
    m.setIdentity();
    AABB aabb(&p1,&p2);
    return 0;
}
