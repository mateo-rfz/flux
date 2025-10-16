#include <unistd.h>
#include <pwd.h>


#define USERNAME_BUFF_SIZE 64




/*
 * getUsername - get the username of the current user
 * copies the username of current user (base on uid) into the buffer
 *
 * INPUTS : 
 *      pointer of a array of char buffer
 *
 * RETURNS :    
 *      NONE
 */
void getUsername (char * buffer)
{
    uid_t uid = getuid();
    struct passwd * pw = getpwuid(uid);
    char * username = pw->pw_name;


    while (*username != '\0')
    {
        *buffer = *username;

        buffer++;username++;
    }
    *buffer = '\0';
}

