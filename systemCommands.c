#include "headers.h"
void execute_system_commands()
{
    int baground = 0;
    //printf("%s",arguments[arglength-1]);
    if (strcmp(arguments[arglength - 1], "&") == 0)
    {
        baground = 1;
       // printf("x");
        free(arguments[arglength - 1]);
        arguments[arglength - 1] = NULL;
    }

    pid_t pid;
    int status;
    pid = fork();
    if (pid < 0)
    {
        perror("System command: fork");
        return;
    }
    else if (pid == 0)
    { //child process

        if (execvp(arguments[0], arguments) == -1)
        {
            perror("System command:execvp");
            return;
        }
    }
    else
    {
        // Parent process
        if (baground)
        {
            printf("%d\n", pid);
            check_baground_process();
        }
        // Wait for child to finish if process is foreground
        if (!baground)
        {   
            wait(&status);
        }
    }
}
static void handler(int signum, siginfo_t *info, void *ucontext)
 {   

     char *process_name=malloc(1024), *exit_status = "normally",*file = malloc(256);
    char* text = malloc(2048);
    pid_t process_pid;
    int fd;

     process_pid = info->si_pid;
     if (info->si_status)
    {
        exit_status = "abnormally";
    }
    //printf("%d",process_pid);
    sprintf(file, "/proc/%d/comm",process_pid);

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("handler");
        return;
    }
    read(fd,process_name,1024);
    process_name[strlen(process_name)-1] = '\0';
    close(fd);
    sprintf(text,"%s with pid %d exited %s\n", process_name, process_pid, exit_status);
    write(1,text,strlen(text));
    free(process_name);
    free(text);
    wait(NULL); //After wait, child is definitely freed.
     return;

}

void check_baground_process()
{
    struct sigaction sa;

    sa.sa_sigaction = handler;

    sa.sa_flags =SA_SIGINFO|SA_RESETHAND|SA_NODEFER;
    //sigfillset(&sa.sa_mask);
    sigprocmask(SIG_UNBLOCK,&sa.sa_mask,NULL); 
    

    if (sigaction(SIGCHLD, &sa, NULL) == -1)        //At the termination of the child, a 'SIGCHLD' signal is generated which is delivered to the parent by the kernel
    {
        perror("check baground process");
        return;
    }
    
    /* Handle error */;
}
