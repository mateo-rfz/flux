#include <fcntl.h>
#include <unistd.h>

#include "string_utils.h"



#define SHELL_PROMPT_BUFF_SIZE 255
#define USERNAME_BUFF_SIZE 50
#define HOSTNAME_BUFF_SIZE 50





void setError ()
{
    ;
}



void setUsername (char * username_buffer)
{
    ;
}


void setHostname (char * hostname_buffer)
{
    ;
}




void shell_prompt (char * shell_prompt_buffer)
{




    
    char prompt[SHELL_PROMPT_BUFF_SIZE]; 

    if ((access(".flux.conf" , F_OK)) != 0)
    {   
        char * dsp = "%U@%H:~$\0";  // dsp -> default shell prompt
        f_str_copy(dsp , prompt);
    }
    else 
    {
        int fd = open(".flux.conf" , O_RDONLY);

        if ((read(fd, prompt , SHELL_PROMPT_BUFF_SIZE)) == -1)
        {
            char * dsp = "%U@%H:~$\0";  // dsp -> default shell prompt
            f_str_copy(dsp , prompt);
        }
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
                    char username[USERNAME_BUFF_SIZE];
                    setUsername (username);
                    break;
                    }

                case 'H' : 
                    {
                    char hostname[HOSTNAME_BUFF_SIZE];
                    setHostname (hostname);
                    break;
                    }

                default : 
                    setError ();
            }

            tmp_p++;
        }
    }

}
