#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <sys/stat.h>

#include "string_utils.h"





#define SHELL_PROMPT_BUFF_SIZE 255
#define USERNAME_BUFF_SIZE 50
#define HOSTNAME_BUFF_SIZE 50



#define CONFIG_PATH "/home/mateo/.flux.conf"
//dir address only for test




void setError ()
{
    ;
}



static void printUsername ()
{
    uid_t uid = getuid();
    struct passwd * pw = getpwuid(uid);
    printf("%s" , pw->pw_name);
    fflush(stdout);
}




static void printHostname ()
{
    char hostname[50];
    gethostname(hostname , 50);
    printf("%s" , hostname);
    fflush(stdout);
}






void shell_prompt ()
{
    
    char prompt[SHELL_PROMPT_BUFF_SIZE]; 

    if (access(CONFIG_PATH , F_OK) != 0)
    {   
        f_str_copy("%U@%H:~$ " , prompt);
    }

    else 
    {
        int fd = open(CONFIG_PATH , O_RDONLY);

        // get file size
        struct stat fs;
        stat(CONFIG_PATH , &fs);

        int n = read(fd, prompt , fs.st_size - 1);
        if (n <= 0)
            f_str_copy("%U@%H:~$ " , prompt);
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

                default : 
                    setError ();
            }

        }
         
        else {
            write(1, tmp_p, 1);  
        }



        tmp_p++;
    }


}
