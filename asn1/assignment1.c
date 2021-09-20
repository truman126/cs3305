#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define PATH "external_program.out"

//create parent
int main()
{

	//create child_1
	pid_t pid = fork();

	// printf("pid is %d", pid);

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
			// create child 2.1

			pid = fork();

			if (pid > 0)
			{
				printf("The fork as unsuccessful (3/3) \n");
			}
			//catches child_2.1
			else if (pid == 0)
			{

				// call_external_program(" for child_2.1");

				exit(1);
			}
			else if (pid > 0)
			{

				wait(NULL);

				exit(1);
			}
		}

		//wait for child_2 to terminate
		wait(NULL);

		//the parent process is ready to terminate
		// exit(1);
	}

	//catches child 1
	if (pid == 0)
	{
		printf("first child");
		char child_name[] = " for child_1";
		//convert pid to a string
		pid_t current_pid = getpid();
		// ex. 34567 for child_2.1
		char arg[40];

		sprintf(arg, "%d", current_pid);

		strcat(arg, child_name);

		printf("\nstring:%s\n",arg);


		execl(PATH, arg, arg );

		

		//call external_program.out /
		// exit(1);

	}

	// printf("process");

	return 0;
}
