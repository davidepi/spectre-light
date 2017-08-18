//Created,   7 Jul 2017
//Last Edit 18 Aug 2017

/**
 *  \file material_library.hpp
 *  \brief MaterialLibrary class
 *  \author Davide Pizzolotto
 *  \version 0.1
 *  \date  18 Aug 2017
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
 *  singleton, since this class store constant values that will be assigned to
 *  the various shape at creation time. The library must be unique and
 *  accessible everywhere.
 *
 *  The library contains a default material that represents a white matte
 *  surface
 *
 *  A define grant access to this singleton just by writing "MtlLib"
 */
class MaterialLibrary
{
public:

    ///Get an instance of the material library
    static MaterialLibrary& getInstance()
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
     *  \note It is not checked if the material is already inside the library
     *
     *  \param[in] name The name of the material
     *  \param[in] material The material that will be added
     */
    void add(const std::string& name, Bsdf* material);


    /** \brief Retrieve a material from the library
     *
     *  Retrieve a material from the library. If the material can not be found
     *  the returned value will be NULL
     *
     * \param[in] name The material to retrieve
     * \return The material, if it is stored in the library, NULL otherwise
     */
    const Bsdf* get(const std::string& name)const;

    /** \brief Retrieve a material from the library
     *
     *  Retrieve a material from the library for editing.
     *  If the material can not be found the returned value will be NULL
     *
     * \param[in] name The material to retrieve
     * \return The material, if it is stored in the library, NULL otherwise
     */
    Bsdf* edit(const std::string& name)const;


    /** \brief Remove and deallocate a material from the library
     *
     * \param[in] name The material that will be removed and deallocated
     */
    void remove(const std::string& name);

private:

    MaterialLibrary();

    std::unordered_map<std::string,Bsdf*> lib;
};

///Access the material library just by writing "MtlLib"
#define MtlLib MaterialLibrary::getInstance()

#endif
