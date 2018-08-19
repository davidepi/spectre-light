//
//  texture_height.hpp
//  spectre-light
//
//  Created by Davide Pizzolotto on 18/08/13.
//

#ifndef __TEXTURE_HEIGHT_HPP__
#define __TEXTURE_HEIGHT_HPP__

#include "textures/texture_image.hpp"
#include "textures/texture_bump.hpp"

class TextureHeight : public TextureBump
{
public:
    
    using TextureBump::TextureBump;
    
    void bump(const HitPoint& hp)const override;
};

#endif
