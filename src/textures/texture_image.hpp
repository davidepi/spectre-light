//Created,   8 May 2018
//Last Edit  9 May 2018

#ifndef __TEXTURE_IMAGE_HPP__
#define __TEXTURE_IMAGE_HPP__

#include "textures/texture.hpp"
#include "textures/texture_image.hpp"
#include "textures/image_map.hpp"
#include "utility/file.hpp"
#include "utility/imageIO.hpp"
#include <mutex>
#include <cmath>

class TextureImage : public Texture
{
public:
    TextureImage(const char* input);

    TextureImage(const TextureImage& old) = delete;

    ~TextureImage();

    Spectrum map(Point2 uv) const;

private:
    void alloc() const;

    File path;
    unsigned char maps_no;
    mutable std::mutex mtx;
    mutable bool allocated;
    mutable ImageMap* mapchain;
};

#endif
