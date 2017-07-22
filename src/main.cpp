#include "utility/scene.hpp"
#include "primitives/sphere.hpp"
#include "renderer.hpp"
#include <cstdlib> //atoi, exit
#include "materials/oren_nayar.hpp"
#ifndef WIN32
#include <getopt.h>
#endif
int main(int argc, char* argv[])
{
    int width = 800;
    int height = 600;
    int spp = 256;
    int threads = 0;
	char output[256];
	char input[256];
    int flags, opt;
	strcpy(output,"test.ppm");
#ifndef WIN32
    while ((opt = getopt(argc, argv, "o:w:h:s:t:")) != -1)
    {
        switch (opt)
        {
            case 'o':
                    strncpy(output,optarg,sizeof(output));
                break;
            case 'w':
                    width = atoi(optarg);
                break;
            case 'h':
                    height = atoi(optarg);
                break;
            case 's':
                    spp = atoi(optarg);
                break;
            case 't':
                    threads = atoi(optarg);
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s -o output [-i name | -w width -h"
                                " height -s spp] \n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }
#endif
    Renderer r(width,height,spp,output,threads);
    Scene s;
    Sphere* sp = new Sphere(1);
    Sphere* s2 = new Sphere(1e5);

    Matrix4 m1; m1.setTranslation(Vec3(0,4,0));
    Matrix4 mbot; mbot.setTranslation(Vec3(0,-1e5,0));
    Matrix4 mleft; mleft.setTranslation(Vec3(-1e5-3,0,0));
    Matrix4 mright; mright.setTranslation(Vec3(1e5+3,0,0));
    Matrix4 mfront; mfront.setTranslation(Vec3(0,0,1e5+3));
    Matrix4 sphere; sphere.setTranslation(Vec3(0,1,-1));

    s.inheritShape(sp);
    s.inheritShape(s2);

    Bsdf onl,onr,onn;
    Bdf* b = new OrenNayar(Color(0.25,0.75,0.25),1);
    Bdf* b2 = new OrenNayar(Color(0.75,0.25,0.25),1);
    Bdf* b3 = new OrenNayar(Color(0.25,0.25,0.25),20);
    onr.addBdf(b);
    onl.addBdf(b2);
    onn.addBdf(b3);

    s.addLight(sp->getID(),&m1,Color(1));
    s.addAsset(s2->getID(),&mbot);
    s.addAsset(s2->getID(),&mleft,&onl);
    s.addAsset(s2->getID(),&mright,&onr);
    s.addAsset(s2->getID(),&mfront);
    s.addAsset(sp->getID(),&sphere,&onn);

    r.setPerspective(Point3(0,2,-5),Point3(0,0,0),Vec3(0,1,0),1);
    r.setMitchellFilter(1/3.f,1/3.f);
    r.setRayTracer();
    return r.render(&s);
}
