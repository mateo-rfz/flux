#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

#include "internal/string_utils.h"



#define STDIN  0
#define STDOUT 1
#define STDERR 3




/*
 * write shell prompt in command input 
 */
void 
shell_prompt () 
{
    write(STDOUT , "$>> " , 4);
}






int 
main () 
{
    int buff_size = 1024;
    char  input_buffer[buff_size];
    clear_buffer(input_buffer , buff_size);



    char current_dir[1024];


    /*
     * main loop of program
     */ 
    while (f_strcomp(input_buffer , "exit")) 
    {
        shell_prompt();

        clear_buffer (input_buffer , buff_size);
        read(0, input_buffer ,  buff_size);
        trim(input_buffer , buff_size);


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
                write(STDOUT, "error\n" , 6);
            }
            exit(0);
        }
    
    }
}
