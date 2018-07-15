//7-13-18
//7-13-18

#ifndef __ENDIANNESS_H__
#define __ENDIANNESS_H__

#include <stdint.h>
//assuming windows ALWAYS little endian. Holds for now, I can't predict future
#define SYSTEM_IS_WINDOWS defined(_WIN32) || defined(_WIN64)

//gcc should generate rol and bswap with these templates in big endian sistems
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ || SYSTEM_IS_WINDOWS
#define ENDIANNESS_LITTLE16(value) value
#define ENDIANNESS_LITTLE32(value) value
#define ENDIANNESS_BIG16(value) ((value & 0xFF) >> 8) | (value << 8)
#define ENDIANNESS_BIG32(value) ((value & 0xFF000000) >> 24) | \
                                       ((value & 0x00FF0000) >> 8) | \
                                       ((value & 0x0000FF00) << 8) | \
                                        (value << 24)
#elif __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define ENDIANNESS_BIG16(value) value
#define ENDIANNESS_BIG32(value) value
#define ENDIANNESS_LITTLE16(value) ((value & 0xFF) >> 8) | (value << 8)
#define ENDIANNESS_LITTLE32(value) ((value & 0xFF000000) >> 24) | \
                                       ((value & 0x00FF0000) >> 8) | \
                                       ((value & 0x0000FF00) << 8) | \
                                        (value << 24)
#elif
#error "Endianness not supported"
#endif

#endif
