#include <stdio.h>

int main(int argc, char **argv)
{

    // for (int i =0; i < argc; i++){
    //     printf("argv[%d]=%s\n",i , argv[i]);
    // }

    printf("From the external program: The PID was %s\n", argv[1]);
}
