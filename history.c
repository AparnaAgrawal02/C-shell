#include "headers.h"
//this function is helping function
char **read_file(char FileName[255], int *count)
{
    char **arr = malloc(21 * sizeof(char *)); //given:stire at most 20 comands
    char c;
    char *buffer = malloc(131072); //max length of an agrument
    FILE *historyFile;
    //checks if file is there
    if (access(FileName, F_OK) != -1)
    { //open file to read
        historyFile = fopen(FileName, "r");
        //Error handle
        if (historyFile < 0)
        {
            perror("Open File to read");
            free(buffer);
            return NULL;
        }
        memset(buffer, '\0', 131072);
        //reading character by character till EOF
        while ((c = fgetc(historyFile)) != EOF)
        {
            if (c == '\n')
            {
                strcat(buffer, "\0");
                //allocate memory
                arr[*count] = malloc(strlen(buffer) + 1);
                strcpy(arr[*count], buffer);
                ++*count;

                memset(buffer, '\0', 131072);
            }
            else
            {
                // append ch to str
                strncat(buffer, &c, 1);
            }
        }

        fclose(historyFile);
    }
    free(buffer);
    return arr;
}
void log_history(char *command)
{
    char FileName[255];
    char **arr;
    int count = 0;
    strcpy(FileName, shell_path);
    strcat(FileName, "/history.txt");
    FILE *historyFile;
    arr = read_file(FileName, &count);
    if (count >= 20)
    {
        //file opened to write it will truncate the original file and then rewrite
        historyFile = fopen(FileName, "w");
        if (historyFile < 0)
        {
            perror("Open File to Write");
            for (int i = 1; i < 20; i++)
            {
                free(arr[i]);
            }
            return;
        }
        //print all leaving the first one
        for (int i = 1; i < 20; i++)
        {
            fprintf(historyFile, "%s\n", arr[i]);
            free(arr[i]);
        }
        //print new command
        fprintf(historyFile, "%s", command);

        //close file
        fclose(historyFile);
    }
    else
    { //open file to append it creates if file not prsent
        historyFile = fopen(FileName, "a");
        if (historyFile < 0)
        {
            perror("Open File to Write");
            return;
        }
        //append command
        fprintf(historyFile, "%s", command);
        //close file
        fclose(historyFile);
    }
    return;
}
void read_history()
{
    char FileName[255];
    char **arr;
    int count = 0;
    strcpy(FileName, shell_path);
    strcat(FileName, "/history.txt");
    //reading history file
    arr = read_file(FileName, &count);
    //printing recent 10 commands

    int i = count - 10; //commmands to skip
    if (i < 0)
    {
        i = 0;
    }
    while (*arr)
    {   //skip
        if (i > 0)
        {
            free(*arr);
            arr++;
            i--;
        }
        //print
        else
        {
            printf("%s\n", *arr);
            free(*arr);
            arr++;
        }
    }

    return;
}