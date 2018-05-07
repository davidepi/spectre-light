//author: Davide Pizzolotto
//license: GNU GPLv3

#include "uniform.hpp"

UniformTexture::UniformTexture(const Spectrum& color)
        :value(color)
{

}

Spectrum UniformTexture::map(Point2) const
{
    return UniformTexture::value;
}
