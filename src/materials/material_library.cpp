//author: Davide Pizzolotto
//license: GNU GPLv3

#include "material_library.hpp"

MaterialLibrary::MaterialLibrary()
{
    Bsdf* defmatl = new Bsdf();
    defmatl->inheritBdf(new Lambertian(SPECTRUM_WHITE));
    lib.insert(std::make_pair("Default",defmatl));
}

void MaterialLibrary::add(const std::string& name, Bsdf* material)
{
    lib.insert(std::make_pair(name,material));
}

const Bsdf* MaterialLibrary::get(const std::string& name)const
{
    const Bsdf* retval;
    std::unordered_map<std::string,Bsdf*>::const_iterator got =
            lib.find(name);

    if(got!=lib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

Bsdf* MaterialLibrary::edit(const std::string& name)const
{
    Bsdf* retval;
    std::unordered_map<std::string,Bsdf*>::const_iterator got =
            lib.find(name);

    if(got!=lib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

void MaterialLibrary::remove(const std::string& name)
{
    std::unordered_map<std::string,Bsdf*>::const_iterator got =
            lib.find(name);

    if(got!=lib.end())
    {
        lib.erase(got);
        delete got->second;
    }
}
