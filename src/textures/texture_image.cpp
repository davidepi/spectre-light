#include "texture_image.hpp"

TextureImage::TextureImage(const char* input)
{
    imagemap = TexLib.get_map(input);
    //no checks if imagemap is not found, shouldn't be user's fault
    //ImageMap constructor already checks if it is user's fault
}

TextureImage::TextureImage(const File* input)
{
    imagemap = TexLib.get_map(input->absolute_path());
}

Spectrum TextureImage::map(const HitPoint*) const
{
    return Spectrum();
}
