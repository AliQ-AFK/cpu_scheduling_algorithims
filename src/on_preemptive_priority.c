#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void non_preemptive_priority(t_process *processes, unsigned int count)
{
   unsigned int completion_time = 0;
   unsigned int total_turnaround = 0;
   unsigned int total_wait = 0;
   unsigned int total_burst = 0;
   t_process temp;

   for (unsigned int i = 0; i < count; i++)
   {
        // similar non preemitve logic found in sjf
        for (unsigned int j = i + 1; j < count; j++)
        {
            if (processes[j].arrival_time <= completion_time)
            {
                if (processes[j].priority < processes[i].priority ||
                    (processes[j].priority == processes[i].priority &&
                     processes[j].arrival_time < processes[i].arrival_time))
                {
                    temp = processes[i];
                    processes[i] = processes[j];
                    processes[j] = temp;
                }
            }
        }

        //  idle cpu time
        if (processes[i].arrival_time > completion_time)
            completion_time = processes[i].arrival_time;

        completion_time += processes[i].burst_time;
        processes[i].completion_time = completion_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_wait +=  processes[i].waiting_time;
        total_turnaround += processes[i].turnaround_time;
        total_burst += processes[i].burst_time;
    }

    printf("Using Priority Scheduling, Non-Preemptive:\n");
    printf("| Process | PID | Arrival Time | Burst Time | Priority | Turnaround Time | Waiting Time | Completion Time |\n");
    printf("|---------|-----|--------------|------------|----------|-----------------|--------------|-----------------|\n");
    for(unsigned int i = 0; i < count; i++)
    {
         printf("| %7d | %3d | %12d | %10d | %8d | %15d | %12d | %16d |\n", 
            i + 1, 
            processes[i].pid, processes[i].arrival_time,
            processes[i].burst_time, processes[i].priority,
            processes[i].turnaround_time, processes[i].waiting_time,
            processes[i].completion_time);
    }
    printf("|---------|-----|--------------|------------|----------|-----------------|--------------|-----------------|\n");
    printf("\nThe average turnaround time is: %.3f\n", (float)total_turnaround / count);
    printf("The average wait time is: %.3f\n", (float)total_wait / count);
    printf("The CPU utilization is: %.3f\n", (float)total_burst / completion_time);
    printf("The throughput is: %.3f processes per second\n",(float) count / completion_time );
}
