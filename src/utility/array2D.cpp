//author: Davide Pizzolotto
//license: GNU GPLv3

#include "array2D.hpp"

///Mask used to get the block offset
#define BLOCK_MASK ((1<<LOG_BS)-1)
///The size of a block
#define BLOCK_SIZE 1<<LOG_BS

template<class T>
Array2D::Array2D(uint32_t side) : BLOCKS_NO((side*side) >> BLOCK_SIZE)
{
    if((side & side-1) != 0)
    {
        //round up to the next power of 2
        side--;
        side |= side >> 1;
        side |= side >> 2;
        side |= side >> 4;
        side |= side >> 8;
        side |= side >> 16;
        side++;
        side += (side == 0); //assert side is at least 1
    }
    Array2D::data = (T*)malloc(sizeof(T)*side*side);
}

template<class T>
Array2D::Array2D(const Array2D& other) : BLOCKS_NO(other.BLOCKS_NO)
{
    Array2D::data = (T*)malloc(sizeof(T)*BLOCKS_NO*BLOCK_SIZE);
    memcpy(data, other.data, sizeof(T)*BLOCKS_NO*BLOCK_SIZE);
}

template<class T>
Array2D<T>::~Array2D()
{
    free(data);
}

template<class T>
T Array2D<T>::get(int x, int y) const
{
    //first LOG_BS bits are the block number, last LOG_BS bits are the offset
    int xblock = x >> LOG_BS;
    int yblock = y >> LOG_BS;
    int xoffset = x & BLOCK_MASK;
    int yoffset = y & BLOCK_MASK;
    //index of the block
    int block_offset = BLOCK_SIZE*BLOCK_SIZE+(yblock*BLOCKS_NO+xblock);
    //index of the requested value INSIDE the block
    int data_offset = BLOCK_SIZE*yoffset+xoffset;
    return data[block_offset+data_offset];
}

template<class T>
void Array2D<T>::set(int x, int y, T value)
{
    //first LOG_BS bits are the block number, last LOG_BS bits are the offset
    int xblock = x >> LOG_BS;
    int yblock = y >> LOG_BS;
    int xoffset = x & BLOCK_MASK;
    int yoffset = y & BLOCK_MASK;
    //index of the block
    int block_offset = BLOCK_SIZE*BLOCK_SIZE+(yblock*BLOCKS_NO+xblock);
    //index of the requested value INSIDE the block
    int data_offset = BLOCK_SIZE*yoffset+xoffset;
    data[block_offset+data_offset] = value;
}
