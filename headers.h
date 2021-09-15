#include <stdio.h>    
#include <sys/utsname.h>
#include <string.h>
#include<stdlib.h>
#include "pwd.h"
#include "prompt.h"
#include "echo.h"
#include "cd.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "history.h"
#include <pwd.h>
#include <dirent.h>
#include <unistd.h>
#include <linux/limits.h>
#include <time.h>
extern char shell_path[PATH_MAX];
char* arguments[256];
extern int arglength;
