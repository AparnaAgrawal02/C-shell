#include "headers.h"
void echo()
{
    //printf("%s\n", string_to_print);
    char *modified_string;
    modified_string = malloc(arglength * 255);
    if (arglength == 0)
    {
        printf("\n");
        return;
    }

    strcpy(modified_string, arguments[1]);
    strcat(modified_string, " ");
    for (int i = 2; i < arglength; i++)
    {
        if (arguments[i][0] == '\'')
        {
            modified_string[strlen(modified_string) - 1] = '\0';
        }
        strcat(modified_string,arguments[i]);
        strcat(modified_string, " ");
    }
    printf("%s\n", modified_string);
    free(modified_string);
}
/* 
How strtok works 
t  h  i  s  ,  i  s  ,  a  ,  s  t  r  i  n  g \0         this,is,a,string

t  h  i  s  \0 i  s  ,  a  ,  s  t  r  i  n  g \0         this
^
t  h  i  s  \0 i  s  \0 a  ,  s  t  r  i  n  g \0         is
               ^
t  h  i  s  \0 i  s  \0 a  \0 s  t  r  i  n  g \0         a
                        ^
t  h  i  s  \0 i  s  \0 a  \0 s  t  r  i  n  g \0         string */