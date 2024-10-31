#include "utils.h"
#include <stdio.h>

void multi_level_queue_scheduling(t_process *processes, unsigned int count)
{
    const unsigned int max_priority_levels = 4;
    for (unsigned int level = 0; level < max_priority_levels; level++)
    {
        unsigned int filtered_count = 0; // resets every cycle
        t_process filtered_processes[count];

        for (unsigned int i = 0; i < count; i++)
        {
            if (processes[i].priority == level)
                filtered_processes[filtered_count++] = processes[i];
        }

        if (filtered_count > 0)
        {
            printf("Executing Level %d Scheduling:\n", level + 1);
            switch (level)
            {
                case 0: 
                    preemptive_priority(filtered_processes, filtered_count);
                    break;
                case 1:
                    preemptive_priority(filtered_processes, filtered_count);
                    break;
                case 2:
                    round_robin(filtered_processes, filtered_count);
                    break;
                case 3:
                    sjf(filtered_processes, filtered_count);
                    break;
            }
        }
    }
}
