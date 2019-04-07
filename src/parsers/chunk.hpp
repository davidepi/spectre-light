//
// Created by Davide Pizzolotto on 2019-04-07.
//

#ifndef __CHUNK_HPP__
#define __CHUNK_HPP__


#include <cstdint>
#include <queue>
#include <string>

class Chunk
{
public:
    Chunk(int id);
    ~Chunk() = default;
    void push_int8(uint8_t value);
    uint8_t pop_int8();
    void push_int16(uint16_t value);
    uint16_t pop_int16();
    void push_int32(uint32_t value);
    uint32_t pop_int32();
    void push_int64(uint64_t value);
    uint64_t pop_int64();
    void push_float(float value);
    float pop_float();
    void push_double(double value);
    double pop_double();
    void push_string(const std::string& value);
    std::string pop_string();
private:
    uint16_t id;
    std::queue<uint8_t> data;
};


#endif
