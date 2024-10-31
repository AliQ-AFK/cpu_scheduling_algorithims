#ifndef UTILS_H
#define UTILS_H

typedef struct
{
    unsigned int     pid;
    unsigned int     arrival_time;
    unsigned int     burst_time;
    unsigned int     turnaround_time;
    unsigned int     waiting_time;
    unsigned int     completion_time;
    unsigned int     priority;
}   t_process;

void generate_processes(t_process *processes, unsigned int count);
void fcfs(t_process *processes, unsigned int count);
void srtf(t_process *processes, unsigned int count);
void sjf(t_process *processes, unsigned int count);
void non_preemptive_priority(t_process *processes, unsigned int count);
void preemptive_priority(t_process *processes, unsigned int count);
void round_robin(t_process *processes, unsigned int count);
void multi_level_queue_scheduling(t_process *processes, unsigned int count);

#endif 