#include "jpg.h"

#define UNUSED(x) (void)(x)

char jpg_save(const char* name, int width, int height, const uint8_t* data)
{
    char retval = 0;
    FILE* fout = fopen(name, "wb");
    if(fout != NULL)
    {
        /*not the best thing, but the jpeg functions wants a modifiable*/
        uint8_t* data_nc = (uint8_t*)malloc(sizeof(uint8_t)*width*height*3);
        struct jpeg_compress_struct jpg_img;
        struct jpeg_error_mgr jpg_err;
        JSAMPROW current_row;
        memcpy(data_nc, data, width*height*3);
        jpg_img.err = jpeg_std_error(&jpg_err);
        jpeg_create_compress(&jpg_img);
        jpg_img.image_width = width;
        jpg_img.image_height = height;
        jpg_img.input_components = 3;
        jpg_img.in_color_space = JCS_RGB;
        jpeg_set_defaults(&jpg_img);
        jpeg_set_quality(&jpg_img, 100, 1);
        jpeg_start_compress(&jpg_img, 1);
        jpeg_stdio_dest(&jpg_img, fout);
        while(jpg_img.next_scanline<jpg_img.image_height)
        {
            current_row = data_nc+jpg_img.next_scanline*3*width;
            jpeg_write_scanlines(&jpg_img, &current_row, 1);
        }
        jpeg_finish_compress(&jpg_img);
        fclose(fout);
        jpeg_destroy_compress(&jpg_img);
        retval = 1;
    }
    return retval;
}

char jpg_dimensions(const char* name, int* width, int* height)
{
    char retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        struct jpeg_decompress_struct jpg_img;
        jpeg_create_decompress(&jpg_img);
        jpeg_stdio_src(&jpg_img, fin);
        if(jpeg_read_header(&jpg_img, TRUE) == JPEG_HEADER_OK)
        {
            /* actual data written in the header. To get the real value I should
             * call the jpeg_decompress and read output_width and output_height.
             * However I don't give a shit if someboy tries to cheat with the
             * header values, their fault, not mine.
             */
            *width = jpg_img.image_width;
            *height = jpg_img.image_height;
            retval = 1;
        }
        jpeg_destroy_decompress(&jpg_img);
        fclose(fin);
    }
    return retval;
}

char jpg_valid(const char* name)
{
    char retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        struct jpeg_decompress_struct jpg_img;
        jpeg_create_decompress(&jpg_img);
        jpeg_stdio_src(&jpg_img, fin);
        retval = jpeg_read_header(&jpg_img, TRUE) == JPEG_HEADER_OK;
        jpeg_destroy_decompress(&jpg_img);
        fclose(fin);
    }
    return retval;
}


char jpg_read(const char* name, uint8_t* values, uint8_t* alpha)
{
    char retval = 0;
    FILE* fin = fopen(name, "rb");
    UNUSED(alpha);
    if(fin != NULL)
    {
        struct jpeg_decompress_struct jpg_img;
        int row_len;
        JSAMPROW current_row;
        jpeg_create_decompress(&jpg_img);
        jpeg_stdio_src(&jpg_img, fin);
        jpeg_read_header(&jpg_img, TRUE);
        jpeg_start_decompress(&jpg_img);
        row_len = jpg_img.output_width*jpg_img.output_components;
        retval = 1;
        while(jpg_img.output_scanline<jpg_img.output_height)
        {
            current_row = values+jpg_img.output_scanline*row_len;
            retval &= jpeg_read_scanlines(&jpg_img, &current_row, 1)>0;
        }
        jpeg_finish_decompress(&jpg_img);
        jpeg_destroy_decompress(&jpg_img);
        fclose(fin);
    }
    return retval;
}
