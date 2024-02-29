#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int args_number(char *input);
void parse(char *input, char ***args, int count, int *input_redir,
	   int *output_redir, int *error_redir);
void pwd(char **args, int output_redir);
void cd(char *path);
void echo(char **args, int output_redir);
void external(char **args, int input_redir, int output_redir,
	      int error_redir);

int main()
{
    // Declare a character array to store user input
    char *input = NULL;
    size_t n = 0;
    // Save a copy of input
    char *copy = NULL;


    // to determine number of arguments 
    int args_count = 0;
    while (1) {
	int input_redir = 0;
	int output_redir = 0;
	int error_redir = 0;
	// Prompt the user to type something
	printf("Type anything >> ");

	// Read input from the user using getline
	int size = getline(&input, &n, stdin);
	// Remove the trailing newline character
	input[size - 1] = '\0';
	// Handling the input as newline
	if (0 == strlen(input)) {
	    continue;
	}

	copy = strdup(input);	//make a copy of input command 
	args_count = args_number(copy);	// count number of arguments needed to be allocated
	char **args = NULL;
	parse(input, &args, args_count, &input_redir, &output_redir, &error_redir);	//parse the input command into arguments
	// The next part is for executing the commands
	// we have built in commands so we will check on them first, if not found in them then execute external command
	if (!strcmp(args[0], "pwd")) {
	    pwd(args, output_redir);
	}
	// check if current command is cd
	else if (!strcmp("cd", args[0])) {
	    cd(args[1]);
	}
	// check if current command is echo     
	else if (!strcmp("echo", args[0])) {
	    echo(args, output_redir);
	}
	//check if command is exit, get out of the shell
	else if (!strcmp("exit", args[0])) {
	    printf("Good Bye :)\n");
	    break;
	}
	//if the command is not supported then execute it's external program
	else {
	    external(args, input_redir, output_redir, error_redir);
	}

	// Free all dynamically allocated memory to avoid memory leaks
	free(input);
	input = NULL;
	free(copy);
	copy = NULL;
	int i = 0;
	for(i;i<args_count;i++){
	  free(args[i]);
      }
	free(args);

    }
    return 0;
}

/*
 * @brief determine number of arguments in command
 * @param input:  the command string
 * @return number of arguments
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

/*
 * @brief parsing the command and dividing it into arguments.
 * 	  dynamic allocation is used to be flexible with number of arguments.
 *	  parser also detect input/output redirections
 * @param input: The command string
 * @param args: Refrence to dynamic array of strings to save the arguments in
 * @param args count: The number of arguments
 **/
void parse(char *input, char ***args, int args_count, int *input_redir,
	   int *output_redir, int *error_redir)
{
    char *token;		//String to determine each token
    *args = (char **) malloc((args_count + 1) * sizeof(char *));	// allocate 2d array in memory with size args_count +1
    int i = 0;
    //save each token in the array of args
    token = strtok(input, " ");
    (*args)[i] = strdup(token);
    while (i < args_count - 1 && token != NULL) {
	token = strtok(NULL, " ");
	if (token == NULL)
	    break;
	//First check if there's redirection , save the index of it and don't store the symbol in args
	if (!strcmp("<", token)) {
	    token = strtok(NULL, " ");
	    *input_redir = i + 1;
	} else if (!strcmp(">", token)) {
	    token = strtok(NULL, " ");
	    *output_redir = i + 1;
	}

	else if (!strcmp("2<", token)) {
	    token = strtok(NULL, " ");
	    *error_redir = i + 1;
	}
	i++;
	(*args)[i] =strdup(token);

    }
    //NULL in the last index of array (needed for exec function)
    i++;
    (*args)[i] = NULL;
    return;

}

/*
 * @brief  execute built in pwd command
 * @param output_redirection: used to detec output redirection
 */
void pwd(char **args, int output_redir)
{

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
	if (output_redir > 0) {

	    int fd =
		open(args[output_redir], O_RDWR | O_CREAT | O_TRUNC, 0644);
	    if (fd != -1) {
		args[output_redir] = NULL;
		dprintf(fd, "%s\n", buf);
		close(fd);
	    }
	} else {
	    printf("%s\n", buf);
	}
    }
    return;
}

/*
 * @brief to execute built in echo command supporting output redirection
 * @param output_redir: used to detect if there is redirection
 * @param args: array of strings contains arguments
 */
void echo(char **args, int output_redir)
{
    //Check if there is output redirection
    if (output_redir > 0) {
	//if output redirection found, open the file needed and print the text in it using dprintf

	int fd =
	    open(args[output_redir], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd != -1) {
	    args[output_redir] = NULL;
	    int i = 1;
	    for (i; args[i] != NULL; i++) {
		dprintf(fd, "%s ", args[i]);
	    }
	    dprintf(fd, "\n");
	    close(fd);
	}
    }
    //If there is no output redirection then print the text on the screen as usual
    else {

	int i = 1;
	// Print the arguments starting from args[1] separated by space
	for (i; args[i] != NULL; i++) {
	    printf("%s ", args[i]);
	}
	// Print new line after finishing
	printf("\n");
    }
    return;
}

/*
 * @brief execute built in cd command
 * @param path: the directory path
 */
void cd(char *path)
{
    char ret;
    //go to the path using chdir
    ret = chdir(path);
    //check for successful changing 
    if (ret != 0) {
	printf("Cannot change directory\n");
    }
    return;
}

/*
 * @brief to execute external commands (which is not included in built in commands), Supports redirections
 * @param args: array of strings contains arguments of the command
 * @param input_redir: used to detect if there is input redirection
 * @param output_redir: used to detect if there is output redirection
 * @param error_redir: used to detect if there is error_redir 
 */
void external(char **args, int input_redir, int output_redir,
	      int error_redir)
{

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

	//first check if there is any redirection, if a redirection was found deal with it based on its type
	if (input_redir > 0) {
	    int fd = open(args[input_redir], O_RDONLY);
	    if (fd != -1) {
		close(0);
		dup2(fd, 0);
		close(fd);
		args[input_redir] = '\0';
	    }

	}if (output_redir > 0) {
	    int fd =
		open(args[output_redir], O_RDWR | O_CREAT | O_TRUNC, 0644);
	    if (fd != -1) {
		close(1);
		dup2(fd, 1);
		close(fd);
		args[output_redir] = '\0';
	    }
	}if (error_redir > 0) {

	    int fd =
		open(args[error_redir], O_RDWR | O_CREAT | O_TRUNC, 0644);
	    if (fd != -1) {
		close(2);
		dup2(fd, 2);
		close(fd);
		args[error_redir] = '\0';
	    }
	}
	execvp(args[0], args);
	// in case of failure print error message and exit the process to return to the parent
	printf("Please enter a valid command\n");
	int exit_stat;
	exit(exit_stat);
    } else {
	printf("Failed to create new process for the external program\n");
    }
    return;
}
