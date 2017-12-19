
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
    EXPECT_EQ(scene.inherit_shape(sphere), sphere->get_id());
    EXPECT_EQ(scene.shapes_size(), 1);

    //add duplicate
    EXPECT_EQ(scene.inherit_shape(sphere), sphere->get_id());
    EXPECT_EQ(scene.shapes_size(), 1);
}

TEST(Scene,add_asset)
{
    //add single asset without material
    Sphere* sphere = new Sphere;
    Scene scene;
    Matrix4 m;
    m.set_identity();
    int id = scene.inherit_shape(sphere);
    EXPECT_EQ(scene.assets_size(), 0);
    //can't test for specific id, just asserting that it has been added
    EXPECT_GT(scene.add_asset(id,m),0);
    EXPECT_EQ(scene.assets_size(), 1);

    //add second asset with material
    Bdf* bxdf = new Lambertian(SPECTRUM_ONE);
    Bsdf material;
    material.inheritBdf(bxdf);
    EXPECT_EQ(scene.assets_size(), 1);
    EXPECT_GT(scene.add_asset(id,m,&material),0);
    EXPECT_EQ(scene.assets_size(), 2);

    //shape not found
    EXPECT_EQ(scene.add_asset(1000,m),0);

    //road to max number of assets
    for(unsigned int i=scene.assets_size();i<_MAX_ASSETS_;i++)
    {
        m.set_translation(Vec3(i,i,i));
        scene.add_asset(id, m);
    }
    EXPECT_EQ(scene.assets_size(), _MAX_ASSETS_);
    EXPECT_EQ(scene.add_asset(id,m), 0);
    EXPECT_EQ(scene.assets_size(), _MAX_ASSETS_);
}

TEST(Scene,add_light)
{
    //add single light
    Sphere* sphere = new Sphere;
    Scene scene;
    Matrix4 m;
    m.set_identity();
    int id = scene.inherit_shape(sphere);
    EXPECT_EQ(scene.lights_size(), 0);
    EXPECT_GT(scene.add_light(id,m,SPECTRUM_ONE),0);
    EXPECT_EQ(scene.lights_size(), 1);

    //shape not found
    EXPECT_EQ(scene.add_light(1000,m,SPECTRUM_ONE),0);

    //fill the number of lights
    for(unsigned int i=scene.lights_size();i<_MAX_LIGHTS_;i++)
    {
        m.set_translation(Vec3(i,i,i));
        scene.add_light(id, m, SPECTRUM_ONE);
    }
    EXPECT_EQ(scene.lights_size(), _MAX_LIGHTS_);
    EXPECT_EQ(scene.add_light(id,m,SPECTRUM_ONE),0);
    EXPECT_EQ(scene.lights_size(), _MAX_LIGHTS_);

    //fill the number of assets
    Scene scene2;
    Sphere* sphere2 = new Sphere;
    id = scene2.inherit_shape(sphere2);
    for(unsigned int i=0;i<_MAX_ASSETS_;i++)
    {
        m.set_translation(Vec3(i,i,i));
        scene2.add_asset(id, m);
    }
    EXPECT_EQ(scene2.assets_size(), _MAX_ASSETS_);
    EXPECT_EQ(scene2.lights_size(), 0);
    EXPECT_EQ(scene2.add_light(id,m,SPECTRUM_ONE),0);
    EXPECT_EQ(scene2.lights_size(), 0);
}

TEST(Scene,get_lights)
{
    //add single light
    Sphere* sphere = new Sphere;
    Scene scene;
    Matrix4 m;
    m.set_identity();
    int id = scene.inherit_shape(sphere);

    //add one asset
    scene.add_asset(id, m);
    //fill some lights
    for(unsigned int i=scene.lights_size();i<_MAX_LIGHTS_/4;i++)
    {
        m.set_translation(Vec3(i,i,i));
        scene.add_light(id, m, SPECTRUM_ONE);
    }
    //add one asset
    scene.add_asset(id, m);
    //fill some lights
    for(unsigned int i=scene.lights_size();i<_MAX_LIGHTS_/4;i++)
    {
        m.set_translation(Vec3(i,i,i));
        scene.add_light(id, m, SPECTRUM_ONE);
    }
    //add one asset
    scene.add_asset(id, m);


    const Asset*const* lights = (const Asset*const*)scene.get_lights();
    for(unsigned int i=0;i<scene.lights_size();i++)
        EXPECT_TRUE(lights[i]->is_light());
}

