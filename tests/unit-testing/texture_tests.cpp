#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#else

#include <gtest/gtest.h>
#include "samplers/sampler_stratified.hpp"
#include "cameras/camera_orthographic.hpp"

#endif

SPECTRE_TEST_INIT(Texture_tests)

#include "utility/spectrum.hpp"
#include "textures/texture.hpp"
#include "textures/texture_uniform.hpp"

SPECTRE_TEST(Texture, UniformTexture_map)
{
    TextureUniform tex(SPECTRUM_WHITE);
    Spectrum res;
    HitPoint h;
    
    res = tex.map(&h);
    EXPECT_EQ(res.w[0], SPECTRUM_WHITE.w[0]);
    EXPECT_EQ(res.w[1], SPECTRUM_WHITE.w[1]);
    EXPECT_EQ(res.w[2], SPECTRUM_WHITE.w[2]);
}

SPECTRE_TEST(Texture, differentials_creation)
{
    Ray r0, rx, ry;
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

    Sample test = samples[0];
    Sample testdx = samples[0];
    testdx.posx++;
    Sample testdy = samples[0];
    testdy.posy++;

    camera.create_ray(&test, &r0, &rx, &ry);
}

SPECTRE_TEST_END(Texture)
