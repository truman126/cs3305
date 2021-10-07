#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

//create parent

int main(int argc, char **argv)
{
    //initialize strings
    char X[strlen(argv[1]) + strlen(argv[3]) + strlen(argv[2]) + 5]; //Z'
    char Y[strlen(argv[2]) + strlen(argv[3]) + 4]; //Y
    char Z[strlen(argv[3]) + 1]; //Z

    


    int port[2];
    int status;

    status = pipe(port);

    //to catch the pipe if it fails
    if (pipe(port) < 0)
    {
        printf("Pipe error!\nAborting...\n");
        return -1;
    }

    //create child_1
    pid_t pid = fork();

    //catches the parent
    if (pid > 0)
    {


        //parent takes in first argument as X
        strcpy(X, argv[1]);
        printf("Parent (%d) receives X = \"%s\" from the user\n", getpid(), X);

        //writing X to the port
        write(port[1], X, sizeof(X));
        printf("Parent (%d) writes X = \"%s\" to the pipe\n", getpid(), X);

        wait(NULL); //waits for the child process to finish before resuming

        //read Z' from the port
        read(port[0], X, sizeof(X));
        printf("Parent (%d) reads X = \"%s\" from the pipe\n", getpid(), X);

    }



    //catches the child
    else if (pid == 0)
    {

        printf("Parent (%d) created a child (%d)\n", getppid(), getpid());


        //child 1 will take in the second and third args as Y and Z resp.

        strcpy(Y, argv[2]);
        strcpy(Z, argv[3]);

        printf("Child (%d) receives Y = \"%s\" and Z = \"%s\" from the user\n", getpid(), Y, Z);

        //concat the strings Y and Z to create Y'
        strcat(Y, " ");
        strcat(Y,Z);
        printf("Child (%d) receives concatenates Y and Z to genertate Y' = \"%s\"\n", getpid(), Y);



        //read from the pipe      
        read(port[0], X, sizeof(X));
        printf("Child (%d) reads X = \"%s\" from the pipe\n", getpid(), X);


         //concat the strings X and Y' to create Z'
        strcat(X, " ");
        strcat(X,Y);
        printf("Child (%d) receives concatenates X and Y to genertate Z' = \"%s\"\n", getpid(), X);

        //writing to the port
        write(port[1], X, sizeof(X));
        printf("Child (%d) writes Z' = \"%s\" to the pipe\n", getpid(), X);


    }

    //fork failed
    else if (pid < 0)
    {
        printf("The fork was unsuccessful!\n");
    }
}