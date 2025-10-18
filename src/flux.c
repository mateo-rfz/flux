#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


#include "../include/string_utils.h"
#include "../include/shell_prompt.h"
#include "../include/parser.h"
#include "../include/utilities.h"




#define STDIN 0 
#define STDOUT 1 
#define STDERR 2

#define INPUT_BUFFER_SIZE 1024




int 
main () 
{



    char username[USERNAME_BUFF_SIZE];
    getUsername(username);



    char DIR[256];
    sprintf(DIR , "/home/%s/" , username);
    chdir(DIR);
    char  input_buffer[INPUT_BUFFER_SIZE];
    u_clear_buffer(input_buffer , INPUT_BUFFER_SIZE);



   



    /*
     * check history file existence if not create
     */
    char history_file_path[250];
    sprintf(history_file_path, "/home/%s/.flux_history" , username);

    int check = access(history_file_path, F_OK);

    int fd;
    if (check != 0)
        fd = open(history_file_path , O_CREAT | O_RDWR | O_APPEND , 0644);
    else 
        fd = open(history_file_path , O_RDWR | O_APPEND);
    /*
     * End of history file checker
     */






    /*
     * main loop of program
     */ 
    while (1) 
    {
        /*
         * read shell prompt config ~/.flux.conf
         * and write to stdout 
         */
        shell_prompt(DIR);




        u_clear_buffer (input_buffer , INPUT_BUFFER_SIZE);
        read(0, input_buffer ,  INPUT_BUFFER_SIZE);
        u_trim(input_buffer , INPUT_BUFFER_SIZE);




        /*
         * History : 
         * append input commands in ~/.flux_history
         */
        write(fd, input_buffer , u_strlen(input_buffer));
        write(fd , "\n" , 1); // new line
        /*
         * End of history section
         */






        /*
         * Internal-command 'pwd'
         * show current path by getcwd() 
         */
        if (u_strcomp(input_buffer , "pwd") == 0)
        {
                u_clear_buffer(DIR, 256);
                char * pwd = getcwd(DIR, 256);
                write(STDOUT , DIR , u_strlen(DIR)); 
                write(STDOUT , "\n" , 1); 
            continue;
        }
       



        /*
         * condition for show history of flux in output
         * read history for ~/.flux_history
         */
        if (u_strcomp(input_buffer , "history") == 0)
        {
            lseek(fd, 0, SEEK_SET);
            char history_buff[518];
            int n = read(fd, history_buff, 518);
            history_buff[n] = '\0';
            printf("%s" , history_buff);

            lseek(fd, 0, SEEK_END);
            continue;
        }




        /*
         * condition for exit internal command
         */
        if (u_strcomp(input_buffer, "exit") == 0)
                exit(0);




        char * argv[10] = {NULL};
        command_spliter(input_buffer, argv);

        if (u_strcomp("cd" , argv[0]) == 0)
        {
            int st = chdir(argv[1]);
            if (st == 0)
            {
                u_clear_buffer(DIR, 256);
                char * pwd = getcwd(DIR, 256);
            }

            else 
                printf("FLUX : %s No such file or directory\n" , argv[1]);


            continue;
        }
            


        //child pid
        pid_t cpid = fork ();
        if (cpid != 0) 
            waitpid (cpid , NULL ,  0);

        else 
        {
            int re = execvp(argv[0] , argv);
            if (re == -1)
            {
                write(STDOUT , "FLUX : " , 7);
                write(STDOUT , input_buffer , u_strlen(input_buffer));
                write(STDOUT , " command not found\n" , 25);
            }
            exit(0);
        }
    
    }
}
