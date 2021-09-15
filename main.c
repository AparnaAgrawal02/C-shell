#include "headers.h"
char shell_path[PATH_MAX];
char* arguments[256];
int arglength;
int main()
{   //int PATH_MAX = 4096; //The longest path allow in Linux is 4095 characters.(256(NAME_MAX) x 16 = 4096).
    size_t size = 0;
    char **allComands = malloc(131072); //MAX_ARG_STRLEN
    char *line, *s;
    char *delim = ";\n";
    char *blank = " \t";
    int success = 0,flag;
    if (getcwd(shell_path, PATH_MAX) == 0)
    {
        perror("getcwd");
        return 1;
    }
    while (1)
    {   flag =0;
        success = prompt(shell_path);
        if (success == 1)
        {
            printf("Error in displaying Prompt");
        }
        getline(&line, &size, stdin);
        int i =0;
// ---------------------------------------------------------       
        char *token = strtok(line, delim);
        while (token != NULL)
        {   allComands[i]= malloc(strlen(token)+1);
            strcpy(allComands[i], token);
            i++;
            token = strtok(NULL, delim);
        }
//-------------------------------------------------------------       
        s = allComands[0];
        s[strlen(s)] = '\0'; 

//------------------------------------------------------   
        arglength =0;    
       token = strtok(s, blank);
        while (token != NULL)
        {   arguments[arglength]= malloc(strlen(token)+1);
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
            flag = 1;
            printf("hi");
            echo();
        }
        else if (strcmp(arguments[0], "pwd") == 0)
        {
            flag = 1;
            pwd();
        }
        else if (strcmp(arguments[0], "cd") == 0)
        {
            flag = 1;
            cd();
        }
        else if (strcmp(arguments[0], "ls") == 0)
        {
            flag = 1;
            ls();
        }
        else if (strcmp(arguments[0], "pinfo") == 0)
        {
            flag = 1;
            pinfo();
        }
        else if (strcmp(arguments[0], "history") == 0)
        {
            log_history(arguments[0]);
            read_history();
        }
        else if(arglength>0){
            execute_system_commands();
        }
        if (flag == 1)
        {
            log_history(arguments[0]);
        }
        while(arglength>0){
            free(arguments[arglength-1]);
            arguments[arglength-1] = NULL;
            arglength--;
        }
    
    }
}
