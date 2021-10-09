#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <pthread.h>

void *sum(int port[])
{
    //initialize variables to store X and Y
    int X, Y, S;

    //read X and Y from the pipe
    read(port[0], &X, sizeof(int));
    read(port[0], &Y, sizeof(int));

    printf("Thread (%d) reads X = %d and Y = %d from the pipe\n", 100, X, Y);

    //write X + Y to the pipe
    S = X + Y;
    write(port[1], &S, sizeof(int)); // writing twice
    printf("Thread (%d) writes X + Y = %d to the pipe\n", 100, S);

    return 0;
}

void *odd_even(int port[])
{

    int S;

    //read S from the pipe
    read(port[0], &S, sizeof(int));

    if (S % 2 == 0)
    {
        printf("Thread (%d) identifies X + Y = %d as an even number\n", 101, S);
    }
    else
    {
        printf("Thread (%d) identifies X + Y = %d as an odd number\n", 101, S);
    }
    write(port[1], &S, sizeof(int));
    return 0;
}

void *digit_count(int port[])
{
    int S, digit_count = 0, S_copy;

    //read S from the pipe
    read(port[0], &S, sizeof(int));

    S_copy = S;
    do
    {

        S_copy = S_copy / 10;
        digit_count++;

    } while (S_copy != 0);

    printf("Thread (%d) identifies X + Y = %d as a %d digit number\n", 102, S,  digit_count);

    return 0;
}


int main(int argc, char **argv)
{

    //take in the parameters from the user
    int X = atoi(argv[1]);
    int Y = atoi(argv[2]);

    printf("Parent (%d) receives X = %d and Y = %d from the user\n", getpid(), X, Y);

    //create the pipe
    int status;
    int port[2];

    status = pipe(port);

    //write to the port
    printf("Parent (%d) writes X = %d and Y = %d to the pipe\n", getpid(), X, Y);
    write(port[1], &X, sizeof(int));
    write(port[1], &Y, sizeof(int));

    //initialize and create the threads
    pthread_t thread_1; //thread 100
    pthread_t thread_2; //thread 101
    pthread_t thread_3; //thread 102

    pthread_create(&thread_1, NULL, sum, port); //thread 100
    pthread_join(thread_1, NULL);

    pthread_create(&thread_2, NULL, odd_even, port); //thread 101
    pthread_join(thread_2, NULL);

    pthread_create(&thread_3, NULL, digit_count, port); //thread 102
    pthread_join(thread_3, NULL);

    return 1;
}
