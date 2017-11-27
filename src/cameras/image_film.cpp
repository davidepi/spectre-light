#include "image_film.hpp"

//check if extension is supported
int check_extension(const char* fn)
{
    const char* name = strrchr(fn,'.');
    int retval;
    if(name == NULL || (name-fn)<(int)strlen(fn)-4) //null or position less than
    {                                          //4 chr expected for an extension
        Console.warning(MESSAGE_MISSING_EXTENSION);
        retval = EXTENSION_NOT_SUPPORTED;
    }
    else
    {
        switch(name[1])
        {
            case 'p':
            {
                if(strcmp(".ppm",name))
                    retval = EXTENSION_PPM;
                else
                    retval = EXTENSION_NOT_SUPPORTED;
                break;
            }
            case 'b':
            {
                if(strcmp(".bmp",name))
                    retval = EXTENSION_BMP;
                else
                    retval = EXTENSION_NOT_SUPPORTED;
                break;
            }
            default:
                retval = EXTENSION_NOT_SUPPORTED;
        }
    }
    return retval;
}

ImageFilm::ImageFilm(int w, int h, const char* fn) :width(w), height(h)
{
    //allocate image
    ImageFilm::image = (Pixel*)malloc(sizeof(Pixel)*w*h);
    //set as zero, I need to have number of samples = 0 for every pixel
    memset(ImageFilm::image, 0, sizeof(Pixel)*w*h);
    ImageFilm::f = NULL;
    ImageFilm::filename = NULL;

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
    }

    if(fn != NULL)
    {
        //check extension, add .ppm if not supported
        int res = check_extension(fn);
        int len = (int)strlen(fn)+1;
        len += res?0:4; //to add the .ppm at the end, if there was no extension
        ImageFilm::filename = (char*)malloc(sizeof(char)*len);
        memcpy(ImageFilm::filename,fn,sizeof(char)*len);
        if(res==EXTENSION_NOT_SUPPORTED)
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
        ImageFilm::filename = (char*)malloc(sizeof(char)*8);
        filename[0] = 'o'; //what about memcpy?
        filename[1] = 'u';
        filename[2] = 't';
        filename[3] = '.';
        filename[4] = 'p';
        filename[5] = 'p';
        filename[6] = 'm';
        filename[7] = '\0';
    }

    free(folder);
}

ImageFilm::~ImageFilm()
{
    if(ImageFilm::image!=NULL)
        free(ImageFilm::image);
}

void ImageFilm::addPixel(const Sample* s, ColorXYZ c, ExecutorData* ex)
{
    if(c.r<0)c.r=0;
    if(c.g<0)c.g=0;
    if(c.b<0)c.b=0;
    float ptmpx = s->posx-0.5f;
    float ptmpy = s->posy-0.5f;
    int p0x = (int)ceilf(ptmpx-f->x_range);
    int p0y = (int)ceilf(ptmpy-f->y_range);
    int p1x = (int)floorf(ptmpx+f->x_range);
    int p1y = (int)floorf(ptmpy+f->y_range);
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

void ImageFilm::deferredAddPixel(ExecutorData* ex)
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

void ImageFilm::forceAddPixel(ExecutorData* ex)
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

void ImageFilm::setFilter(Filter* f)
{
    ImageFilm::f = f;
}

bool ImageFilm::saveImage()
{
    uint8_t* tmp = (uint8_t*)malloc(ImageFilm::width*ImageFilm::height*3U);
    unsigned int i = 0;
    ColorRGB rgb;
    //use scale stored colour and output as .ppm
    for(int j=0;j<ImageFilm::width*ImageFilm::height;j++)
    {
        if(image[j].samples>0.f) //if at least one sample
        {
            float weight = 1.f/image[j].samples;
            rgb = ColorXYZ(image[j].cie_x*weight,
                           image[j].cie_y*weight,
                           image[j].cie_z*weight).toStandardRGB();
        }
        tmp[i++] = (uint8_t)::min((::max(0.f,rgb.r)*0xFF),255.0f);
        tmp[i++] = (uint8_t)::min((::max(0.f,rgb.g)*0xFF),255.0f);
        tmp[i++] = (uint8_t)::min((::max(0.f,rgb.b)*0xFF),255.0f);
    }
    free(ImageFilm::image);
    bool retval = savePPM(filename, width, height, tmp);
    free(tmp);
    ImageFilm::image = NULL;
    return retval;
}
