//Just for testing purposes
#include <iostream>
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
#include "kdtree.hpp"
#include "wellrng.hpp"
#include "sampler.hpp"
#include "console.hpp"
int main()
{
    unsigned int seed[32];
    WELLrng rng(seed);
    Ray r(Point3(0,0,-10),Vec3(0,0,1));
    KdTree* k = new KdTree;
    for(int i=0;i<100;i++)
    {
        Matrix4 *m = new Matrix4();
        float f1 = rng.getNumberf();
        float f2 = rng.getNumberf();
        float f3 = rng.getNumberf();
        m->setTranslation(Vec3(f1,f2,f3));
        Sphere *s = new Sphere(1,m);
        s->obj2world();
        Asset *a = new Asset(s);
        k->addAsset(a);
    }
    k->buildTree();
    Asset* res;
    k->intersect(&r, res);
    delete k;
    
    
    return 0;
}
