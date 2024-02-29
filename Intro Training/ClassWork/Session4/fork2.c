#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int x = 5;
int y;

//int main(int argc, char** argv)
int main(int argc, char *current_prog_argv[])
{
    printf("Num of args = %d\n", argc);

    int z = 10;
    for (int i = 0; i < argc; i++) {
	printf("argv[%d] = %s\n", i, current_prog_argv[i]);
    }

    getchar();

    printf("Before Fork: x= %d, y=%d, z=%d\n", x, y, z);
    x++;
    y++;
    z++;
    printf("Before Fork (edit): x= %d, y=%d, z=%d\n", x, y, z);

    pid_t returned_pid = fork();
    if (returned_pid > 0) {
	printf
	    ("PARENT: My PID = %d,  I have a new child and his PID = %d\n",
	     getpid(), returned_pid);
	printf("PARENT: x= %d, y=%d, z=%d\n", x, y, z);
	x++; y++; z++;
	printf("PARENT: x= %d, y=%d, z=%d\n", x, y, z);
	getchar();
    } else if (returned_pid == 0) {
	printf("CHILD: My PID = %d,  My parent PID = %d\n", getpid(),
	       getppid());
	printf("CHILD: x= %d, y=%d, z=%d\n", x, y, z);
	x++; y++; z++;
	x++; y++; z++;
	x++; y++; z++;
	printf("CHILD: x= %d, y=%d, z=%d\n", x, y, z);
	getchar();
    } else {
	printf("ERROR: I could not get a child\n");
    }
    return 0;
}
