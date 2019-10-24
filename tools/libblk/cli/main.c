#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "blk.h"

int startswith(char* a, const char* b)
{
    if (strlen(a) < strlen(b))
    {
        return 0;
    }
    while (*a != '\0' && *b != '\0')
    {
        if (*a != *b)
        {
            return 0;
        }

        a++;
        b++;
    }

    return 1;
}

void getword(char* a, const char* b, int n, int len)
{
    int cur = 0;
    int ch = 0;
    while (*b != '\0')
    {
        if (cur == n)
        {
            if (ch == len - 1)
            {
                break;
            }
            *a = *b;
            a++;
            ch++;
        }

        if (cur > n)
        {
            break;
        }

        if (*b == ' ' && *(b + 1) != ' ')
        {
            cur += 1;
        }

        b++;
    }

    *a = '\0';
}

int main(int argc, char** argv)
{
    printf("libblk cli version 1.0\n\n");

    int quit = 0;
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    BLK* map = NULL;

    while (!quit)
    {
        printf(">>> ");
        // read input
        fgets(buffer, sizeof(buffer), stdin);
        // trim newline
        buffer[strlen(buffer) - 1] = '\0';

        if (startswith(buffer, "new"))
        {
            int w = 0;
            int h = 0;
            char word[20];
            getword(word, buffer, 1, sizeof(word));
            w = atoi(word);
            getword(word, buffer, 1, sizeof(word));
            h = atoi(word);

            if (w <= 0 || h <= 0)
            {
                printf("bad args\n");
                continue;
            }

            map = blk_new(w, h);
        }

        else if (startswith(buffer, "open"))
        {
            char word[20];
            getword(word, buffer, 1, sizeof(word));
            map = blk_open(word);
        }
        else if (startswith(buffer, "save"))
        {
            if (map == NULL)
            {
                continue;
            }
            char word[20];
            getword(word, buffer, 1, sizeof(word));
            blk_save(map, word);
        }
        else if (startswith(buffer, "export"))
        {
            char word[20];
            getword(word, buffer, 1, sizeof(word));
            blk_save(map, word);
        }
        else if (startswith(buffer, "summary"))
        {
            if (map == NULL)
            {
                printf("nothing in memory\n");
                continue;
            }
            printf("w: %d, h: %d, entries: %d\n", map->dimension.x, map->dimension.y, map->entries);
        }
        else if (startswith(buffer, "reset"))
        {
            if (map != NULL)
            {
                int err = blk_free(map);
                map = NULL;
                if (err)
                {
                    printf("deallocate error\n");
                }
            }
            else
            {
                printf("map has not been allocated\n");
            }
        }
        else if (startswith(buffer, "exit"))
        {
            quit = 1;
        }
        else if (strlen(buffer) > 0)
        {
            printf("unknown command\n");
        }
    }

    if (map != NULL)
    {
        blk_free(map);
    }

    return 0;
}