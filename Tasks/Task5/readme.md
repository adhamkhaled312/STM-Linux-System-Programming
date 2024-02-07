### Description
##### enhancing and cleaning myPicoShell and adding IO Feature
Pico shell supports:
- Built-in echo, pwd and cd, in addition to exit.
- IO redirection.
- Command line parsing to parse the command line entered by the user, divide it into arguments (the only supported separator is the space or multiple successive spaces). If the user entered any thing other than (echo, pwd, cd, exit) shell will execute the command using fork/exec system calls.
- executing the programs using their names directly without the need to enter the full path.
- Using dynamic allocation to be flexible with number of arguments and ensuring there is no memory leaks.

### How to Compile and Run
To compile the program, execute the following command:
```bash
gcc myPicoShell.c -o myPicoShell
./myPicoShell
```

### Sample output
This is an example for some tests on built-in command, external commands and IO redirection.
![Screenshot from 2024-02-07 18-42-57](https://github.com/adhamkhaled312/STM_System_Linux_Programming/assets/105177075/4d6793bb-af66-4d2f-ab0d-8841241daf09)
