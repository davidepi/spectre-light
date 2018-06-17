//Created,   8 May 2018
//Last Edit 17 Jun 2018

#ifndef __TEXTURE_IMAGE_HPP__
#define __TEXTURE_IMAGE_HPP__

#include "textures/texture.hpp"
#include "textures/texture_image.hpp"
#include "textures/image_map.hpp"
#include "textures/texture_library.hpp"

class TextureImage : public Texture
{
public:
    TextureImage(const ImageMap* map, Vec2& scale, Vec2& shift);

    TextureImage(const TextureImage& old) = delete;

    ~TextureImage() override = default;

    Vec2 get_shift() const;

    Vec2 get_scale() const;

    Spectrum map(const HitPoint* hp) const override;

private:
    Vec2 scale;
    Vec2 shift;
    bool filtered;
    const ImageMap* imagemap;

};

#endif
