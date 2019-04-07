#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <dirent.h>
#define PNG_DEBUG 3
#include <png.h>

#include "util.h"
#include "texture.h"

#define MAX_FILES 1000
#define MAX_LENGTH 255

int main(int argc, char** argv)
{
    if (argc < 3)
    {
        printf("usage: ./tpack <directory> <output>\n");
        return 1;
    }

    char** files = (char**)malloc(MAX_FILES * sizeof(char*));
    int i;
    for (i=0; i<MAX_FILES; i++)
    {
        files[i] = (char*)malloc(MAX_LENGTH * 2 * sizeof(char));
    }
    int num_files;

    DIR* dir;
    struct dirent* ent;
    if ((dir = opendir(argv[1])) != NULL)
    {
        i = 0;
        while ((ent = readdir(dir)) != NULL && i < MAX_FILES)
        {
            if (ent->d_type == DT_REG && !strcmp(file_ext(ent->d_name), "png"))
            {
                strcat(files[i], argv[1]);
                if (argv[1][strlen(argv[1]) - 1] != '/')
                {
                    strcat(files[i], "/");
                }
                strcat(files[i], ent->d_name);
                i++;
            }
        }
        num_files = i;
        closedir(dir);
    }
    else
    {
        printf("couldn't open directory\n");
        return 1;
    }

    char out_fn[256];
    strcat(out_fn, argv[2]);
    strcat(out_fn, ".png");

    Texture* inputs = (Texture*)malloc(num_files * sizeof(Texture));

    uint32_t area;
    for (i=0; i<num_files; i++)
    {
        printf("loading %s ", files[i]);
        texture_read_png(&inputs[i], files[i]);
        area += texture_get_area(&inputs[i]);
        printf("(%.1f%%)\n", ((double)(area) / (double)(8192 * 8192)) * 100.0);

    }

    if (area > 8192 * 8192)
    {
        printf("warning: trying to fit area %u into area %u", area, 8192 * 8192);
    }
    
    Texture out;
    texture_open_png(&out, out_fn);
    texture_close_png(&out);

    for (i=0; i<MAX_FILES; i++)
    {
        free(files[i]);
    }
    free(files);

    free(inputs);

    return 0;
}