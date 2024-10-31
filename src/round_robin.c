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

    // Print results
    printf("Using Round Robin, Preemptive:\n");
    printf("| Process | PID | Arrival Time | Burst Time | Turnaround Time | Waiting Time | Completion Time |\n");
    printf("|---------|-----|--------------|------------|-----------------|--------------|-----------------|\n");
    for (unsigned int i = 0; i < count; i++)
    {
        printf("| %7d | %3d | %12d | %10d | %15d | %12d | %15d |\n",
               i + 1, processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].turnaround_time,
               processes[i].waiting_time, processes[i].completion_time);
    }
    printf("|---------|-----|--------------|------------|-----------------|--------------|-----------------|\n");
    printf("\nThe average turnaround time is: %.3f\n", (float)total_turnaround / count);
    printf("The average wait time is: %.3f\n", (float)total_wait / count);
    printf("The CPU utilization is: %.3f\n", (float)total_burst / time);
    printf("The throughput is: %.3f processes per millisecond\n", (float)count / time);
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
}