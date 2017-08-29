#include <stdio.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
	int task;
	printf("The input have : %d \n", argc);
	if (argc < 2)
	{
		printf("Error: missing argument\\n");
		return 1;
	}
	//note that argv[0] is the name of yoru executable 
	// e.g . a.out, and the fiirst argument to your program 
	// is stored in argv[1]
	task = atoi(argv[1]);

	switch (task) 
	{
		case 1:
		//call the function(s) responsible for task 1 here
		break;

		case 2:
		//call the functions responsible for task 2 here
		break;

		case 3:
		//call the functions responsible for task 3 here 
		break;

		default:
			printf("Error: unrecognized task number %d\n", task);
			break;
	}
	return 0; 
}