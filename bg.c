#include "headers.h"
void bg()
{
    if (arglength != 2)
    {
        fprintf(stderr, "invalid number of argument \n");
        return;
    }
    int job_number;
    int id;
    job_number = atoi(arguments[1]);
    id = get_process_id(job_number);
    if (id == -1)
    {
        fprintf(stderr, "job number doesn't exist");
        return;
    }
    if (kill(id, SIGCONT) < 0)
    {
        perror("Could not run background process");
        return;
    }
}