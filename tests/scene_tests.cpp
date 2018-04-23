
#include <gtest/gtest.h>


#include "primitives/sphere.hpp"
#include "materials/lambertian.hpp"
#include "utility/scene.hpp"
#include "utility/utility.hpp"
#include <climits>

TEST(Scene,inherit_shape)
{
    Sphere* sphere = new Sphere;
    Scene scene;
    EXPECT_EQ(scene.shapes_size(), 0);
    scene.inherit_shape(sphere);
    EXPECT_EQ(scene.shapes_size(), 1);

    //add duplicate
    scene.inherit_shape(sphere);
    EXPECT_EQ(scene.shapes_size(), 1);
}

TEST(Scene,inherit_asset)
{

    Scene scene;
    Sphere* sphere = new Sphere();
    Matrix4 transform;
    transform.set_identity();
    Asset* addme = new Asset(sphere,transform,1);
    EXPECT_EQ(scene.assets_size(), 0);
    scene.inherit_shape(sphere);
    scene.inherit_asset(addme);
    EXPECT_EQ(scene.shapes_size(), 1);
    EXPECT_EQ(scene.assets_size(), 1);

    //duplicates can not be added
    scene.inherit_asset(addme);
    EXPECT_EQ(scene.assets_size(), 1);
}

TEST(Scene,inherit_light)
{
    Scene scene;
    Sphere* sphere = new Sphere();
    Matrix4 transform;
    transform.set_identity();
    Asset* addme1 = new AreaLight(sphere,transform,Spectrum(1500));
    EXPECT_EQ(scene.assets_size(), 0);
    EXPECT_EQ(scene.lights_size(), 0);
    scene.inherit_shape(sphere);
    scene.inherit_asset(addme1);
    EXPECT_EQ(scene.assets_size(), 1);
    EXPECT_EQ(scene.lights_size(), 0);

    Asset* addme2 = new AreaLight(sphere,transform,Spectrum(1500));
    scene.inherit_light((AreaLight*)addme2);
    EXPECT_EQ(scene.assets_size(), 2);
    EXPECT_EQ(scene.lights_size(), 1);

    //don't add duplicates
    for(int i=scene.lights_size();i<_MAX_LIGHTS_;i++)
        scene.inherit_light((AreaLight*)addme1);
    EXPECT_EQ(scene.assets_size(), 2);
    EXPECT_EQ(scene.lights_size(), 1);

    //fill all lights
    for(int i=scene.lights_size();i<_MAX_LIGHTS_;i++)
        scene.inherit_light(new AreaLight(sphere,transform,Spectrum(1500)));
    EXPECT_EQ(scene.lights_size(),_MAX_LIGHTS_);

    //add extra light
    errors_count[WARNING_INDEX] = 0;
    AreaLight* last_light = new AreaLight(sphere,transform,Spectrum(1500));
    scene.inherit_light(last_light);
    EXPECT_EQ(errors_count[WARNING_INDEX],1);
    errors_count[WARNING_INDEX] = 0;
}

TEST(Scene,get_lights)
{
    Scene scene;
    Sphere* sphere = new Sphere();
    Matrix4 transform;
    transform.set_identity();
    const AreaLight* values[_MAX_LIGHTS_];
    for(int i=0;i<_MAX_LIGHTS_;i++)
    {
        values[i] = new AreaLight(sphere,transform,Spectrum(1500));
        scene.inherit_light(values[i]);
    }
    for(int i=0;i<scene.lights_size();i++)
        EXPECT_EQ(scene.get_light(i),values[i]);
}

