//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_image.hpp"
#include "textures/texture_library.hpp"
#include "primitives/hit_point.hpp"

TextureImage::TextureImage(const ImageMap* map, const Vec2& shift,
                           const Vec2& scale):scale(scale), shift(shift),
                                              imagemap(map)
{}

TexelUnion TextureImage::map_value(const HitPoint* hit) const
{
    float u = hit->uv.x*scale.x+shift.x;
    float v = hit->uv.y*scale.y+shift.y;

    //apply repeating if uv are outside 0-1 range
    if(u>1.f)
        u = u-(int)u;
    if(v>1.f)
        v = v-(int)v;

    TexelUnion res;
    if(!imagemap->filtered())
    {
        res = imagemap->filter(u, v, 0, 0, 0, 0);
    }
    else
    {
        if(hit->differentials)
        {
            //scale dudx dvdx dudy dvdy
            float dudx = hit->du.x*scale.x;
            float dudy = hit->du.y*scale.y;
            float dvdx = hit->dv.x*scale.x;
            float dvdy = hit->dv.y*scale.y;
            res = imagemap->filter(u, v, dudx, dvdx, dudy, dvdy);
        }
        else
        {
            res = imagemap->filter(u, v, 0, 0, 0, 0);
        }
    }
    return res;
}

Vec2 TextureImage::get_shift() const
{
    return TextureImage::shift;
}

Vec2 TextureImage::get_scale() const
{
    return TextureImage::scale;
}

uint16_t TextureImage::get_side() const
{
    return imagemap->get_side();
}
