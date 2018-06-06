#include "texture_image.hpp"

TextureImage::TextureImage(const ImageMap* map, Vec2& scale, Vec2& shift)
        :scale(scale), shift(shift)
{
    imagemap = map;
    filtered = !TexLib.is_unfiltered();
}

Spectrum TextureImage::map(const HitPoint* hit) const
{
    float u = hit->uv.x*scale.x+shift.x;
    float v = hit->uv.y*scale.y+shift.y;

    //apply repeating if uv are outside 0-1 range
    if(u>1.f)
        u = u-(int)u;
    if(v>1.f)
        v = v-(int)v;

    ColorRGB res;
    if(!filtered)
    {
        res = (imagemap->*(imagemap->filter))(u, v, 0, 0, 0, 0);
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
            res = (imagemap->*(imagemap->filter))(u, v, dudx, dvdx, dudy, dvdy);
        }
        else
        {
            res = (imagemap->*(imagemap->filter))(u, v, 0, 0, 0, 0);
        }
    }
    return Spectrum(res, false);
}


