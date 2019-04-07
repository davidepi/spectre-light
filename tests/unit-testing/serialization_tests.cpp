#include "spectre_tests.h"

#ifdef __XCODE__
#import <XCTest/XCTest.h>
#elif defined(__VS__)
#include "CppUnitTest.h"
#else

#include <gtest/gtest.h>

#endif

#include "geometry/vec3.hpp"
#include "geometry/vec2.hpp"
#include "utility/utility.hpp"
#include <climits>
#include "parsers/chunk.hpp"

SPECTRE_TEST_INIT(Serialization_tests)

SPECTRE_TEST(Serialization, chunk_int8)
{
    Chunk chunk(0);
    chunk.push_int8(10);
    chunk.push_int8(255);
    chunk.push_int8(-3);
    chunk.push_int8(32);
    EXPECT_EQ((uint8_t)chunk.pop_int8(), (uint8_t)10);
    EXPECT_EQ((uint8_t)chunk.pop_int8(), (uint8_t)255);
    EXPECT_EQ((int8_t)chunk.pop_int8(), (int8_t)-3);
    EXPECT_EQ((uint8_t)chunk.pop_int8(), (uint8_t)32);
}

SPECTRE_TEST(Serialization, chunk_int16)
{
    Chunk chunk(0);
    chunk.push_int16(10);
    chunk.push_int16(25500);
    chunk.push_int16(-3000);
    chunk.push_int16(32);
    EXPECT_EQ((uint16_t)chunk.pop_int16(), (uint16_t)10);
    EXPECT_EQ((uint16_t)chunk.pop_int16(), (uint16_t)25500);
    EXPECT_EQ((int16_t)chunk.pop_int16(), (int16_t)-3000);
    EXPECT_EQ((uint16_t)chunk.pop_int16(), (uint16_t)32);
}

SPECTRE_TEST(Serialization, chunk_int32)
{
    Chunk chunk(0);
    chunk.push_int32(10);
    chunk.push_int32(25678986);
    chunk.push_int32(-5358657);
    chunk.push_int32(32);
    EXPECT_EQ((uint32_t)chunk.pop_int32(), (uint32_t)10);
    EXPECT_EQ((uint32_t)chunk.pop_int32(), (uint32_t)25678986);
    EXPECT_EQ((int32_t)chunk.pop_int32(), (int32_t)-5358657);
    EXPECT_EQ((uint32_t)chunk.pop_int32(), (uint32_t)32);
}

SPECTRE_TEST(Serialization, chunk_int64)
{
    Chunk chunk(0);
    chunk.push_int64(10);
    chunk.push_int64((uint64_t)2567898765445656786);
    chunk.push_int64((int64_t)-53456758659876547);
    chunk.push_int64(32);
    EXPECT_EQ((uint64_t)chunk.pop_int64(), (uint64_t)10);
    EXPECT_EQ((uint64_t)chunk.pop_int64(), (uint64_t)2567898765445656786);
    EXPECT_EQ((int64_t)chunk.pop_int64(), (int64_t)-53456758659876547);
    EXPECT_EQ((uint64_t)chunk.pop_int64(), (uint64_t)32);
}

SPECTRE_TEST(Serialization, chunk_float)
{
    Chunk chunk(0);
    chunk.push_float(3.14f);
    chunk.push_float(354.34f);
    EXPECT_EQ(chunk.pop_float(), 3.14f);
    EXPECT_EQ(chunk.pop_float(), 354.34f);
}

SPECTRE_TEST(Serialization, chunk_double)
{
    Chunk chunk(0);
    chunk.push_double(3.14f);
    chunk.push_double(354.34f);
    chunk.push_double(-6437.876469766);
    EXPECT_EQ(chunk.pop_double(), 3.14f);
    EXPECT_EQ(chunk.pop_double(), 354.34f);
    EXPECT_EQ(chunk.pop_double(), -6437.876469766);
}

SPECTRE_TEST(Serialization, chunk_string)
{
    Chunk chunk(0);
    chunk.push_string("/root/vmlinuz");
    chunk.push_string("output.ppm");
    EXPECT_STREQ(chunk.pop_string().c_str(), "/root/vmlinuz");
    EXPECT_STREQ(chunk.pop_string().c_str(), "output.ppm");
}
