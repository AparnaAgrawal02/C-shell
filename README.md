# C-shell
## headers.h
    contails all header files and extern and global variables
### Specification 1:
## prompt.c 
     Display requirement is coverd in this file

    used getpwuid to get the user name
    used uname to get nodename ie system name
    found relative path between from where the shell was started and where the proess cureently is and printing accordingly
    declaration is in prompt.h

### Specification 2: Builtin commands
## pwd.c
    pwd.c contains implementation of pwd command  which prints name of current/working directory
    declaration is in pwd.h

## cd.c
    cd.c contains implementation of cd command
    declaration is in cd.h
## echo.c
    echo.c contains implementation of cd command, managed empty spaces
    declaration is in echo.h
### Specification 3: ls command
## ls.c
    ls.c contains implementation of ls command
    Implemented the ls command with its two flags “-a” and “-l”. You should be able to handle all
    the following cases also:(used getopt)
    ● ls
    ● ls -a
    ● ls -l
    ● ls .
    ● ls ..
    ● ls ~
    ● ls -a -l
    ● ls -la / ls -al
    ● ls <Directory/File_name>
    ● ls -<flags> <Directory/File_name>
    declaration is in ls.h

### Specification 4: System commands with and without arguments
## systemCommands.c
    contains implementation for foreground and background processes that are system commands
    declaration of functions in systemCommand.h
    parent waits for foreground not for baground process.
    used fork,execvp,wait

### Specification 5: pinfo command
## pinfo.c 
    contains impementation of pinfo command.got all information from proc/<pid>/.. files
    declaration in pinfo.h
### Specification 6: Finished Background Processes
## systemCommands.c
    check_baground_process(), handler(...) contains implementation  to print exit status of baground process whenever it exits.used sigaction.

### Specification 7: repeat Command
## repeat.c 
    contains implementation of repeat .
    The command is responsible for executing the given
    instruction multiple times. The first argument to the command specifies the number of
    times the following command is to be run.

    declaration in repeat.h
### Specification 8: history
## history.c
    implement user defined history command.
    declaration in history.h

    
## Part two
### Specification 1: Input/Output Redirection
## execute.c
    implemented in split_into_arguments,switch_input_output functions
    used dup2()
    An error message  displays if the input file does not exist.
    The output file is created (with permissions ​0644​)if it does not already exist.
    In case the output file already exists,it  overwrits in case of >​ and appends to in case of ​>>


### Specification 2:Command Pipelines
## execute.c
    used dup2() ,pipes() 
### Specification 3: I/O Redirection within Command Pipelines
## execute.c
    used dup2() ,pipes() 
### Specification 4: User-defined Commands
## jobs.c
    formed a linked list to store 
    void add_job(int pid);
    void delete_jobs(int pid);
    void print_jobs();
    update_status(pid);
    int get_process_id(int job_no);
    This command prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with
    their job number (a sequential number assigned by your shell), process ID and their state, which can either be r ​ unning​ or ​stopped​ . There may be flags specified
    as well. If the flag specified is -r , then print only the running processes else if the flag is -s then print the stopped processes only.

## sig
### sig.c
    Takes the job number (assigned by your shell) of a running job and sends the signal corresponding to s ​ ignal number​ to that process. The shell throws an error if no job with the given number exists
 ## fg
### fg.c
    Brings the running or stopped background job corresponding to ​job number​ to the foreground, and changes its state to ​running .​The shell throws an error if no job with the given job number exists.

## bg
### bg.c
    Changes the state of a stopped background job to running (in the background). The shell should throw an error if no background job corresponding to the
    given job number exists, and do nothing if the job is already running in the background.

## Specification 5: Signal Handling 
### In signaL.C
1. CTRL-Z It should push any currently running foreground job into the background, and change its state from running to stopped. This should have no effect on the
shell if there is no foreground process running.
2. CTRL-C It should interrupt any currently running foreground job, by sending it the ​SIGINT​ signal. This should have no effect on the shell if there is no foreground
process running.
### GETLINE (exeute.c)
3. CTRL-D It should log you out of your shell, without having any effect on the actual terminal.

## Bonus 1: replay :
   ### Replay.c
   Implemented a ‘replay’ command which executes a particular command in fixed time interval for a certain period.

