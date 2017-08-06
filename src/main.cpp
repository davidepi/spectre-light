#include "utility/scene.hpp"
#include "primitives/sphere.hpp"
#include "primitives/box.hpp"
#include "primitives/triangle.hpp"
#include "renderer.hpp"
#include <cstdlib> //atoi, exit
#include "materials/oren_nayar.hpp"
#include "materials/reflection.hpp"
#include "materials/refraction.hpp"
#ifndef WIN32
#include <getopt.h>
#include <primitives/mesh.hpp>


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
    Box* bb = new Box(Vec3(1,1.5,1));

    Mesh* me = new Mesh(20);
    Point3 p01(0.000000,0.000000,0.000000);
    Point3 p02(0.723600,0.552785,0.525720);
    Point3 p03(-0.276385,0.552785,0.850640);
    Point3 p04(-0.894425,0.552785,0.000000);
    Point3 p05(-0.276385,0.552785,-0.850640);
    Point3 p06(0.723600,0.552785,-0.525720);
    Point3 p07(0.276385,1.447215,0.850640);
    Point3 p08(-0.723600,1.447215,0.525720);
    Point3 p09(-0.723600,1.447215,-0.525720);
    Point3 p10(0.276385,1.447215,-0.850640);
    Point3 p11(0.894425,1.447215,0.000000);
    Point3 p12(0.000000,2.000000,0.000000);
    Normal n0;

    me->addTriangle(&p01,&p02,&p03,&n0);
    me->addTriangle(&p02,&p01,&p06,&n0);
    me->addTriangle(&p01,&p03,&p04,&n0);
    me->addTriangle(&p01,&p04,&p05,&n0);
    me->addTriangle(&p01,&p05,&p06,&n0);
    me->addTriangle(&p02,&p06,&p11,&n0);
    me->addTriangle(&p03,&p02,&p07,&n0);
    me->addTriangle(&p04,&p03,&p08,&n0);
    me->addTriangle(&p05,&p04,&p09,&n0);
    me->addTriangle(&p06,&p05,&p10,&n0);
    me->addTriangle(&p02,&p11,&p07,&n0);
    me->addTriangle(&p03,&p07,&p08,&n0);
    me->addTriangle(&p04,&p08,&p09,&n0);
    me->addTriangle(&p05,&p09,&p10,&n0);
    me->addTriangle(&p06,&p10,&p11,&n0);
    me->addTriangle(&p07,&p11,&p12,&n0);
    me->addTriangle(&p08,&p07,&p12,&n0);
    me->addTriangle(&p09,&p08,&p12,&n0);
    me->addTriangle(&p10,&p09,&p12,&n0);
    me->addTriangle(&p11,&p10,&p12,&n0);
    me->finalize();


    Matrix4 m1; m1.setTranslation(Vec3(0,3.25,0));
    Matrix4 mbot; mbot.setTranslation(Vec3(0,-1e5,0));
    Matrix4 mleft; mleft.setTranslation(Vec3(-1e5-3,0,0));
    Matrix4 mright; mright.setTranslation(Vec3(1e5+3,0,0));
    Matrix4 mfront; mfront.setTranslation(Vec3(0,0,1e5+3));
    Matrix4 mtop; mtop.setTranslation(Vec3(0,1e5+3,0));
    Matrix4 sphere; sphere.setTranslation(Vec3(1,1,-1));
    Matrix4 box; box.setScale(2);
    Matrix4 triangle; triangle.setIdentity();

    s.inheritShape(sp);
    s.inheritShape(s2);
    s.inheritShape(bb);
    s.inheritShape(me);

    Bsdf onl,onr,glass;
    Bdf* b1 = new OrenNayar(Color(0.25,0.75,0.25),1);
    Bdf* b2 = new OrenNayar(Color(0.75,0.25,0.25),1);
    Bdf* b3 = new Reflection(Color(1.0),1.0f,1.5f);
    Bdf* b4 = new Refraction(Color(1.0),1.0f,1.5f);
    onr.addBdf(b1);
    onl.addBdf(b2);
    glass.addBdf(b3);
    glass.addBdf(b4);

    s.addLight(sp->getID(),&m1,Color(1));
    s.addAsset(s2->getID(),&mbot);
    s.addAsset(s2->getID(),&mleft,&onl);
    s.addAsset(s2->getID(),&mright,&onr);
    s.addAsset(s2->getID(),&mfront);
    s.addAsset(s2->getID(),&mtop);
    //s.addAsset(bb->getID(),&box);
    s.addAsset(me->getID(),&triangle);

    r.setStratifiedSampler();
    r.setPerspective(Point3(0,2,-5),Point3(0,0,0),Vec3(0,1,0),1);
    r.setMitchellFilter(1/3.f,1/3.f);
    r.setPathTracer();
    return r.render(&s);
}
