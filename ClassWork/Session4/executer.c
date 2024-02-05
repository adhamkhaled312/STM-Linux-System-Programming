#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#if 0
       int execve(const char *pathname, char *const argv[],
                  char *const envp[]);
#endif

//int main(int argc, char** argv)
int main(int argc, char* current_prog_argv[])
{
	printf("Num of args = %d\n", argc);

	for (int i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i, current_prog_argv[i]);
	}

	char *new_program_argv[] = {NULL};
	char *new_program_envp[] = {NULL};

	getchar();
	execve(current_prog_argv[1], new_program_argv, new_program_envp);

	printf("I am not in the mode of execution. Exec failed\n");
	return 0;
}
