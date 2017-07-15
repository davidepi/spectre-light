#include "utility/scene.hpp"
#include "primitives/sphere.hpp"
#include "renderer.hpp"
int main()
{
    Renderer r(800,600,1,"test.ppm");
    Scene s;
    Sphere* sp = new Sphere(1);
    Matrix4* m = new Matrix4();
    m->setTranslation(Vec3(0,0,0));
    s.addLight(s.inheritShape(sp),m,Color(1));
    for(int i=2;i<100;i+=2)
    {
        Sphere* sp = new Sphere(1);
        Matrix4* m = new Matrix4();
        m->setTranslation(Vec3(i,i,i));
        s.addAsset(s.inheritShape(sp),m);
    }
    r.setPerspective(Point3(0,0,-10),Point3(0,0,0),Vec3(0,1,0),1);
    r.setTentFilter();
    return r.render(&s);
}
