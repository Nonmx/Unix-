#define _LARGEFILE64_SOURCE
//#define __USE_FILE_OFFSET64
//#define __USR_LARGEFILE64

#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include "tlpi.hdr.h" //这个头文件书上有，但是懒得打了

int main(int argc, char *argv[])
{
	int fd;
	off_t off;
	if(argc != 3 || strcmp(argv[1],"--help") == 0)
		printf("%s pathname offset\n",argv[0]);
	fd = open(argv[1], O_RDWR|O_CREAT|O_LARGEFILE, S_IRUSR| S_IWUSR);
	if(fd == -1)
		exit(0);
	off = atoll(argv[2]);
	if(lseek(fd,off,SEEK_SET) == -1)
		exit(0);

	if(write(fd, "test", 4) == -1)
		exit(0);
	exit(0);
}

