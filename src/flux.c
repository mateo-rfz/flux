#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "internal/string_utils.h"
#include "internal/shell_prompt.h"



#define STDIN  0
#define STDOUT 1
#define STDERR 3




#define INPUT_BUFFER_SIZE 1024




int 
main () 
{
    char  input_buffer[INPUT_BUFFER_SIZE];
    clear_buffer(input_buffer , INPUT_BUFFER_SIZE);


    /*
     * check history file existence if not create
     */
    const char * history_file_path = "/home/mateo/.flux_history";
    int check = access(history_file_path, F_OK);

    int fd;
    if (check != 0)
        fd = open(history_file_path , O_CREAT|O_WRONLY , 0644);
    else 
        fd = open(history_file_path , O_WRONLY);
    /*
     * End of history file checker
     */



    /*
     * main loop of program
     */ 
    while (1) 
    {
        shell_prompt();

        clear_buffer (input_buffer , INPUT_BUFFER_SIZE);
        read(0, input_buffer ,  INPUT_BUFFER_SIZE);
        trim(input_buffer , INPUT_BUFFER_SIZE);

        /*
         * History : 
         * append input commands in ~/.flux_history
         */
        write(fd, input_buffer , f_string_len(input_buffer));
        write(fd , "\n" , 1); // new line
        /*
         * End of history section
         */
       



        /*
         * condition for show history of flux in output
         * read history for ~/.flux_history
         */
        if (f_strcomp(input_buffer , "history") == 0)
        {

            /*
             * TO DO
             */
            continue;
        }




        if (f_strcomp(input_buffer, "exit") == 0)
                exit(0);


        char * argv[10] = {NULL};
        command_spliter(input_buffer, argv);


        //child pid
        pid_t cpid = fork ();
        if (cpid != 0) 
            waitpid (cpid , NULL ,  0);

        else 
        {
            int re = execvp(argv[0] , argv);
            if (re == -1)
            {
                write(STDOUT , "flux : " , 7);
                write(STDOUT , input_buffer , f_string_len(input_buffer));
                write(STDOUT, " command not found\n" , 25);
            }

            exit(0);
        }
    
    }
}
