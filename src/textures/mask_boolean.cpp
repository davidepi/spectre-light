//author: Davide Pizzolotto
//license: GNU GPLv3

#include "mask_boolean.hpp"

MaskBoolean::MaskBoolean():map(NULL)
{}

MaskBoolean::MaskBoolean(const TextureImage* map, ImageChannel channel, bool
inverted):map(map), channel(channel), inverted(inverted)
{}

bool MaskBoolean::is_masked(const HitPoint* hp) const
{
    if(map == NULL)
        return false;
    else
    {
        Texel texel = map->map_value(hp).bgra_texel;
        uint8_t channel_value;
#ifndef IS_BIG_ENDIAN
        channel_value = *(&(texel.a)+channel);
#else
        channel_value = *(&(texel.b)+channel);
#endif
        bool masked = channel_value>=MASK_BINARY_THRESHOLD;

        //account for mask inversion with a XOR (both are bool so this with a !=)
        return masked != inverted;
    }
}
