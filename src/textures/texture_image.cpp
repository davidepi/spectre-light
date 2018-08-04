#include "texture_image.hpp"

TextureImage::TextureImage(const File& src, Vec2& scale, Vec2& shift,
                           TextureFilter_t filter):scale(scale), shift(shift)
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
                //TODO: Remove the uint8_t when ImageMap will have alpha support
                uint8_t* data = (uint8_t*)malloc(width*height*3);
                uint32_t* bgra_data = (uint32_t*)malloc(width*height);
                img_read8(src.absolute_path(), src.extension(), bgra_data);
                BGRAtoRGB(data, bgra_data, width*height);
                free(bgra_data);

                switch(filter)
                {
                    case UNFILTERED:
                        imagemap = new ImageMapUnfiltered(data, width);
                        break;
                    case TRILINEAR:
                        imagemap = new ImageMapTrilinear(data, width);
                        break;
                    case EWA:imagemap = new ImageMapEWA(data, width);
                        break;
                }
                free(data);
                TexLib.inherit_map(src.absolute_path(), imagemap);
            }
            else
            {
                Console.warning(MESSAGE_TEXTURE_POWER2, src.absolute_path());
                imagemap = TexLib.get_map("Default");
            }
        }
        else
        {
            //should be checked by parser
            Console.warning(MESSAGE_TEXTURE_ERROR, src.absolute_path());
            imagemap = TexLib.get_map("Default");
        }
    }
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
    return Spectrum(res, false);
}

Vec2 TextureImage::get_shift() const
{
    return TextureImage::shift;
}

Vec2 TextureImage::get_scale() const
{
    return TextureImage::scale;
}
