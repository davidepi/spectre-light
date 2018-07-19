//author: Davide Pizzolotto
//license: GNU GPLv3

#include "image_film.hpp"

ImageFilm::ImageFilm(int width, int height, const char* fullpath)
        :width(width), height(height), output(fullpath)
{
    ImageFilm::filter = NULL;
    //allocate image
    ImageFilm::buffer = (Pixel*)malloc(sizeof(Pixel)*width*height);
    //set as zero, I need to have number of samples = 0 for every pixel
    memset(ImageFilm::buffer, 0, sizeof(Pixel)*width*height);
    if(output.exists() && output.is_folder())
    {
        Console.critical(MESSAGE_OUTPUT_ISFOLDER);
        return; // <- bail out in tests since critical msg does not kill program
    }
    File parent_folder = output.get_parent();
    if(parent_folder.writable())
    {
        //check extension, add .ppm if not supported
        bool valid = img_valid(output.absolute_path(), output.extension());
        int path_len = (int)strlen(fullpath)+1;
        //to add the .ppm at the end, if necessary
        if(!valid)
        {
            char* tmp_buf = (char*)malloc(sizeof(char)*path_len+4);
            strcpy(tmp_buf, fullpath);
            strcat(tmp_buf, ".ppm");
            output = File(tmp_buf);
            free(tmp_buf);
            Console.warning(MESSAGE_IM_OUT, output.absolute_path());
            //check again the folder, since the extension changed it
            if(output.exists() && output.is_folder())
            {
                Console.critical((const char*)MESSAGE_W_DENIED,
                                 parent_folder.absolute_path());
                return; //bail out during tests
            }
        }
    }
    else
        Console.critical(MESSAGE_W_DENIED, parent_folder.absolute_path());
}

ImageFilm::~ImageFilm()
{
    if(ImageFilm::buffer != NULL)
        free(ImageFilm::buffer);
}

void ImageFilm::add_pixel(const Sample* sample, ColorXYZ color,
                          ExecutorData* secure_area)
{
    if(color.r<0)color.r = 0;
    if(color.g<0)color.g = 0;
    if(color.b<0)color.b = 0;

    //calculate the affected pixels
    float centre_x = sample->posx-0.5f;
    float centre_y = sample->posy-0.5f;
    int update_x0 = (int)ceilf(centre_x-filter->range_x);
    int update_y0 = (int)ceilf(centre_y-filter->range_y);
    int update_x1 = (int)floorf(centre_x+filter->range_x);
    int update_y1 = (int)floorf(centre_y+filter->range_y);
    update_x0 = max(update_x0, 0);
    update_y0 = max(update_y0, 0);
    update_x1 = min(update_x1, width);
    update_y1 = min(update_y1, height);

    //foreach affected pixel
    for(int y = update_y0; y<update_y1; y++)
        for(int x = update_x0; x<update_x1; x++)
        {
            float weight = filter->weight(x-centre_x, y-centre_y);
            if(x<secure_area->startx || x>secure_area->endx ||
               y<secure_area->starty || y>secure_area->endy)
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
    uint8_t* rgb_buffer = (uint8_t*)malloc(
            ImageFilm::width*ImageFilm::height*3);
    unsigned int i = 0;
    ColorRGB rgb;
    //use scale stored colour and output as .ppm
    for(int j = 0; j<ImageFilm::width*ImageFilm::height; j++)
    {
        if(buffer[j].samples>0.f) //if at least one sample
        {
            float weight = 1.f/buffer[j].samples;
            rgb = ColorXYZ(buffer[j].cie_x*weight,
                           buffer[j].cie_y*weight,
                           buffer[j].cie_z*weight).to_sRGB();
        }
        else
            rgb = ColorRGB(0.f, 0.f, 0.f);
        rgb_buffer[i++] = (uint8_t)::min((::max(0.f, rgb.r)*0xFF), 255.0f);
        rgb_buffer[i++] = (uint8_t)::min((::max(0.f, rgb.g)*0xFF), 255.0f);
        rgb_buffer[i++] = (uint8_t)::min((::max(0.f, rgb.b)*0xFF), 255.0f);
    }
    free(ImageFilm::buffer);
    ImageFilm::buffer = NULL;
    bool retval = img_write(output.absolute_path(), output.extension(),
                            width, height, rgb_buffer);
    free(rgb_buffer);
    return retval;
}
