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
### history
## history.c
    implement user defined history command.
    declaration in history.h