//author: Davide Pizzolotto
//license: GNU GPLv3

#include "mask_boolean.hpp"

MaskBoolean::MaskBoolean():map(NULL)
{}

MaskBoolean::MaskBoolean(const Texture* map, imgchannel_t channel, bool
inverted):map(map), channel(channel), inverted(inverted)
{}

bool MaskBoolean::is_visible(const HitPoint* hp) const
{
    if(map == NULL)
        return true;
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

        //XOR returns if the value is visible, XNOR return if masked
        return masked != inverted;
    }
}

bool MaskBoolean::is_masked(const HitPoint* hp) const
{
    return !is_visible(hp);
}
