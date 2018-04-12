//author: Davide Pizzolotto
//license: GNU GPLv3

#include "material_library.hpp"

MaterialLibrary::MaterialLibrary()
{
    Bsdf* dflt = new Bsdf();
    dflt->inherit_bdf(new Lambertian());
    lib.insert(std::make_pair("Default",dflt));
}

MaterialLibrary::~MaterialLibrary()
{
    MaterialLibrary::clear();
}

void MaterialLibrary::add_inherit(const std::string& name, Bsdf* material)
{
    lib.insert(std::make_pair(name,material));
}

const Bsdf* MaterialLibrary::get(const std::string& name)const
{
    const Bsdf* retval;
    std::unordered_map<std::string,Bsdf*>::const_iterator got = lib.find(name);
    if(got!=lib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

void MaterialLibrary::erase(const std::string& name)
{
    if(name!="Default")
    {
        std::unordered_map<std::string,Bsdf*>::const_iterator it=lib.find(name);
        if(it!=lib.end())
        {
            lib.erase(it);
            delete it->second;
        }
    }
}

void MaterialLibrary::clear()
{
    std::unordered_map<std::string,Bsdf*>::const_iterator got = lib.find("Default");
    Bsdf* dflt = got->second;
    lib.erase(got);
    
    for(std::pair<std::string, Bsdf*> element:MaterialLibrary::lib)
        delete element.second;
    MaterialLibrary::lib.clear();
    
    //readd default for integrity reasons
    lib.insert(std::make_pair("Default",dflt));
}

bool MaterialLibrary::contains(const std::string &name)const
{
    std::unordered_map<std::string,Bsdf*>::const_iterator got = lib.find(name);
    if(got!=lib.end())
        return true;
    else
        return false;
}
