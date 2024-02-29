#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define RET_STAT  0
#define FD_STD_OP 1
int main(int argc,char *argv[])
{
    int fd, num_read, num_write;
    unsigned char buf[100];
    if(argc!=2){
    	printf("Couldn't open");
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
	printf(">>Could't open");
	return -1;
    }

    while ((num_read = read(fd, buf, 100)) != 0) {
	if (num_read < 0) {
	    printf(">>Could't open");
	    return -1;
	}
	num_write = write(FD_STD_OP, buf, num_read);
	if (num_write < 0) {
	    printf(">>Could't open");
	    return -1;
	}
    }
    close(fd);
    return RET_STAT;

}
