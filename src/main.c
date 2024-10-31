#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{

    if(argc ==2)
    {
        unsigned int    count = atoi(argv[1]);   
        t_process* processes = malloc(count * sizeof(t_process));

        if (processes == NULL)
        {
            fprintf(stderr, "ERROR: failed/invalid memory allocation.\n");
            return (EXIT_FAILURE);
        }
        generate_processes(processes, count);
        fcfs(processes, count);
        sjf(processes, count);
        srtf(processes,count);
        non_preemptive_priority(processes, count);
        preemptive_priority(processes, count);
        round_robin(processes, count);
        multi_level_queue_scheduling(processes, count);
        free(processes);//to prevent memory leak
        return (EXIT_SUCCESS);
    }
    else
    {
        fprintf(stderr, "ERORR: please input only one arguemt!\n");
        return (EXIT_SUCCESS);
    }
}
