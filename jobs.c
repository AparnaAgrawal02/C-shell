#include "headers.h"
job *job_head = NULL;
int baground_job_count = 0;
void update_status(job *new);
void add_job(pid_t pid)
{
    char file[256], statfile[256], line[4096], *values[5], *process_name = malloc(1024);
    sprintf(file, "/proc/%d/", pid);

    job *new = (job *)malloc(sizeof(job));

    new->next = NULL;
    strcpy(statfile, file);
    strcat(statfile, "stat");
    FILE *fd = fopen(statfile, "r");
    if (fd == NULL)
    {
        perror("pinfo");
        return;
    }
    fgets(line, 4096, fd);
    fclose(fd);
    //---------------------------------------------------------------------
    //seperated values in stat
    int i = 0;
    char *token = strtok(line, " ");
    while (token != NULL)
    {
        values[i] = malloc(strlen(token) + 1);
        strcpy(values[i], token);
        i++;
        token = strtok(NULL, " ");
        if (i == 4)
        {
            break;
        }
    }
    if (strcmp(values[2], "R") == 0)
    {
        //printf("%s", values[2]);
        new->status = "Running";
    }
    else if (strcmp(values[2], "T") == 0)
    {
        new->status = "Stopped";
    }
    else
    {
        new->status = values[2];
    }

    //--------------------------------------------------------------------
    new->job_number = ++baground_job_count;
    new->process_ID = pid;

    //get name of process from file----------------------------------------
    char buf[500];
    if (strcmp(arguments[0], "fg") == 0)
    {
        sprintf(file, "/proc/%d/status", pid);

        FILE *fp = fopen(file, "r"); //Open the file
        if (NULL != fp)
        {
            if (fgets(buf, 500, fp) == NULL)
            {
                fclose(fp);
            }
            sscanf(buf, "%*s %s", process_name);
        }
    }
    else
    {
        int args = arglength;
        strcpy(process_name, arguments[0]);
        if (arguments[arglength - 1] == NULL)
        {
            args -= 1;
        }
        for (int r = 1; r < args; r++)
        {
            strcat(process_name, " ");

            strcat(process_name, arguments[r]);
        }
    }
    new->name = process_name;

    if (job_head == NULL)
    {
        job_head = new;
    }
    else
    {
        job *p = job_head;
        job *prev = NULL;
        if (strcmp(p->name, new->name) > 0)
        {
            new->next = p;
            job_head = new;
            return;
        }
        while (p != NULL)
        {

            if (strcmp(p->name, new->name) > 0)
            {
                new->next = p;
                prev->next = new;
                return;
            }
            prev = p;
            p = p->next;
        }
        prev->next = new;
    }

    return;
}

void delete_jobs(pid_t pid)
{
    if (job_head == NULL)
    {
        return;
    }
    else
    {
        job *p = job_head;
        job *prev = NULL;
        //printf("[%d] %s %s [%d]", job_head->job_number, job_head->status, job_head->name, job_head->process_ID);
        if (p->process_ID == pid)
        {
            job_head = p->next;
            free(p);
            p = NULL;
            return;
        }
        while (p != NULL)
        {
            if (p->process_ID == pid)
            {

                prev->next = p->next;
                free(p);
                break;
            }

            prev = p;
            p = p->next;
        }
    }
}
void print_jobs()
{
    int rflag = 0, sflag = 0, err = 0, c;
    //printf("%s", arguments[1]);
    while ((c = getopt(arglength, arguments, "rs")) != -1)
    {
        switch (c)
        {
        case 'r':
            rflag = 1;
            break;
        case 's':
            sflag = 1;
            break;
        case '?':
            err = 1;
            break;
        }
    }
    if (err)
    {
        fprintf(stderr, "jobs: invalid option: \n");
        return;
    }
    if (job_head == NULL)
    {
        return;
    }
    else
    {
        job *p1 = job_head;
        while (p1 != NULL)
        {
            update_status(p1);

            if (strcmp(p1->status, "Running") == 0 && sflag != 1)
            {
                printf("[%d] %s %s [%d]\n", p1->job_number, p1->status, p1->name, p1->process_ID);
            }
            if (strcmp(p1->status, "Stopped") == 0 && rflag != 1)
            {
                printf("[%d] %s %s [%d]\n", p1->job_number, p1->status, p1->name, p1->process_ID);
            }

            p1 = p1->next;
        }
    }
    optind = 0; //OPTIND is initialized to 1 each time the shell or a shell script is invoked.
                //The shell does not reset OPTIND automatically; it must be manually reset between multiple calls to getopts within the same shell invocation if a new set of parameters is to be used.
}

void update_status(job *new)
{
    char file[256], statfile[256], line[4096], *values[5];
    sprintf(file, "/proc/%d/", new->process_ID);
    strcpy(statfile, file);
    strcat(statfile, "stat");
    FILE *fd = fopen(statfile, "r");
    if (fd == NULL)
    {
        return;
    }

    fgets(line, 4096, fd);
    fclose(fd);
    //---------------------------------------------------------------------
    //seperated values in stat
    int i = 0;
    char *token = strtok(line, " ");
    while (token != NULL)
    {
        values[i] = malloc(strlen(token) + 1);
        strcpy(values[i], token);
        i++;
        token = strtok(NULL, " ");
        if (i == 4)
        {
            break;
        }
    }
    if (strcmp(values[2], "R") == 0 || strcmp(values[2], "S") == 0)
    {
        //printf("%s", values[2]);
        new->status = "Running";
    }
    else if (strcmp(values[2], "T") == 0)
    {
        new->status = "Stopped";
    }
    else
    {
        new->status = values[2];
    }
}
int get_process_id(int job_no)
{

    if (job_head == NULL)
    {
        return -1;
    }
    else
    {
        job *p = job_head;
       
        if (p->job_number == job_no)
        {
            return p->process_ID;
        }
        while (p != NULL)
        {
            if (p->job_number == job_no)
            {

                return p->process_ID;
            }

            p = p->next;
        }
        return -1;
    }
}
