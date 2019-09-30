#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "maze.h"

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

        if (*b == ' ' && *(b+1) != ' ')
        {
            cur += 1;
        }

        b++;
    }

    *a = '\0';
}

int main(int argc, char** argv)
{
    printf("libmap cli version 1.0\n\n");
    
    int quit = 0;
    char buffer[256];
    memset(buffer, 0, sizeof(buffer));

    LM_Maze* m = NULL;
    LM_Grid* g = NULL;

    while (!quit)
    {
        printf(">>> ");
        // read input
        fgets(buffer, sizeof(buffer), stdin);
        // trim newline
        buffer[strlen(buffer)-1] = '\0';

        if (startswith(buffer, "new"))
        {
            int w = -1;
            int h = -1;

            char word[20];
            getword(word, buffer, 1, sizeof(word));
            w = atoi(word);
            getword(word, buffer, 2, sizeof(word));
            h = atoi(word);

            if (w == 0 || h == 0)
            {
                printf("bad args\n");
                continue;
            }
            if (m != NULL)
            {
                printf("maze already exists\n");
                continue;
            }
            
            printf("generating maze of size %d,%d\n", w, h);
            m = maze_generate(w, h);
        }

        else if (startswith(buffer, "format"))
        {
            if (m == NULL)
            {
                printf("need to open/generate maze first\n");
                continue;
            }

            int scale = 1;

            char word[20];
            getword(word, buffer, 1, sizeof(word));
            if (strlen(word) > 0)
            {
                scale = atoi(word);
                if (scale < 1)
                {
                    scale = 1;
                }
            }

            g = maze_format(m, scale);
        }

        else if (startswith(buffer, "open"))
        {

        }
        else if (startswith(buffer, "save"))
        {
            if (m == NULL)
            {
                printf("need to create a maze first\n");
                continue;
            }
            char word[20];
            getword(word, buffer, 1, sizeof(word));
            if (strlen(word) < 1)
            {
                printf("bad arg\n");
                continue;
            }
            maze_save(m, word);
        }
        else if (startswith(buffer, "export"))
        {
            if (g == NULL)
            {
                printf("need to create grid first\n");
                continue;
            }
            
            int i;
            int j;
            for (i = 0; i < g->dimension.y; ++i)
            {
                for (j = 0; j < g->dimension.x; ++j)
                {
                    printf("%d ", grid_get(g, j, i));
                }
                printf("\n");
            }
        }
        else if (startswith(buffer, "reset"))
        {
            if (m != NULL)
            {
                printf("delete maze\n");
                maze_free(m);
                m = NULL;
            }

            if (g != NULL)
            {
                printf("delete grid\n");
                grid_free(g);
                g = NULL;
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

    if (m != NULL)
    {
        maze_free(m);
    }

    if (g != NULL)
    {
        grid_free(g);
    }
    return 0;
}