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
void list_all_files(char *directory, int aflag, int lflag)
{
  struct dirent **namelist;
  struct stat stats;
  int n;
  char x = '\0';
  // The  scandir()  function scans the directory dirp, calling filter() on each directory entry.  Entries for which filter() returns non‐
  //      zero are stored in strings allocated via malloc(3), sorted using qsort(3) with the comparison function compar(), and collected in ar‐
  //      ray namelist which is allocated via malloc(3).  If filter is NULL, all entries are selected.

  /*   The scandir() function returns the number of directory entries selected.  On error, -1 is returned, with errno set  to  indicate  the
       cause of the error. */
  n = scandir(directory, &namelist, NULL, alphasort);
  if (n == -1)
  {
    perror("ls:scandir\n");
    return;
  }

  if (!aflag)
  {
    x = '.'; //for hidden files
  }
  int r = 0, total = 0;

  //-------------------------to print total in longlisting------------------------------------  
  if (lflag)
  {
    while (r < n)
    {
      if (namelist[r]->d_name[0] != x)
      {
        if (stat(namelist[r]->d_name, &stats) == 0)
        {
          total += stats.st_blocks;
        }
      }
      r++;
    }
    printf("total %d\n", total/2); //for 1024 bytes of block (in st_blocks 1block = 512 )
  }
//--------------------------------------------------------------------------------------------
  r = 0;
  while (r < n)
  {
    if (namelist[r]->d_name[0] != x)
    {
      if (lflag) // long listing
      {
        if (stat(namelist[r]->d_name, &stats) == 0)
        {
          print_file_properties(stats);
        }
        else
        {
          printf("Unable to get file properties. ");
        }
      }
      printf("%s\n", namelist[r]->d_name);
    }
    free(namelist[r]);
    r++;
  }
  free(namelist);
}
void ls()
{
  int aflag = 0, lflag = 0, err = 0, c;
  char *directory = ".";

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
  if (err)
  {
    printf("invalid option\n");
    return;
  }
  //ony one directory given
  if (arglength - optind == 1)
  {
    directory = arguments[optind];
  }
  //set to home directory
  if (strcmp(directory, "~") == 0)
  {
    directory = shell_path;
  }
  //when only 0/1 directory given
  if (arglength - optind < 2)
  {

    list_all_files(directory, aflag, lflag);
  }
  else
  {
    int dict = arglength - 1;
    while (dict >= optind)
    {
      directory = arguments[dict];
      if (strcmp(directory, "~") == 0)
      {
        directory = shell_path;
      }
      printf("%s:\n", directory);
      list_all_files(directory, aflag, lflag);
      dict--;
    }
  }

  optind = 0; //OPTIND is initialized to 1 each time the shell or a shell script is invoked.
              //The shell does not reset OPTIND automatically; it must be manually reset between multiple calls to getopts within the same shell invocation if a new set of parameters is to be used.

  //printf("%s",directory);
}