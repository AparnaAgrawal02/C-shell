#include "headers.h"
void replay()
{
  int interval = -1, period = -1, f = 0;
  char *command = malloc(1024);
  //command = NULL;

  //The  getopt()  function parses the command-line arguments
  //If getopt() is called repeatedly, it re‐turns successively each of the option characters from each of the option elements.
  char *prev;
  for (int i = 1; i < arglength; i++)
  {
    if (arguments[i][0] == '-')
    {
      prev = arguments[i];
      continue;
    }
    if (strcmp(prev, "-interval") == 0)
    {
      interval = atoi(arguments[i]);
    }
    else if (strcmp(prev, "-period") == 0)
    {
      period = atoi(arguments[i]);
    }
    else if (strcmp(prev, "-command") == 0)
    {
      
      if (f == 0)
      {
        strcpy(command, arguments[i]);
      }
      else
      {
        strcat(command, " ");
        strcat(command, arguments[i]);
      }
      f=1;
    }
    else
    {
      fprintf(stderr, "invalid interval option");
      return;
    }
  }
  if (command == NULL)
  {
    fprintf(stderr, "invalid Command option");
    return;
  }
  if (interval < 0)
  {
    fprintf(stderr, "invalid interval option");
    return;
  }
  if (period < 0)
  {
    fprintf(stderr, "invalid period option");
    return;
  }

  while (period > 0)
  {
    executeCommand(command);
    for(int i=0;i<= interval;i++){
      sleep(1);
      period -=1;
      if(period ==0){
        break;
      }
    }
  }

  optind = 0; //OPTIND is initialized to 1 each time the shell or a shell script is invoked.
  //The shell does not reset OPTIND automatically; it must be manually reset between multiple calls to getopts within the same shell invocation if a new set of parameters is to be used.
  free(command);
}