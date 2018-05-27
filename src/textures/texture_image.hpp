//Created,   8 May 2018
//Last Edit 27 May 2018

#ifndef __TEXTURE_IMAGE_HPP__
#define __TEXTURE_IMAGE_HPP__

#include "textures/texture.hpp"
#include "textures/texture_image.hpp"
#include "textures/image_map.hpp"
#include "textures/texture_library.hpp"

class TextureImage : public Texture
{
public:
    TextureImage(const ImageMap* map, float sx, float sy);

    TextureImage(const TextureImage& old) = delete;

    ~TextureImage() override = default;

    Spectrum map(const HitPoint* hp) const override;

private:
    
    float scale_x;
    float scale_y;
    bool filtered;
    const ImageMap* imagemap;
    
};

#endif
