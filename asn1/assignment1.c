#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define PATH "external_program.out"

//create parent
int main(int argc, char **argv)
{

	//create child_1
	pid_t pid = fork();

	if (pid < 0) // fork unsuccessful
	{
		printf("The fork as unsuccessful (1/3) \n");
	}

	if (pid > 0) //parent
	{



		//wait for child_1 to terminate
		wait(NULL);

		//create child_2

		pid = fork();

		//check if child 2 is successful
		if (pid < 0)
		{

			printf("The fork as unsuccessful (2/3) \n");

			// exit(1);
		}

		// catches child_2
		else if (pid == 0)
		{
			printf("parent(PID %d) created child_2(PID %d)\n", getppid(), getpid());

			// create child 2.1

			pid = fork();
			wait(NULL);

			if (pid > 0)
			{
				printf("The fork as unsuccessful (3/3) \n");
			}
			//catches child_2.1
			else if (pid == 0)
			{
				printf("child_2(PID %d) created child_2.1(PID %d)\n", getppid(), getpid());

				//

				char child_name[] = " for child_2.1";
				//convert pid to a string
				pid_t current_pid = getpid();
				// ex. 34567 for child_2.1
				char arg[21];

				sprintf(arg, "%d", current_pid);

				strcat(arg, child_name);

				printf("child_2.1 (PID %d) is calling an external program external_program.out and leaving parent\n", getpid());

				execl(argv[1], PATH, arg, NULL);

				// call_external_program(" for child_2.1");

				exit(1);
			}
			else if (pid > 0)
			{
				printf("child_2 (PID %d) is waiting for child_2.1 (PID %d) to complete before creating child_2\n", getppid(), getpid());

			}
			exit(1);
		}

		//wait for child_2 to terminate
		wait(NULL);

		printf("child_1 and child_2 are completed and parent process is terminating…\n");

		//the parent process is ready to terminate
		// exit(1);
	}

	//catches child 1
	if (pid == 0)
	{


		printf("parent(PID %d) created child_1(PID %d)\n", getppid(), getpid());
		printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", getppid(), getpid());


		char child_name[] = " for child_1";
		//convert pid to a string
		pid_t current_pid = getpid();
		// ex. 34567 for child_2.1
		char arg[40];

		sprintf(arg, "%d", current_pid);

		strcat(arg, child_name);

		printf("child_1 (PID %d) is calling an external program external_program.out and leaving parent\n", getpid());

				// execl(*argv, PATH, arg, (char*) NULL);

		exit(1);

		//call external_program.out /
		// exit(1);
	}

	// printf("process");



	return 0;
}
