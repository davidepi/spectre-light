//Created,  14 Mar 2018
//Last Edit 14 Apr 2018

/**
 *  \file texture_library.hpp
 *  \brief TextureLibrary class
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date  14 Apr 2018
 *  \copyright GNU GPLv3
 */


#ifndef __TEXTURE_LIBRARY_HPP__
#define __TEXTURE_LIBRARY_HPP__

#include "textures/texture.hpp"
#include "textures/texture_uniform.hpp"
#include <unordered_map>
#include <string>

/**
 * \class TextureLibrary texture_library.hpp "textures/texture_library.hpp"
 * \brief Container for every texture used
 *
 *  This class is used to store every texture used in the renderer. It is a
 *  singleton, since this class stores constant values that will be assigned to
 *  the various shape at creation time. The library must be unique and
 *  accessible everywhere.
 *
 *  A define grants access to this singleton just by writing "TexLib"
 *
 *  \warning This class is NOT thread-safe
 */
class TextureLibrary
{
public:

    ///Get an instance of the texture library
    static TextureLibrary& instance()
    {
        static TextureLibrary instance;
        return instance;
    }

    ///Avoid a copy of the object
    TextureLibrary(TextureLibrary const&) = delete;

    ///Avoid a copy of the object
    void operator=(TextureLibrary const&) = delete;

    /** \brief Add a texture to the library
     *
     *  Inherit a texture and add it to the library. The library will ensure
     *  its deallocation.
     *
     *  \warning Adding the same texture with different names will cause a
     *  double free error
     *
     *  \param[in] name The name of the texture
     *  \param[in] texture The texture that will be added
     */
    void add_inherit(const std::string& name, Texture* texture);

    /** \brief Retrieve a texture from the library
     *
     *  Retrieve a texture from the library. If the texture can not be found
     *  the returned value will be NULL
     *
     * \param[in] name The texture to retrieve
     * \return The texture, if it is stored in the library, NULL otherwise
     */
    const Texture* get(const std::string& name) const;

    /** \brief Remove and deallocate a texture from the library
     *
     *  Note that it is not possible to erase the "Default" texture
     *
     * \param[in] name The texture that will be removed and deallocated
     */
    void erase(const std::string& name);

    /** \brief Erase and deallocate everything inside the texture library
     *
     *  This method will clear and thus deallocate every texture stored in the
     *  library. It is the same as calling erase for every stored texture.
     *  Note, however, that the "Default" texture will not be removed for
     *  integrity reasons
     */
    void clear();

    /** \brief Check if the texture library already contains a texture
     *
     *  This method only checks if a texture with the input name is already
     *  inside the texture library
     *
     *  \param[in] name The name of the texture that will be checked
     *  \return true if the texture is already inside the library
     */
    bool contains(const std::string& name) const;

    /** \brief Returns the "Default" texture
     *
     *  This method returns the "Default" texture. It performs the same action
     *  as calling TextureLibrary::get() with "Default" as parameter. However,
     *  since "Default" is a system texture, it is cached inside this class
     *  and by using this method a call to the underlying hash map is avoided
     *
     *  \return The "Default" texture
     */
    const Texture* get_default() const;

private:

    TextureLibrary();

    ~TextureLibrary();

    std::unordered_map<std::string, const Texture*> lib;
    const Texture* default_texture;
};

///Access the texture library just by writing "TexLib"
#define TexLib TextureLibrary::instance()

#endif

