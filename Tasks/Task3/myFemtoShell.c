#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Define a macro constant representing the maximum length of input string
#define MAX 100

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
	if(0==strlen(input)){
	    printf("Please enter valid command\n");
	    continue;
	}
	char *token;		//to save current token
	char ret;		// to check for the success of operations
	token = strtok(input, " ");
	//check if current command is pwd
	if (!strcmp(token, "pwd")) {
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
	} else if (!strcmp("cd", token)) {
	    //get the path
	    token = strtok(NULL, " ");
	    //go to the path using chdir
	    ret = chdir(token);
	    //check for successful changing 
	    if (ret != 0) {
		printf("Cannot change directory\n");
	    }
	    // check if current command is echo
	} else if (!strcmp("echo", token)) {
	    //print or upcoming tokens (strings), only print if not null
	    while (token != NULL) {
		token = strtok(NULL, " ");
		if (token) {
		    printf("%s ", token);
		}
	    }
	    //print new line after finishing 
	    printf("\n");
	}
	//check if command is exit, get out of the shell
	else if (!strcmp("exit", token)) {
	    printf("Good Bye :)\n");
	    break;
	    //if the command is not supported print error message
	} else {
	    printf("Unsupported command\n");
	}
    }

    return 0;
}
