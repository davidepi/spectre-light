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
