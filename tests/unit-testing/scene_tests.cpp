#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#else

#include <gtest/gtest.h>

#endif

SPECTRE_TEST_INIT(Scene_tests)

#include "primitives/sphere.hpp"
#include "materials/lambertian.hpp"
#include "utility/scene.hpp"
#include "utility/utility.hpp"
#include <climits>

SPECTRE_TEST(Scene, inherit_shape)
{
    Sphere* sphere = new Sphere;
    Scene scene;
    EXPECT_EQ(scene.size_shapes(), 0);
    scene.inherit_shape(sphere);
    EXPECT_EQ(scene.size_shapes(), 1);

    //add duplicate
    scene.inherit_shape(sphere);
    EXPECT_EQ(scene.size_shapes(), 1);
}

SPECTRE_TEST(Scene, inherit_asset)
{

    Scene scene;
    Sphere* sphere = new Sphere();
    Matrix4 transform;
    transform.set_identity();
    Asset* addme = new Asset(sphere, transform, 1);
    EXPECT_EQ(scene.size_assets(), 0);
    scene.inherit_shape(sphere);
    scene.inherit_asset(addme);
    EXPECT_EQ(scene.size_shapes(), 1);
    EXPECT_EQ(scene.size_assets(), 1);

    //duplicates can not be added
    scene.inherit_asset(addme);
    EXPECT_EQ(scene.size_assets(), 1);
}

SPECTRE_TEST(Scene, inherit_light)
{
    Scene scene;
    Sphere* sphere = new Sphere();
    Matrix4 transform;
    transform.set_identity();
    Asset* addme1 = new AreaLight(sphere, transform, Spectrum(1500));
    EXPECT_EQ(scene.size_assets(), 0);
    EXPECT_EQ(scene.size_lights(), 0);
    scene.inherit_shape(sphere);
    scene.inherit_asset(addme1);
    EXPECT_EQ(scene.size_assets(), 1);
    EXPECT_EQ(scene.size_lights(), 0);

    Asset* addme2 = new AreaLight(sphere, transform, Spectrum(1500));
    scene.inherit_light((AreaLight*)addme2);
    EXPECT_EQ(scene.size_assets(), 2);
    EXPECT_EQ(scene.size_lights(), 1);

    //don't add duplicates
    for(int i = scene.size_lights(); i<_MAX_LIGHTS_; i++)
        scene.inherit_light((AreaLight*)addme1);
    EXPECT_EQ(scene.size_assets(), 2);
    EXPECT_EQ(scene.size_lights(), 1);

    //fill all lights
    for(int i = scene.size_lights(); i<_MAX_LIGHTS_; i++)
        scene.inherit_light(new AreaLight(sphere, transform, Spectrum(1500)));
    EXPECT_EQ(scene.size_lights(), _MAX_LIGHTS_);

    //add extra light
    errors_count[WARNING_INDEX] = 0;
    AreaLight* last_light = new AreaLight(sphere, transform, Spectrum(1500));
    scene.inherit_light(last_light);
    EXPECT_EQ(errors_count[WARNING_INDEX], 1);
    errors_count[WARNING_INDEX] = 0;
}

SPECTRE_TEST(Scene, get_lights)
{
    Scene scene;
    Sphere* sphere = new Sphere();
    Matrix4 transform;
    transform.set_identity();
    const AreaLight* values[_MAX_LIGHTS_];
    for(int i = 0; i<_MAX_LIGHTS_; i++)
    {
        values[i] = new AreaLight(sphere, transform, Spectrum(1500));
        scene.inherit_light(values[i]);
    }
    for(int i = 0; i<scene.size_lights(); i++)
        EXPECT_EQ(scene.get_light(i), values[i]);
}

SPECTRE_TEST_END(Scene_tests)
