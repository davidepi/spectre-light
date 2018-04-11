//author: Davide Pizzolotto
//license: GNU GPLv3

#include "material_library.hpp"

MaterialLibrary::MaterialLibrary()
{
    Bsdf* default_mat = new Bsdf();
    default_mat->inherit_bdf(new Lambertian());
    lib.insert(std::make_pair("Default",default_mat));
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

Bsdf* MaterialLibrary::edit(const std::string& name)const
{
    Bsdf* retval;
    std::unordered_map<std::string,Bsdf*>::const_iterator got = lib.find(name);
    if(got!=lib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

void MaterialLibrary::erase(const std::string& name)
{
    std::unordered_map<std::string,Bsdf*>::const_iterator got = lib.find(name);
    if(got!=lib.end())
    {
        lib.erase(got);
        delete got->second;
    }
}

void MaterialLibrary::clear()
{
    for(std::pair<std::string, Bsdf*> element:MaterialLibrary::lib)
        delete element.second;
    MaterialLibrary::lib.clear();
}

bool MaterialLibrary::contains(const std::string &name)const
{
    std::unordered_map<std::string,Bsdf*>::const_iterator got = lib.find(name);
    if(got!=lib.end())
        return true;
    else
        return false;
}
