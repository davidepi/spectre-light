//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_uniform.hpp"

TextureUniform::TextureUniform(const Spectrum& color)
        :value(color)
{

}

Spectrum TextureUniform::map(const HitPoint*) const
{
    return TextureUniform::value;
}

TexelUnion TextureUniform::map_value(const HitPoint*) const
{
    TexelUnion result;
    constexpr const float INV255 = 1.f/255.f;
    result.bgra_texel.r = (uint8_t)(value.w[0]*INV255);
    result.bgra_texel.g = (uint8_t)(value.w[1]*INV255);
    result.bgra_texel.b = (uint8_t)(value.w[2]*INV255);
    result.bgra_texel.a = 0xFF;
    return result;
}

uint16_t TextureUniform::get_side() const
{
    return 1;
}
