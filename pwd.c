#include "headers.h"
int pwd(){
    char* path = malloc(PATH_MAX);
     if (arglength > 1)
    {
        printf("Error pwd: too many argument\n");
        return 1;
    }
    if(getcwd(path,PATH_MAX)== 0)
	{
		perror("getcwd");
		return 1;
	}
    printf("%s\n",path);
    free(path);
    return 0;
}