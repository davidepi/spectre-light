//
//  texture_bump.hpp
//  spectre-light
//
//  Created by Davide Pizzolotto on 18/08/17.
//

#ifndef __TEXTURE_BUMP_HPP__
#define __TEXTURE_BUMP_HPP__

#include "primitives/shape.hpp"
#include "textures/texture_image.hpp"

class TextureBump : public TextureImage
{
public:
    using TextureImage::TextureImage;
    
    virtual void bump(const HitPoint& hp)const;
};

#endif
