#include "utils.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void    generate_processes(t_process *processes, unsigned int count)
{
    srand(time(NULL));
    for(unsigned int i = 0; i < count; i++)
    {
        if (count <= 0 || processes == NULL)
        {
           fprintf(stderr, "ERROR: invalid count or process\ntry inputing postive integers.\n");
           return;
        }
        processes[i].pid = i + 1;// assigns different pid for every processes 1 to 20.
        processes[i].arrival_time = rand() % 35; // higher range, allows for more idle state
        processes[i].burst_time = rand() % 10 + 1; // rang [1, 10]. +1 so no zero burst time
        processes[i].priority = rand() % 4; // 0 to 3;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

    printf("\033[1;34mGenerated Processes:\033[0m\n");
    printf("\033[1;34m| Process | PID | Arrival Time | Burst Time | Priority |\033[0m\n");
    printf("|---------|-----|--------------|------------|----------|\n");

    for (unsigned int i = 0; i < count; i++) 
    {
        printf("| \033[0;36m%7d\033[0m | \033[0;36m%3d\033[0m | \033[0;36m%12d\033[0m | \033[0;36m%10d\033[0m | \033[0;36m%8d\033[0m |\n", 
            i + 1, 
            processes[i].pid,
            processes[i].arrival_time,
            processes[i].burst_time,
            processes[i].priority);
    }
    printf("|---------|-----|--------------|------------|----------|\n");
}