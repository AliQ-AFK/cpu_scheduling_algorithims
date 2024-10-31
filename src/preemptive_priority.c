#include "utils.h"
#include <stdio.h>
#include <limits.h>

void preemptive_priority(t_process *processes, unsigned int count)
{
    unsigned int remaining_time[count];
    unsigned int total_turnaround = 0;
    unsigned int total_wait = 0;
    unsigned int total_burst = 0;
    unsigned int completed = 0;
    unsigned int time = 0;

    for (unsigned int i = 0; i < count; i++) {
        remaining_time[i] = processes[i].burst_time;
        total_burst += processes[i].burst_time;
    }

    while (completed < count)
    {
        int min_index = -1;
        unsigned int min_priority = UINT_MAX;

        for (unsigned int i = 0; i < count; i++)
        {
            if (processes[i].arrival_time <= time && remaining_time[i] > 0)
            {
                if (processes[i].priority < min_priority ||
                    (processes[i].priority == min_priority && 
                    remaining_time[i] < remaining_time[min_index]))
                {
                    min_priority = processes[i].priority;
                    min_index = i;
                }
            }
        }

        //for CPU is idle
        if (min_index == -1)
            time++;

        remaining_time[min_index]--;
        
        if (remaining_time[min_index] == 0)
        {
            completed++;
            processes[min_index].completion_time = time + 1; // Finished at time + 1
            processes[min_index].turnaround_time = processes[min_index].completion_time - processes[min_index].arrival_time;
            processes[min_index].waiting_time = processes[min_index].turnaround_time - processes[min_index].burst_time;
            total_turnaround += processes[min_index].turnaround_time;
            total_wait += processes[min_index].waiting_time;
        }

        time++;
    }

    // Print results
    printf("Using Preemptive Priority Scheduling:\n");
    printf("| Process | PID | Arrival Time | Burst Time | Priority | Turnaround Time | Waiting Time | Completion Time |\n");
    printf("|---------|-----|--------------|------------|----------|-----------------|--------------|-----------------|\n");
    for (unsigned int i = 0; i < count; i++)
    {
        printf("| %7d | %3d | %12d | %10d | %8d | %15d | %12d | %16d |\n",
               i + 1,
               processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority,
               processes[i].turnaround_time, processes[i].waiting_time,
               processes[i].completion_time);
    }
    printf("|---------|-----|--------------|------------|----------|-----------------|--------------|----------------|\n");
    printf("\nThe average turnaround time is: %.3f\n", (float)total_turnaround / count);
    printf("The average wait time is: %.3f\n", (float)total_wait / count);
    printf("The CPU utilization is: %.3f\n", (float)total_burst / time);
    printf("The throughput is: %.3f processes per second\n", (float)count / time);
     printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
}
