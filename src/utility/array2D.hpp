//Created,   5 Aug 2018
//Last Edit  7 Aug 2018

/**
 *  \file array2D.hpp
 *  \brief Cache-efficient allocation for a bidimensional array
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date 7 Aug 2018
 *  \copyright GNU GPLv3
 */


#ifndef __ARRAY2D_HPP__
#define __ARRAY2D_HPP__

#include <cstdlib>
#include <cstdint>
#include <cstring>

#ifndef TESTS
///Log2 of the block size. The block size will always be a power of 2.
#define LOG_BS 5
#else
#define LOG_BS 3 //low value to simplify test checking
#endif
///The size of a block side
#define BLOCK_SIDE (1<<LOG_BS)
///Mask used to get the block offset
#define BLOCK_MASK (BLOCK_SIDE-1)

/**
 *  \brief Class allocating values in a cache-efficient way for 2D arrays
 *
 *  Array2D class is used to better allocate bidimensional arrays. This is done
 *  by storing data in blocks instead of lines. Instead of storing every
 *  value in the first y line, and then every value in the second y line and
 *  so on, this class store only the first 2^LOG_BS values of the first line up
 *  to the first 2^LOG_BS lines. Then the values from 2^LOG_BS to 2*2^LOG_BS and
 *  so forth.
 *
 *  With a LOG_BS of 2 (just for thi example), the data is laid out as follow:
 *  <pre>
 *  2D view
 *  normal          Array2D
 *  0 1 2 3         0 1 4 5
 *  4 5 6 7         2 3 6 7
 *  8 9 A B         8 9 C D
 *  C D E F         A B E F
 *
 *  1D view
 *  normal:  0 1 2 3 4 5 6 7 8 9 A B C D E F
 *  Array2D: 0 1 4 5 2 3 6 7 8 9 C D A B E F
 *  </pre>
 *  Ensuring that the values "4" and "0" which are nearby on a 2D perspective
 *  but not on a 1D one, are on the same cache line.
 *
 *  This dramatically improves the cache performance when accessing an
 *  element implies accessing also nearby elements on the y row.
 *  (An example of this is the bilinear filter which requires the 4 pixel
 *  nearby a given point)
 *  The price to pay for this is an increase in the operations required to get
 *  the element index (11 operations, versus the 3 required by the classic
 *  y*width+x), however, in most of the cases the benefits are worth it.
 *
 *  To ensure faster lookup, both sides of the array will be equal and power
 *  of two.
 *
 *  \tparam T datatype that will be stored inside the array
 */
template<class T>
class Array2D
{
public:

    /**
     *  \brief Constructor
     *
     *  Allocates an empty array of elements T, with size side*side. To
     *  ensure faster lookup, side will be rounded to the next power of two.
     *
     *  \param[in] side The lenght of a side of the array. The other side
     *  MUST be equal to this one
     */
    Array2D(uint32_t side)
    {
        //assert at least 1 block for small arrays
        if(side<BLOCK_SIDE)
            side = BLOCK_SIDE;
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
        Array2D<T>::data = (T*)malloc(sizeof(T)*side*side);
        Array2D<T>::blocks_no_side = (side >> LOG_BS);
    }

    /**
     *  \brief Constructor with initialization
     *
     *  Allocates an array of elements T with size side*side. The input 1D
     *  array will also be copied into this 2D array. The input 1D array is
     *  expected to be of length side*side. To ensure faster lookup, side
     *  will be rounded to the next power of two.
     *
     *  \param[in] values The input 1D array that will be converted into this
     *  2D array. This array should be of side*side length
     *  \param[in] side The squared length of the array.
     */
    Array2D(const T* values, uint32_t side)
    {
        //record old side of the array to avoid invalid read
        int old_side = side;
        //assert at least 1 block for small arrays
        if(side<BLOCK_SIDE)
            side = BLOCK_SIDE;
        //possibly round up side to a power of 2
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
        Array2D<T>::data = (T*)malloc(sizeof(T)*side*side);
        Array2D<T>::blocks_no_side = (side >> LOG_BS);
        //use the old_side to avoid invalid reads
        for(int y = 0; y<old_side; y++)
            for(int x = 0; x<old_side; x++)
                set(x, y, values[y*old_side+x]);
    }

    ///Copy-constructor
    Array2D(const Array2D& other)
    {
        blocks_no_side = other.blocks_no_side;
        size_t array_len = blocks_no_side*blocks_no_side*BLOCK_SIDE*BLOCK_SIDE;
        array_len *= sizeof(T);
        data = (T*)malloc(array_len);
        memcpy(data, other.data, array_len);
    }

    ///Destructor
    ~Array2D()
    {
        free(data);
    }

    /**
     *  \brief Returns the element at position (x,y)
     *
     *  \param[in] x Coordinate x of the element
     *  \param[in] y Coordinate y of the element
     *  \return Value found at position (x,y)
     */
    T get(int x, int y) const
    {
        //first LOG_BS bits are the block number, last bits are the offset
        int xblock = x >> LOG_BS;
        int yblock = y >> LOG_BS;
        int xoffset = x & BLOCK_MASK;
        int yoffset = y & BLOCK_MASK;
        //index of the block
        int block_offset = BLOCK_SIDE*BLOCK_SIDE*(yblock*blocks_no_side+xblock);
        //index of the requested value INSIDE the block
        int data_offset = BLOCK_SIDE*yoffset+xoffset;
        return data[block_offset+data_offset];
    }

    /**
     *  \brief Sets the value for the element at position (x,y)
     *
     *  \param[in] x Coordinate x of the element
     *  \param[in] y Coordinate y of the element
     *  \param[in] value The value that will be written at the given position
     */
    void set(int x, int y, T value)
    {
        //first LOG_BS bits are the block number, last bits are the offset
        int xblock = x >> LOG_BS;
        int yblock = y >> LOG_BS;
        int xoffset = x & BLOCK_MASK;
        int yoffset = y & BLOCK_MASK;
        //index of the block
        int block_offset = BLOCK_SIDE*BLOCK_SIDE*(yblock*blocks_no_side+xblock);
        //index of the requested value INSIDE the block
        int data_offset = BLOCK_SIDE*yoffset+xoffset;
        data[block_offset+data_offset] = value;
    }

    ///Copy-assignment operator
    Array2D& operator=(const Array2D& other)
    {
        blocks_no_side = other.blocks_no_side;
        size_t array_len = blocks_no_side*blocks_no_side*BLOCK_SIDE*BLOCK_SIDE;
        array_len *= sizeof(T);
        data = (T*)malloc(array_len);
        memcpy(data, other.data, array_len);
        return *this;
    }

    ///Clears the entire array by writing only zeroes
    void zero_out()
    {
        size_t array_len = blocks_no_side*blocks_no_side*BLOCK_SIDE*BLOCK_SIDE;
        memset(data, 0, sizeof(T)*array_len);
    }

    //Need to ensure that the internal allocation is correct during tests
#ifndef TESTS
    private:
#endif

    //number of blocks for each dimension
    uint32_t blocks_no_side;

    //allocated data
    T* data;
};

#endif
