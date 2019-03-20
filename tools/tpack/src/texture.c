#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int texture_read_png(Texture* tex, const char* fn)
{
    FILE* fp = fopen(fn, "rb");
    if (!fp)
    {
        return 1;
    }

    // validate header
    uint8_t header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8) != 0)
    {
        return 1;
    }

    tex->png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    tex->info_ptr = png_create_info_struct(tex->png_ptr);

    png_init_io(tex->png_ptr, fp);
    png_set_sig_bytes(tex->png_ptr, 8);
    png_read_png(tex->png_ptr, tex->info_ptr, PNG_TRANSFORM_IDENTITY, NULL);

    tex->w = png_get_image_width(tex->png_ptr, tex->info_ptr);
    tex->h = png_get_image_height(tex->png_ptr, tex->info_ptr);
    tex->bpc = png_get_bit_depth(tex->png_ptr, tex->info_ptr);
    tex->nc = png_get_channels(tex->png_ptr, tex->info_ptr);

    fclose(fp);
    return 0;
}

int texture_open_png(Texture* tex, const char* fn)
{
    strcpy(tex->file.fn, fn);
    tex->file.fp = fopen(fn, "wb");
    if (tex->file.fp == NULL)
    {
        return 1;
    }
    tex->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (tex->png_ptr == NULL)
    {
        return 1;
    }

    tex->info_ptr = png_create_info_struct(tex->png_ptr);
    if (tex->info_ptr == NULL)
    {
        return 1;
    }

    if (setjmp(png_jmpbuf(tex->png_ptr)))
    {
        printf("error during png creation\n");
        return 1;
    }

    png_init_io(tex->png_ptr, tex->file.fp);

    png_set_IHDR(tex->png_ptr, tex->info_ptr, 8192, 8192, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(tex->png_ptr, tex->info_ptr);

    return 0;
}

int texture_close_png(Texture* tex)
{
    fclose(tex->file.fp);
    tex->file.fp = NULL;
    tex->file.fn[0] = '\0';

    return 0;
}

int texture_write_png(Texture* dest, Texture* src)
{
    png_bytep* dest_rows = png_get_rows(dest->png_ptr, dest->info_ptr);
    png_bytep* src_rows = png_get_rows(src->png_ptr, src->info_ptr)
    int i, j;
    for (i=0; i<src->h; ++i)
    {
        for (j=0; j<src->w; ++j)
        {

        }
    }
    return 0;
}

uint32_t texture_get_area(Texture* tex)
{
    return tex->w * tex->h;
}

Box texture_getbox(Texture* tex)
{
    Box b;
    b.x = tex->x;
    b.y = tex->y;
    b.w = tex->w;
    b.h = tex->h;
}