//author: Davide Pizzolotto
//license: GNU GPLv3

#include "material_library.hpp"

MaterialLibrary::MaterialLibrary()
{
    MaterialLibrary::default_material = new Bsdf();
    default_material->inherit_bdf(new Lambertian());
    lib.insert(std::make_pair("Default", default_material));
}

MaterialLibrary::~MaterialLibrary()
{
    MaterialLibrary::clear();
}

void MaterialLibrary::add_inherit(const std::string& name, Bsdf* material)
{
    lib.insert(std::make_pair(name, material));
}

const Bsdf* MaterialLibrary::get(const std::string& name) const
{
    const Bsdf* retval;
    std::unordered_map<std::string, const Bsdf*>::const_iterator got =
            lib.find(name);
    if(got != lib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

void MaterialLibrary::erase(const std::string& name)
{
    if(name != "Default")
    {
        std::unordered_map<std::string, const Bsdf*>::const_iterator it =
                lib.find(name);
        if(it != lib.end())
        {
            delete it->second;
            lib.erase(it);
        }
    }
}

void MaterialLibrary::clear()
{
    //remove "Default" material to avoid deallocation
    std::unordered_map<std::string, const Bsdf*>::const_iterator got =
            lib.find("Default");
    const Bsdf* dflt = got->second;
    lib.erase(got);

    for(std::pair<std::string, const Bsdf*> element:MaterialLibrary::lib)
        delete element.second;
    MaterialLibrary::lib.clear();

    //readd "Default" for integrity reasons
    lib.insert(std::make_pair("Default", dflt));
}

bool MaterialLibrary::contains(const std::string& name) const
{
    std::unordered_map<std::string, const Bsdf*>::const_iterator got =
            lib.find(name);
    if(got != lib.end())
        return true;
    else
        return false;
}

const Bsdf* MaterialLibrary::get_default() const
{
    return MaterialLibrary::default_material;
}
