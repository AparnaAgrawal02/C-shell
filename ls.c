#include "headers.h"
//lists all directory except startng with .
//The  getopt()  function parses the command-line arguments
//If getopt() is called repeatedly, it re‐turns successively each of the option characters from each of the option elements.

void print_file_properties(struct stat stats)
{
  struct tm dt;
  struct passwd *pws;
  struct group *grp;
  int i = 0;
  char permision[11];
  char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Nov", "Dec"};
  for (i = 0; i < 10; i++)
  {
    permision[i] = '-';
  }
  permision[i] = '\0';
  if (S_IFDIR & stats.st_mode)
  {
    permision[0] = 'd';
  }
  if (stats.st_mode & S_IRUSR)
  {
    permision[1] = 'r';
  }
  if (stats.st_mode & S_IWUSR)
  {
    permision[2] = 'w';
  }
  if (stats.st_mode & S_IXUSR)
  {
    permision[3] = 'x';
  }
  if (stats.st_mode & S_IRGRP)
  {
    permision[4] = 'r';
  }
  if (stats.st_mode & S_IWGRP)
  {
    permision[5] = 'w';
  }
  if (stats.st_mode & S_IXGRP)
  {
    permision[6] = 'x';
  }
  if (stats.st_mode & S_IROTH)
  {
    permision[7] = 'r';
  }
  if (stats.st_mode & S_IWOTH)
  {
    permision[8] = 'w';
  }
  if (stats.st_mode & S_IXOTH)
  {
    permision[9] = 'x';
  }

  //  print permissions
  printf("%s ", permision);
  //number of hardlinks
  printf("%ld ", stats.st_nlink);
  //print username
  pws = getpwuid(stats.st_uid);
  printf("%s ", pws->pw_name);
  //print group name
  grp = getgrgid(stats.st_gid);
  printf("%s ", grp->gr_name);

  // File size
  printf("%5ld ", stats.st_size);

  // File last modification time
  dt = *(localtime(&stats.st_mtime));
  //month
  printf("%s ", months[dt.tm_mon]);
  //date
  printf("%2d ", dt.tm_mday);
  //time
  printf("%2d:%2d ", dt.tm_hour, dt.tm_min);
}

void ls()
{
  DIR *d;
  struct dirent *de;
  struct stat stats;
  int aflag = 0, lflag = 0, err = 0, c;
  char x = '\0';
  struct dirent **namelist;

  int n;

  n = scandir(".", &namelist, NULL, alphasort);
  if (n == -1)
  {
    perror("scandir");
    return;
  }

  // for(int i=0;i<arglength;i++){
  //   printf("%s ",arguments[i]);
  // }
  // printf("%d",arglength);
  while ((c = getopt(arglength, arguments, "al")) != -1)
  {
    switch (c)
    {
    case 'a':
      aflag = 1;
      break;
    case 'l':
      lflag = 1;
      break;
    case '?':
      err = 1;
      break;
    }
  }
  optind = 0; //OPTIND is initialized to 1 each time the shell or a shell script is invoked.
              //The shell does not reset OPTIND automatically; it must be manually reset between multiple calls to getopts within the same shell invocation if a new set of parameters is to be used.

  if (err)
  {
    printf("invalid option");
    return;
  }

  if (!aflag)
  {
    x = '.';
  }
  int r = 0;
  while (r < n)
  {
    if (namelist[r]->d_name[0] != x)
    {
      if (lflag)
      {
        if (stat(namelist[r]->d_name, &stats) == 0)
        {
          print_file_properties(stats);
        }
        else
        {
          printf("Unable to get file properties.\n");
        }
      }
      printf("%s\n", namelist[r]->d_name);
    }
    free(namelist[r]);
    r++;
  }
  free(namelist);
}