#include <unistd.h>
#include <pwd.h>


#define USERNAME_BUFF_SIZE 64


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
}

