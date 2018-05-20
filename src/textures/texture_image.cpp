#include "texture_image.hpp"

TextureImage::TextureImage(const ImageMap* map)
{
    imagemap = map;
    scale_x = 1.f;
    scale_y = 1.f;
    filtered = false;
}

Spectrum TextureImage::map(const HitPoint* hit) const
{
    float u = hit->uv.x * scale_x;
    float v = hit->uv.y * scale_y;

    //apply repeating if uv are outside 0-1 range
    if(u >1.f)
        u = u-(int)u;
    if(v>1.f)
        v = v-(int)v;

    ColorRGB res;
    if(!filtered)
    {
        res = (imagemap->*(imagemap->filter))(u,v,0,0,0,0);
    }
    return Spectrum(res,false);
}
