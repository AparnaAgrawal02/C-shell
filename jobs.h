#ifndef __JOBS_H
#define __JOBS_H
void add_job(int pid);
void delete_jobs(int pid);
void print_jobs();
void sig();
void bg();
void fg();
#endif