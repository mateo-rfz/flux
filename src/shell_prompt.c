#ifndef SHELL_PROMPT
#define SHELL_PROMPT

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <sys/stat.h>

#include "../include/string_utils.h"
#include "../include/utilities.h"




#define SHELL_PROMPT_BUFF_SIZE 255
#define HOSTNAME_BUFF_SIZE 50





/* printUsername - print username of current user
 * print username for current user (by uid)
 *
 * INPUTS : 
 *      NONE
 *
 * OUTPUT : 
 *      NONE
 */
static void 
printUsername ()
{
    uid_t uid = getuid();
    struct passwd * pw = getpwuid(uid);
    printf("%s" , pw->pw_name);
    fflush(stdout);
}



/* printHostname - print hostname 
 *
 * INPUTS : 
 *      NONE
 *
 * OUTPUT : 
 *      NONE
 */
static void 
printHostname ()
{
    char hostname[50];
    gethostname(hostname , 50);
    printf("%s" , hostname);
    fflush(stdout);
}



/* printPath - print current path
 *
 * INPUTS : 
 *      pointer to a char array of buffer
 *
 * OUTPUT : 
 *      NONE
 */
static 
void printPath (char * path)
{
    printf("%s" , path);
    fflush(stdout);
}






void 
shell_prompt (char * DIR)
{
    char username[USERNAME_BUFF_SIZE];
    getUsername(username);
    
    char config_path[250]; 
    sprintf(config_path , "/home/%s/.flux.conf" , username);


    
    char prompt[SHELL_PROMPT_BUFF_SIZE]; 


    /*
     * check for file exist 
     */
    if (access(config_path , F_OK) != 0)
        u_strcpy("%U@%H:~$ " , prompt);

    else 
    {
        int fd = open(config_path , O_RDONLY);

        // get file size
        struct stat fs;
        stat(config_path , &fs);

        int n = read(fd, prompt , fs.st_size - 1);
        if (n <= 0)
            u_strcpy("%U@%H:~$ " , prompt);
        else 
            prompt[n] = '\0';

        close(fd);
    }


    char * tmp_p = prompt;

    while (*tmp_p != '\0')
    {
        if (*tmp_p == '%')
        {
            tmp_p++;
            switch (*tmp_p)
            {
                case 'U' :
                    {
                    printUsername();
                    break;
                    }

                case 'H' : 
                    {
                    printHostname ();
                    break;
                    }
                case 'P' : 
                    printPath (DIR);

                default : 
                    ;
            }
        }
         
        else 
            write(1, tmp_p, 1);  
        



        tmp_p++;
    }
}





#endif /* SHELL_PROMPT */
