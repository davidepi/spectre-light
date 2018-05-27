#include "texture_image.hpp"

TextureImage::TextureImage(const ImageMap* map, float sx, float sy)
{
    imagemap = map;
    scale_x = sx;
    scale_y = sy;
    filtered = !TexLib.is_unfiltered();
}

Spectrum TextureImage::map(const HitPoint* hit) const
{
    float u = hit->uv.x*scale_x;
    float v = hit->uv.y*scale_y;

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
            float dudx = hit->du.x*scale_x;
            float dudy = hit->du.y*scale_y;
            float dvdx = hit->dv.x*scale_x;
            float dvdy = hit->dv.y*scale_y;
            res = (imagemap->*(imagemap->filter))(u, v, dudx, dvdx, dudy, dvdy);
        }
        else
        {
            res = (imagemap->*(imagemap->filter))(u, v, 0, 0, 0, 0);
        }
    }
    return Spectrum(res, false);
}


