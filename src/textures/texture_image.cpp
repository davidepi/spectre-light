#include "texture_image.hpp"

TextureImage::TextureImage(const ImageMap* map)
{
    imagemap = map;
}

Spectrum TextureImage::map(const HitPoint*) const
{
    return Spectrum();
}
