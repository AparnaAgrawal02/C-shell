# include "headers.h"
void sig()
{
    if (arglength != 3)
    {
        fprintf(stderr, "invalid number of argument \n");
        return;
    }
    int signal_number;
    int job_number;
    int id;
    job_number = atoi(arguments[1]);
    signal_number = atoi(arguments[2]);
    id = get_process_id(job_number);
    if (id == -1)
    {
        fprintf(stderr, "job number doesn't exist\n");
        return;
    }
    kill(id, signal_number);

}
