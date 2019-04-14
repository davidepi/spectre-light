//author: Davide Pizzolotto
//license: GNU GPLv3

#include "chunk.hpp"

void Chunk::push_int8(uint8_t value)
{
    data.push_back(value);
}

uint8_t Chunk::pop_int8()
{
    uint8_t retval = data[head];
    head++;
    return retval;
}

void Chunk::push_int16(uint16_t value)
{
    data.push_back(value & 0x00FFU);
    data.push_back((value & 0xFF00U) >> 8U);
}

uint16_t Chunk::pop_int16()
{
    uint16_t retval = data[head];
    head++;
    retval |= (uint32_t)data[head] << 8U;
    head++;
    return retval;
}

void Chunk::push_int32(uint32_t value)
{
    data.push_back((value >> 0U) & 0xFFU);
    data.push_back((value >> 8U) & 0xFFU);
    data.push_back((value >> 16U) & 0xFFU);
    data.push_back((value >> 24U) & 0xFFU);
}

uint32_t Chunk::pop_int32()
{
    uint32_t retval = data[head];
    head++;
    retval |= (uint32_t)data[head] << 8U;
    head++;
    retval |= (uint32_t)data[head] << 16U;
    head++;
    retval |= (uint32_t)data[head] << 24U;
    head++;
    return retval;
}

void Chunk::push_int64(uint64_t value)
{
    data.push_back((value >> 0U) & 0xFFU);
    data.push_back((value >> 8U) & 0xFFU);
    data.push_back((value >> 16U) & 0xFFU);
    data.push_back((value >> 24U) & 0xFFU);
    data.push_back((value >> 32U) & 0xFFU);
    data.push_back((value >> 40U) & 0xFFU);
    data.push_back((value >> 48U) & 0xFFU);
    data.push_back((value >> 56U) & 0xFFU);
}

uint64_t Chunk::pop_int64()
{
    uint64_t retval = (uint32_t)data[head];
    head++;
    retval |= (uint32_t)data[head] << 8U;
    head++;
    retval |= (uint32_t)data[head] << 16U;
    head++;
    retval |= (uint32_t)data[head] << 24U;
    head++;
    retval |= (uint64_t)data[head] << 32U;
    head++;
    retval |= (uint64_t)data[head] << 40U;
    head++;
    retval |= (uint64_t)data[head] << 48U;
    head++;
    retval |= (uint64_t)data[head] << 56U;
    head++;
    return retval;
}

void Chunk::push_float(float value)
{
    uint32_t float_as_int = reinterpret_cast<uint32_t&>(value);
    Chunk::push_int64(float_as_int);
}

float Chunk::pop_float()
{
    uint32_t float_as_int = Chunk::pop_int64();
    return reinterpret_cast<float&>(float_as_int);
}

void Chunk::push_double(double value)
{
    uint64_t double_as_int = reinterpret_cast<uint64_t&>(value);
    Chunk::push_int64(double_as_int);
}

double Chunk::pop_double()
{
    uint64_t double_as_int = Chunk::pop_int64();
    return reinterpret_cast<double&>(double_as_int);
}

void Chunk::push_string(const std::string& value)
{
    uint16_t len = value.length();
    Chunk::push_int16(len);
    int i = 0;
    while(i<len && value[i] != 0)
        Chunk::push_int8(value[i++]);
}

std::string Chunk::pop_string()
{
    uint16_t len = Chunk::pop_int16();
    std::string retval(len, 0);
    int i = 0;
    while(i<len)
        retval[i++] = Chunk::pop_int8();
    return retval;
}

uint64_t Chunk::size() const
{
    return (uint64_t)data.size()-head;
}

uint16_t ChunkNamed::get_id() const
{
    return ChunkNamed::id;
}

void ChunkNamed::set_id(uint16_t in_id)
{
    ChunkNamed::id = in_id;
}

void ChunkNamed::push_chunk(const Chunk* chunk)
{
    for(uint8_t value : chunk->data)
    {
        ChunkNamed::data.push_back(value);
    }
}

void ChunkNamed::pop_chunk(Chunk* chunk, uint64_t size)
{
    for(uint64_t i = 0; i<size; i++)
    {
        chunk->push_int8(ChunkNamed::data[head]);
        ChunkNamed::head++;
    }
}
