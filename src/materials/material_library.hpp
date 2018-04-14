//Created,   7 Jul 2017
//Last Edit 14 Apr 2018

/**
 *  \file material_library.hpp
 *  \brief MaterialLibrary class
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date  14 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __MATERIAL_LIBRARY_HPP__
#define __MATERIAL_LIBRARY_HPP__

#include "materials/bdf.hpp"
#include "materials/lambertian.hpp"
#include <unordered_map>
#include <string>

/**
 * \class MaterialLibrary material_library.hpp "materials/material_library.hpp"
 * \brief Container for every material used
 *
 *  This class is used to store every material used in the renderer. It is a
 *  singleton, since this class stores constant values that will be assigned to
 *  the various shape at creation time. The library must be unique and
 *  accessible everywhere.
 *
 *  The library contains a default material called "Default" that represents a
 *  white matte surface
 *
 *  A define grants access to this singleton just by writing "MtlLib"
 *
 *  \warning This class is NOT thread-safe
 */
class MaterialLibrary
{
public:

    ///Get an instance of the material library
    static MaterialLibrary& instance()
    {
        static MaterialLibrary instance;
        return instance;
    }

    ///Avoid a copy of the object
    MaterialLibrary(MaterialLibrary const&) = delete;

    ///Avoid a copy of the object
    void operator=(MaterialLibrary const&) = delete;

    /** \brief Add a material to the library
     *
     *  Inherit a material and add it to the library. The library will ensure
     *  its deallocation.
     *
     *  \warning Adding the same material with different names will cause a
     *  double free error
     *
     *  \param[in] name The name of the material
     *  \param[in] material The material that will be added
     */
    void add_inherit(const std::string& name, Bsdf* material);

    /** \brief Retrieve a material from the library
     *
     *  Retrieve a material from the library. If the material can not be found
     *  the returned value will be NULL
     *
     * \param[in] name The material to retrieve
     * \return The material, if it is stored in the library, NULL otherwise
     */
    const Bsdf* get(const std::string& name)const;

    /** \brief Remove and deallocate a material from the library
     *
     *  Note that it is not possible to erase the default material
     *
     * \param[in] name The material that will be removed and deallocated
     */
    void erase(const std::string& name);

    /** \brief Erase and deallocate everything inside the material library
     *
     *  This method will clear and thus deallocate every material stored in the
     *  library. It is the same as calling erase for every stored material
     *  Note, however, that the default material will not be erased for
     *  integrity reasons.
     */
    void clear();

    /** \brief Check if the material library already contains a material
     *
     *  This method only checks if a material with the input name is already
     *  inside the material library
     *
     *  \param[in] name The name of the material that will be checked
     *  \return true if the material is already inside the library
     */
    bool contains(const std::string& name)const;
    
    /** \brief Returns the "Default" material
     *
     *  This method returns the "Default" material. It performs the same action
     *  as calling MaterialLibrary::get() with "Default" as parameter. However,
     *  since "Default" is a system material, it is cached inside this class
     *  and by using this method a call to the underlying hash map is avoided
     *
     *  \return The "Default" material
     */
    const Bsdf* get_default()const;

private:

    MaterialLibrary();
    ~MaterialLibrary();
    std::unordered_map<std::string,const Bsdf*> lib;
    Bsdf* default_material;
};

///Access the material library just by writing "MtlLib"
#define MtlLib MaterialLibrary::instance()

#endif
