#include "sphere.hpp"
#include "renderer.hpp"
int main()
{
    Renderer r(800,600,1,"/home/davide/Desktop/test.ppm");
    Scene s;
    for(int i=0;i<100;i++)
    {
        Sphere* sp = new Sphere(1);
        Matrix4* m = new Matrix4();
        m->setTranslation(Vec3(i,i,i));
        s.addAsset(s.inheritShape(sp),m);
    }
    r.setPerspective(Point3(0,0,-10),Point3(0,0,0),Vec3(0,1,0),1);
    r.setMitchellFilter(1.f/3.f,1.f/3.f);
    return r.render(&s);
}
