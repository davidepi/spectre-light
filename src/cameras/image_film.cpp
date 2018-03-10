//author: Davide Pizzolotto
//license: GNU GPLv3

#include "image_film.hpp"

//check if extension is supported
static char check_extension(const char* fullpath)
{
    //dot included
    const char* extension = strrchr(fullpath,'.');
    int retval;
    //pos less than 4 chr expected for an extension
    if(strlen(extension)<4)
    {
        Console.warning(MESSAGE_MISSING_EXTENSION);
        retval = EXTENSION_NOT_SUPPORTED;
    }
    else
    {
        switch(extension[1])
        {
            case 'p':
            {
                if(strcmp(".ppm",extension)==0)
                {
                    retval = EXTENSION_PPM;
                    break;
                }
            }
            case 'b':
            {
                if(strcmp(".bmp",extension)==0)
                {
                    retval = EXTENSION_BMP;
                    break;
                }
            }
            default:
            {
#ifdef IMAGEMAGICK
                try
                {
                    Magick::CoderInfo info(extension+1);
                    if(info.isWritable())
                        retval = EXTENSION_NON_NATIVE;
                    else
                        //a fake message but... it is used to explain what
                        //happens now, instead of what genereted the issue
                        throw new Magick::Exception(MESSAGE_IM_UNSUPPORTED);
                }
                catch(Magick::Exception e)
                {
                    Console.warning(MESSAGE_IM_UNSUPPORTED);
                    retval = EXTENSION_NOT_SUPPORTED;
                }
#else
                Console.warning(MESSAGE_IM_OUT);
                retval = EXTENSION_NOT_SUPPORTED;
#endif
            }
        }
    }
    return retval;
}

ImageFilm::ImageFilm(int width, int height, const char* fullpath)
:width(width), height(height)
{
    //allocate image
    ImageFilm::buffer = (Pixel*)malloc(sizeof(Pixel)*width*height);
    //set as zero, I need to have number of samples = 0 for every pixel
    memset(ImageFilm::buffer, 0, sizeof(Pixel)*width*height);
    ImageFilm::filter = NULL;
    ImageFilm::filename = NULL;
    
    //check if folder is writable
    const char* file = strrchr(fullpath,PATH_SEPARATOR);
    char* folder;
    if(file!=NULL) //the path references another folder
    {
        int last_separator=(int)(file-fullpath)+1;
        folder = (char*) malloc(sizeof(char)*(last_separator+1));
        memcpy(folder, fullpath, sizeof(char)*last_separator);
        folder[last_separator] = '\0';
    }
    else //current folder
    {
        folder= (char*)malloc(sizeof(char)*3);
        folder[0] = '.';
        folder[1] = '/';
        folder[2] = '\0';
    }
    
#ifdef WIN32
    if(_access(folder,2)==-1)
#else
        if(access(folder,W_OK)!=0)
#endif
        {
            char* err=(char*)malloc(sizeof(char)*(strlen(MESSAGE_W_DENIED)
                                                  +strlen(folder)+1));
            sprintf(err,MESSAGE_W_DENIED,folder);
            Console.critical(err);
            free(err);
            return; //bail out during tests
        }
    
    //check extension, add .ppm if not supported
    ImageFilm::extension = check_extension(fullpath);
    int path_len = (int)strlen(fullpath)+1;
    //to add the .ppm at the end, if necessary
    if(ImageFilm::extension==EXTENSION_NOT_SUPPORTED)
        path_len+=4;
    ImageFilm::filename = (char*)malloc(sizeof(char)*path_len);
    memcpy(ImageFilm::filename,fullpath,sizeof(char)*path_len);
    if(ImageFilm::extension==EXTENSION_NOT_SUPPORTED)
    {
        path_len-=5; //point to the \0 of the string
        filename[path_len] = '.';    //add the new extension
        filename[path_len+1] = 'p';
        filename[path_len+2] = 'p';
        filename[path_len+3] = 'm';
        filename[path_len+4] = '\0';
    }
    free(folder);
}

ImageFilm::~ImageFilm()
{
    if(ImageFilm::buffer!=NULL)
        free(ImageFilm::buffer);
}

void ImageFilm::add_pixel(const Sample* sample, ColorXYZ color,
                          ExecutorData* secure_area)
{
    if(color.r<0)color.r=0;
    if(color.g<0)color.g=0;
    if(color.b<0)color.b=0;
    
    //calculate the affected pixels
    float centre_x = sample->posx-0.5f;
    float centre_y = sample->posy-0.5f;
    int update_x0 = (int)ceilf(centre_x-filter->x_range);
    int update_y0 = (int)ceilf(centre_y-filter->y_range);
    int update_x1 = (int)floorf(centre_x+filter->x_range);
    int update_y1 = (int)floorf(centre_y+filter->y_range);
    update_x0 = max(update_x0,0);
    update_y0 = max(update_y0,0);
    update_x1 = min(update_x1,width);
    update_y1 = min(update_y1,height);
    
    //foreach affected pixel
    for(int y=update_y0;y<update_y1;y++)
        for(int x=update_x0;x<update_x1;x++)
        {
            float weight = filter->weight(x-centre_x, y-centre_y);
            if(x < secure_area->startx || x > secure_area->endx ||
               y < secure_area->starty || y > secure_area->endy)
            {
                //critical section, other threads could interfere. deferred add
                TodoPixel pixel_toadd;
                pixel_toadd.x = x;
                pixel_toadd.y = y;
                pixel_toadd.cie_x = color.r*weight;
                pixel_toadd.cie_y = color.g*weight;
                pixel_toadd.cie_z = color.b*weight;
                pixel_toadd.samples = weight;
                secure_area->deferred.push(pixel_toadd);
            }
            else
            {
                //no chance that other threads will write this pixel, insta add
                Pixel* val = buffer+(width*y+x);
                val->cie_x += color.r*weight;
                val->cie_y += color.g*weight;
                val->cie_z += color.b*weight;
                val->samples += weight;
            }
        }
}

void ImageFilm::add_pixel_deferred(ExecutorData* secure_area)
{
    //try to gain the lock
    if(mtx.try_lock())
    {
        Pixel* value;
        TodoPixel pixel_toadd;
        //until the pixel not in the secure area are finished
        while(!secure_area->deferred.empty())
        {
            //add the current pixel, since I have the lock
            pixel_toadd = secure_area->deferred.top();
            secure_area->deferred.pop();
            value = buffer+(width*pixel_toadd.y+pixel_toadd.x);
            value->cie_x += pixel_toadd.cie_x;
            value->cie_y += pixel_toadd.cie_y;
            value->cie_z += pixel_toadd.cie_z;
            value->samples += pixel_toadd.samples;
        }
        mtx.unlock();
    }
}

void ImageFilm::add_pixel_forced(ExecutorData* secure_area)
{
    Pixel* value;
    TodoPixel pixel_toadd;
    
    //last chance to add the pixel, now I need the lock at any cost
    mtx.lock();
    //add every leftover
    while(!secure_area->deferred.empty())
    {
        pixel_toadd = secure_area->deferred.top();
        secure_area->deferred.pop();
        value = buffer+(width*pixel_toadd.y+pixel_toadd.x);
        value->cie_x += pixel_toadd.cie_x;
        value->cie_y += pixel_toadd.cie_y;
        value->cie_z += pixel_toadd.cie_z;
        value->samples += pixel_toadd.samples;
    }
    mtx.unlock();
}

void ImageFilm::set_filter(Filter* f)
{
    ImageFilm::filter = f;
}

bool ImageFilm::save_image()
{
    uint8_t* rgb_buffer=(uint8_t*)malloc(ImageFilm::width*ImageFilm::height*3);
    unsigned int i = 0;
    ColorRGB rgb;
    //use scale stored colour and output as .ppm
    for(int j=0;j<ImageFilm::width*ImageFilm::height;j++)
    {
        if(buffer[j].samples>0.f) //if at least one sample
        {
            float weight = 1.f/buffer[j].samples;
            rgb = ColorXYZ(buffer[j].cie_x*weight,
                           buffer[j].cie_y*weight,
                           buffer[j].cie_z*weight).to_sRGB();
        }
        rgb_buffer[i++] = (uint8_t)::min((::max(0.f,rgb.r)*0xFF),255.0f);
        rgb_buffer[i++] = (uint8_t)::min((::max(0.f,rgb.g)*0xFF),255.0f);
        rgb_buffer[i++] = (uint8_t)::min((::max(0.f,rgb.b)*0xFF),255.0f);
    }
    free(ImageFilm::buffer);
    ImageFilm::buffer = NULL;
    bool retval;
    switch(ImageFilm::extension)
    {
        case EXTENSION_BMP:
        {
            retval=save_bmp(filename, width, height, rgb_buffer);
            break;
        }
        case EXTENSION_NON_NATIVE:
        {
            retval=save_RGB(filename, width, height, rgb_buffer);
            break;
        }
        case EXTENSION_PPM:
        case EXTENSION_NOT_SUPPORTED:
        default:
            retval=save_ppm(filename, width, height, rgb_buffer);
    }
    free(rgb_buffer);
    return retval;
}
