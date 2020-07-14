#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
int main(int argc, char *argv[])
{
	if(argc != 4)
		printf("./run file_name seek_size inpuit\n");
	else
	{
		int fd = open(argv[1],O_APPEND|O_WRONLY,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		if(fd == -1)
			printf("open failed\n");
		off_t off = atoll(argv[2]);
		if(lseek(fd,off,SEEK_SET) == -1)
			printf("seek failed\n");
		ssize_t written_size = write(fd,argv[3],strlen(argv[3]));
		if(written_size != strlen(argv[3]))
			printf("write failed\n");

		exit(0);//success
	}
}

