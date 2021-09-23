#include "headers.h"
int pwd()
{
    char path[PATH_MAX];
    //case of too many argument
    if (arglength > 1)
    {
        printf("Error pwd: too many argument\n");
        return 1;
    }
    if (getcwd(path, PATH_MAX) == 0)
    {
        perror("getcwd");
        return 1;
    }
    printf("%s\n", path);
    return 0;
}