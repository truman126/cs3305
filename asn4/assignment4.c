/**
 * Truman Johnston, tjohn54
 * Assignment 4, CS3305
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct process {
   char  name[4];
   int arrival_time;
   int burst_time;
};
struct readyQueue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};


//parse the string split up each element
char **parse_string(char *input)
{

    char *array[256];
    int i = 0;

    array[i] = strtok(input, " ");

    while (array[i] != NULL)
    {
        array[++i] = strtok(NULL, " ");
    }

    return array;
}



void round_robin(struct process *processes, int quantum){
    //find the smallest arrival time

    int shortest = 0;

    for (int i=1; i < sizeof(processes); i++){
        if (processes[i].arrival_time < processes[shortest].arrival_time) {
            shortest = i;
        }
    }


    

} 
int main()
{

    // parse the input file
    FILE *file = fopen("rr_input.txt", "r");
    char line[256];



    // restart this loop everytime new processes are needed
    // when loop is done, every batch of processes has been completeted
    while (fgets(line, sizeof(line), file))
    {

        char **array = parse_string(line);

        //array of process structures
        struct process processes[sizeof(array)];

        int time_quantum = 0;


        // split each process into an array element
        int j = 0;
        for (int i = 0; i < sizeof(array); i+=3){



            
            strcpy( processes[j].name, array[i]);
            processes[j].arrival_time = atoi(array[i+1]);
            processes[j].burst_time = atoi(array[i+2]);
            j++;

            if (i > sizeof(array) + 3){
                time_quantum = array[i+1];
            }
        }



    }

    // close the file
    fclose(file);
    return 0;
}