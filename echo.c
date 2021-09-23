#include "headers.h"
void echo()
{
    //printf("%s\n", string_to_print);
    char *modified_string;
    modified_string = malloc(arglength * 255);
    //if no arguments are given
    if (arglength == 1)
    {
        printf("\n");
        free(modified_string);
        return;
    }
    //copy the argument in modified string
    strcpy(modified_string, arguments[1]);
    strcat(modified_string, " ");
    //concating the arguments in modified string
    for (int i = 2; i < arglength; i++)
    {
        strcat(modified_string, arguments[i]);
        strcat(modified_string, " ");
    }
    //display
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