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

    printf("\033[1;34mUsing Priority Scheduling, Non-Preemptive:\033[0m\n");
    printf("\033[1;34m| Process | PID | Arrival Time | Burst Time | Turnaround Time | Waiting Time | Completion Time |\033[0m\n");
    printf("|---------|-----|--------------|------------|-----------------|--------------|-----------------|\n");
    
    for (unsigned int i = 0; i < count; i++)
    {
        printf("| \033[0;36m%7d\033[0m | \033[0;36m%3d\033[0m | \033[0;36m%12d\033[0m | \033[0;36m%10d\033[0m | \033[0;36m%15d\033[0m | \033[0;36m%12d\033[0m | \033[0;36m%15d\033[0m |\n",
               i+1, processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].turnaround_time, processes[i].waiting_time, processes[i].completion_time);
    }
    
    printf("|---------|-----|--------------|------------|-----------------|--------------|-----------------|\n");
    printf("\033[0;32mThe average turnaround time is: %.3f\033[0m\n", (float)total_turnaround / count);
    printf("\033[0;32mThe average wait time is: %.3f\033[0m\n", (float)total_wait / count);
    printf("\033[0;32mThe CPU utilization is: %.3f\033[0m\n", (float)total_burst / completion_time);
    printf("\033[0;32mThe throughput is: %.3f processes per millisecond\033[0m\n", (float)count / completion_time);
    printf("----------------------------------------------------------------------------------------------------------\n");
}