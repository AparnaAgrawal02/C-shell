#include <stdio.h>
#include <sys/utsname.h>
#include <string.h>
#include <stdlib.h>
#include "pwd.h"
#include "fg.h"
#include "bg.h"
#include "sig.h"
#include "execute.h"
#include "jobs.h"
#include "replay.h"
#include "prompt.h"
#include "echo.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "systemCommands.h"
#include "repeat.h"
#include "signals.h"
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
#include <wait.h>
pid_t shell_pgid;
extern char shell_path[PATH_MAX];
char *allComands[256];
char *arguments[256];
extern int arglength;
extern pid_t fgpid;
extern int numberOfCommands;
typedef struct _job {
 int job_number;
 int process_ID;
 char *status;
 char *name;
 struct _job *next;
}job;
extern job *job_head;
extern int baground_job_count;