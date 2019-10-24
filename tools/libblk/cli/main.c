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

    BLK* map;

    while (!quit)
    {
        printf(">>> ");
        // read input
        fgets(buffer, sizeof(buffer), stdin);
        // trim newline
        buffer[strlen(buffer) - 1] = '\0';

        if (startswith(buffer, "new"))
        {
            char word[20];
        }

        else if (startswith(buffer, "open"))
        {

        }
        else if (startswith(buffer, "save"))
        {
            
        }
        else if (startswith(buffer, "export"))
        {
            
        }
        else if (startswith(buffer, "reset"))
        {
            
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

    return 0;
}