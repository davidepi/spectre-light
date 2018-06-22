//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_library.hpp"

TextureLibrary::TextureLibrary()
        :default_texture(new TextureUniform(SPECTRUM_ONE))
{
    texlib.insert(std::make_pair("Default", default_texture));
    unfiltered = false;
}

TextureLibrary::~TextureLibrary()
{
    TextureLibrary::clear();
}

void TextureLibrary::inherit_texture(const std::string& name,
                                     const Texture* texture)
{
    texlib.insert(std::make_pair(name, texture));
}

void TextureLibrary::inherit_texture(const Texture* texture)
{
    unreferenced.push_back(texture);
}

void TextureLibrary::inherit_map(const std::string& name, const ImageMap* map)
{
    maplib.insert(std::make_pair(name, map));
}

const Texture* TextureLibrary::get_texture(const std::string& name) const
{
    const Texture* retval;
    std::unordered_map<std::string, const Texture*>::const_iterator got =
            texlib.find(name);
    if(got != texlib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

const ImageMap* TextureLibrary::get_map(const std::string& name) const
{
    const ImageMap* retval;
    std::unordered_map<std::string, const ImageMap*>::const_iterator got =
            maplib.find(name);
    if(got != maplib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

void TextureLibrary::erase_texture(const std::string& name)
{
    if(name != "Default")
    {
        std::unordered_map<std::string, const Texture*>::const_iterator it =
                texlib.find(name);
        if(it != texlib.end())
        {
            delete it->second;
            texlib.erase(it);
        }
    }
}

void TextureLibrary::erase_map(const std::string& name)
{
    std::unordered_map<std::string, const ImageMap*>::const_iterator it =
            maplib.find(name);
    if(it != maplib.end())
    {
        delete it->second;
        maplib.erase(it);
    }
}

void TextureLibrary::clear()
{
    //remove Default to avoid deallocation
    std::unordered_map<std::string, const Texture*>::const_iterator got =
            texlib.find("Default");

    const Texture* dflt = got->second;
    texlib.erase(got);

    for(std::pair<std::string, const Texture*> element:TextureLibrary::texlib)
        delete element.second;
    TextureLibrary::texlib.clear();

    for(std::pair<std::string, const ImageMap*> element:TextureLibrary::maplib)
        delete element.second;
    TextureLibrary::maplib.clear();

    for(const Texture* element:TextureLibrary::unreferenced)
        delete element;
    unreferenced.clear();

    //readd default texture
    texlib.insert(std::make_pair("Default", dflt));
}

bool TextureLibrary::contains_texture(const std::string& name) const
{
    std::unordered_map<std::string, const Texture*>::const_iterator got =
            texlib.find(name);
    return got != texlib.end();
}

bool TextureLibrary::contains_map(const std::string& name) const
{
    std::unordered_map<std::string, const ImageMap*>::const_iterator got =
            maplib.find(name);
    return got != maplib.end();
}

const Texture* TextureLibrary::get_default() const
{
    return TextureLibrary::default_texture;
}
