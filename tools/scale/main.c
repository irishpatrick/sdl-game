#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <stdint.h>

#define PNG_DEBUG 3
#include <png.h>

struct Image
{
    int width;
    int height;
    png_structp png_p;
    png_infop info_p;
    png_bytep* rows;
};

struct Pixel
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Point
{
    int x;
    int y;
};

void err(const char* s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}

void set_pixel(struct Image* img, struct Point pt, struct Pixel pix)
{
    int bytes = -1;
    if (png_get_color_type(img->png_p, img->info_p) == PNG_COLOR_TYPE_RGB)
    {
        bytes = 3;
    }
    else if (png_get_color_type(img->png_p, img->info_p) == PNG_COLOR_TYPE_RGBA)
    {
        bytes = 4;
    }
    else
    {
        err("bad format");
    }

    png_byte* row = img->rows[pt.y];
    png_byte* ptr = &(row[pt.x*bytes]);
    
    ptr[0] = pix.r;
    ptr[1] = pix.g;
    ptr[2] = pix.b;
    if (bytes > 3)
    {
        ptr[3] = pix.a;
    }
}

void make_img(struct Image* img, int w, int h)
{
    img->width = w;
    img->height = h;
    img->png_p = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (img->png_p == NULL)
    {
        err("cannot create image\n");
    }

    img->info_p = png_create_info_struct(img->png_p);
    if (img->info_p == NULL)
    {
        err("couldn't allocate info\n");
    }

    if (setjmp(png_jmpbuf(img->png_p)))
    {
        err("png creation error\n");
    }

    img->rows = (png_bytep*)malloc(sizeof(png_bytep) * img->height);
    int i;
    for (i = 0; i < img->height; ++i)
    {
        img->rows[i] = (png_byte*)malloc(png_get_rowbytes(img->png_p, img->info_p));
    }
}

void read_img(struct Image* img, const char* fn)
{
    char header[8];

    FILE* fp = fopen(fn, "rb");
    if (!fp)
    {
        err("cannot open file: %s\n", fn);
    }

    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8))
    {
        err("bad png format\n");
    }

    img->png_p = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!img->png_p)
    {
        err("png error\n");
    }

    img->info_p = png_create_info_struct(img->png_p);
    if (!img->info_p)
    {
        err("info pointer error");
    }

    if (setjmp(png_jmpbuf(img->png_p)))
    {
        err("setjmp error\n");
    }

    png_init_io(img->png_p, fp);
    png_set_sig_bytes(img->png_p, 8);

    png_read_info(img->png_p, img->info_p);

    img->width = png_get_image_width(img->png_p, img->info_p);
    img->height = png_get_image_height(img->png_p, img->info_p);
    
    /* read file */
    if (setjmp(png_jmpbuf(img->png_p)))
    {
        err("read image error\n");
    }

    img->rows = (png_bytep*)malloc(sizeof(png_bytep) * img->height);
    int i;
    for (i = 0; i < img->height; ++i)
    {
        img->rows[i] = (png_byte*)malloc(png_get_rowbytes(img->png_p, img->info_p));
    }

    png_read_image(img->png_p, img->rows);

    fclose(fp);
}

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("usage: scale <png file> <scale>\n");
        return 0;
    }

    int scale = atoi(argv[2]);
    struct Image orig;
    struct Image scaled;

    read_img(&orig, argv[1]);
    make_img(&scaled, orig.width * scale, orig.height * scale);

    return 0;
}
