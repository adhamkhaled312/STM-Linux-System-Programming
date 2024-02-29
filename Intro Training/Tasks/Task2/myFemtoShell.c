#include <stdio.h>
#include <string.h>

// Define a macro constant representing the maximum length of input string
#define MAX 100 

int main() {
    // Declare a character array to store user input
    char input[MAX]; 
    
    while (1) { 
        // Prompt the user to type something
        printf("Type anything > "); 

        // Read input from the user using fgets 
        fgets(input, MAX, stdin);

        // Remove the trailing newline character
        input[strcspn(input, "\n")] = '\0'; 

        // Compare the input string with "exit"
        char flag = strcmp("exit", input); 

        // If input is not "exit", print the input
        if (flag) { 
            printf("%s\n", input);
        } 
        // If input is "exit" print "Good Bye" and terminate
        else { 
            printf("Good Bye :)\n");
            break;
        }
    }
    return 0;
}
