//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_library.hpp"

TextureLibrary::TextureLibrary()
        :default_texture(new UniformTexture(SPECTRUM_ONE))
{
    lib.insert(std::make_pair("Default", default_texture));
}

TextureLibrary::~TextureLibrary()
{
    TextureLibrary::clear();
}

void TextureLibrary::add_inherit(const std::string& name, Texture* texture)
{
    lib.insert(std::make_pair(name, texture));
}

const Texture* TextureLibrary::get(const std::string& name) const
{
    const Texture* retval;
    std::unordered_map<std::string, const Texture*>::const_iterator got =
            lib.find(name);
    if(got != lib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

void TextureLibrary::erase(const std::string& name)
{
    if(name != "Default")
    {
        std::unordered_map<std::string, const Texture*>::const_iterator it =
                lib.find(name);
        if(it != lib.end())
        {
            delete it->second;
            lib.erase(it);
        }
    }
}

void TextureLibrary::clear()
{
    //remove Default to avoid deallocation
    std::unordered_map<std::string, const Texture*>::const_iterator got = lib.find(
            "Default");
    const Texture* dflt = got->second;
    lib.erase(got);

    for(std::pair<std::string, const Texture*> element:TextureLibrary::lib)
        delete element.second;
    TextureLibrary::lib.clear();

    //readd default texture
    lib.insert(std::make_pair("Default", dflt));
}

bool TextureLibrary::contains(const std::string& name) const
{
    std::unordered_map<std::string, const Texture*>::const_iterator got =
            lib.find(name);
    if(got != lib.end())
        return true;
    else
        return false;
}

const Texture* TextureLibrary::get_default() const
{
    return TextureLibrary::default_texture;
}
