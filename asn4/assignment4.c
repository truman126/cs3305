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
struct process *parse_string(char *input, int size , int *time_quantum)
{

    

    // tokenize items in the input line and split into array
    char *array[size];
    int i = 0;

    array[i] = strtok(input, "/");

    while (array[i] != NULL)
    {
        array[++i] = strtok(NULL, "/");
    }


    //split array into process struct elements

    i = 0; //reset the loop counter
    int process_counter = 0;

    // array of process structures
    struct process processes[(sizeof(array))/3];

    //loop condition checks if the element after the time quantum is null
    while (array [i+1] != NULL)
    {
        
        strcpy(processes[process_counter].name, array[i]);
        processes[process_counter].arrival_time = atoi(array[i+1]);
        processes[process_counter].burst_time = atoi(array[i+2]);
        processes[process_counter].original_burst_time = atoi(array[i+2]);
        processes[process_counter].waiting_time = 0;
        processes[process_counter].turnaround_time = 0;



        i = i + 3;
        process_counter++;

    }
    //the final part of each line is always the time quantum
    *time_quantum = atoi(array[i]);

    // while array is not null
    printf("array from inside parsing algo\n");


    return processes;
}

void round_robin(struct process processes, int time_quantum)
{

    // infinite loop for parsing through the array multiple times if needed,
    // will need to break from loop
    while (1)
    {

        int i = 0;
        int not_empty = 0;
        int waiting_time = 0;
        
        //do a pass through the processes
        while (processes[i].name != NULL){

            if (processes[i].burst_time > 0){
                not_empty = 1;
                //set the waiting time of the process
                processes[i].waiting_time += waiting_time;

                //add the burst time to the waiting time
                waiting_time += processes[i].burst_time;

                
                if (processes[i].burst_time =< 0){
                    processes[i].waiting_time -= processes[i].arrival_time;
                    processes[i].turnaround_time = processes[i].original_burst_time + processes[i].waiting_time;
                }
            }
        }
        if (not_empty == 0) break;
    }
}


int main()
{

    // parse the input file
    FILE *file = fopen("rr_input.txt", "r");
    char line[512];
    

    // restart this loop everytime new processes are needed
    // when loop is done, every batch of processes has been completeted
    while (fgets(line, sizeof(line), file))
    {
        int time_quantum;
        printf("%s\n\n\n", line);
        
        struct process processes[sizeof(line)];
        processes[] = create_ready_queue(&time_quantum, );

        // round_robin(processes, time_quantum);
    }

    // close the file
    fclose(file);
    return 0;
}