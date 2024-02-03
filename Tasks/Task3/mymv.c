#include <stdio.h>
#include <stdlib.h>

#define RET_STAT  0

int main(int argc, char *argv[])
{
    //if number of arguments is wrong print error message
    if(argc!=3){
        printf("Usage: %s src dest\n",argv[0]);
        return -1;   
    }
    char *oldpath = argv[1]; //String to store old path
    char *newpath = argv[2]; //String to store new path
    
    //if ret==0:successful moving
    //if ret==-1:failed to move
    char ret;
    //Move using rename
    ret = rename(oldpath, newpath);
    // in case of failure print a message and return -1
    if (ret == -1) {
        printf("Cannot move the file\n");
	return -1;
    }
    
    //in case of successful moving print 0
    return RET_STAT;
}
