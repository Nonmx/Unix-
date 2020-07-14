#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if(argc < 2)
		printf("atomic_append filename num-bytes [x]\n");
	else
	{
		ssize_t written_size;
		int num_of_bytes = atol(argv[2]);
		int fd = open(argv[1],O_CREAT|O_RDWR, S_IRUSR| S_IWUSR|S_IRGRP|S_IROTH);
		if(fd == -1)
			printf("open failed\n");
		if(argv[3]!=NULL)
		{
			if(lseek(fd,0,SEEK_END)== -1)
				printf("lseek failed\n");
			for(int i = 0; i< num_of_bytes;i++)
			{
				written_size = write(fd,"1",1);
				if(written_size != 1)
					printf("write failed\n");
			}

		}
		else
		{
			//获取flags
			int flags = fcntl(fd, F_GETFL);
			if(flags == -1)
				printf("get %d flags failed\n",fd);
			flags |= O_APPEND;
			if(fcntl(fd, F_SETFL,flags) == -1)
				printf("%d set new flag failed\n",fd);
			//一个一个的写入
			for(int i = 0; i < num_of_bytes;i++)
			{
				written_size = write(fd,"1",1);
				if(written_size != 1)
					printf("writen failed\n");
			}


		}
		close(fd);
		exit(0);
	}
}
