#pragma once

#include <stdint.h>
#define PNG_DEBUG 3
#include <png.h>
#include "boundingbox.h"

typedef struct _TextureIterator
{
    png_bytep* row_pointers;
} TextureIterator;

typedef struct _TextureFile
{
    FILE* fp;
    char fn[256];
} TextureFile;

typedef struct _Texture
{
    png_structp png_ptr;
    png_infop info_ptr;
    uint32_t x;
    uint32_t y;
    uint32_t w;
    uint32_t h;
    uint32_t bpc;
    uint32_t nc;
    TextureFile file;
    TextureIterator iterator;

} Texture;

uint32_t texture_get_area(Texture*);
int texture_read_png(Texture*, const char*);
int texture_open_png(Texture*, const char*);
int texture_close_png(Texture*);
Box texture_getbox(Texture*);
int texture_write_png(Texture*, Texture*);