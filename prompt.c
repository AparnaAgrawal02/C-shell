#include "headers.h"
//  this function display promt of my terminal,changes if directory is changed
int prompt()
{
    struct utsname buffer;
    char current_path[PATH_MAX];
    char relative_path[PATH_MAX];
    struct passwd *pws;
    //fetch currrent process path
    if (getcwd(current_path, PATH_MAX) == 0)
    {
        perror("getcwd");
        return 1;
    }
    //for host/system/node name
    if (uname(&buffer) != 0)
    {
        perror("uname:");
        return 1;
    }
    //For user name
    /*getpwuid function returns a pointer to a structure containing the broken-out fields of the record in  the  pass‐
       word database that matches the user ID uid.The passwd structure is defined in <pwd.h> */
    //geteuid() returns the effective user ID of the calling process.
    pws = getpwuid(geteuid());
    if (pws == NULL)
    {
        perror("getpwuid");
        return 1;
    }
    strcpy(relative_path,"~");

    //if path is not same change relativePath
    if (strcmp(shell_path, current_path) != 0)
    {
        if (strlen(shell_path) < strlen(current_path))
        {
            strcat(relative_path, &current_path[strlen(shell_path)]);
        }
        else
        {
            strcpy(relative_path, shell_path);
            relative_path[strlen(current_path)] = '\0';
        }
    }
    //print
    printf("%s@%s:%s>", buffer.nodename, pws->pw_name, relative_path);
    return 0;
}
