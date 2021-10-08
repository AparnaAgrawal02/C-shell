#include "headers.h"
void ctrlc_handler(__attribute__ ((unused)) int signum){
//as soon as ctrlc is pressed foreground child terminates and send SIGCHLD which is handled in systemcommand.c
//for parent process it should do nothing thus
if(fgpid !=-1){
    kill(fgpid,SIGINT);
}
printf("\n");
return;
}

void ctrlz_handler(__attribute__ ((unused)) int signum){
/* a child process inherits signal settings from its parent during fork (). When process performs exec (),
    previously ignored signals remain ignored but installed handlers are set back to the default handler. */

//this will only work with parent shell
//printf("%d",fgpid);                  
if(fgpid !=-1){
    kill(fgpid,SIGTSTP);
}
printf("\n");
return;
}

/* when you press CTRL+C, parent shell handle this signal but the child will receive it - with the default action - terminate. */
void ctrlc_signal(){
    struct sigaction ctrlc;
    ctrlc.sa_handler = ctrlc_handler;
    ctrlc.sa_flags = 0; 
    sigfillset(&ctrlc.sa_mask);
    /* sa_mask  specifies  a  mask  of  signals which should be blocked (i.e.,
       added to the signal mask of the thread in which the signal  handler  is
       invoked) during execution of the signal handler.  In addition, the sig‐
       nal which triggered the handler will be blocked, unless the  SA_NODEFER
       flag is used. */

    if (sigaction(SIGINT, &ctrlc, NULL) == -1) //At the termination of the child, a 'SIGCHLD' signal is generated which is delivered to the parent by the kernel
    {
        perror("CLTR C");
        return;
    }
    sigprocmask(SIG_UNBLOCK, &ctrlc.sa_mask, NULL);
}

void ctrlz_signal(){
    struct sigaction ctrlz;
    ctrlz.sa_handler = ctrlz_handler;
    ctrlz.sa_flags = 0; 
    sigfillset(&ctrlz.sa_mask);
    /* sa_mask  specifies  a  mask  of  signals which should be blocked (i.e.,
       added to the signal mask of the thread in which the signal  handler  is
       invoked) during execution of the signal handler.  In addition, the sig‐
       nal which triggered the handler will be blocked, unless the  SA_NODEFER
       flag is used. */

    if (sigaction(SIGTSTP, &ctrlz, NULL) == -1) 
    {
        perror("CLTR Z");
        return;
    }
    sigprocmask(SIG_UNBLOCK, &ctrlz.sa_mask, NULL);
}

