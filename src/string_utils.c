#ifndef STRING_UTILS
#define STRING_UTILS 


/*
 * strcomp - str compare 
 * a function for compare two array of characters 
 *
 * Returns : 
 * return 0 on same strings
 * return 1 on differents
 */
#include <stdatomic.h>
int 
u_strcomp (char * c1 , char * c2)
{
    while (*c1 != '\0' && *c2 != '\0')
    {
        if (*c1 != *c2)
            return 1;

        c1++; c2++;
    }

    if (*c1 == '\0' && *c2 == '\0')
        return 0;
    return 0;
}






/*
 * strlen - str lenght
 * a function for calculate lenght of a string
 *
 * Returns : 
 * return n (lenght)
 */
int 
u_strlen (char * s) 
{
    int counter = 0;
    while (*s != '\0')
    {
        counter++;
        s++;
    }

    return counter;
}






/*
 * add_to_end - add a char array to other char array
 * a function for merge two char arary
 */
void 
u_add_t_end (char * s1 , char * s2)
{
    while (*s1 != '\0') 
        ++s1;

    while (*s2 != '\0')
    {
        *s1 = *s2;
        s1++;s2++;
    }
    *s1 = '\0';
}








/*
 * strcopy - copy strings 
 * copies each character from src to dest
 */
void 
u_strcpy (char * src , char * dest)
{
    while (*src != '\0' && *dest != '\0')
    {
        *dest = *src ;
        src++;dest++;
    }
    *dest = '\0';
}







/*
 * clear_buffer - fill a buffer with null terminator
 */
void
u_clear_buffer (char * buffer , int buff_size) 
{
    for (int i = 0 ; i < buff_size ; i++)
        buffer[i] = '\0';
}







/*
 * trim 
 * trim the buffer 
 */
void 
u_trim (char * buffer , int buff_size)
{
    for (int i = buff_size ; i >= 0 ; i--)
    {
        if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
        }
    }
}




#endif /* STRING_UTILS */
