/*
 * strcomp - str sompare 
 * a function for compare two array of characters 
 *
 * Returns : 
 * return 0 on same strings
 * return 1 on differents
 */
#include <string.h>
int 
f_strcomp (char * c1 , char * c2)
{
    while (*c1 != '\0' || *c2 != '\0')
    {
        if (*c1 != *c2)
            return 1;

        c1++; c2++;
    }
    return 0;
}







void 
f_str_copy (char * s1 , char * s2)
{
    while (*s1 != '\0')
    {
        *s2 = *s1 ;
        s1++;s2++;
    }
}







char * 
str_clearner (char * c) 
{
    int counter = 0 ;

    while (*c != '\0')
    {
        counter++; c++;
    }


    return c;
}







int 
f_strlen (char * c) 
{
    int counter = 0 ; 

    while (*c != '\0') 
    {
        c++; counter++;
    }

    return counter;
}










void clear_buffer (char * buffer , int buff_size) 
{
    for (int i = 0 ; i < buff_size ; i++)
        buffer[i] = '\0';
}








void trim (char * buffer , int buff_size)
{
    for (int i = buff_size ; i >= 0 ; i--)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
        }
    }
}











void command_spliter(char *input, char **argv)
{
    int argc = 0;
    int i = 0;
    int start = 0;

    while (input[i] != '\0') 
    {
        if (input[i] == ' ') 
        {
            input[i] = '\0';           
            if (i > start)            
                argv[argc++] = &input[start];
            start = i + 1;           
        }
        i++;
    }

    if (i > start)
        argv[argc++] = &input[start];

    argv[argc] = NULL;  
}

