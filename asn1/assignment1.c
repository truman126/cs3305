#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//create parent
int main(){

	//create child_1
	pid_t pid = fork();
	
	if (pid <0) // fork unsuccessful
	{
		printf("fork unsuccessful");
		exit(1);
	}
	
	if (pid>0) //parent
	{
		//make it waiti
		
		wait(NULL);

		//create child_2
		pid = fork();

		excel()



	}

	if (pid==0) //child
	{

		//call external_program.out

	}

printf("id: %d ", pid);

}
