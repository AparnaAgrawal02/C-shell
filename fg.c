#include "headers.h"
//fg : Brings the running or stopped background job corresponding to ​job number​ to the foreground, and changes its state to ​running .​The shell should throw an
//error if no job with the given job number exists.
void fg()
{
    if (arglength != 2)
    {
        fprintf(stderr, "invalid number of argument \n");
        return;
    }
    int job_number;
    int id;
    job_number = atoi(arguments[1]);
    id = get_process_id(job_number);
    if (id == -1)
    {
        fprintf(stderr, "job number doesn't exist\n");
        return;
    }
    delete_jobs(id); //only bground processes
    // protect shell against signals for illegal use of stdin and stdout
    fgpid = id;
    if (kill(id, SIGCONT) < 0)
    {
        perror("Could not run background process");
        return;
    }
    fgpid = id;
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    pid_t shell_pid = getpid();
    //giving control to bg process
    tcsetpgrp(STDIN_FILENO, getpgid(id));
    //wait for child
    waitForForegroundProcess(id);
    //waitpid(getpgid(id), NULL, WUNTRACED);
    //giving controll back to shell
    tcsetpgrp(STDIN_FILENO, getpgid(shell_pid));
    // safe to end protection from signals
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);

    /*    The  function tcsetpgrp() makes the process group with process group ID
       pgrp the foreground process group on the  terminal  associated  to  fd,
       which  must  be  the  controlling  terminal of the calling process, and
       still be associated  with  its  session.   Moreover,  pgrp  must  be  a
       (nonempty)  process  group belonging to the same session as the calling
       process. */
}
