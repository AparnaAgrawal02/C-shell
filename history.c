#include "headers.h"
int log_history(char *command)
{
    char FileName[255];
    strcpy(FileName,shell_path);
    strcat(FileName,"/history.txt");
    int historyFile, success;
    historyFile = open(FileName, O_WRONLY | O_CREAT | O_APPEND, 0600);
    if (historyFile < 0)
    {
        perror("Open File to Write");
        return 1;
    }
    success = write(historyFile, command, strlen(command));
    if (success < 0)
    {
        perror("write History");
        return 1;
    }
    success = write(historyFile," ",1);
    if (success < 0)
    {
        perror("write History");
        return 1;
    }
    return 0;
}
int read_history()
{
    char *FileName = "history.txt", buffer[2];
    int historyFile, success =1;
    historyFile = open(FileName, O_RDONLY);
    if (historyFile < 0)
    {
        perror("Open File to Read");
        return 1;
    }
    
    while (success)
    {
        success = read(historyFile, buffer, 1);
        if (success < 0)
        {
            perror("read History");
            return 1;
        }
        if (strcmp(buffer, " ") == 0)
        {
            printf("\n");
        }
        else{
            printf("%s",buffer);
        }
    
    }
    char *delim = " ";
    char *token = strtok(buffer, delim);
    while (token != NULL)
    {
        printf("%s", token);
        token = strtok(NULL, delim);
    }
    return 0;
}