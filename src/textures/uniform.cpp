//author: Davide Pizzolotto
//license: GNU GPLv3

#include "uniform.hpp"

UniformTexture::UniformTexture(const Spectrum& color)
:value(color)
{
    
}

Spectrum UniformTexture::map(float, float)const
{
    return UniformTexture::value;
}
