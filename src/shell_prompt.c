#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <sys/stat.h>

#include "../include/string_utils.h"
#include "../include/utilities.h"





#define SHELL_PROMPT_BUFF_SIZE 255
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



static void printPath (char * path)
{
    printf("%s" , path);
    fflush(stdout);
}






void shell_prompt (char * DIR)
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
    {   
        u_strcpy("%U@%H:~$ " , prompt);
    }

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
                    setError ();
            }

        }
         
        else {
            write(1, tmp_p, 1);  
        }



        tmp_p++;
    }


}
