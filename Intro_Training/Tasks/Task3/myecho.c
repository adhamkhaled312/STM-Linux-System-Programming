#include <stdio.h>

#define RET_STAT 0

int main(int argc, char *argv[])
{
    int i = 1;
    //print all arguments separated my one space
    for (i; i < argc; i++) {
	printf("%s ", argv[i]);
    }
    printf("\n"); //print new line after printing all arguments
    return RET_STAT;
}
