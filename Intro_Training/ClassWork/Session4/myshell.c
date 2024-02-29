#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

//int main(int argc, char** argv)
int main(int argc, char *current_prog_argv[])
{
    printf("Num of args = %d\n", argc);

    for (int i = 0; i < argc; i++) {
	printf("argv[%d] = %s\n", i, current_prog_argv[i]);
    }

    getchar();

    char *cmd = NULL;
    size_t n = 0;
    while (1) {
	printf(">>>>>>> ");
	int size = getline(&cmd, &n, stdin);
	cmd[size - 1] = 0;
	if (strlen(cmd) == 0)
		continue;

	pid_t returned_pid = fork();
	if (returned_pid > 0) {
	    int wstatus;
	    printf
		("PARENT: My PID = %d,  I have a new child and his PID = %d\n",
		 getpid(), returned_pid);
	    wait(&wstatus);
	} else if (returned_pid == 0) {
	    printf("CHILD: My PID = %d,  My parent PID = %d\n", getpid(),
		   getppid());
	    getchar();

	    char *new_program_argv[] = { NULL };
	    char *new_program_envp[] = { NULL };

	    execve(cmd, new_program_argv, new_program_envp);

	    printf("I am not in the mode of execution. Exec failed\n");

	    return -1;
	} else {
	    printf("ERROR: I could not get a child\n");
	}

	free(cmd);
	cmd = NULL;
	n = 0;
    }
    return 0;
}
