#include "headers.h"
pid_t fgpid = -1;

//signal is handeld by check_child_process
void waitForForegroundProcess(pid_t pid)
{
    fgpid = pid;
    //printf("%d",fgpid);
    sigset_t empty;
    sigemptyset(&empty);
    while (fgpid == pid)
    {
        sigsuspend(&empty);
        /* sigsuspend does (in one atomic operation)
     * 1) update blocked set to this mask
     * 2) go to sleep until signal
     * 3) when woken up, restore original mask
     */
    }
}
void execute_system_commands()
{
    int baground = 0;
    //checks if process is baground
    if (strcmp(arguments[arglength - 1], "&") == 0)
    {
        baground = 1;
        free(arguments[arglength - 1]);
        arguments[arglength - 1] = NULL;
    }

    pid_t pid;

    /* fork()  creates  a new process by duplicating the calling process.  The
    new process is referred to as the child process.  The  calling  process
       is referred to as the parent process. */

    pid = fork();
    if (pid < 0)
    {
        perror("System command: fork");
        return;
    }
    else if (pid == 0)
    { //child process
        /*   Loads the executable file path, or a file found through a search path, into the memory associated with the calling
        process, and starts executing the program therein. If successful, it obliterates whatever
    program is currently running in the calling process. */
        setpgid(0, 0); //terminal signals will not affect child proces
        if (execvp(arguments[0], arguments) == -1)
        {
            fprintf(stderr, "System command:execvp:command not found %s\n", arguments[0]);

            exit(0);
        }
    }
    else
    {
        // Parent process
        // Wait for child to finish if process is foreground
        if (baground)
        {
            printf("%d\n", pid);
            add_job(pid);
        }
        if (!baground)

        {

            waitForForegroundProcess(pid);

            //wait(&status);
        }
    }
}
static void handler(__attribute__((unused)) int signum, siginfo_t *info, __attribute__((unused)) void *ucontext)
{ 
    char process_name[1024], *exit_status = "normally", file[256];
    char text[2048];
    pid_t process_pid;
    int fd;
    int status = 0;
    //get pid of process
    process_pid = info->si_pid;
    if (info->si_status == SIGCONT)
    {
        return;
    }
    //check if it is of foreground
    if (process_pid == fgpid)
    {
        fgpid = -1;
        //printf("i got executed");
        // WUNTRACED used to stop waiting when suspended

        waitpid(info->si_pid, &status, WUNTRACED);

        if (WEXITSTATUS(status) == SIGTSTP)
        {
            add_job(info->si_pid);
        }

        return;
    }
    if (arguments[0] != NULL)
    {
        if (strcmp(arguments[0], "fg") == 0 || strcmp(arguments[0], "bg") == 0)
        {
            return;
        }
    }
    //printf("a%s",arguments[0]);

    //check exit status
    if (info->si_status)
    {
        exit_status = "abnormally";
    }
    //printf("%d",info->si_status);
    //get name of process from file----------------------------------------
    sprintf(file, "/proc/%d/comm", process_pid);
    strcpy(process_name, "x");
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("handler");
    }
    else
    {
        read(fd, process_name, 1024);
        process_name[strlen(process_name) - 1] = '\0';
        close(fd);
    }
    //-------------------------------------------------------------------------

    //waitpid(getpgid(id), NULL, WUNTRACED);

    waitpid(info->si_pid, &status, WNOHANG);
    //printf("%d",x);
    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        delete_jobs(process_pid);
    }


    if (WIFSTOPPED(status))
    {
        sprintf(text, "%s with pid %d stopped\n", process_name, process_pid);
        write(1, text, strlen(text));
    }
    else{
         sprintf(text, "%s with pid %d exited %s\n", process_name, process_pid, exit_status);
        write(1, text, strlen(text));
    }
        return;
}

void check_child_process()
{
    struct sigaction sa;

    sa.sa_sigaction = handler;

    sa.sa_flags = SA_SIGINFO; /*   When the SA_SIGINFO flag is specified in act.sa_flags, the signal  han‐
       dler  address  is  passed via the act.sa_sigaction field.  This handler
       takes three arguments */
    sigfillset(&sa.sa_mask);
    /* sa_mask  specifies  a  mask  of  signals which should be blocked (i.e.,
       added to the signal mask of the thread in which the signal  handler  is
       invoked) during execution of the signal handler.  In addition, the sig‐
       nal which triggered the handler will be blocked, unless the  SA_NODEFER
       flag is used. */

    if (sigaction(SIGCHLD, &sa, NULL) == -1) //At the termination of the child, a 'SIGCHLD' signal is generated which is delivered to the parent by the kernel
    {
        perror("check baground process");
        return;
    }
    sigprocmask(SIG_UNBLOCK, &sa.sa_mask, NULL);
    /* Handle error */;
}
