#include "headers.h"
char shell_path[PATH_MAX];
char* arguments[256];
int arglength;
int main()
{   //int PATH_MAX = 4096; //The longest path allow in Linux is 4095 characters.(256(NAME_MAX) x 16 = 4096).
    size_t size = 0;
    char **allComands = malloc(131072); //MAX_ARG_STRLEN
    char command[100],*line, *s;
    char raw[131072];
    char *delim = ";\n";
    char *blank = " \t";
    int success = 0;
    if (getcwd(shell_path, PATH_MAX) == 0)
    {
        perror("getcwd");
        return 1;
    }
    while (1)
    {
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
        i = 0;
        int r = 0;
        int flag = 0;
        s = allComands[0];
        s[strlen(s)] = '\0'; 

        while (s[i] == ' ' | s[i] == '\t')
        {
            i++;
        }
        while (i < 100 && s[i] != '\0' && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
        {
            command[r] = s[i];
            i++;
            r++;
        }
        if(s[i] == '\0' || s[i] == '\n'){
            i++;
        }
        else{strcpy(raw,&s[i + 1]);}
//------------------------------------------------------   
        arglength =0;    
       token = strtok(raw, blank);
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
        command[i] = '\0';
        if (i == 100)
        {
            printf("invalid Command");
        }
        if (strcmp(command, "echo") == 0)
        {
            flag = 1;
            //echo();
        }
        if (strcmp(command, "pwd") == 0)
        {
            flag = 1;
            pwd();
        }
        if (strcmp(command, "cd") == 0)
        {
            flag = 1;
            cd();
        }
        if (strcmp(command, "ls") == 0)
        {
            flag = 1;
            ls();
        }
        if (strcmp(command, "history") == 0)
        {
            log_history(command);
            read_history();
        }
        if (flag == 1)
        {
            log_history(command);
        }
        while(arglength>0){
            free(arguments[arglength]);
            arglength--;
        }
        raw[0] = '\0';
    }
}
