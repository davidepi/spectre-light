//Created,   8 May 2018
//Last Edit 20 May 2018

#ifndef __TEXTURE_IMAGE_HPP__
#define __TEXTURE_IMAGE_HPP__

#include "textures/texture.hpp"
#include "textures/texture_image.hpp"
#include "textures/image_map.hpp"
#include "textures/texture_library.hpp"
#include "primitives/shape.hpp"
#include "utility/file.hpp"
#include "utility/imageIO.hpp"
#include <mutex>
#include <cmath>

class TextureImage : public Texture
{
public:
    TextureImage(const ImageMap* map);

    TextureImage(const TextureImage& old) = delete;

    ~TextureImage() override = default;

    Spectrum map(const HitPoint* hp) const override;

private:
    
    float scale_x;
    float scale_y;
    const ImageMap* imagemap;
    
};

#endif
