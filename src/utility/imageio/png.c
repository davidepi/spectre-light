#include "png.h"

char png_write(const char* name, int width, int height, const uint8_t* data)
{
    char retval = 0;
    const int COMPONENTS = 3;
    FILE* fout = fopen(name, "wb");
    if(fout != NULL)
    {
        int y;
        png_structp png_img;
        png_infop png_info;
        /* avoid discarding const from data */
        png_bytep* rows = (png_bytep*)malloc(sizeof(png_bytep)*height);
        for(y = 0; y<height; y++)
        {
            rows[y] = (png_bytep)malloc(sizeof(png_bytep)*width*COMPONENTS);
            memcpy(rows[y], data+y*width*COMPONENTS, width*COMPONENTS);
        }
        png_img = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,
                                          NULL);
        png_info = png_create_info_struct(png_img);
        png_init_io(png_img, fout);
        png_set_IHDR(png_img, png_info, width, height,
                     8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
        png_write_info(png_img, png_info);
        png_write_image(png_img, rows);
        png_write_end(png_img, NULL);
        for(y = 0; y<height; y++)
            free(rows[y]);
        free(rows);
        png_destroy_write_struct(&png_img, &png_info);
        fclose(fout);
        retval = 1;
    }
    return retval;
}

char png_valid(const char* name)
{
    char retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        uint8_t header[8];
        fread(header, 1, 8, fin);
        retval = png_sig_cmp(header, 0, 8) == 0;
        fclose(fin);
    }
    return retval;
}

char png_dimensions(const char* name, int* width, int* height)
{
    char retval = 0;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        uint8_t header[8];
        png_structp png_img;
        png_infop png_info;
        fread(header, 1, 8, fin);
        if(png_sig_cmp(header, 0, 8) == 0)
        {
            png_img = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,
                                             NULL);
            png_info = png_create_info_struct(png_img);
            png_init_io(png_img, fin);
            png_set_sig_bytes(png_img, 8);
            png_read_info(png_img, png_info);
            *width = png_get_image_width(png_img, png_info);
            *height = png_get_image_height(png_img, png_info);
            png_destroy_read_struct(&png_img, &png_info, NULL);
            retval = 1;
        }
        fclose(fin);
    }
    return retval;
}

char png_read(const char* name, uint8_t* values, uint8_t* alpha)
{
    char retval = 0;
    const char has_alpha = alpha != NULL;
    FILE* fin = fopen(name, "rb");
    if(fin != NULL)
    {
        int y;
        int x;
        uint8_t header[8];
        png_byte** rows;
        png_structp png_img;
        png_infop png_info;
        int width;
        int height;
        int color_type;
        int bpp;
        fread(header, 1, 8, fin);
        if(png_sig_cmp(header, 0, 8) == 0)
        {
            png_img = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,
                                             NULL);
            png_info = png_create_info_struct(png_img);
            png_init_io(png_img, fin);
            png_set_sig_bytes(png_img, 8);
            png_read_info(png_img, png_info);

            width = png_get_image_width(png_img, png_info);
            height = png_get_image_height(png_img, png_info);
            color_type = png_get_color_type(png_img, png_info);
            bpp = png_get_bit_depth(png_img, png_info);
            /* -------- Convert every possible PNG to RGBA format ----------- */
            if(bpp == 16)
                png_set_strip_16(png_img);
            if(color_type == PNG_COLOR_TYPE_PALETTE)
                png_set_palette_to_rgb(png_img);
            if(color_type == PNG_COLOR_TYPE_GRAY && bpp<8)
                png_set_expand_gray_1_2_4_to_8(png_img);
            if(png_get_valid(png_img, png_info, PNG_INFO_tRNS))
                png_set_tRNS_to_alpha(png_img);
            /* write 0xFF as alpha */
            if(color_type == PNG_COLOR_TYPE_RGB ||
               color_type == PNG_COLOR_TYPE_GRAY ||
               color_type == PNG_COLOR_TYPE_PALETTE)
                png_set_filler(png_img, 0xFF, PNG_FILLER_AFTER);
            if(color_type == PNG_COLOR_TYPE_GRAY ||
               color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
                png_set_gray_to_rgb(png_img);
            /* -------------------------------------------------------------- */
            png_read_update_info(png_img, png_info);
            rows = (png_byte**)malloc(sizeof(png_byte*)*height);
            for(y = 0; y<height; y++)
                rows[y] = (png_byte*)malloc(sizeof(png_byte)*width*4);
            png_read_image(png_img, rows);
            for(y = 0; y<height; y++)
            {
                for(x = 0; x<width; x++)
                {
                    int index_alpha = y*width+x;
                    int index_rgb = index_alpha*3;
                    values[index_rgb+0] = rows[y][x*4+0];
                    values[index_rgb+1] = rows[y][x*4+1];
                    values[index_rgb+2] = rows[y][x*4+2];
                    if(has_alpha)
                        alpha[index_alpha] = rows[y][x*4+3];
                }
                free(rows[y]);
            }
            free(rows);
            png_destroy_read_struct(&png_img, &png_info, NULL);
            retval = 1;
            if(color_type == PNG_COLOR_TYPE_GRAY_ALPHA ||
               color_type == PNG_COLOR_TYPE_RGB_ALPHA)
                retval++;
        }
        fclose(fin);
    }
    return retval;
}
