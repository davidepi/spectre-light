//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_library.hpp"

TextureLibrary::~TextureLibrary()
{
    TextureLibrary::clear();
}

void TextureLibrary::add_inherit(const std::string& name, Texture* texture)
{
    lib.insert(std::make_pair(name,texture));
}

const Texture* TextureLibrary::get(const std::string& name)const
{
    const Texture* retval;
    std::unordered_map<std::string,Texture*>::const_iterator got=lib.find(name);
    if(got!=lib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

void TextureLibrary::erase(const std::string& name)
{
    std::unordered_map<std::string,Texture*>::const_iterator got=lib.find(name);
    if(got!=lib.end())
    {
        lib.erase(got);
        delete got->second;
    }
}

void TextureLibrary::clear()
{
    for(std::pair<std::string, Texture*> element:TextureLibrary::lib)
        delete element.second;
    TextureLibrary::lib.clear();
}

bool TextureLibrary::contains(const std::string &name)const
{
    std::unordered_map<std::string,Texture*>::const_iterator got=lib.find(name);
    if(got!=lib.end())
        return true;
    else
        return false;
}
