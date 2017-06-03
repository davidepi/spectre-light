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
#include "stratified_sampler.hpp"
#include "box_filter.hpp"
#include "perspective_camera.hpp"
#include "orthographic_camera.hpp"
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
        m->setTranslation(Vec3(i,i,i));
        Sphere *sh = new Sphere(0.5,m);
        sh->obj2world();
        Asset *a = new Asset(sh);
        k->addAsset(a);
    }
    k->buildTree();
    Asset* res;
    if(k->intersect(&r, res))
        std::cout<<"test ok"<<std::endl;
    
    
    Point3 pos(0,0,-10);
    Point3 tar(1,5,0);
    Vec3 up(0,1,0);
    PerspectiveCamera pc(&pos, &tar, &up, 800, 600, "test.ppm",1);
    int spp = 1;
    StratifiedSampler s(0, 800, 0, 600, 1, (unsigned int*)&pc, false);
    BoxFilter* f = new BoxFilter(1.0,1.0);
    pc.film.setFilter(f);
    Sample* sam = (Sample*)malloc(sizeof(Sample)*spp);
    while(s.getSamples(sam))
    {
        pc.createRay(sam, &r);
        if(k->intersect(&r, res))
        {
            Color c;
            c.r =1;
            c.g =1;
            c.b =1;
            pc.film.addPixel(sam, &c);
        }
    }
    pc.film.saveImage();
    
    return 0;
}
