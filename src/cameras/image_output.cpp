#include "image_output.hpp"

//check if extension is supported
bool check_extension(const char* fn)
{
    const char* name = strrchr(fn,'.');
    if(name == NULL)
    {
        Console.warning(MESSAGE_MISSING_EXTENSION);
        return false;
    }
    else
    {
#ifndef IMAGEMAGICK_FOUND
        Console.warning(
                   "ImageMagick is not installed. Image will be saved as .ppm");
        return false;
#else
        return true;
#endif
    }
}

ImageOutput::ImageOutput(int w, int h, const char* fn) :width(w), height(h)
{
    //allocate image
    ImageOutput::image = (Pixel*)malloc(sizeof(Pixel)*w*h);
    //set as zero, I need to have number of samples = 0 for every pixel
    memset(ImageOutput::image, 0, sizeof(Pixel)*w*h);
    ImageOutput::f = NULL;
    ImageOutput::filename = NULL;
    if(fn != NULL)
    {
        //check extension, add .ppm if not supported
        bool res = check_extension(fn);
        int len = (int)strlen(fn)+1;
        len += res?0:4; //to add the .ppm at the end, if there was no extension
        ImageOutput::filename = (char*)malloc(sizeof(char)*len);
        memcpy(ImageOutput::filename,fn,sizeof(char)*len);
        if(!res)
        {
            len-=5; //point to the \0 of the string
            filename[len] = '.';    //add the new extension
            filename[len+1] = 'p';
            filename[len+2] = 'p';
            filename[len+3] = 'm';
            filename[len+4] = '\0';
        }
    }
    else
    {
        ImageOutput::filename = (char*)malloc(sizeof(char)*8);
        filename[0] = 'o'; //what about memcpy?
        filename[1] = 'u';
        filename[2] = 't';
        filename[3] = '.';
        filename[4] = 'p';
        filename[5] = 'p';
        filename[6] = 'm';
        filename[7] = '\0';
    }
}

ImageOutput::~ImageOutput()
{
    free(ImageOutput::image);
}

void ImageOutput::addPixel(Sample* s, Color* c)
{
    float ptmpx = s->posx-0.5f;
    float ptmpy = s->posy-0.5f;
    int p0x = (int)ceil(ptmpx-f->x_range);
    int p0y = (int)ceil(ptmpy-f->y_range);
    int p1x = (int)floor(ptmpx+f->x_range);
    int p1y = (int)floor(ptmpy+f->y_range);
    p0x = max(p0x,0);
    p0y = max(p0y,0);
    p1x = min(p1x,width);
    p1y = min(p1y,height);
    for(int y=p0y;y<p1y;y++)
        for(int x=p0x;x<p1x;x++)
        {
            float weight = f->weight(x-ptmpx, y-ptmpy);
            Pixel* val = image+(width*y+x);
            mtx.lock();
            val->r += c->r*weight;
            val->g += c->g*weight;
            val->b += c->b*weight;
            val->samples += weight;
            mtx.unlock();
        }
}

void ImageOutput::setFilter(Filter* f)
{
    ImageOutput::f = f;
}

bool ImageOutput::saveImage()
{
    uint8_t* tmp = (uint8_t*)malloc((size_t)(ImageOutput::width
                                             *ImageOutput::height*3));
    int i = 0;
    
    //evaluate average for every pixel
    for(int j=0;j<ImageOutput::width*ImageOutput::height;j++)
    {
        if(image[j].samples>0.f) //if at least one sample
        {
            float weight = 1.f/image[j].samples;
            tmp[i++] = (uint8_t)(image[j].r*255*weight);
            tmp[i++] = (uint8_t)(image[j].g*255*weight);
            tmp[i++] = (uint8_t)(image[j].b*255*weight);
        }
        else
        {
            tmp[i++] = 0;
            tmp[i++] = 0;
            tmp[i++] = 0;
        }
    }
    
    //TODO: consider moving this inside utility class
    FILE* fout = fopen(filename,"wb"); //save as ppm
    if(fout != NULL)
    {
        fprintf(fout,"P6 %d %d 255 ",width,height);
        fwrite(tmp, sizeof(unsigned char), (size_t)(width*height*3), fout);
        fclose(fout);
        free(tmp);
        return true;
    }
    else
    {
        free(tmp);
        return false;
    }
}
