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

    printf("\033[1;34mUsing Preemptive Priority Scheduling:\033[0m\n");
    printf("\033[1;34m| Process | PID | Arrival Time | Burst Time | Priority | Turnaround Time | Waiting Time | Completion Time |\033[0m\n");
    printf("|---------|-----|--------------|------------|----------|-----------------|--------------|-----------------|\n");
    
    for (unsigned int i = 0; i < count; i++)
    {
        printf("| \033[0;36m%7d\033[0m | \033[0;36m%3d\033[0m | \033[0;36m%12d\033[0m | \033[0;36m%10d\033[0m | \033[0;36m%8d\033[0m | \033[0;36m%15d\033[0m | \033[0;36m%12d\033[0m | \033[0;36m%15d\033[0m |\n",
               i + 1,
               processes[i].pid, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority,
               processes[i].turnaround_time, processes[i].waiting_time,
               processes[i].completion_time);
    }
    
    printf("|---------|-----|--------------|------------|----------|-----------------|--------------|-----------------|\n");
    printf("\033[0;32mThe average turnaround time is: %.3f\033[0m\n", (float)total_turnaround / count);
    printf("\033[0;32mThe average wait time is: %.3f\033[0m\n", (float)total_wait / count);
    printf("\033[0;32mThe CPU utilization is: %.3f\033[0m\n", (float)total_burst / time);
    printf("\033[0;32mThe throughput is: %.3f processes per millisecond\033[0m\n", (float)count / time);
    printf("----------------------------------------------------------------------------------------------------------\n");
}