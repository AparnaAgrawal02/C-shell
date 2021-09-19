#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>
#include "pwd.h"
#include "prompt.h"
#include "echo.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "systemCommands.h"
#include "repeat.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "history.h"
#include <pwd.h>
#include <dirent.h>
#include <unistd.h>
#include <linux/limits.h>
#include <time.h>
#include <grp.h>
#include <signal.h>
#include <errno.h>

extern char shell_path[PATH_MAX];
char *allComands[256];
char *arguments[256];
extern int arglength;
extern int numberOfCommands;
