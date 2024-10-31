#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void    fcfs(t_process *processes, unsigned int count)
{
    unsigned int     completion_time = 0;
    unsigned int     total_wait = 0;
    unsigned int     total_turnaround = 0;
    unsigned int     total_burst = 0;

    for (unsigned int i = 0; i < count; i++)
    {
        if (completion_time < processes[i].arrival_time)// if the cpu is idle that time should be included
             completion_time = processes[i].arrival_time;

        completion_time += processes[i].burst_time;// current completion time, it accumaltes
        processes[i].completion_time = completion_time; // assign the completion time thus far to the specifc process
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        
        total_wait += processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
        total_burst += processes[i].burst_time;
    }
    printf("Using First Comes, Frst Served:\n");
    printf("| Process | PID | Arrival Time | Burst Time | Turnaround Time | Waiting Time | Completion Time |\n");
    printf("|---------|-----|--------------|------------|-----------------|--------------|-----------------|\n");

    for(unsigned int i = 0; i < count; i++)
    {
         printf("| %7d | %3d | %12d | %10d | %15d | %12d | %16d |\n", 
            i + 1, 
            processes[i].pid, processes[i].arrival_time,
            processes[i].burst_time, processes[i].turnaround_time,
            processes[i].waiting_time, processes[i].completion_time);
    }
    printf("|---------|-----|--------------|------------|-----------------|--------------|----------------|\n");
    printf("\nThe average turnaround time is: %.3f\n", (float)total_turnaround / count);
    printf("The average wait time is: %.3f\n", (float)total_wait / count);
    printf("The CPU utilization is: %.3f\n", (float)total_burst / completion_time);
    printf("The throughput is: %.3f processes per second\n",(float) count / completion_time );
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
}