/*  Created,  13 Jul 2018   */
/*  Last Edit 26 Jul 2018   */

#ifndef __ENDIANNESS_H__
#define __ENDIANNESS_H__

#include <stdint.h>

/*gcc should generate rol and bswap with these templates in big endian systems*/
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ || defined(_WIN32) || \
!defined(IS_BIG_ENDIAN)
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
#else
#error "Endianness not supported"
#endif

#endif
