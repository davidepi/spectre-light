//Created,  14 Mar 2018
//Last Edit  7 Sep 2018

/**
 *  \file texture_library.hpp
 *  \brief TextureLibrary class
 *  \author Davide Pizzolotto
 *  \version 0.2
 *  \date  7 Sep 2018
 *  \copyright GNU GPLv3
 */


#ifndef __TEXTURE_LIBRARY_HPP__
#define __TEXTURE_LIBRARY_HPP__

#include "textures/texture.hpp"
#include "textures/image_map.hpp"
#include <unordered_map>
#include <string>

//Forward declaration, since TextureImage needs TexLib
class TextureImage;

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
     *  \param[in] texture The Texture that will be added
     */
    void inherit_texture(const std::string& name, const Texture* texture);

    /** \brief Add an image to the library
     *
     *  Inherit an ImageMap and add it to the library. The library will ensure
     *  its deallocation.
     *
     *  \warning Adding the same image with different names will cause a
     *  double free error
     *
     *  \param[in] name The name of the texture
     *  \param[in] map The ImageMap that will be added
     */
    void inherit_map(const std::string& name, const ImageMap* map);

    /** \brief Retrieve a texture from the library
     *
     *  Retrieve a texture from the library. If the texture can not be found
     *  the returned value will be NULL
     *
     * \param[in] name The texture to retrieve
     * \return The texture, if it is stored in the library, NULL otherwise
     */
    const Texture* get_texture(const std::string& name) const;

    /** \brief Retrieve a map from the library
     *
     *  Retrieve an ImageMap from the library. If the ImageMap can not be found
     *  the returned value will be NULL
     *
     * \param[in] name The ImageMap to retrieve
     * \return The ImageMap, if it is stored in the library, NULL otherwise
     */
    const ImageMap* get_map(const std::string& name) const;

    /** \brief Remove and deallocate a texture from the library
     *
     * \param[in] name The texture that will be removed and deallocated
     */
    void erase_texture(const std::string& name);

    /** \brief Remove and deallocate a map from the library
     *
     * \param[in] name The name of the ImageMap that will be removed and
     *  deallocated
     */
    void erase_map(const std::string& name);

    /** \brief Erase and deallocate everything inside the texture library
     *
     *  This method will clear and thus deallocate every texture stored in the
     *  library, included maps and anonymous textures
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
    bool contains_texture(const std::string& name) const;

    /** \brief Check if the texture library already contains a map
     *
     *  This method only checks if an ImageMap with the input name is already
     *  inside the texture library
     *
     *  \param[in] name The name of the ImageMap that will be checked
     *  \return true if the ImageMap is already inside the library
     */
    bool contains_map(const std::string& name) const;

    /** \brief Returns the default texture
     *
     *  This method returns a default texture. This returned texture can be used
     *  whenever a Texture object and correspond to a white TextureUniform.
     *
     *  \return The default texture
     */
    const Texture* get_dflt_texture() const;

    /**
     *  \brief Returns the default ImageMap
     *
     *  Similar to the get_dflt_texture() method, this one returns the
     *  default ImageMap. The default ImageMap is a map of size 1 by 1,
     *  composed only of one white pixel and unfiltered
     *
     *  \return The default ImageMap
     */
    const ImageMap* get_dflt_map() const;

    /**
     *  \brief Returns the number of Texture elements in the TextureLibrary
     *
     *  The default texture is not counted, since it always exists.
     *
     *  \return The number of Texture elements contained in this TextureLibrary
     */
    int size_texture() const;

    /**
     *  \brief Returns the number of ImageMap elements in the TextureLibrary
     *
     *  The default map is not counted, since it always exists.
     *
     *  \return The number of ImageMap elements contained in this TextureLibrary
     */
    int size_map() const;

private:

    TextureLibrary();

    ~TextureLibrary();

    std::unordered_map<std::string, const Texture*> texlib;
    std::unordered_map<std::string, const ImageMap*> maplib;
    const Texture* default_texture;
    const ImageMap* default_map;
};

///Access the texture library just by writing "TexLib"
#define TexLib TextureLibrary::instance()

#endif
