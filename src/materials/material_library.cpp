#include "material_library.hpp"

MaterialLibrary::MaterialLibrary()
{
    Bsdf* defmatl = new Bsdf();
    Color white;
    white.r = 1.f;
    white.g = 1.f;
    white.b = 1.f;
    defmatl->inheritBdf(new Lambertian(white));
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
