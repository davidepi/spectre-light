#ifndef __TYPES_IMGCHANNEL_H__
#define __TYPES_IMGCHANNEL_H__

#ifndef IS_BIG_ENDIAN
/** Channel of the TextureImage. ARGB order in little endian machines */
enum imgchannel_t
{
    ALPHA = 0,
    RED = 1,
    GREEN = 2,
    BLUE = 3,
};
#else
/** Channel of the TextureImage. BGRA order in big endian machines */
enum imgchannel_t
{
    BLUE = 0,
    GREEN = 1,
    RED = 2,
    ALPHA = 3
};
#endif

/** Filtering type used by the TextureImage */
enum texturefilter_t
{
    UNFILTERED,
    TRILINEAR,
    EWA
};

#endif
