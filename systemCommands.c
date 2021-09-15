#include "headers.h"
void execute_system_commands(){
    int baground=0;
    //printf("%s",arguments[arglength-1]);
    if(strcmp(arguments[arglength-1],"&")==0){
        baground =1;
        free(arguments[arglength-1]);
        arguments[arglength-1] = NULL;
    }
 
    pid_t pid;
	pid = fork();
    if (pid < 0) {     
            perror("System command: fork");
            return;
        }
    else if (pid == 0)
	{   //child process
    
		if(execvp(arguments[0], arguments)==-1){
            perror("System command:execvp");
            return;
        }
	}
	else
	{
		// Parent process
        if(baground){
        printf("%d\n",pid);
        }
		// Wait for child to finish if process is foreground
        if(!baground){
            wait(NULL);
        }
	}

}