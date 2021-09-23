#include "headers.h"
void repeat()
{
    if (arglength < 3)
    {
        fprintf(stderr, "repeat:less argumnets\n");
        return ;
    }
    //converting 2nd argument to int
    int x = atoi(arguments[1]);
    if (x==0){
        printf("\n");
    }
    //printf("%d",x);
    char *command = malloc(131072);
    if(command == NULL){
        perror("repeat:malloc");
    }
    //getting command
    strcpy(command, arguments[2]);
    for (int j = 3; j < arglength; j++)
    {
        strcat(command, " ");
        strcat(command, arguments[j]);
    }
    //adding commands to allcommands
    while (x)
    {
        allComands[numberOfCommands] = malloc(strlen(command) + 1);
        strcpy(allComands[numberOfCommands], command);
        numberOfCommands++;
        x--;
    }
    free(command);

}