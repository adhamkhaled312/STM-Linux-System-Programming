### Description

Our Femto Shell shall grow and will become a Pico Shell :D\
Pico shell supports:\
      - Built-in echo, pwd and cd, in addition to exit.\
      - Command line parsing to parse the command line entered by the user, divide it into arguments (the only supported separator is the space or multiple successive spaces). If the user entered any thing other than (echo, pwd, cd, exit) shell will execute the command using fork/exec system calls.\
       - executing the programs using their names directly without the need to enter the full path.\
       - Using dynamic allocation to be flexible with number of arguments and ensuring there is no memory leaks.
       
### How to Compile and Run
To compile the program, execute the following command:
```bash
gcc myPicoShell.c -o myPicoShell
./myPicoShell
```

### Sample output
![Screenshot from 2024-02-05 23-31-05](https://github.com/adhamkhaled312/STM_System_Linux_Programming/assets/105177075/6db50771-2205-4471-a690-71d918979578)


