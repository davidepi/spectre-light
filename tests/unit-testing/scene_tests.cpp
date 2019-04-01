#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "primitives/sphere.hpp"
#include "materials/lambertian.hpp"
#include "utility/scene.hpp"
#include "utility/utility.hpp"
#include "lights/light_omni.hpp"
#include "lights/light_sky.hpp"
#include <climits>

SPECTRE_TEST_INIT(Scene_tests)

SPECTRE_TEST(Scene, inherit_shape)
{
    Sphere* sphere = new Sphere;
    Scene scene;
    EXPECT_EQ(scene.size_shapes(), (unsigned int)0);
    scene.inherit_shape(sphere);
    EXPECT_EQ(scene.size_shapes(), (unsigned int)1);

    //add duplicate
    scene.inherit_shape(sphere);
    EXPECT_EQ(scene.size_shapes(), (unsigned int)1);
}

SPECTRE_TEST(Scene, inherit_asset)
{

    Scene scene;
    Sphere* sphere = new Sphere();
    Matrix4 transform;
    transform.set_identity();
    Asset* addme = new Asset(sphere, transform, 1);
    EXPECT_EQ(scene.size_assets(), (unsigned int)0);
    scene.inherit_shape(sphere);
    scene.inherit_asset(addme);
    EXPECT_EQ(scene.size_shapes(), (unsigned int)1);
    EXPECT_EQ(scene.size_assets(), (unsigned int)1);

    //duplicates can not be added
    scene.inherit_asset(addme);
    EXPECT_EQ(scene.size_assets(), (unsigned int)1);
}

SPECTRE_TEST(Scene, radius)
{
    Scene scene;
    Sphere* sphere = new Sphere();
    Matrix4 transform;
    transform.set_identity();
    scene.inherit_shape(sphere);

    Asset* addme = new Asset(sphere, transform, 1);
    scene.inherit_asset(addme);
    EXPECT_EQ(scene.radius(), sqrtf(1+1+1));

    transform.set_scale(Vec3(-10.f, 0, 0));
    addme = new Asset(sphere, transform, 1);
    scene.inherit_asset(addme);
    EXPECT_EQ(scene.radius(), sqrtf(-10.f*-10.f+(-1.f*-1.f)+(-1.f*-1.f)));
}

SPECTRE_TEST(Scene, inherit_light)
{
    Matrix4 transform;
    transform.set_identity();
    LightOmni* addme = new LightOmni(SPECTRUM_WHITE, transform);
    Scene scene;
    scene.inherit_light(addme);
    EXPECT_EQ(scene.size_lights(), (unsigned int)1);

    //fill up
    for(int i = scene.size_lights(); i<_MAX_LIGHTS_; i++)
        scene.inherit_light(new LightOmni(SPECTRUM_WHITE, transform));
    ASSERT_EQ(scene.size_lights(), _MAX_LIGHTS_);
    //add extra light
    LightOmni* last_light = new LightOmni(SPECTRUM_WHITE, transform);
    errors_count[WARNING_INDEX] = 0;
    scene.inherit_light(last_light);
    ASSERT_EQ(errors_count[WARNING_INDEX], 1);
    delete last_light;
}

SPECTRE_TEST(Scene, inherit_area_light)
{
    Scene scene;
    Sphere* sphere = new Sphere();
    Matrix4 transform;
    transform.set_identity();
    Asset* addme1 = new LightArea(sphere, transform, Spectrum(1500));
    EXPECT_EQ(scene.size_assets(), (unsigned int)0);
    EXPECT_EQ(scene.size_lights(), (unsigned int)0);
    scene.inherit_shape(sphere);
    scene.inherit_asset(addme1);
    EXPECT_EQ(scene.size_assets(), (unsigned int)1);
    EXPECT_EQ(scene.size_lights(), (unsigned int)0);

    Asset* addme2 = new LightArea(sphere, transform, Spectrum(1500));
    scene.inherit_arealight((LightArea*)addme2);
    EXPECT_EQ(scene.size_assets(), (unsigned int)2);
    EXPECT_EQ(scene.size_lights(), (unsigned int)1);

    //don't add duplicates
    for(int i = scene.size_lights(); i<_MAX_LIGHTS_; i++)
        scene.inherit_arealight((LightArea*)addme1);
    EXPECT_EQ(scene.size_assets(), (unsigned int)2);
    EXPECT_EQ(scene.size_lights(), (unsigned int)1);

    //fill all lights
    for(int i = scene.size_lights(); i<_MAX_LIGHTS_; i++)
        scene.inherit_arealight(
                new LightArea(sphere, transform, Spectrum(1500)));
    EXPECT_EQ(scene.size_lights(), (unsigned int)_MAX_LIGHTS_);

    //add extra light
    errors_count[WARNING_INDEX] = 0;
    LightArea* last_light = new LightArea(sphere, transform, Spectrum(1500));
    scene.inherit_arealight(last_light);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
}

SPECTRE_TEST(Scene, get_lights)
{
    Scene scene;
    Sphere* sphere = new Sphere();
    Matrix4 transform;
    transform.set_identity();
    const LightArea* values[_MAX_LIGHTS_];
    for(int i = 0; i<_MAX_LIGHTS_; i++)
    {
        values[i] = new LightArea(sphere, transform, Spectrum(1500));
        scene.inherit_arealight(values[i]);
    }
    for(unsigned int i = 0; i<scene.size_lights(); i++)
        EXPECT_PTR_EQ(scene.get_light(i), values[i]);
}

SPECTRE_TEST(Scene, inherit_sky)
{
    TextureUniform tex(SPECTRUM_WHITE);
    LightSky* sky = new LightSky(&tex, 10.f);
    Scene scene;
    Ray r(Point3(2, 2, 2), Vec3(0, 0, 1));

    //assert no sky is present
    EXPECT_TRUE(scene.get_escaped_radiance(&r).is_black());

    //inherit the sky
    scene.inherit_sky(sky);

    //assert the radiance is changed -> there is the sky
    Spectrum res = scene.get_escaped_radiance(&r);
    EXPECT_NEAR(res.w[0], 0.95f, 1e-2f);
    EXPECT_NEAR(res.w[1], 1.f, 1e-2f);
    EXPECT_NEAR(res.w[2], 1.08f, 1e-2f);
}

SPECTRE_TEST_END(Scene_tests)
