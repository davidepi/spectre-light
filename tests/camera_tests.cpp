
#include <gtest/gtest.h>


#include "cameras/camera.hpp"
#include "cameras/perspective_camera.hpp"
#include "cameras/orthographic_camera.hpp"
#include "cameras/camera360.hpp"
#include "samplers/stratified_sampler.hpp"

TEST(Camera,Orthographic_create_ray)
{
    //create sampler
    unsigned int seed[32];
    for(int i=0;i<32;i++)
        seed[i] = i;
    StratifiedSampler sam(0,2,0,2,4,seed,true);

    //create camera
    Point3 pos(0.f,0.f,-10.f);
    Point3 target(0.f,0.f,100.f);
    Vec3 up(0.f,1.f,0.f);

    //square image
    OrthographicCamera camera(&pos,&target,&up,2,2);
    Sample samples[4];
    sam.get_samples(samples);
    Ray r0,r1,r2,r3;
    camera.create_ray(samples,&r0);
    camera.create_ray(samples+1,&r1);
    camera.create_ray(samples+2,&r2);
    camera.create_ray(samples+3,&r3);

    Point3 r0origin(-0.842283427f,0.764850139f,-10);
    Point3 r1origin(-0.480320871f,0.82242161f,-10.f);
    Point3 r2origin(-0.822956681f,0.469664872f,-10.f);
    Point3 r3origin(-0.0777702333f,0.0454626679f,-10.f);
    Vec3 direction(0.f,0.f,1.f);

    EXPECT_EQ(r0.origin,r0origin);
    EXPECT_EQ(r1.origin,r1origin);
    EXPECT_EQ(r2.origin,r2origin);
    EXPECT_EQ(r3.origin,r3origin);
    EXPECT_EQ(r0.direction,direction);
    EXPECT_EQ(r1.direction,direction);
    EXPECT_EQ(r2.direction,direction);
    EXPECT_EQ(r3.direction,direction);

    //horizontal image
    camera = OrthographicCamera(&pos,&target,&up,2,1);
    camera.create_ray(samples,&r0);
    camera.create_ray(samples+1,&r1);
    camera.create_ray(samples+2,&r2);
    camera.create_ray(samples+3,&r3);
    r0origin = Point3(-1.68456686f,0.529700279f,-10);
    r1origin = Point3(-0.960641741f,0.64484334f,-10.f);
    r2origin = Point3(-1.64591336f,-0.060670197f,-10.f);
    r3origin = Point3(-0.155540466f,-0.909074604f,-10.f);

    EXPECT_EQ(r0.origin,r0origin);
    EXPECT_EQ(r1.origin,r1origin);
    EXPECT_EQ(r2.origin,r2origin);
    EXPECT_EQ(r3.origin,r3origin);
    EXPECT_EQ(r0.direction,direction);
    EXPECT_EQ(r1.direction,direction);
    EXPECT_EQ(r2.direction,direction);
    EXPECT_EQ(r3.direction,direction);
}

TEST(Camera,Perspective_create_ray)
{
    //create sampler
    unsigned int seed[32];
    for(int i=0;i<32;i++)
        seed[i] = i;
    StratifiedSampler sam(0,2,0,2,4,seed,true);

    //create camera
    Point3 pos(0.f,0.f,-10.f);
    Point3 target(0.f,0.f,100.f);
    Vec3 up(0.f,1.f,0.f);

    //square image
    PerspectiveCamera camera(&pos,&target,&up,2,2,radians(60));
    Sample samples[4];
    sam.get_samples(samples);
    Ray r0,r1,r2,r3;
    camera.create_ray(samples,&r0);
    camera.create_ray(samples+1,&r1);
    camera.create_ray(samples+2,&r2);
    camera.create_ray(samples+3,&r3);

    Point3 origin(0.f,0.f,-10);
    Vec3 r0direction(-0.406448096f,0.369082272f,0.835809767f);
    Vec3 r1direction(-0.2429993f,0.416071594f,0.876262366f);
    Vec3 r2direction(-0.416835636f,0.237889841f,0.87730062f);
    Vec3 r3direction(-0.0448400453f,0.0262124259f,0.998650133f);

    EXPECT_EQ(r0.origin,origin);
    EXPECT_EQ(r1.origin,origin);
    EXPECT_EQ(r2.origin,origin);
    EXPECT_EQ(r3.origin,origin);
    EXPECT_EQ(r0.direction,r0direction);
    EXPECT_EQ(r1.direction,r1direction);
    EXPECT_EQ(r2.direction,r2direction);
    EXPECT_EQ(r3.direction,r3direction);

    //horizontal image
    camera = PerspectiveCamera(&pos,&target,&up,2,1,radians(60));
    camera.create_ray(samples,&r0);
    camera.create_ray(samples+1,&r1);
    camera.create_ray(samples+2,&r2);
    camera.create_ray(samples+3,&r3);
    r0direction = Vec3(-0.681037724f,0.214147553f,0.700234532f);
    r1direction = Vec3(-0.461194247f,0.309582621f,0.83153975f);
    r2direction = Vec3(-0.688629866f,-0.0253836755f,0.724668562f);
    r3direction = Vec3(-0.0792644619f,-0.463270664f,0.882664859f);

    EXPECT_EQ(r0.origin,origin);
    EXPECT_EQ(r1.origin,origin);
    EXPECT_EQ(r2.origin,origin);
    EXPECT_EQ(r3.origin,origin);
    EXPECT_EQ(r0.direction,r0direction);
    EXPECT_EQ(r1.direction,r1direction);
    EXPECT_EQ(r2.direction,r2direction);
    EXPECT_EQ(r3.direction,r3direction);
}

TEST(Camera,Camera360_create_ray)
{
    //create sampler
    unsigned int seed[32];
    for(int i=0;i<32;i++)
        seed[i] = i;
    StratifiedSampler sam(0,2,0,2,4,seed,true);

    //create camera
    Point3 pos(0.f,0.f,-10.f);
    Point3 target(0.f,0.f,100.f);
    Vec3 up(0.f,1.f,0.f);

    Camera360 camera(&pos,&target,&up,2,2);
    Sample samples[4];
    sam.get_samples(samples);
    Ray r0,r1,r2,r3;
    camera.create_ray(samples,&r0);
    camera.create_ray(samples+1,&r1);
    camera.create_ray(samples+2,&r2);
    camera.create_ray(samples+3,&r3);

    Point3 origin(0.f,0.f,-10);
    Vec3 r0direction(0.317612857f,0.932554125f,0.171653703f);
    Vec3 r1direction(-0.0170115158f,0.961348056f,0.274810165f);
    Vec3 r2direction(0.628446341f,0.672623038f,0.390683413f);
    Vec3 r3direction(-0.967828512f,0.0713518411f,0.24128218f);

    EXPECT_FLOAT_EQ(r0.origin.x,origin.x);
    EXPECT_FLOAT_EQ(r0.origin.y,origin.y);
    EXPECT_FLOAT_EQ(r0.origin.z,origin.z);
    EXPECT_FLOAT_EQ(r1.origin.x,origin.x);
    EXPECT_FLOAT_EQ(r1.origin.y,origin.y);
    EXPECT_FLOAT_EQ(r1.origin.z,origin.z);
    EXPECT_FLOAT_EQ(r2.origin.x,origin.x);
    EXPECT_FLOAT_EQ(r2.origin.y,origin.y);
    EXPECT_FLOAT_EQ(r2.origin.z,origin.z);
    EXPECT_FLOAT_EQ(r3.origin.x,origin.x);
    EXPECT_FLOAT_EQ(r3.origin.y,origin.y);
    EXPECT_FLOAT_EQ(r3.origin.z,origin.z);
    EXPECT_FLOAT_EQ(r0.direction.x,r0direction.x);
    EXPECT_FLOAT_EQ(r0.direction.y,r0direction.y);
    EXPECT_FLOAT_EQ(r0.direction.z,r0direction.z);
    EXPECT_FLOAT_EQ(r1.direction.x,r1direction.x);
    EXPECT_FLOAT_EQ(r1.direction.y,r1direction.y);
    EXPECT_FLOAT_EQ(r1.direction.z,r1direction.z);
    EXPECT_FLOAT_EQ(r2.direction.x,r2direction.x);
    EXPECT_FLOAT_EQ(r2.direction.y,r2direction.y);
    EXPECT_FLOAT_EQ(r2.direction.z,r2direction.z);
    EXPECT_FLOAT_EQ(r3.direction.x,r3direction.x);
    EXPECT_FLOAT_EQ(r3.direction.y,r3direction.y);
    EXPECT_FLOAT_EQ(r3.direction.z,r3direction.z);
}

