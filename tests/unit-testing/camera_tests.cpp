#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "cameras/camera.hpp"
#include "cameras/camera_perspective.hpp"
#include "cameras/camera_orthographic.hpp"
#include "cameras/camera360.hpp"
#include "samplers/sampler_stratified.hpp"

SPECTRE_TEST_INIT(Camera_tests)

SPECTRE_TEST(Camera, Orthographic_create_ray)
{
    //create sampler
    unsigned int seed[32];
    for(int i = 0; i<32; i++)
        seed[i] = i;
    SamplerStratified sam(0, 2, 0, 2, 4, seed, true);

    //create camera
    Point3 pos(0.f, 0.f, -10.f);
    Point3 target(0.f, 0.f, 100.f);
    Vec3 up(0.f, 1.f, 0.f);

    //square image
    CameraOrthographic camera(&pos, &target, &up, 2, 2);
    Sample samples[4];
    sam.get_samples(samples);
    Ray r0, r1, r2, r3;
    ((Camera*)&camera)->create_ray(samples, &r0);
    ((Camera*)&camera)->create_ray(samples+1, &r1);
    ((Camera*)&camera)->create_ray(samples+2, &r2);
    ((Camera*)&camera)->create_ray(samples+3, &r3);

    Point3 r0origin(-0.842283427f, 0.764850139f, -10);
    Point3 r1origin(-0.480320871f, 0.82242161f, -10.f);
    Point3 r2origin(-0.822956681f, 0.469664872f, -10.f);
    Point3 r3origin(-0.0777702333f, 0.0454626679f, -10.f);
    Vec3 direction(0.f, 0.f, 1.f);

    EXPECT_NEAR(r0.origin.x, r0origin.x, 1e-5f);
    EXPECT_NEAR(r0.origin.y, r0origin.y, 1e-5f);
    EXPECT_NEAR(r0.origin.z, r0origin.z, 1e-5f);
    EXPECT_NEAR(r1.origin.x, r1origin.x, 1e-5f);
    EXPECT_NEAR(r1.origin.y, r1origin.y, 1e-5f);
    EXPECT_NEAR(r1.origin.z, r1origin.z, 1e-5f);
    EXPECT_NEAR(r2.origin.x, r2origin.x, 1e-5f);
    EXPECT_NEAR(r2.origin.y, r2origin.y, 1e-5f);
    EXPECT_NEAR(r2.origin.z, r2origin.z, 1e-5f);
    EXPECT_NEAR(r3.origin.x, r3origin.x, 1e-5f);
    EXPECT_NEAR(r3.origin.y, r3origin.y, 1e-5f);
    EXPECT_NEAR(r3.origin.z, r3origin.z, 1e-5f);
    EXPECT_NEAR(r0.direction.x, direction.x, 1e-5f);
    EXPECT_NEAR(r0.direction.y, direction.y, 1e-5f);
    EXPECT_NEAR(r0.direction.z, direction.z, 1e-5f);
    EXPECT_NEAR(r1.direction.x, direction.x, 1e-5f);
    EXPECT_NEAR(r1.direction.y, direction.y, 1e-5f);
    EXPECT_NEAR(r1.direction.z, direction.z, 1e-5f);
    EXPECT_NEAR(r2.direction.x, direction.x, 1e-5f);
    EXPECT_NEAR(r2.direction.y, direction.y, 1e-5f);
    EXPECT_NEAR(r2.direction.z, direction.z, 1e-5f);
    EXPECT_NEAR(r3.direction.x, direction.x, 1e-5f);
    EXPECT_NEAR(r3.direction.y, direction.y, 1e-5f);
    EXPECT_NEAR(r3.direction.z, direction.z, 1e-5f);

    //horizontal image
    camera = CameraOrthographic(&pos, &target, &up, 2, 1);
    ((Camera*)&camera)->create_ray(samples, &r0);
    ((Camera*)&camera)->create_ray(samples+1, &r1);
    ((Camera*)&camera)->create_ray(samples+2, &r2);
    ((Camera*)&camera)->create_ray(samples+3, &r3);
    r0origin = Point3(-1.68456686f, 0.529700279f, -10);
    r1origin = Point3(-0.960641741f, 0.64484334f, -10.f);
    r2origin = Point3(-1.64591336f, -0.060670197f, -10.f);
    r3origin = Point3(-0.155540466f, -0.909074604f, -10.f);

    EXPECT_NEAR(r0.origin.x, r0origin.x, 1e-5f);
    EXPECT_NEAR(r0.origin.y, r0origin.y, 1e-5f);
    EXPECT_NEAR(r0.origin.z, r0origin.z, 1e-5f);
    EXPECT_NEAR(r1.origin.x, r1origin.x, 1e-5f);
    EXPECT_NEAR(r1.origin.y, r1origin.y, 1e-5f);
    EXPECT_NEAR(r1.origin.z, r1origin.z, 1e-5f);
    EXPECT_NEAR(r2.origin.x, r2origin.x, 1e-5f);
    EXPECT_NEAR(r2.origin.y, r2origin.y, 1e-5f);
    EXPECT_NEAR(r2.origin.z, r2origin.z, 1e-5f);
    EXPECT_NEAR(r3.origin.x, r3origin.x, 1e-5f);
    EXPECT_NEAR(r3.origin.y, r3origin.y, 1e-5f);
    EXPECT_NEAR(r3.origin.z, r3origin.z, 1e-5f);
    EXPECT_NEAR(r0.direction.x, direction.x, 1e-5f);
    EXPECT_NEAR(r0.direction.y, direction.y, 1e-5f);
    EXPECT_NEAR(r0.direction.z, direction.z, 1e-5f);
    EXPECT_NEAR(r1.direction.x, direction.x, 1e-5f);
    EXPECT_NEAR(r1.direction.y, direction.y, 1e-5f);
    EXPECT_NEAR(r1.direction.z, direction.z, 1e-5f);
    EXPECT_NEAR(r2.direction.x, direction.x, 1e-5f);
    EXPECT_NEAR(r2.direction.y, direction.y, 1e-5f);
    EXPECT_NEAR(r2.direction.z, direction.z, 1e-5f);
    EXPECT_NEAR(r3.direction.x, direction.x, 1e-5f);
    EXPECT_NEAR(r3.direction.y, direction.y, 1e-5f);
    EXPECT_NEAR(r3.direction.z, direction.z, 1e-5f);
}

SPECTRE_TEST(Camera, Perspective_create_ray)
{
    //create sampler
    unsigned int seed[32];
    for(int i = 0; i<32; i++)
        seed[i] = i;
    SamplerStratified sam(0, 2, 0, 2, 4, seed, true);

    //create camera
    Point3 pos(0.f, 0.f, -10.f);
    Point3 target(0.f, 0.f, 100.f);
    Vec3 up(0.f, 1.f, 0.f);

    //square image
    CameraPerspective camera(&pos, &target, &up, 2, 2, radians(60));
    Sample samples[4];
    sam.get_samples(samples);
    Ray r0, r1, r2, r3;
    ((Camera*)&camera)->create_ray(samples, &r0);
    ((Camera*)&camera)->create_ray(samples+1, &r1);
    ((Camera*)&camera)->create_ray(samples+2, &r2);
    ((Camera*)&camera)->create_ray(samples+3, &r3);

    Point3 origin(0.f, 0.f, -10);
    Vec3 r0direction(-0.406448096f, 0.369082272f, 0.835809767f);
    Vec3 r1direction(-0.2429993f, 0.416071594f, 0.876262366f);
    Vec3 r2direction(-0.416835636f, 0.237889841f, 0.87730062f);
    Vec3 r3direction(-0.0448400453f, 0.0262124259f, 0.998650133f);

    EXPECT_NEAR(r0.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r0.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r0.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r1.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r1.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r1.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r2.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r2.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r2.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r3.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r3.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r3.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r0.direction.x, r0direction.x, 1e-5f);
    EXPECT_NEAR(r0.direction.y, r0direction.y, 1e-5f);
    EXPECT_NEAR(r0.direction.z, r0direction.z, 1e-5f);
    EXPECT_NEAR(r1.direction.x, r1direction.x, 1e-5f);
    EXPECT_NEAR(r1.direction.y, r1direction.y, 1e-5f);
    EXPECT_NEAR(r1.direction.z, r1direction.z, 1e-5f);
    EXPECT_NEAR(r2.direction.x, r2direction.x, 1e-5f);
    EXPECT_NEAR(r2.direction.y, r2direction.y, 1e-5f);
    EXPECT_NEAR(r2.direction.z, r2direction.z, 1e-5f);
    EXPECT_NEAR(r3.direction.x, r3direction.x, 1e-5f);
    EXPECT_NEAR(r3.direction.y, r3direction.y, 1e-5f);
    EXPECT_NEAR(r3.direction.z, r3direction.z, 1e-5f);

    //horizontal image
    camera = CameraPerspective(&pos, &target, &up, 2, 1, radians(60));
    ((Camera*)&camera)->create_ray(samples, &r0);
    ((Camera*)&camera)->create_ray(samples+1, &r1);
    ((Camera*)&camera)->create_ray(samples+2, &r2);
    ((Camera*)&camera)->create_ray(samples+3, &r3);
    r0direction = Vec3(-0.681037724f, 0.214147553f, 0.700234532f);
    r1direction = Vec3(-0.461194247f, 0.309582621f, 0.83153975f);
    r2direction = Vec3(-0.688629866f, -0.0253836755f, 0.724668562f);
    r3direction = Vec3(-0.0792644619f, -0.463270664f, 0.882664859f);

    EXPECT_NEAR(r0.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r0.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r0.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r1.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r1.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r1.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r2.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r2.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r2.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r3.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r3.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r3.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r0.direction.x, r0direction.x, 1e-5f);
    EXPECT_NEAR(r0.direction.y, r0direction.y, 1e-5f);
    EXPECT_NEAR(r0.direction.z, r0direction.z, 1e-5f);
    EXPECT_NEAR(r1.direction.x, r1direction.x, 1e-5f);
    EXPECT_NEAR(r1.direction.y, r1direction.y, 1e-5f);
    EXPECT_NEAR(r1.direction.z, r1direction.z, 1e-5f);
    EXPECT_NEAR(r2.direction.x, r2direction.x, 1e-5f);
    EXPECT_NEAR(r2.direction.y, r2direction.y, 1e-5f);
    EXPECT_NEAR(r2.direction.z, r2direction.z, 1e-5f);
    EXPECT_NEAR(r3.direction.x, r3direction.x, 1e-5f);
    EXPECT_NEAR(r3.direction.y, r3direction.y, 1e-5f);
    EXPECT_NEAR(r3.direction.z, r3direction.z, 1e-5f);
}

SPECTRE_TEST(Camera, Camera360_create_ray)
{
    //create sampler
    unsigned int seed[32];
    for(int i = 0; i<32; i++)
        seed[i] = i;
    SamplerStratified sam(0, 2, 0, 2, 4, seed, true);

    //create camera
    Point3 pos(0.f, 0.f, -10.f);
    Point3 target(0.f, 0.f, 100.f);
    Vec3 up(0.f, 1.f, 0.f);

    Camera360 camera(&pos, &target, &up, 2, 2);
    Sample samples[4];
    sam.get_samples(samples);
    Ray r0, r1, r2, r3;
    camera.create_ray(samples, &r0);
    camera.create_ray(samples+1, &r1);
    camera.create_ray(samples+2, &r2);
    camera.create_ray(samples+3, &r3);

    Point3 origin(0.f, 0.f, -10);
    Vec3 r0direction(0.317612857f, 0.932554125f, 0.171653703f);
    Vec3 r1direction(-0.0170115158f, 0.961348056f, 0.274810165f);
    Vec3 r2direction(0.628446341f, 0.672623038f, 0.390683413f);
    Vec3 r3direction(-0.967828512f, 0.0713518411f, 0.24128218f);

    EXPECT_NEAR(r0.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r0.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r0.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r1.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r1.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r1.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r2.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r2.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r2.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r3.origin.x, origin.x, 1e-5f);
    EXPECT_NEAR(r3.origin.y, origin.y, 1e-5f);
    EXPECT_NEAR(r3.origin.z, origin.z, 1e-5f);
    EXPECT_NEAR(r0.direction.x, r0direction.x, 1e-5f);
    EXPECT_NEAR(r0.direction.y, r0direction.y, 1e-5f);
    EXPECT_NEAR(r0.direction.z, r0direction.z, 1e-5f);
    EXPECT_NEAR(r1.direction.x, r1direction.x, 1e-5f);
    EXPECT_NEAR(r1.direction.y, r1direction.y, 1e-5f);
    EXPECT_NEAR(r1.direction.z, r1direction.z, 1e-5f);
    EXPECT_NEAR(r2.direction.x, r2direction.x, 1e-5f);
    EXPECT_NEAR(r2.direction.y, r2direction.y, 1e-5f);
    EXPECT_NEAR(r2.direction.z, r2direction.z, 1e-5f);
    EXPECT_NEAR(r3.direction.x, r3direction.x, 1e-5f);
    EXPECT_NEAR(r3.direction.y, r3direction.y, 1e-5f);
    EXPECT_NEAR(r3.direction.z, r3direction.z, 1e-5f);
}

SPECTRE_TEST_END(Camera_tests)
