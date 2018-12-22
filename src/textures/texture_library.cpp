//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_library.hpp"
#include "texture_image.hpp"

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
