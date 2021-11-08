/**
 * Truman Johnston, tjohn54
 * Assignment 4, CS3305
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process
{
    char name[4];
    int arrival_time;
    int burst_time;
    int original_burst_time;
    int waiting_time;
    int turnaround_time;
};

// parse the string split up each element
void create_ready_queue(int *time_quantum, struct process *processes, char **array)
{

    // split array into process struct elements

    int i = 0; // reset the loop counter
    int process_counter = 0;

    // loop condition checks if the element after the time quantum is null
    while (array[i + 1] != NULL)
    {

        strcpy(processes[process_counter].name, array[i]);
        processes[process_counter].arrival_time = atoi(array[i + 1]);
        processes[process_counter].burst_time = atoi(array[i + 2]);
        processes[process_counter].original_burst_time = atoi(array[i + 2]);
        processes[process_counter].waiting_time = 0;
        processes[process_counter].turnaround_time = 0;

        i = i + 3;
        process_counter++;
    }
    // the final part of each line is always the time quantum
    *time_quantum = atoi(array[i]);
}

void round_robin(struct process *processes, int time_quantum, int num_processes)
{

    int waiting_time = 0;
    int last_updated = -1;

    // infinite loop for parsing through the array multiple times if needed,
    // will need to break from loop

    while (1)
    {
        // printf("starting round robin loop\n");

        int not_empty = 0;


        for (int j = 0; j < num_processes; j++)
        {
            // printf("starting inner round robin loop %d \n", num_processes);

            if (processes[j].burst_time > 0)
            {

                not_empty = 1;

                // set the waiting time of the process

                    if (processes[j].burst_time < time_quantum)
                        waiting_time += processes[j].burst_time;
                    else
                        waiting_time += time_quantum;
                
                 



                // subtract from the burst time
                processes[j].burst_time -= time_quantum;

                if (processes[j].burst_time <= 0)
                {
                    processes[j].waiting_time = waiting_time - processes[j].arrival_time - processes[j].original_burst_time;
                    processes[j].turnaround_time = processes[j].original_burst_time + processes[j].waiting_time;
                }
                else {
                    processes[j].waiting_time += waiting_time - processes[j].burst_time;
                }

                last_updated = j;

            }
        }
        if (not_empty == 0)
        {
            break;
        }
    }
}

int main()
{

    // parse the input file
    FILE *file = fopen("rr_input.txt.txt", "r");
    char line[512];

    // restart this loop everytime new processes are needed
    // when loop is done, every batch of processes has been completeted
    while (fgets(line, sizeof(line), file))
    {
        int time_quantum;
        int num_processes = 0;

        // split up the line string into an array
        //  tokenize items in the input line and split into array
        char *array[sizeof(line)];
        int i = 0;

        array[i] = strtok(line, " ");

        while (array[i] != NULL)
        {
            array[++i] = strtok(NULL, " ");
            num_processes++;
        }
        num_processes = (num_processes - 1) / 3;
        // printf("array::: \n%s\n%s\n%s\n::\n", array[0], array[1], array[2]);

        struct process processes[num_processes];
        create_ready_queue(&time_quantum, processes, array);

        round_robin(processes, time_quantum, num_processes);
        

        //print the info related to the executed process
        
        float ttl_waiting = 0;
        float ttl_turnaround = 0;
        for (int j = 0; j < num_processes; j++)
        {
            
            printf("Process: %s Arrival Time: %d Burst time: %d Waiting Time: %d Turnaround Time: %d\n", processes[j].name, processes[j].arrival_time, processes[j].original_burst_time, processes[j].waiting_time, processes[j].turnaround_time);
            
            ttl_waiting += processes[j].waiting_time;
            ttl_turnaround += processes[j].turnaround_time;

        }
            printf("Total Turnaround Time: %2.0f\n", ttl_turnaround );
            printf("Average Waiting Time: %.2fs\n", (ttl_waiting / num_processes));
            printf("Average Turnaround Time: %.2f\n\n", (ttl_turnaround / num_processes) );
    }

    // close the file
    fclose(file);
    return 0;
}