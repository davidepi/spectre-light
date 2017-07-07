#include "material_library.hpp"

MaterialLibrary::MaterialLibrary()
{
    Bsdf* defmatl = new Bsdf();
    Color white;
    white.r = 1.f;
    white.g = 1.f;
    white.b = 1.f;
    Lambertian l(white);
    defmatl->addBdf(static_cast<Bdf*>(&l));
    lib.insert({{"Default",defmatl}});
}

void MaterialLibrary::add(std::string name, const Bsdf* material)
{
    lib.insert({{name,material}});
}

const Bsdf* MaterialLibrary::get(std::string name)const
{
    const Bsdf* retval;
    std::unordered_map<std::string,const Bsdf*>::const_iterator got =
            lib.find(name);

    if(got!=lib.end())
        retval = got->second;
    else
        retval = NULL;
    return retval;
}

void MaterialLibrary::remove(std::string name)
{
    std::unordered_map<std::string,const Bsdf*>::const_iterator got =
            lib.find(name);

    if(got!=lib.end())
    {
        lib.erase(got);
        delete got->second;
    }
}