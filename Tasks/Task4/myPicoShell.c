#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

//extern char **environ;

// Define a macro for maximum number of arguments
#define ARG_MAX 20

int args_number(char *input);
int main()
{
    // Declare a character array to store user input
    char *input = NULL;
    size_t n = 0;
    // Save a copy of input
    char *copy;
    // to determine number of arguments 
    int args_count;
    while (1) {
	// Prompt the user to type something
	printf("Type anything > ");

	// Read input from the user using getline
	int size = getline(&input, &n, stdin);
	// Remove the trailing newline character
	input[size - 1] = '\0';
	// Handling the input as newline
	if (0 == strlen(input)) {
	    continue;
	}
	copy = strdup(input);
	args_count = args_number(copy);

	/*
	 * This part is for parsing the command and dividing it into arguments
	 * dynamic allocation is used to be flexible with number of arguments
	 * */
	char **args;		// array to save arguments of the command 
	char *token;	   //String to determine each token
	args = (char **) malloc((args_count+1) * sizeof(char *)); // allocate 2d array in memory with size args_count +1
	int i = 0;
	//save each token in the array of args
	token = strtok(input, " ");
	args[i]=strdup(token);
	while (i < args_count-1 && token != NULL) {
	    i++;
	    token = strtok(NULL, " ");
	    args[i]=strdup(token);
	    
	}
	//NULL in the last index of array (needed for exec function)
	args[args_count]=NULL;
	/********************************************************************/
 
	char ret;		// to check for the success of operations
	if (!strcmp(args[0], "pwd")) {
	    //Define string to save the pathname 
	    unsigned char buf[200];
	    //define string for the return value
	    //in case of failure will contain NULL
	    unsigned char *ret;
	    //get Pathname using getcwd
	    ret = getcwd(buf, sizeof(buf));
	    //if NULL there is an error in getting pathname (buffer size should increase)
	    if (!ret) {
		printf("Couldn't get pathname\n");
	    }
	    //if not NULL then print the pathname
	    else {
		printf("%s\n", buf);
	    }
	    // check if current command is cd
	} else if (!strcmp("cd", args[0])) {
	    //go to the path using chdir
	    ret = chdir(args[1]);
	    //check for successful changing 
	    if (ret != 0) {
		printf("Cannot change directory\n");
	    }
	    // check if current command is echo
	} else if (!strcmp("echo", args[0])) {
	    int i = 1;
	    // Print the arguments starting from args[1] separated by space
	    for (i;i<args_count; i++) {
		printf("%s ", args[i]);
	    }
	    // Print new line after finishing
	    printf("\n");
	}
	//check if command is exit, get out of the shell
	else if (!strcmp("exit", args[0])) {
	    printf("Good Bye :)\n");
	    break;
	    //if the command is not supported then execute it's external program
	} else {
	    // fork to create new process for the external program
	    pid_t returned_pid = fork();

	    //in case of parent process wait for the child process to finish
	    if (returned_pid > 0) {
		int wstatus;
		pid_t wait_pid = wait(&wstatus);
		if (wait_pid == -1) {
		    printf("Failed to wait the new process to finish\n");
		}
	    }
	    //in case of child process , execute the process from external program
	    else if (returned_pid == 0) {
		execvp(args[0], args);

		// in case of failure print error message and exit the process to return to the parent
		printf("Please enter a valid command\n");
		int exit_stat;
		exit(exit_stat);
	    } else {
		printf
		    ("Failed to create new process for the external program\n");
	    }
	}
	// Free all dynamically allocated memory
	free(input);
	input = NULL;
	free(copy);
	copy = NULL;
        for(int i=1;i<=args_count;i++){
	    free(args[i]);
	}
	free(args);
    }
    return 0;
}
/*
 * Function to determine number of arguments in command
 * input: the command string
 * retVal: return number of arguments
 */
int args_number(char *input)
{
    char *token;
    int number_arguments = 0;
    token = strtok(input, " ");
    while (token != NULL) {
	token = strtok(NULL, " ");
	number_arguments++;
    }
    return number_arguments;
}
