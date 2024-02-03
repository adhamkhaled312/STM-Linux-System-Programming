#include <stdio.h>
#include <unistd.h>

#define MAX_SIZE 200
#define RET_STAT 0
int main()
{
    //Define string to save the pathname 
    unsigned char buf[MAX_SIZE];

    //define string for the return value
    //in case of failure will contain NULL
    unsigned char *ret;

    //get Pathname using getcwd
    ret= getcwd(buf,MAX_SIZE);

    //if NULL there is an error in getting pathname (buffer size should increase)
    if(!ret){
        printf("Couldn't get pathname\n");
   	return -1;
    }
    //if not NULL then print the pathname
    else{
    	printf("%s\n",buf);
    }
    return RET_STAT;

}
