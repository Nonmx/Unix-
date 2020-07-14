#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>


int DUP(int fd)
{
	if(fcntl(fd,F_GETFL) != -1)
		return fcntl(fd,F_DUPFD,fd+1);
	else
		return -1;
}

int DUP2(int oldfd, int new_fd)
{
	if(fcntl(oldfd,F_GETFL) != -1)//old 有效
	{
		if(fcntl(new_fd, F_GETFL) != -1)//new 有效
		{
			close(new_fd);
			return fcntl(oldfd, F_DUPFD,new_fd);
		}
		else
		{
			return fcntl(oldfd,F_DUPFD,new_fd);
		}

	}
	else
		return -1;
}

int is_same(int fd1, int fd2)
{
	int flags = fcntl(fd1, F_GETFL);
	int accmode = flags & O_ACCMODE;
	int FLAGS = fcntl(fd2, F_GETFL);
	int ACCMODE = FLAGS & O_ACCMODE;
	printf("%d: flags = %d\n%d: flags = %d\n",fd1,flags,fd2,FLAGS);
	if(accmode == ACCMODE)
		return 1;
	else
		return 0;
}

void is_share_seek(int fd, int fd2)
{
	off_t seek = lseek(fd,0,SEEK_CUR);
	off_t SEEK = lseek(fd2,0,SEEK_CUR);
	printf("fd%d : seek is %ld\nfd%d : seek is %ld\n",fd,seek,fd2,SEEK);
}

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("./run filname\n");
		return -1;
	}
	else
	{
		int fd = open(argv[1],O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		if(fd == -1)
			printf("open failed\n");
		int new_fd = DUP(fd);
		if((is_same(fd,new_fd)) == 1)
			printf("fd %d == new_fd %d\n",fd,new_fd);
		lseek(fd,3,SEEK_SET);
		int new_fdd = DUP2(fd,2);
		if((is_same(fd,new_fd)) == 1)
			printf("fd %d == new_fdd %d\n",fd,new_fdd);

		is_share_seek(fd,new_fd);
		is_share_seek(fd,new_fdd);

		close(fd);
		close(new_fd);
		close(new_fdd);
		exit(0);
		
	}
	return 0;
}

