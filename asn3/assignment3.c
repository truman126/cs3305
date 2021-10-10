#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

//global variable for the pipe
int port[2];

void *sum(void *thread_id)
{
    //initialize variables to store X and Y
    int X = 1, Y = 2, S;

    //read X and Y from the pipe
    read(port[0], (&X, &Y), sizeof(int) * 2);

    printf("Thread (%d) reads X = %d and Y = %d from the pipe\n", thread_id, X, Y);

    //write X + Y to the pipe
    S = X + Y;
    write(port[1], &S, sizeof(int)); // writing twice
    printf("Thread (%d) writes X + Y = %d to the pipe\n", thread_id, S);

    return 0;
}

void *odd_even(void *thread_id)
{

    int S;

    //read S from the pipe
    read(port[0], &S, sizeof(int));
    printf("Thread (%d) reads X + Y = %d from the pipe\n", thread_id, S);



    //determine if odd or even
    if (S % 2 == 0)
    {
        printf("Thread (%d) identifies X + Y = %d as an even number\n", thread_id, S);
    }
    else
    {
        printf("Thread (%d) identifies X + Y = %d as an odd number\n", thread_id, S);
    }
    
    printf("Thread (%d) writes X + Y = %d to the pipe\n", thread_id, S);
    write(port[1], &S, sizeof(int));
    
    return 0;
}

void *digit_count(void *thread_id)
{
    int S, digit_count = 0, S_copy;

    //read S from the pipe
    read(port[0], &S, sizeof(int));
    printf("Thread (%d) reads X + Y = %d from the pipe\n", thread_id, S);


    S_copy = S;
    do
    {

        S_copy = S_copy / 10;
        digit_count++;

    } while (S_copy != 0);

    printf("Thread (%d) identifies X + Y = %d as a %d digit number\n", thread_id, S, digit_count);

    return 0;
}

int port[2];

int main(int argc, char **argv)
{

    //take in the parameters from the user
    int X = atoi(argv[1]);
    int Y = atoi(argv[2]);

    printf("Parent (%d) receives X = %d and Y = %d from the user\n", getpid(), X, Y);


    //create the pipe
    int status;
    status = pipe(port);


    //write to the port
    write(port[1], (&X, &Y), sizeof(int) * 2);

    printf("Parent (%d) writes X = %d and Y = %d to the pipe\n", getpid(), X, Y);

    //initialize and create the threads
    pthread_t thread_1, thread_2, thread_3;

    //define thread ids
    int thread_id_1 = 100, thread_id_2 = 101, thread_id_3 = 102;



    //create and run each thread

    pthread_create(&thread_1, NULL, sum, thread_id_1); //thread 100
    pthread_join(thread_1, NULL);


    pthread_create(&thread_2, NULL, odd_even, thread_id_2); //thread 101
    pthread_join(thread_2, NULL);


    pthread_create(&thread_3, NULL, digit_count, thread_id_3); //thread 102
    pthread_join(thread_3, NULL);

    return 1;
}
