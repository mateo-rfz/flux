#include <stdio.h>
#include <string.h>
#include <ctype.h>



void command_spliter(char *input, char **argv)
{
    int argc = 0;
    int in_quotes = 0;
    char *p = input;
    char *start = NULL;

    while (*p)
    {
        if (isspace(*p) && !in_quotes)
        {
            if (start)
            {
                *p = '\0';
                argv[argc++] = start;
                start = NULL;
            }
        }
        else if (*p == '"')
        {
            in_quotes = !in_quotes;
            memmove(p, p + 1, strlen(p));
            p--; 
        }
        else
        {
            if (!start)
                start = p;
        }
        p++;
    }

    if (start)
        argv[argc++] = start;

    argv[argc] = NULL;
}

