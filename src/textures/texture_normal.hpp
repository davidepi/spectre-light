//
// Created by davide on 12/08/18.
//

#ifndef __TEXTURENORMAL_HPP__
#define __TEXTURENORMAL_HPP__

#include "textures/texture_image.hpp"

class TextureNormal : public Bump
{
public:
    TextureNormal(const TextureImage* image);
    ~TextureNormal() override = default;

    void bump(const HitPoint* hp, ShadingSpace* matrix) const override;
private:
    const TextureImage* image;
};


#endif
