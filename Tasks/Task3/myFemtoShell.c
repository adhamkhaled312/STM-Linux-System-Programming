#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Define a macro constant representing the maximum length of input string
#define MAX 100
// Define a macro for maximum number of arguments
#define ARG_MAX 20

void parse(char *input, char *args[]);
int main()
{
    // Declare a character array to store user input
    char input[MAX];

    while (1) {
	// Prompt the user to type something
	printf("Type anything > ");

	// Read input from the user using fgets 
	fgets(input, MAX, stdin);

	// Remove the trailing newline character
	input[strcspn(input, "\n")] = '\0';
	// Handling the input as newline
	if (0 == strlen(input)) {
	    printf("Please enter valid command\n");
	    continue;
	}
	char *args[ARG_MAX];	// array to save arguments of the command 
	parse(input, args);	// parsing the command
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
	    for (i; args[i] != NULL; i++) {
		printf("%s ", args[i]);
	    }
	    // Print new line after finishing
	    printf("\n");
	}
	//check if command is exit, get out of the shell
	else if (!strcmp("exit", args[0])) {
	    printf("Good Bye :)\n");
	    break;
	    //if the command is not supported print error message
	} else {
	    printf("Unsupported command\n");
	}
    }

    return 0;
}

/**
 * Function to parse the command into arguments
 * input: the command input string
 * args: array of strings to save the arguments
 */
void parse(char *input, char *args[])
{
    int i = 0;
    args[i] = strtok(input, " ");
    while (i < ARG_MAX && args[i] != NULL) {
	i++;
	args[i] = strtok(NULL, " ");
    }
    return;
}
