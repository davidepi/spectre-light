#include "chunk.hpp"

struct reinterpret
{
    union
    {
        uint32_t val_int32;
        float val_float;
    };

    union
    {
        uint64_t val_int64;
        double val_double;
    };
};

Chunk::Chunk(int id)
{
    Chunk::id = id;
}

void Chunk::push_int8(uint8_t value)
{
    data.push(value);
}

uint8_t Chunk::pop_int8()
{
    uint8_t retval = data.front();
    data.pop();
    return retval;
}

void Chunk::push_int16(uint16_t value)
{
    data.push(value & 0x00FFU);
    data.push((value & 0xFF00U)>>8U);
}

uint16_t Chunk::pop_int16()
{
    uint16_t retval = data.front();
    data.pop();
    retval |= (uint32_t)data.front() << 8U;
    data.pop();
    return retval;
}

void Chunk::push_int32(uint32_t value)
{
    data.push((value >>  0U) & 0xFFU);
    data.push((value >>  8U) & 0xFFU);
    data.push((value >> 16U) & 0xFFU);
    data.push((value >> 24U) & 0xFFU);
}

uint32_t Chunk::pop_int32()
{
    uint32_t retval = data.front();
    data.pop();
    retval |= (uint32_t)data.front() << 8U;
    data.pop();
    retval |= (uint32_t)data.front() << 16U;
    data.pop();
    retval |= (uint32_t)data.front() << 24U;
    data.pop();
    return retval;
}

void Chunk::push_int64(uint64_t value)
{
    data.push((value >>  0U) & 0xFFU);
    data.push((value >>  8U) & 0xFFU);
    data.push((value >> 16U) & 0xFFU);
    data.push((value >> 24U) & 0xFFU);
    data.push((value >> 32U) & 0xFFU);
    data.push((value >> 40U) & 0xFFU);
    data.push((value >> 48U) & 0xFFU);
    data.push((value >> 56U) & 0xFFU);
}

uint64_t Chunk::pop_int64()
{
    uint64_t retval = (uint32_t)data.front();
    data.pop();
    retval |= (uint32_t)data.front() << 8U;
    data.pop();
    retval |= (uint32_t)data.front() << 16U;
    data.pop();
    retval |= (uint32_t)data.front() << 24U;
    data.pop();
    retval |= (uint64_t)data.front() << 32U;
    data.pop();
    retval |= (uint64_t)data.front() << 40U;
    data.pop();
    retval |= (uint64_t)data.front() << 48U;
    data.pop();
    retval |= (uint64_t)data.front() << 56U;
    data.pop();
    return retval;
}

void Chunk::push_float(float value)
{
    struct reinterpret tmp;
    tmp.val_float = value;
    Chunk::push_int32(tmp.val_int32);
}

float Chunk::pop_float()
{
    struct reinterpret tmp;
    tmp.val_int32 = Chunk::pop_int32();
    return tmp.val_float;
}

void Chunk::push_double(double value)
{
    struct reinterpret tmp;
    tmp.val_double = value;
    Chunk::push_int64(tmp.val_int64);
}

double Chunk::pop_double()
{
    struct reinterpret tmp;
    tmp.val_int64 = Chunk::pop_int64();
    return tmp.val_double;
}

void Chunk::push_string(const std::string& value)
{
    uint16_t len = value.length();
    Chunk::push_int16(len);
    int i=0;
    while(i<len && value[i]!=0)
        Chunk::push_int8(value[i++]);
}

std::string Chunk::pop_string()
{
    uint16_t len = Chunk::pop_int16();
    std::string retval(len, 0);
    int i=0;
    while(i<len)
        retval[i++] = Chunk::pop_int8();
    return retval;
}
