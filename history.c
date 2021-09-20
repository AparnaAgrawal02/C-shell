#include "headers.h"
char **read_file(char FileName[255], int *count)
{
    char **arr = malloc(21 * sizeof(char *));
    char c;
    char *buffer = malloc(131072);
    FILE *historyFile;
    if (access(FileName, F_OK) != -1)
    {
        historyFile = fopen(FileName, "r");
        if (historyFile < 0)
        {
            perror("Open File to read");
            free(buffer);
            return NULL;
        }
        memset(buffer, '\0', 131072);
        while ((c = fgetc(historyFile)) != EOF)
        {
            if (c == '\n')
            {
                strcat(buffer, "\0");
                //printf("%s", buffer);
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
        free(buffer);
        fclose(historyFile);
    }
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
    if (count == 20)
    {
        historyFile = fopen(FileName, "w");
        if (historyFile < 0)
        {
            perror("Open File to Write");
            return;
        }
        for (int i = 1; i++; i < 20)
        {
            fprintf(historyFile, "%s", arr[i]);
            free(arr[i]);
            
        }
        fprintf(historyFile, "%s", command);
        
        free(command);
        fclose(historyFile);
    }
    else
    {
        historyFile = fopen(FileName, "a");
        if (historyFile < 0)
        {
            perror("Open File to Write");
            return;
        }
        fprintf(historyFile, "%s", command);
     
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
    FILE *historyFile;
    arr = read_file(FileName, &count);
   // printf("%d", count);
   if (arglength >1){

   }
   else{
    if (count >= 10)
    {
        int i = count - 10;
        int r = 0;
        while (*arr)
        {
            if (r < i)
            {   free(*arr);
                arr++;
                r++;
            }
            else
            {
                printf("%s\n", *arr);
                free(*arr);
                arr++;
            }
        }
    }
    else
    {
        //printf("/n%d", count);
        while (*arr)
        {
            printf("%s\n", *arr);
            arr++;
        }
    }
   }
    return;
}