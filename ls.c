#include "headers.h"
//lists all directory except startng with .
//The  getopt()  function parses the command-line arguments
//If getopt() is called repeatedly, it re‐turns successively each of the option characters from each of the option elements.
void list_directory(struct dirent **namelist, int n)
{
  int r = 0;
  while (r < n)
  {
    if (namelist[r]->d_name[0] != '.')
    {
      printf("%s\n", namelist[r]->d_name);
    }
    free(namelist[r]);
    r++;
  }
  free(namelist);
}
void list_all_directory(struct dirent **namelist, int n)
{
  int r = 0;
  while (r < n)
  {
    printf("%s\n", namelist[r]->d_name);

    free(namelist[r]);
    r++;
  }
  free(namelist);
}
printFileProperties( struct stat stats){
   struct tm dt;

    // File permissions
    printf("\nFile access: ");
    if (stats.st_mode & R_OK)
        printf("read ");
    if (stats.st_mode & W_OK)
        printf("write ");
    if (stats.st_mode & X_OK)
        printf("execute");

    // File size
    printf("\nFile size: %d", stats.st_size);

    // Get file creation time in seconds and 
    // convert seconds to date and time format
    dt = *(gmtime(&stats.st_ctime));
    printf("\nCreated on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                              dt.tm_hour, dt.tm_min, dt.tm_sec);

    // File modification time
    dt = *(gmtime(&stats.st_mtime));
    printf("\nModified on: %d-%d-%d %d:%d:%d", dt.tm_mday, dt.tm_mon, dt.tm_year + 1900, 
                                              dt.tm_hour, dt.tm_min, dt.tm_sec);
}
void print_all_files_properties(struct dirent **namelist,int n){
   struct stat stats;
  // stat() returns 0 on successful operation,
    // otherwise returns -1 if unable to get file properties.
    int r = 0;
  while (r < n)
  { 
    if (stat(namelist[r]->d_name, &stats) == 0)
    {
        printFileProperties(stats);
    }
    else
    {
        printf("Unable to get file properties.\n");
    }
    printf("%s\n", namelist[r]->d_name);

    free(namelist[r]);
    r++;
  }
  free(namelist);
    
}

void ls()
{
  DIR *d;
  struct dirent *de;
  int aflag = 0, lflag = 0, err = 0, c;

  struct dirent **namelist;
 
  int n;

  n = scandir(".", &namelist, NULL, alphasort);
  if (n == -1)
  {
    perror("scandir");
    return;
  }

  if (arglength == 0)
  {
    list_directory(namelist, n);
    return;
  }
  int z =0;
  for(int i=0;i<arglength;i++){
            printf("%s\n",arguments[i]);
        }
  while ((c = getopt(arglength, arguments, "al")) != -1){

    switch (c)
    {
    case 'a':
      aflag = 1;
      printf("a");
      break;
    case 'l':
      lflag = 1;
      printf("v");
      break;
    case '?':
      err = 1;
      printf ("Input file: \"%s\"\n", optarg);
      break;
    z++;
    }
  }
  printf("%d",z);
  if (err)
  {
    printf("invalid option");
    return;
  }

  if(aflag){
    list_all_directory(namelist,n);
  }
  if(lflag){
    print_all_files_properties(namelist,n);
  }


  

    
//   /* The  opendir()  function  opens a directory stream corresponding to the
//        directory name, and returns a pointer to  the  directory  stream.   The
//        stream is positioned at the first entry in the directory. */
//   d = opendir(".");
//   if (d == NULL)
//   {
//     printf("Couldn't open current directory");
//     return;
//   }
//   /* The  readdir()  function returns a pointer to a dirent structure repre‐
//        senting the next directory entry in the directory stream pointed to  by
//        dirp. */
//   while ((de = readdir(d)) != NULL)
//     printf("%s\n", de->d_name);
//   closedir(d);
//   return 0;
 }