//
// Created by Davide Pizzolotto on 18/08/21.
//

#ifndef __TEXTURE_HEIGHT_HPP__
#define __TEXTURE_HEIGHT_HPP__

#include "materials/bump.hpp"
#include "textures/texture_image.hpp"
#include "textures/image_map.hpp"

class TextureHeight : public Bump
{
public:

    TextureHeight(const TextureImage* image, ImageChannel channel);
    void bump(const HitPoint* hp, ShadingSpace* matrix) const override;

private:
    void gradient(const HitPoint* hp, float* u, float* v)const;
    const TextureImage* image;
    const ImageChannel channel;
};

#endif
