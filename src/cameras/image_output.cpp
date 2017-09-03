#include "image_output.hpp"

//check if extension is supported
bool check_extension(const char* fn)
{
    const char* name = strrchr(fn,'.');
    if(name == NULL || (name-fn)<(int)strlen(fn)-4) //null or position less than the
    {                                          //4 chr expected for an extension
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

    //check if folder is writable
    const char* file = strrchr(fn,PATH_SEPARATOR);
    char* folder;
    if(file!=NULL) //the path references another folder
    {
        int last_separator=(int)(file-fn)+1;
        folder = (char*) malloc(sizeof(char)*(last_separator+1));
        memcpy(folder, fn, sizeof(char)*last_separator);
        folder[last_separator] = '\0';
    }
    else //current folder
    {
        folder= (char*)malloc(sizeof(char)*2);
        folder[0] = '.';
        folder[2] = '\n';
    }

#ifdef WIN32
    if(_access(folder,2)!=-1)
#else
    if(access(folder,W_OK)!=0)
#endif
    {
        char* err=(char*)malloc(sizeof(char)*(strlen(MESSAGE_W_DENIED)
                                              +strlen(folder)+1));
        sprintf(err,MESSAGE_W_DENIED,folder);
        Console.critical(err);
        free(err);
    }

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

    //check if writable
    free(folder);
}

ImageOutput::~ImageOutput()
{
    free(ImageOutput::image);
}

void ImageOutput::addPixel(const Sample* s, const ColorXYZ c, ExecutorData* ex)
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
			if(x < ex->startx || x > ex->endx || y < ex->starty || y > ex->endy)
			{
				//critical section, deferred processing
				TodoPixel tp;
				tp.x = x;
				tp.y = y;
				tp.cie_x = c.r*weight;
				tp.cie_y = c.g*weight;
				tp.cie_z = c.b*weight;
				tp.samples = weight;
				ex->deferred.push(tp);
			}
			else
			{
            	Pixel* val = image+(width*y+x);
            	val->cie_x += c.r*weight;
            	val->cie_y += c.g*weight;
            	val->cie_z += c.b*weight;
            	val->samples += weight;
			}
        }
}

void ImageOutput::deferredAddPixel(ExecutorData* ex)
{
	if(mtx.try_lock())
	{
		Pixel* val;
		TodoPixel tp;
		while(!ex->deferred.empty())
		{
			tp = ex->deferred.top();
			ex->deferred.pop();
			val = image+(width*tp.y+tp.x);
			val->cie_x += tp.cie_x;
			val->cie_y += tp.cie_y;
			val->cie_z += tp.cie_z;
			val->samples += tp.samples;
		}
		mtx.unlock();
	}
}

void ImageOutput::forceAddPixel(ExecutorData* ex)
{
	Pixel* val;
	TodoPixel tp;
	mtx.lock();
	while(!ex->deferred.empty())
	{
		tp = ex->deferred.top();
		ex->deferred.pop();
		val = image+(width*tp.y+tp.x);
		val->cie_x += tp.cie_x;
		val->cie_y += tp.cie_y;
		val->cie_z += tp.cie_z;
		val->samples += tp.samples;
	}
	mtx.unlock();
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
            ColorRGB col = ColorXYZ(image[j].cie_x*weight,
                                    image[j].cie_y*weight,
                                    image[j].cie_z*weight).toStandardRGB();
            tmp[i++] = (uint8_t)(::clamp(col.r,0.f,1.f)*0xFF);
            tmp[i++] = (uint8_t)(::clamp(col.g,0.f,1.f)*0xFF);
            tmp[i++] = (uint8_t)(::clamp(col.b,0.f,1.f)*0xFF);
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
        Console.critical(MESSAGE_W_DENIED_RC);
        free(tmp);
        return false;
    }
}
