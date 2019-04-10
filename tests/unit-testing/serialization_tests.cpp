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
#include "parsers/chunk_wrapper.hpp"
#include <cstdio> //mktemp
#include <cstdlib>
#include "utility/file.hpp"

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
    //thanks vs for not supporting uint16_t comparison with Assert::AreEqual
    EXPECT_TRUE((uint16_t)chunk.pop_int16() == (uint16_t)10);
    EXPECT_TRUE((uint16_t)chunk.pop_int16() == (uint16_t)25500);
    EXPECT_EQ((int16_t)chunk.pop_int16(), (int16_t)-3000);
    EXPECT_TRUE((uint16_t)chunk.pop_int16() == (uint16_t)32);
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
    EXPECT_TRUE((uint64_t)chunk.pop_int64()==(uint64_t)2567898765445656786);
    EXPECT_TRUE((int64_t)chunk.pop_int64()==(int64_t)-53456758659876547);
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
    chunk.push_double(3.14);
    chunk.push_double(354.34);
    chunk.push_double(-6437.876469766);
    EXPECT_EQ(chunk.pop_double(), 3.14);
    EXPECT_EQ(chunk.pop_double(), 354.34);
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

SPECTRE_TEST(Serialization, chunk_all_types)
{
    Chunk chunk(0);
    chunk.push_int8(250);
    chunk.push_float(3.14f);
    chunk.push_string("test string!!!");
    chunk.push_int32(21476543);
    chunk.push_string("another string");
    chunk.push_int16(-3);

    EXPECT_EQ(chunk.pop_int8(), (uint8_t)250);
    EXPECT_EQ(chunk.pop_float(), 3.14f);
    EXPECT_STREQ(chunk.pop_string().c_str(), "test string!!!");
    EXPECT_EQ(chunk.pop_int32(), (uint32_t)21476543);
    EXPECT_STREQ(chunk.pop_string().c_str(), "another string");
    EXPECT_EQ((int16_t)chunk.pop_int16(), (int16_t)-3);
}

SPECTRE_TEST(Serialization, wrapper_add_remove_chunks)
{
    Chunk chunk0(0);
    chunk0.push_string("test string for chunk 0");
    chunk0.push_string("another one");
    Chunk chunk1(1);
    chunk1.push_string("test string for chunk 1");
    chunk1.push_float(3.14f);
    chunk1.push_string("another one for chunk 1");
    ChunkWrapper wrapper;
    EXPECT_TRUE(wrapper.empty());
    wrapper.push_chunk(chunk0);
    EXPECT_FALSE(wrapper.empty());
    wrapper.push_chunk(chunk1);

    Chunk retrieved0 = wrapper.pop_chunk();
    Chunk retrieved1 = wrapper.pop_chunk();
    EXPECT_TRUE(wrapper.empty());
    EXPECT_STREQ(retrieved0.pop_string().c_str(), "test string for chunk 0");
    EXPECT_STREQ(retrieved0.pop_string().c_str(), "another one");
    EXPECT_STREQ(retrieved1.pop_string().c_str(), "test string for chunk 1");
    EXPECT_EQ(retrieved1.pop_float(), 3.14f);
    EXPECT_STREQ(retrieved1.pop_string().c_str(), "another one for chunk 1");
}

SPECTRE_TEST(Serialization, wrapper_to_file)
{
    Chunk chunk0(0);
    chunk0.push_string("test string for chunk 0");
    chunk0.push_string("another one");
    Chunk chunk1(1);
    chunk1.push_string("test string for chunk 1");
    chunk1.push_float(3.14f);
    chunk1.push_string("another one for chunk 1");
    ChunkWrapper wrapper;
    wrapper.push_chunk(chunk0);
    wrapper.push_chunk(chunk1);

    //there is a security risk in mktemp due to data race, but this is testing
    //so who cares
    File tmp = File::get_temp_file();
    const char* tmp_file = tmp.absolute_path();

    wrapper.write(tmp_file);
    ChunkWrapper retrieved_wrapper;
    retrieved_wrapper.read(tmp_file);

    Chunk retrieved0 = retrieved_wrapper.pop_chunk();
    Chunk retrieved1 = retrieved_wrapper.pop_chunk();
    EXPECT_STREQ(retrieved0.pop_string().c_str(), "test string for chunk 0");
    EXPECT_STREQ(retrieved0.pop_string().c_str(), "another one");
    EXPECT_STREQ(retrieved1.pop_string().c_str(), "test string for chunk 1");
    EXPECT_EQ(retrieved1.pop_float(), 3.14f);
    EXPECT_STREQ(retrieved1.pop_string().c_str(), "another one for chunk 1");

    unlink(tmp_file);
}

SPECTRE_TEST_END(Serialization)
