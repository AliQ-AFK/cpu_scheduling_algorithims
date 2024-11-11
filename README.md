
# Process Scheduling Algorithms in C

This project implements several process scheduling algorithms in C, allowing users to simulate different scheduling strategies and observe their performance metrics. The algorithms included in this project are:
1. Process Generation
2. First-Come, First-Served (FCFS)
3. Non-Preemptive Priority Scheduling
4. Preemptive Priority Scheduling
5. Round Robin Scheduling
6. Shortest Job First (SJF)
7. Shortest Remaining Time first (SRTF)
8. A multilevel algorithm.

## Project Structure

```
cpu_scheduling_algorithms/
├── src/
│   ├── fcfs.c
|   ├── main.c 
|   ├── multilevel_queue.c
│   ├── non_preemptive_priority.c
│   ├── preemptive_priority.c
|   ├── process.c
│   ├── round_robin.c
│   ├── sjf.c
│   └── srtf.c
├── utils.h
├── LICENSE
├── makefile
├── Report.pdf
└── README.md
```

- `src/`: Contains all the C source files implementing the scheduling algorithms.
- `utils.h`: Header file defining the process structure and utility functions.
- `README.md`: This documentation file.

## Process Structure

The `t_process` structure is defined in the `utils.h` file and contains the following fields:

```c
typedef struct s_process
{
    int pid;               // Process ID
    unsigned int arrival_time; // Time at which process arrives in the ready queue
    unsigned int burst_time;   // CPU time required by the process
    unsigned int completion_time; // Time at which process completes execution
    unsigned int turnaround_time; // Total time taken from arrival to completion
    unsigned int waiting_time; // Total time the process has been waiting in the ready queue
    unsigned int priority;     // Priority of the process (lower number indicates higher priority)
} t_process;
```

### Fields Explanation
- **pid**: Unique identifier for each process.
- **arrival_time**: Time when the process enters the ready queue.
- **burst_time**: Total CPU time required for the process to complete.
- **completion_time**: Time when the process finishes its execution.
- **turnaround_time**: Total time taken from arrival to completion (completion_time - arrival_time).
- **waiting_time**: Time the process has been in the ready queue (turnaround_time - burst_time).
- **priority**: Priority level of the process, where a lower number indicates higher priority.

## Algorithms

### 1. Process Generation

The `process_generator.c` file contains a function to generate random processes for testing the scheduling algorithms.

**Source Code**: `process_generator.c`

#### Key Functions:
- **void    generate_processes(t_process *processes, unsigned int count)**:
    - Generates `n` random processes with random arrival times, burst times, and priorities.
    - This function provides each process with a unique ID and random attributes, which allows for comprehensive testing of scheduling behaviors.

### 2. First-Come, First-Served (FCFS)

This algorithm processes jobs in the order they arrive.

**Source Code**: `fcfs.c`

#### Key Functions:
- **void    fcfs(t_process *processes, unsigned int count)**:
    - Sorts processes by arrival time.
    - Iteratively calculates each process's completion time based on the end time of the previous process.
    - Computes turnaround and waiting times using formulas:
        - `turnaround_time = completion_time - arrival_time`
        - `waiting_time = turnaround_time - burst_time`
    - FCFS does not consider priority, making it straightforward but potentially inefficient for varied process times.

### 3. Non-Preemptive Priority Scheduling

Processes with higher priority execute first. In cases of equal priority, the one arriving first executes.

**Source Code**: `non_preemptive_priority.c`

#### Key Functions:
- **void non_preemptive_priority(t_process *processes, unsigned int count)**:
    - Sorts by priority and arrival time, ensuring high-priority tasks are executed first.
    - Similar to FCFS in terms of time calculations, but processes cannot preempt others once they begin executing.
    - Provides a simple but static priority-based scheduling mechanism.

### 4. Preemptive Priority Scheduling

A higher-priority process can preempt a currently running process.

**Source Code**: `preemptive_priority.c`

#### Key Functions:
- **void preemptive_priority(t_process *processes, unsigned int count)**:
    - Tracks active processes and the highest-priority job.
    - Allows preemption, suspending the current process to run a new, higher-priority one.
    - Uses dynamic checks to handle each process's waiting and turnaround times while allowing priority-based interruption.

### 5. Round Robin Scheduling

A time-slice scheduling approach, ensuring all processes get a fair share of CPU time.

**Source Code**: `round_robin.c`

#### Key Functions:
- **void round_robin(t_process *processes, unsigned int count)**:
    - Cycles processes in a queue, with each given a maximum `quantum` time.
    - A process reenters the queue if unfinished, balancing wait times by rotating through jobs.
    - Measures and updates waiting time for each process when it is in the queue but not executing.

### 6. Shortest Job First (SJF)

Schedules the process with the shortest burst time next.

**Source Code**: `sjf.c`

#### Key Functions:
- **oid sjf(t_process *processes, unsigned int count)**:
    - Sorts by burst time, optimizing for lower average waiting times.
    - Completes processes with the shortest execution requirements first, leading to efficient CPU utilization.
    - As with other algorithms, it calculates completion, turnaround, and waiting times.

### 7. Shortest Remaining Time First (SRTF)

A preemptive form of SJF that checks for the shortest burst time at each interval.

**Source Code**: `srtf.c`

#### Key Functions:
- **void srtf(t_process *processes, unsigned int count)**:
    - Monitors remaining burst times of all ready processes.
    - Preempts currently running processes if a new one with a shorter burst time arrives.
    - Adjusts metrics dynamically, aiming for minimal average waiting and turnaround times.

### 8. Multilevel Algorithm

Utilizes multiple scheduling queues, each with a distinct algorithm for handling processes.

**Source Code**: `multilevel_queue.c`

#### Key Functions:
- **void multi_level_queue_scheduling(t_process *processes, unsigned int count)**:
    - Assigns processes to distinct priority levels, each level using a different algorithm.
    - Allows low-priority processes to defer to higher-priority ones, ideal for systems with a mix of urgent and background tasks.

## Compilation and Usage

To compile the program, navigate to the project directory and run:

```bash
make 
```

You can execute the compiled program with:

```bash
./cpu_scheduling <postive int>
```
to clean comiled files simply run
```bash
make clean
```

## Running the Program

To run the program, use the following command with command-line arguments specifying the number of processes. The program expects only positive integer arguments:

```bash
./cpu_scheduling <number_of_processes>
```

Example:

```bash
./cpu_scheduling 5
```

> **Note:** Only positive integers should be used for process numbers. Non-positive integers or non-integer inputs will result in an error.

## Cloning the Repository and Setup

To clone the repository and set up the environment:

```bash
git clone https://github.com/AliQ-AFK/cpu_scheduling_algorithims.git


Then you can run the program as shown above.

### Sample Execution

When you run the program, it will generate random processes and display the results of each scheduling algorithm, including process metrics like turnaround time, waiting time, CPU utilization, and throughput.

## Conclusion

This project provides a clear implementation of various process scheduling algorithms, making it a valuable resource for understanding how different algorithms work and their performance implications. You can modify the `process_generator.c` file to experiment with different sets of processes for more extensive testing.
