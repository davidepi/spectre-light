#include "image_output.hpp"

bool check_extension(const char* fn)
{
    const char* name = strrchr(fn,'.');
    if(name == NULL)
    {
        Console.warning(
                   "Missing extension in filename. File will be saved as .ppm");
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
    ImageOutput::image = (Pixel*)malloc(sizeof(Pixel)*w*h);
    ImageOutput::filename = NULL;
    if(fn != NULL)
    {
        bool res = check_extension(fn);
        int len = (int)strlen(fn)+1;
        len += res?0:4; //to add the .bmp at the end, if there was no extension
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
    int p1x = (int)floor(ptmpx-f->x_range);
    int p1y = (int)floor(ptmpy-f->y_range);
    for(int y=p0y;y<p1y;y++)
        for(int x=p0x;x<p1x;x++)
        {
            float weight = f->weight(x-ptmpx, y-ptmpy);
            Pixel* val = image+(x*y+x);
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
    ImageOutput::f = dynamic_cast<Filter*>(f);
}

bool ImageOutput::saveImage()
{
    unsigned char tmp[ImageOutput::width*ImageOutput::height*3];
    int i = 0;
    for(int j=0;j<ImageOutput::width*ImageOutput::height;j++)
    {
        tmp[i++] = (unsigned char)(image[j].r*255/image[j].samples);
        tmp[i++] = (unsigned char)(image[j].g*255/image[j].samples);
        tmp[i++] = (unsigned char)(image[j].b*255/image[j].samples);
    }
    FILE* fout = fopen(filename,"wb");
    if(fout != NULL)
    {
        fprintf(fout,"P6 %d %d 255 ",width,height);
        fwrite(tmp, sizeof(unsigned char), width*height*3, fout);
        fclose(fout);
        return true;
    }
    else
        return false;
}

void ImageOutput::test()
{
    WELLrng rng((unsigned int*)this);
    for(int i=0;i<width*height;i++)
    {
        image[i].r = rng.getNumberf();
        image[i].g = rng.getNumberf();
        image[i].b = rng.getNumberf();
        image[i].samples = 1.0f;
    }
}
