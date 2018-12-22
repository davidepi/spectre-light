//author: Davide Pizzolotto
//license: GNU GPLv3

#include "material_library.hpp"

MaterialLibrary::MaterialLibrary()
{
    MaterialLibrary::default_material = new SingleBRDF(new Lambertian());
}

MaterialLibrary::~MaterialLibrary()
{
    MaterialLibrary::clear();
    delete default_material;
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
    auto it = lib.find(name);
    if(it != lib.end())
    {
        delete it->second;
        lib.erase(it);
    }
}

void MaterialLibrary::clear()
{
    for(std::pair<std::string, const Bsdf*> element:MaterialLibrary::lib)
        delete element.second;
    MaterialLibrary::lib.clear();
}

bool MaterialLibrary::contains(const std::string& name) const
{
    std::unordered_map<std::string, const Bsdf*>::const_iterator got =
            lib.find(name);
    return got != lib.end();
}

const Bsdf* MaterialLibrary::get_default() const
{
    return MaterialLibrary::default_material;
}

int MaterialLibrary::size() const
{
    return (int)lib.size();
}
