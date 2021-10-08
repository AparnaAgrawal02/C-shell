#include "headers.h"
char shell_path[PATH_MAX];
char *allComands[256];
char *arguments[256];
int arglength, numberOfCommands;
pid_t shell_pgid;

void semicolon_split(char *line);

int main()
{
    //int PATH_MAX = 4096; //The longest path allow in Linux is 4095 characters.(256(NAME_MAX) x 16 = 4096).
    size_t size = 0;
    //char **allComands = malloc(131072); //MAX_ARG_STRLEN
    char *line = NULL, *command;
    int success = 0, flag;
    //-------------------------------------------------------------------------------------------------
    if (getcwd(shell_path, PATH_MAX) == 0)
    {
        perror("getcwd");
        return 1;
    }
    /*------------------- Put ourselves in our own process group.--------------------  */
    shell_pgid = getpid();
    if (setpgid(shell_pgid, shell_pgid) < 0)
    {
        perror("Couldn't put the shell in its own process group");
        exit(1);
    }

    //----------------------signal calls-------------------------------------------------------
    ctrlc_signal();
    ctrlz_signal();
    check_child_process(); //signal handling for when child process exits
    //-----------------------------------------------------------------------------------------
    while (1)
    {
        line = NULL;
        flag = 0;
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

        //-------------------------------------------------------------
        for (int num = 0; num < numberOfCommands; num++)

        {
            //printf("%d", num);
            command = allComands[num];
            command[strlen(command)] = '\0';
            flag = executeCommand(command);

            //-----------------------------------------------
        }

        if (flag == 1)
        {
            break;
        }
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
