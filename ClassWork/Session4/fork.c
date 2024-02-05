#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

//int main(int argc, char** argv)
int main(int argc, char* current_prog_argv[])
{
	printf("Num of args = %d\n", argc);

	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i, current_prog_argv[i]);
	}

	getchar();

	pid_t returned_pid = fork();
	if (returned_pid > 0)
	{
		printf("PARENT: My PID = %d,  I have a new child and his PID = %d\n", getpid(), returned_pid);
		getchar();
	}
	else if (returned_pid == 0)
	{
		printf("CHILD: My PID = %d,  My parent PID = %d\n", getpid(), getppid());
		getchar();
	}
	else
	{
		printf("ERROR: I could not get a child\n");
	}
	return 0;
}
