#include "headers.h"
void pinfo()
{
    FILE *fd;
    pid_t pid; //pid_t == int
    int i = 0, num = 3;
    char status, line[4096], file[256], statfile[256], exefile[256], *values[23], *ptr;
    char relative_path[PATH_MAX];
    if (arglength > 2)
    {
        fprintf(stderr, "too many argumnets\n");
        return;
    }
    if (arglength == 2)
    {
        pid = atoi(arguments[1]);
    }
    else
    {
        pid = getpid();
    }
    //--------------------------read stat file------------------------------------- 
    sprintf(file, "/proc/%d/", pid);
    printf("pid -- %d\n", pid);
    strcpy(statfile, file);
    strcat(statfile, "stat");
    fd = fopen(statfile, "r");
    if (fd == NULL)
    {
        perror("pinfo");
        return;
    }
    fgets(line, 4096, fd);
    fclose(fd);
    //---------------------------------------------------------------------
    //seperated values in stat
    char *token = strtok(line, " ");
    while (token != NULL)
    {
        values[i] = malloc(strlen(token) + 1);
        strcpy(values[i], token);
        i++;
        token = strtok(NULL, " ");
        if (i == 23)
        {
            break;
        }
    }
    if (i > 22)
    {
        printf("Process Status -- %s", values[2]); //state  %c
        if (strcmp(values[4], values[7]))          //5 th and 8th position
        {                                          //Foreground processes are those whose process group id (pgid) is the foreground one on the terminal (tpgid):
            printf("+");
        }
        printf("\n");
        printf("memory -- %lu\n", strtol(values[22], &ptr, 10)); //vsize  %lu
    }
    else
    {
        fprintf(stderr, "pinfo:buffer is small\n");
        return;
    }
    //--------------------------------reading exefile------------------
    strcpy(exefile, file);
    strcat(exefile, "exe");
    ssize_t len = readlink(exefile, line, 4095);
    if (len != -1)
    {
        line[len] = '\0';
    strcpy(relative_path,"~");
    //if path is not same change relativePath
    if (strcmp(shell_path,line) != 0)
    {
        if (strlen(shell_path) < strlen(line))
        {
            strcat(relative_path, &line[strlen(shell_path)]);
        }
        else
        {
            strcpy(relative_path, shell_path);
            relative_path[strlen(line)] = '\0';
        }
    }
        printf("Executable Path -- %s\n", relative_path);
    }
    else
    {
        perror("pinfo");
        return;
    }
}