#include "headers.h"

int cd()
{
    char *path = malloc(PATH_MAX);
    char *pathcpy = malloc(PATH_MAX);
    static char *previous_directory = shell_path;
    char *garbage;
    char* arg = malloc(4096);
    if (getcwd(path, PATH_MAX) == 0)
    {
        perror("getcwd");
        return 1;
    }
    strcpy(pathcpy,path);
   
    if (arglength > 1)
    {
        printf("Error:cd too many argument\n");
        return 1;
    }
    
    //no argument given then switch to home directory
    if(arglength == 0){
        strcpy(arg,"~");
    }else{
        //change to current directory only
    strcpy(arg,arguments[0]);
    }
    if(arg == "."){
        return 0;
    }

    //switch to home directory
    else if (strcmp(arg, "~") == 0)
    {
        if (chdir(shell_path) == -1)
        {
            perror("chdir");
            return -1;
        }
    }
    //switch to previous directory and print
    else if (strcmp(arg, "-") == 0)
    {
         printf("%s\n",previous_directory);
            if (chdir(previous_directory) == -1)
            {
                perror("chdir");
                return -1;
            }
        
    }
    else
    {   // change to directory token
        //manages .. too
        if (chdir(arg) == -1)
        {
            perror("chdir");
            return -1;
        }
    }
    previous_directory = pathcpy;
    free(path);
    return 0;
}