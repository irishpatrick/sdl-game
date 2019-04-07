#include "util.h"
#include <string.h>

char* file_ext(char* str)
{
    int len = strlen(str);
    int i;
    for (i=len-1; i>=0; i--)
    {
        if (str[i] == '.')
        {
            break;
        }
    }
    return str + i + 1;
}