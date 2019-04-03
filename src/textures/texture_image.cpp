//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_image.hpp"
#include "textures/texture_library.hpp"
#include "primitives/hit_point.hpp"

TextureImage::TextureImage(const File& src, const Vec2& shift, const Vec2& scale,
                           texturefilter_t filter):scale(scale), shift(shift)
{
    unfiltered = filter == UNFILTERED;
    if(TexLib.contains_map(src.absolute_path())) //imagemap already parsed
    {
        imagemap = TexLib.get_map(src.absolute_path());
    }
    else //create imagemap
    {
        if(src.readable())
        {
            int width;
            int height;
            img_dimensions(src.absolute_path(), src.extension(),
                           &width, &height);
            if(width == height && (height & (height-1)) == 0) //power of 2
            {
                uint32_t* bgra_data = (uint32_t*)malloc(width*height*sizeof
                        (uint32_t));
                img_read8(src.absolute_path(), src.extension(), bgra_data);
                switch(filter)
                {
                    case UNFILTERED:
                        imagemap = new ImageMapUnfiltered(bgra_data, width);
                        break;
                    case TRILINEAR:
                        imagemap = new ImageMapTrilinear(bgra_data, width);
                        break;
                    case EWA:imagemap = new ImageMapEWA(bgra_data, width);
                        break;
                }
                free(bgra_data);
                TexLib.inherit_map(src.absolute_path(), imagemap);
            }
            else
            {
                Console.warning(MESSAGE_TEXTURE_POWER2, src.absolute_path());
                imagemap = TexLib.get_dflt_map();
            }
        }
        else
        {
            //should be checked by parser
            Console.warning(MESSAGE_TEXTURE_ERROR, src.absolute_path());
            imagemap = TexLib.get_dflt_map();
        }
    }
}

TextureImage::TextureImage(const ImageMap* map, Vec2& shift, Vec2& scale,
                           bool unfiltered):scale(scale), shift(shift),
                                            unfiltered(unfiltered),
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
    if(unfiltered)
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
