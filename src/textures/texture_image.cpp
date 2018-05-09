#include "texture_image.hpp"

TextureImage::TextureImage(const char* input):path(input)
{
    allocated = false;
    if(path.readable())
    {
        int width;
        int height;
        dimensions_RGB(path.absolute_path(), path.extension(), &width, &height);
        //square and power of two
        if(width == height && (width & (width-1)) == 0)
        {
            maps_no = (unsigned char)(1+(int)log2f(width));
            mapchain = new ImageMap[maps_no];
        }
        else
            Console.critical(MESSAGE_TEXTURE_POWER2, path.absolute_path());
    }
    else
        Console.critical(MESSAGE_TEXTURE_ERROR, path.absolute_path());
}

void TextureImage::alloc() const
{
    mtx.lock();
    //ensures that only 1 thread can access, even if multiples are stopped on
    //lock. Otherwise one could gain the mutex, and allocate, the other wait and
    //as soon as the mutex is released allocate aswell
    if(!allocated)
    {
        unsigned short side = (unsigned short)pow(2, maps_no-1);
        float* values = (float*)malloc(sizeof(float)*side*side*3);
        int res = read_RGB(path.absolute_path(), path.extension(), values,
                           NULL);
        if(res<0)
        {
            Console.critical(MESSAGE_TEXTURE_ERROR_2ND, path.absolute_path());
            mtx.unlock(); //to prevent locking during tests
            return;
        }
        //allocate original texture
        mapchain[0] = ImageMap(values, (int)pow(2, maps_no-1));
        free(values);
        if(!mapchain[0].is_valid())
        {
            //dealloc
            for(int j = 0; j<maps_no; j++)
                mapchain[j].dealloc();
        }
        else //allocate MIP maps
        {
            allocated = true;
            for(int i = 1; i<maps_no; i++)
            {
                mapchain[i].init_mipmap(mapchain[i-1], false);
                if(!mapchain[i].is_valid())
                {
                    //dealloc
                    for(int j = 0; j<maps_no; j++)
                        mapchain[j].dealloc();
                    allocated = false;
                }
            }
        }
        /* TODO: out of memory
        if(!allocated)
            ;
        */
    }
    mtx.unlock();
}

Spectrum TextureImage::map(Point2 uv) const
{
    if(!allocated)
        alloc();
    //TODO: bogus implementation, waiting for filter
    return Spectrum(mapchain[0].val((unsigned short)uv.x, (unsigned short)uv.y),
                    false);
}

TextureImage::~TextureImage()
{
    //dealloc(); //ImageMap destructor will do the job
    delete[] mapchain;
}
