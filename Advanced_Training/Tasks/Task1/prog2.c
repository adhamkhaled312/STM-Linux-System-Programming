#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <unistd.h>

int main() 
{
	int fd=open("test2",O_RDWR,0644);
	lseek(fd,100000,SEEK_END);
	write(fd,"qwertyuiop",10);
	close(fd);
	return 0;
}
