#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
struct iovec
{
	void *iov_base;
	size_t iov_len;
};

ssize_t readv(int fd,const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

int main(int argc, char* argv[]) //5-2程序
{
	int fd;
	struct iovec iov[3];
	//struct stat myStruct; //First buffer
	int x; 			//Second buffer
#define STR_SIZE 100
	char str[STR_SIZE]; 	//Third buffer
	ssize_t numRead,totRequired;

	if(argc != 2 || strcmp(argv[1],"--help") == 0)
		printf("%s file\n",argv[0]);

	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
		printf("open");

	totRequired = 0;

	iov[0].iov_base = &x;
	iov[0].iov_len = sizeof(x);
	totRequired += iov[0].iov_len; //计算字符串的数量

	iov[1].iov_base = str;
	iov[1].iov_len = STR_SIZE;
	totRequired += iov[1].iov_len; //语义同上

	numRead = readv(fd,iov,3);
	if(numRead == -1)
		printf("readv");

	if(numRead < totRequired)
	printf("Read fewer bytes than requested\n");
	printf("total bytes requested: %ld; bytes readL %ld\n",(long) totRequired, (long)numRead);

	if(argv[2] != NULL){
		int fd1 = open(argv[2],O_CREAT|O_APPEND|O_RDWR, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
		if(fd == -1)
			printf("open failed\n");
		ssize_t written_size = writev(fd1,iov,3);
		if(written_size == -1 )
			printf("writev");
	
		printf("totoal bytes requested : %ld; bytes writeL %ld\n",(long)totRequired, (long)written_size);
	}
	exit(0);

}

ssize_t readv(int fd,const struct iovec *iov, int iovcnt)//如果iov_base过小,存在读不完文件的问题,这个问题以后改良.
{
	if(fd != -1)
	{
		//struct iovec *temp = (struct iovec*)malloc(sizeof(struct iovec) * iovcnt); //开iovcnt个空间
		ssize_t count = 0;
		for(int i = 0; i < iovcnt; i++)
		{
			ssize_t read_num = read(fd,iov[i].iov_base,iov[i].iov_len);
			count += read_num;
		}
		return count;

	}
	else
	{
		return -1;
	}


}

ssize_t writev(int fd, const struct iovec *iov, int iovcnt)
{
	if(fd != -1)
	{
		ssize_t count = 0;
		for(int i = 0; i< iovcnt;i++)
		{
			ssize_t written_num = write(fd,iov[i].iov_base,iov[i].iov_len);
			printf("%s %ld\n",(char*)iov[i].iov_base,sizeof(iov[i].iov_base));
			count+=written_num;
		}
		return count;

	}
	else
		return -1;
}
