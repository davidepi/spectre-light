//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_library.hpp"
#include "texture_image.hpp"
#include "textures/texture_uniform.hpp"
#include "materials/bump.hpp"
#include "texture_image.hpp"
#include <vector>

TextureLibrary::TextureLibrary()
{
    default_texture = new TextureUniform(SPECTRUM_ONE);
    pixBGRA value = 0xFFFFFFFF;
    default_map = new ImageMapUnfiltered(&value, 1);
}

TextureLibrary::~TextureLibrary()
{
    TextureLibrary::clear();
    delete default_map;
    delete default_texture;
}

void TextureLibrary::inherit_texture(const std::string& name,
                                     const Texture* texture)
{
    texlib.insert(std::make_pair(name, texture));
}

void TextureLibrary::inherit_map(const std::string& name, const ImageMap* map)
{
    maplib.insert(std::make_pair(name, map));
}

const Texture* TextureLibrary::get_texture(const std::string& name) const
{
    const Texture* retval;
    auto got = texlib.find(name);
    if(got != texlib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

const ImageMap* TextureLibrary::get_map(const std::string& name) const
{
    const ImageMap* retval;
    auto got = maplib.find(name);
    if(got != maplib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

void TextureLibrary::erase_texture(const std::string& name)
{
    auto it = texlib.find(name);
    if(it != texlib.end())
    {
        delete it->second;
        texlib.erase(it);
    }
}

void TextureLibrary::erase_map(const std::string& name)
{
    auto it = maplib.find(name);
    if(it != maplib.end())
    {
        delete it->second;
        maplib.erase(it);
    }
}

void TextureLibrary::clear()
{
    for(std::pair<std::string, const Texture*> element:TextureLibrary::texlib)
        delete element.second;
    TextureLibrary::texlib.clear();

    for(std::pair<std::string, const ImageMap*> element:TextureLibrary::maplib)
        delete element.second;
    TextureLibrary::maplib.clear();
}

bool TextureLibrary::contains_texture(const std::string& name) const
{
    auto got = texlib.find(name);
    return got != texlib.end();
}

bool TextureLibrary::contains_map(const std::string& name) const
{
    auto got = maplib.find(name);
    return got != maplib.end();
}

const Texture* TextureLibrary::get_dflt_texture() const
{
    return TextureLibrary::default_texture;
}

const ImageMap* TextureLibrary::get_dflt_map() const
{
    return TextureLibrary::default_map;
}

int TextureLibrary::size_texture() const
{
    return (int)texlib.size();
}

int TextureLibrary::size_map() const
{
    return (int)maplib.size();
}

const ImageMap* resolve_map(const File* src, TextureLibrary* texlib,
                            texturefilter_t filter)
{
    const ImageMap* imagemap;
    if(texlib->contains_map(src->absolute_path())) //imagemap already parsed
    {
        imagemap = texlib->get_map(src->absolute_path());
    }
    else //create imagemap
    {
        if(src->readable())
        {
            int width;
            int height;
            img_dimensions(src->absolute_path(), src->extension(),
                           &width, &height);
            if(width == height && (height & (height-1)) == 0) //power of 2
            {
                uint32_t* bgra_data = (uint32_t*)malloc(width*height*sizeof
                        (uint32_t));
                img_read8(src->absolute_path(), src->extension(), bgra_data);
                switch(filter)
                {
                    case TRILINEAR:
                        imagemap = new ImageMapTrilinear(bgra_data, width);
                        break;
                    case EWA:imagemap = new ImageMapEWA(bgra_data, width);
                        break;
                    case UNFILTERED:
                    default:imagemap = new ImageMapUnfiltered(bgra_data, width);
                }
                free(bgra_data);
                texlib->inherit_map(src->absolute_path(), imagemap);
            }
            else
            {
                Console.warning(MESSAGE_TEXTURE_POWER2, src->absolute_path());
                imagemap = texlib->get_dflt_map();
            }
        }
        else
        {
            //should be checked by parser
            Console.warning(MESSAGE_TEXTURE_ERROR, src->absolute_path());
            imagemap = texlib->get_dflt_map();
        }
    }
    return imagemap;
}
