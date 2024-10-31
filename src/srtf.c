#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void srtf(t_process *processes, unsigned int count) {
    unsigned int    remaining_time[count];
    unsigned int    total_turnaround = 0;
    unsigned int    total_wait = 0;
    unsigned int    total_burst = 0;
    unsigned int    completed = 0;
    unsigned int    time = 0;

    for (unsigned int i = 0; i < count; i++)
    {
        remaining_time[i] = processes[i].burst_time;
        total_burst += processes[i].burst_time;
    }

    while (completed < count) 
    {
        int min_index = -1;// -1 if no processes arives; serves as a lowerbound.
        unsigned int min_remaining_time = UINT_MAX;// serves as a max bound.
        
        //this loop will iterate untill it finds the process with the shortest burst time within the time given
        for (unsigned int i = 0; i < count; i++)
        {
            if (processes[i].arrival_time <= time && remaining_time[i] > 0)
            {
                // new remianing time is less than the current min time, update 
                if (remaining_time[i] < min_remaining_time)
                {
                    min_remaining_time = remaining_time[i];
                    min_index = i;
                }
            }
        }

        //this is idle cpu state.
        if (min_index == -1) 
            time++;
        //decrement by 1 second or whatever the time chosen time unit is.
        remaining_time[min_index]--;

        // checks if the process is finished, updates values and increases completion.
        /*unlike bubble sort, if remaining time == 0 the process will never be able to be processed in the cycle.
        as "remaining_time[i] > 0" */
        if (remaining_time[min_index] == 0)
        {
            completed++;
            processes[min_index].completion_time = time + 1; // Completed at time + 1
            processes[min_index].turnaround_time = processes[min_index].completion_time - processes[min_index].arrival_time;
            processes[min_index].waiting_time = processes[min_index].turnaround_time - processes[min_index].burst_time;
            total_turnaround += processes[min_index].turnaround_time;
            total_wait += processes[min_index].waiting_time;
        }
        
        time++;
    }

    // Print results
    printf("Using Shortest Remaining Time First, Preemptive:\n");
    printf("| Process | PID | Arrival Time | Burst Time | Turnaround Time | Waiting Time | Completion Time |\n");
    printf("|---------|-----|--------------|------------|-----------------|--------------|-----------------|\n");
    for (unsigned int i = 0; i < count; i++)
    {
        printf("| %7d | %3d | %12d | %10d | %15d | %12d | %16d |\n",
               i + 1,
               processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].turnaround_time,
               processes[i].waiting_time, processes[i].completion_time);
    }
    printf("|---------|-----|--------------|------------|-----------------|--------------|-----------------|\n");
    printf("\nThe average turnaround time is: %.3f\n", (float)total_turnaround / count);
    printf("The average wait time is: %.3f\n", (float)total_wait / count);
    printf("The CPU utilization is: %.3f\n", (float)total_burst / time);
    printf("The throughput is: %.3f processes per second\n", (float)count / time);
}
