#include "headers.h"
char shell_path[PATH_MAX];
char *allComands[256];
char *arguments[256];
int arglength, numberOfCommands;
int main()
{ //int PATH_MAX = 4096; //The longest path allow in Linux is 4095 characters.(256(NAME_MAX) x 16 = 4096).
    size_t size = 0;
    //char **allComands = malloc(131072); //MAX_ARG_STRLEN
    char *line = NULL, *s;
    char *delim = ";\n";
    char *blank = " \t";
    int success = 0, flag;
    if (getcwd(shell_path, PATH_MAX) == 0)
    {
        perror("getcwd");
        return 1;
    }
    check_child_process(); //signal handling for when child process exits
    while (1)
    {

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
            else
            {
                perror("getline");
            }
        }
        log_history(line);
        numberOfCommands = 0;
        // ---------------------------------------------------------
        char *token = strtok(line, delim);
        while (token != NULL)
        {
            allComands[numberOfCommands] = malloc(strlen(token) + 1);
            strcpy(allComands[numberOfCommands], token);
            numberOfCommands++;
            token = strtok(NULL, delim);
        }
        //-------------------------------------------------------------
        for (int num = 0; num < numberOfCommands; num++)

        {
            //printf("%d", num);
            s = allComands[num];
            s[strlen(s)] = '\0';

            //------------------------------------------------------
            arglength = 0;
            token = strtok(s, blank);
            while (token != NULL)
            {
                arguments[arglength] = malloc(strlen(token) + 1);
                strcpy(arguments[arglength], token);
                arglength++;
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
            {   flag =1;
                break;
            }
            else if (strcmp(arguments[0], "history") == 0)
            {
                
                read_history();
            }

            else if (arglength > 0)
            {  
                execute_system_commands();
            }
        
            while (arglength > 0)
            {
                free(arguments[arglength - 1]);
                arguments[arglength - 1] = NULL;
                arglength--;
            }
        }
        if(flag==1){
            break;
        }

    }
}
