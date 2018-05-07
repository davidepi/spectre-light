//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_uniform.hpp"

TextureUniform::TextureUniform(const Spectrum& color)
        :value(color)
{

}

Spectrum TextureUniform::map(Point2) const
{
    return TextureUniform::value;
}
