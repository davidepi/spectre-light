//author: Davide Pizzolotto
//license: GNU GPLv3

#include "texture_library.hpp"

TextureLibrary::TextureLibrary()
{
    Texture* dflt = new UniformTexture(SPECTRUM_ONE);
    lib.insert(std::make_pair("Default",dflt));
}

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
    if(name!="Default")
    {
        std::unordered_map<std::string,Texture*>::const_iterator it =
            lib.find(name);
        if(it!=lib.end())
        {
            lib.erase(it);
            delete it->second;
        }
    }
}

void TextureLibrary::clear()
{
    //remove Default to avoid deallocation
    std::unordered_map<std::string,Texture*>::const_iterator got=lib.find("Default");
    Texture* dflt = got->second;
    lib.erase(got);
    
    for(std::pair<std::string, Texture*> element:TextureLibrary::lib)
        delete element.second;
    TextureLibrary::lib.clear();
    
    //readd default texture
    lib.insert(std::make_pair("Default",dflt));
}

bool TextureLibrary::contains(const std::string &name)const
{
    std::unordered_map<std::string,Texture*>::const_iterator got=lib.find(name);
    if(got!=lib.end())
        return true;
    else
        return false;
}
