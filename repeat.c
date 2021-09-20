#include "headers.h"
void repeat()
{
    if (arglength < 3)
    {
        fprintf(stderr, "repeat:less argumnets\n");
        return ;
    }
    int x = atoi(arguments[1]);
    if (x==0){
        printf("\n");
    }
    //printf("%d",x);
    char *command = malloc(4096);
    strcpy(command, arguments[2]);
    for (int j = 3; j < arglength; j++)
    {
        strcat(command, " ");
        strcat(command, arguments[j]);
    }
    while (x)
    {
        allComands[numberOfCommands] = malloc(strlen(command) + 1);
        strcpy(allComands[numberOfCommands], command);
        numberOfCommands++;
        x--;
    }
    free(command);

}