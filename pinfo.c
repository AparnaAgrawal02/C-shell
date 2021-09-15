#include "headers.h"
void pinfo()
{
    char *file, *statfile,*exefile;
    FILE * fd;
    pid_t pid; //pid_t == int
    file = malloc(256);
    statfile = malloc(256);
    exefile = malloc(256);
    if (arglength > 2)
    {
        printf("too many argumnets\n");
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
    sprintf(file, "/proc/%d/",pid);
    printf("pid -- %d\n", pid);
    strcpy(statfile, file);
    strcat(statfile, "stat");
    
    fd = fopen(statfile, "r");
    if (fd == NULL)
    {
        perror("pinfo");
        return;
    }
    int i = 0, num = 3;
    char status;
    char line[4096];
    char *values[23],*ptr;
    fgets(line, 4096, fd);
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
    printf("Process Status -- %s\n", values[2]);
    printf("memory -- %lu\n", strtol(values[22],&ptr,10));
    strcpy(exefile,file);
    strcat(exefile,"exe");
    ssize_t len = readlink(exefile, line, 4095);
    if (len != -1) {
      line[len] = '\0';
      printf("Executable Path -- %s\n",line);
    }
    else{
        perror("pinfo");
        return;
    }
    
}