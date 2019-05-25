#include "blueprint.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "boundingbox.h"

void swap(Texture* a, Texture* b)
{
    Texture* tmp = a;
    a = b;
    b = tmp;
}

void insertion_sort(Texture** tlist, size_t len)
{
    int i, j;
    Texture* k;
    for (i=1; i<len; ++i)
    {
        k = tlist[i];
        j = i-1;
        while ((j >= 0) && (texture_get_area(k) < texture_get_area(tlist[j])))
        {
            tlist[j+1] = tlist[j];
            j--;
        }
        tlist[j+1] = k;
    }
}

int blueprint_generate(Texture** tlist, size_t len)
{
    // sort textures
    insertion_sort(tlist, len);

    Box last;
    last.x = 0;
    last.y = 0;

    tlist[0]->x = last.x;
    tlist[0]->y = last.y;
    last.w = tlist[0]->w;
    last.h = tlist[0]->h;

    int i;
    for (i=1; i<len; ++i)
    {
        Texture* t = tlist[i];
        last.x += last.w;
        if (last.x > 8192 - t->w)
        {
            last.x = 0;
            last.y += last.h;
        }
        last.w = t->w;
        last.h = t->h;
        t->x = last.x;
        t->y = last.y;
           
    }

    return 0;
}