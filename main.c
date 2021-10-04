#include "headers.h"
char shell_path[PATH_MAX];
char *allComands[256];
char *arguments[256];
int arglength, numberOfCommands;

void switch_input_output(int *open_case, char *file);
void back_to_original_file(char *file, int save, int dis);
void semicolon_split(char *line);
char **pipe_split(char *command, int *loop);


int main()
{  
    //int PATH_MAX = 4096; //The longest path allow in Linux is 4095 characters.(256(NAME_MAX) x 16 = 4096).
    size_t size = 0;
    //char **allComands = malloc(131072); //MAX_ARG_STRLEN
    char *line = NULL, *command, *s, **seperatedPipedCommand, *blank = " \t";
    int success = 0, flag, in = 0, out_truncate = 0, out_append = 0, save_stdin = dup(0), save_stdout = dup(1);
 //-------------------------------------------------------------------------------------------------   
    if (getcwd(shell_path, PATH_MAX) == 0)
    {
        perror("getcwd");
        return 1;
    }
    /*------------------- Put ourselves in our own process group.--------------------  */
    pid_t shell_pgid = getpid();
    if (setpgid(shell_pgid, shell_pgid) < 0)
    {
        perror("Couldn't put the shell in its own process group");
        exit(1);
    }

//----------------------signal calls-------------------------------------------------------
    ctrlc_signal();
    check_child_process(); //signal handling for when child process exits
//-----------------------------------------------------------------------------------------
    while (1)
    {
        line = NULL;
        flag = 0, in = 0, out_append = 0, out_truncate = 0;
        success = prompt(shell_path);
        if (success == 1)
        {
            printf("Error in displaying Prompt");
        }

        if (getline(&line, &size, stdin) < 0)
        {
            if (errno == EINTR)
            {
                clearerr(stdin); // to continue after signal is handled using single handler
                continue;
            }
            //getline return -1 on failure to read a line (including end-of-file condition).
            //handling ctrl D--exiting my shell
            else if (errno == 0)
            {
                exit(0);
            }
            else
            {
                perror("getline");
            }
        }
        log_history(line);
        numberOfCommands = 0;
        // ---------------------------------------------------------
        semicolon_split(line);
        // 0 is read end, 1 is write end
        int pipefd[2];
        if (pipe(pipefd) < 0)
        {
            printf("\nPipe could not be initialized\n");
            continue;
        }
        //-------------------------------------------------------------
        for (int num = 0; num < numberOfCommands; num++)

        {
            //printf("%d", num);
            command = allComands[num];
            command[strlen(command)] = '\0';
            int loop = 0;
            seperatedPipedCommand = pipe_split(command, &loop);
            //printf("%d%s",loop,seperatedPipedCommand[1]);
            for (int i = 0; i < loop; i++)
            {
                //---------original---------------------
                if (i == loop - 1 && i == 0)
                {
                    dup2(save_stdin, 0);
                    dup2(save_stdout, 1);
                }

                //-----------------------------------------------
                else if (i == 0)
                {
                    /* The first process should get its input from the original file descriptor 0.  */
                    //close(pipefd[0]);
                    
                    dup2(pipefd[1], STDOUT_FILENO);
                    close(pipefd[1]);
                }
                else if (i == loop - 1)
                {    // replace standard input with input part of pipe
                    dup2(pipefd[0], STDIN_FILENO);
                    close(pipefd[0]);
                    //the last process should output to original stdout
                    dup2(save_stdout, STDOUT_FILENO);
                    
                }
                else
                {   
                    
                    //close(STDOUT_FILENO);
                    //close(STDIN_FILENO);
                    dup2(pipefd[0], STDIN_FILENO);
                    close(pipefd[0]);
                    pipe(pipefd);
                    dup2(pipefd[1], STDOUT_FILENO);
                    close(pipefd[1]);
                }

                s = seperatedPipedCommand[i];
                arglength = 0;
                in = 0, out_truncate = 0, out_append = 0;
                char *token = strtok(s, blank);
                while (token != NULL)
                {
                    if (in == 1)
                    {
                        switch_input_output(&in, token);
                    }
                    else if (out_truncate == 2)
                    {
                        switch_input_output(&out_truncate, token);
                    }
                    else if (out_append == 3)
                    {
                        switch_input_output(&out_append, token);
                    }
                    else if (strcmp(token, "<") == 0)
                    {
                        in = 1;
                    }
                    else if (strcmp(token, ">") == 0)
                    {
                        out_truncate = 2;
                    }
                    else if (strcmp(token, ">>") == 0)
                    {
                        out_append = 3;
                    }
                    else
                    {
                        arguments[arglength] = malloc(strlen(token) + 1);
                        strcpy(arguments[arglength], token);
                        arglength++;
                    }
                    token = strtok(NULL, blank);
                }
                //------------------------------------------------------------
                // printf("%s %d",raw,arglength);
                // for(int i=0;i<arglength;i++){
                //     printf("%s\n",arguments[i]);
                // }

                if (strcmp(arguments[0], "echo") == 0)
                {
                    echo();
                }
                else if (strcmp(arguments[0], "pwd") == 0)
                {
                    pwd();
                }
                else if (strcmp(arguments[0], "cd") == 0)
                {
                    cd();
                }
                else if (strcmp(arguments[0], "ls") == 0)
                {
                    ls();
                }
                else if (strcmp(arguments[0], "pinfo") == 0)
                {
                    pinfo();
                }
                else if (strcmp(arguments[0], "repeat") == 0)
                {
                    repeat();
                }

                else if (strcmp(arguments[0], "exit") == 0)
                {
                    flag = 1;
                    break;
                }
                else if (strcmp(arguments[0], "history") == 0)
                {
                    read_history();
                }

                else if (arglength > 0)
                {
                    //printf("Hello");
                    execute_system_commands();
                }

                while (arglength > 0)
                {
                    free(arguments[arglength - 1]);
                    arguments[arglength - 1] = NULL;
                    arglength--;
                }
            }
            //original
            dup2(save_stdin, 0);
            dup2(save_stdout, 1);

            //-----------------------------------------------
        }

        if (flag == 1)
        {
            break;
        }
    }
}
//std file discriptor to point input/outputfile
void switch_input_output(int *open_case, char *file)
{
    int fd1;
    switch (*open_case)
    {
    case 1:
        fd1 = open(file, O_RDONLY);
        break;
    case 2:
        fd1 = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        break;
    case 3:
        fd1 = open(file, O_WRONLY | O_APPEND, 0644);
        break;
    }
    if (fd1 < 0)
    {
        perror("Couldn't open input file");
        *open_case = 0;
    }
    else
    {
        if (*open_case == 1)
        {
            dup2(fd1, 0); /* The dup2() system call performs the same task as dup(), but instead  of
                        using  the lowest-numbered unused file descriptor, it uses the file de‐
                        scriptor number specified in newfd.  If the file descriptor  newfd  was
                        previously open, it is silently closed before being reused. */
        }
        else
        {
            dup2(fd1, 1);
        }
        *open_case = 0;
        close(fd1);
    }
}
//spliting by ;
void semicolon_split(char *line)
{
    char *delim = ";\n";
    char *token = strtok(line, delim);
    while (token != NULL)
    {
        allComands[numberOfCommands] = malloc(strlen(token) + 1);
        strcpy(allComands[numberOfCommands], token);
        numberOfCommands++;
        token = strtok(NULL, delim);
    }
}

// spliting by |
char **pipe_split(char *command, int *loop)
{
    char *delim = "|";
    char **s = malloc(256);
    char *token = strtok(command, delim);
    while (token != NULL)
    {
        s[*loop] = malloc(strlen(token) + 1);
        strcpy(s[*loop], token);
        *loop += 1;
        //printf("%d",*loop);
        token = strtok(NULL, delim);
    }
    return s;
}