/* pack a struct, both on MSVC and GCC/clang */
#ifndef __PACKED_STRUCT_H__
#define __PACKED_STRUCT_H__

#ifdef _MSC_VER
#define PACKED_STRUCT(name) \
__pragma(pack(push, 1)) struct name
#define END_PACKED_STRUCT __pragma(pack(pop))
#elif defined(__GNUC__)
#define PACKED_STRUCT(name) struct __attribute__((packed)) name
#define END_PACKED_STRUCT
#else
#error "Compiler not supported"
#endif

#endif
