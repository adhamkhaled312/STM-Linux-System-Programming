#include <stdio.h>
#include <unistd.h>

#define MAX_SIZE 100
#define RET_STAT 0
int main()
{
    unsigned char buf[MAX_SIZE];
    unsigned char *ret;
    ret= getcwd(buf,MAX_SIZE);
    if(!ret){
        printf("Couldn't get pathname\n");
    }
    else{
    	printf("%s\n",buf);
    }
    return RET_STAT;

}
