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
        processes[i].arrival_time = rand() % 50; // high range, allows for more idle state
        processes[i].burst_time = rand() % 10 + 1; // rang [1, 10]. +1 so no zero burst time
        processes[i].priority = rand() % 4; // 0 to 3;
        processes[i].completion_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
    }

}
