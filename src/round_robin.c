#include <stdio.h>
#include "utils.h"

void round_robin(t_process *processes, unsigned int count)
{
    const unsigned int time_quantum = 1;
    
    int remaining_time[count]; /*it is normal int here as if it is unsigned if remainging 
    time < time slice the result will be a very large positive number*/

    unsigned int total_turnaround = 0;
    unsigned int total_wait = 0;
    unsigned int total_burst = 0;
    unsigned int completed = 0;
    unsigned int time = 0;
    unsigned int executed;

    for (unsigned int i = 0; i < count; i++)
    {
        remaining_time[i] = processes[i].burst_time;
        total_burst += processes[i].burst_time;
    }

    while (completed < count)
    {
        executed = 0;
        for (unsigned int i = 0; i < count; i++) 
        {
            if (processes[i].arrival_time <= time && remaining_time[i] > 0)
            {
                remaining_time[i] -= time_quantum;
                time += time_quantum;
                executed = 1;

                if (remaining_time[i] <= 0)
                {
                    remaining_time[i] = 0; // Avoid any potential underflow
                    completed++;
                    processes[i].completion_time = time;
                    processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    total_turnaround += processes[i].turnaround_time;
                    total_wait += processes[i].waiting_time;
                }
            }
            else if (!executed)
                time++;
        }
    }

    printf("\033[1;34mUsing Round Robin, Preemptive:\033[0m\n");
    printf("\033[1;34m| Process | PID | Arrival Time | Burst Time | Turnaround Time | Waiting Time | Completion Time |\033[0m\n");
    printf("|---------|-----|--------------|------------|-----------------|--------------|-----------------|\n");
    
    for (unsigned int i = 0; i < count; i++)
    {
        printf("| \033[0;36m%7d\033[0m | \033[0;36m%3d\033[0m | \033[0;36m%12d\033[0m | \033[0;36m%10d\033[0m | \033[0;36m%15d\033[0m | \033[0;36m%12d\033[0m | \033[0;36m%15d\033[0m |\n",
               i + 1, processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].turnaround_time,
               processes[i].waiting_time, processes[i].completion_time);
    }
    
    printf("|---------|-----|--------------|------------|-----------------|--------------|-----------------|\n");
    printf("\033[0;32mThe average turnaround time is: %.3f\033[0m\n", (float)total_turnaround / count);
    printf("\033[0;32mThe average wait time is: %.3f\033[0m\n", (float)total_wait / count);
    printf("\033[0;32mThe CPU utilization is: %.3f\033[0m\n", (float)total_burst / time);
    printf("\033[0;32mThe throughput is: %.3f processes per millisecond\033[0m\n", (float)count / time);
    printf("----------------------------------------------------------------------------------------------------------\n");
}