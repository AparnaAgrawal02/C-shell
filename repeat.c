#include "headers.h"
int  repeat()
{
    if (arglength < 3)
    {
        fprintf(stderr, "repeat:less argumnets\n");
        return -1;
    }
    int x = atoi(arguments[1]);
    char *command = malloc(4096);
    strcpy(command, arguments[2]);
    for (int j = 3; j < arglength; j++)
    {
        strcat(command, " ");
        strcat(command, arguments[j]);
    }
    printf("%d", numberOfCommands);
    while (x)
    {
        allComands[numberOfCommands] = malloc(strlen(command) + 1);
        strcpy(allComands[numberOfCommands], command);
        numberOfCommands++;
        x--;
    }
    free(command);
    return numberOfCommands;
}