/*  author: Davide Pizzolotto   */
/*  license: MIT                */

#include "jpg.h"

#define UNUSED(x) (void)(x)

static void jpg_error(j_common_ptr jpg_img)
{
    UNUSED(jpg_img);
    /* avoid terminating program if jpg error is encountered */
}

char jpg_write(const char* name, int width, int height, const uint8_t* data)
{
    char retval = 0;
    FILE* fout = fopen(name, "wb");
    if(fout != NULL)
    {
        struct jpeg_compress_struct jpg_img;
        struct jpeg_error_mgr jpg_err;
        JSAMPROW current_row;
        /*not the best thing, but the jpeg functions wants a modifiable array*/
        uint8_t* data_nc = (uint8_t*)malloc(sizeof(uint8_t)*width*height*3);
        memset(&jpg_img, 0, sizeof(jpg_img));
        memset(&jpg_err, 0, sizeof(jpg_img));
        memcpy(data_nc, data, width*height*3);
        jpg_img.err = jpeg_std_error(&jpg_err);
        jpg_err.error_exit = jpg_error;
        jpg_err.output_message = jpg_error;
        jpeg_create_compress(&jpg_img);
        jpeg_stdio_dest(&jpg_img, fout);
        jpg_img.image_width = width;
        jpg_img.image_height = height;
        jpg_img.input_components = 3;
        jpg_img.in_color_space = JCS_RGB;
        jpeg_set_defaults(&jpg_img);
        jpeg_set_quality(&jpg_img, 100, 1);
        jpeg_start_compress(&jpg_img, 1);
        while(jpg_img.next_scanline<jpg_img.image_height)
        {
            current_row = data_nc+jpg_img.next_scanline*3*width;
            jpeg_write_scanlines(&jpg_img, &current_row, 1);
        }
        jpeg_finish_compress(&jpg_img);
        fclose(fout);
        free(data_nc);
        jpeg_destroy_compress(&jpg_img);
        retval = 1;
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
        /* without error handling SIGSEGV will be generated */
        struct jpeg_error_mgr jpg_err;
        memset(&jpg_img, 0, sizeof(jpg_img));
        memset(&jpg_err, 0, sizeof(jpg_img));
        jpg_img.err = jpeg_std_error(&jpg_err);
        jpg_err.error_exit = jpg_error;
        jpg_err.output_message = jpg_error;
        jpeg_create_decompress(&jpg_img);
        jpeg_stdio_src(&jpg_img, fin);
        /* check if the header is correct. The actual error handling does
         * nothing, as the detection is performed by the read_header retval and
         * distinguishing between errors is not required
         */
        retval = jpeg_read_header(&jpg_img, TRUE) == JPEG_HEADER_OK;
        jpeg_destroy_decompress(&jpg_img);
        fclose(fin);
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
        /* without error handling SIGSEGV will be generated */
        struct jpeg_error_mgr jpg_err;
        memset(&jpg_img, 0, sizeof(jpg_img));
        memset(&jpg_err, 0, sizeof(jpg_img));
        jpg_img.err = jpeg_std_error(&jpg_err);
        jpg_err.error_exit = jpg_error;
        jpg_err.output_message = jpg_error;
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


char jpg_read(const char* name, uint8_t* values)
{
    char retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        int row_len;
        JSAMPROW current_row;
        struct jpeg_decompress_struct jpg_img;
        /* without error handling SIGSEGV will be generated */
        struct jpeg_error_mgr jpg_err;
        memset(&jpg_img, 0, sizeof(jpg_img));
        memset(&jpg_err, 0, sizeof(jpg_img));
        jpg_img.err = jpeg_std_error(&jpg_err);
        jpg_err.error_exit = jpg_error;
        jpg_err.output_message = jpg_error;
        jpeg_create_decompress(&jpg_img);
        jpeg_stdio_src(&jpg_img, fin);
        if(jpeg_read_header(&jpg_img, TRUE) == JPEG_HEADER_OK)
        {
            jpeg_start_decompress(&jpg_img);
            row_len = jpg_img.output_width*jpg_img.output_components;
            retval = 1;
            while(jpg_img.output_scanline<jpg_img.output_height)
            {
                current_row = values+jpg_img.output_scanline*row_len;
                retval &= jpeg_read_scanlines(&jpg_img, &current_row, 1)>0;
            }
        }
        jpeg_finish_decompress(&jpg_img);
        jpeg_destroy_decompress(&jpg_img);
        fclose(fin);
    }
    return retval;
}
