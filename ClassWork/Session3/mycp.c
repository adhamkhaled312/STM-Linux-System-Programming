#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
        

#define RET_STAT  0
#define FD_STD_OP 1
int main(int argc,char *argv[])
{
    int fd_read,fd_write, num_read, num_write;
    unsigned char buf[100];
    if(argc!=3){
    	printf(">>Couldn't open, Invalid number of arguments\n");
    }
    fd_read = open(argv[1], O_RDONLY);
    fd_write = open(argv[2],O_CREAT | O_RDWR | O_TRUNC,0644);
    if (fd_read <0||fd_write<0) {
	printf(">>Could't open as fd is wrong\n");
	printf("%i %i",fd_read,fd_write);
	return -1;
    }

    while ((num_read = read(fd_read, buf, 100)) != 0) {
	if (num_read < 0) {
	    printf(">>Could't read to the file\n");
	    return -1;
	}
	num_write = write(fd_write, buf, num_read);
	if (num_write < 0) {
	    printf(">>Could't write to the file\n");
	    return -1;
	}
    }
    close(fd_read);
    close(fd_write);
    return RET_STAT;

}
