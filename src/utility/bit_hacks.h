//
// Created by davide on 4/17/19.
//

#ifndef __BIT_HACKS_H__
#define __BIT_HACKS_H__

#include <stdint.h>

/**
 * \brief Rounds up a number to the next power of 2
 *
 * \warning This routine returns 0 for the value 0 which is not a power of two
 *
 * \param[in] val The number that will be converted
 * \return The minimum power of 2 greater than the input number
 * \author Sean Eron Anderson
 * (https://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2)
 */
inline int next_power_of_2(uint32_t val)
{
    val--;
    val |= val >> 1;
    val |= val >> 2;
    val |= val >> 4;
    val |= val >> 8;
    val |= val >> 16;
    val++;
    return val;
}

#endif //__BIT_HACKS_H__
