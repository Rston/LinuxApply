/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：dup和dup2和fcntrl及标准IO
 * 功能：使用fcntl模拟dup2。
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define PATHNAME "./test.txt"
 
int main(int argc, char **argv)
{
	int fd1 = -1, fd2 = -1;
	int ret = -1;
	
	// 若文件存在则截断，若不存在则创建
	fd1 = open(PATHNAME, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd1 < 0)
	{
		perror("open error");
		exit(-1);
	}
	printf("fd1 = %d.\n", fd1);
	
	fd2 = fcntl(fd1,  F_DUPFD, 20);		// fd2和fd1指向同一个文件，对应同一个文件指针
	printf("fd2 = %d.\n", fd2);
	
	// fcntl返回的fd和原来的oldfd同时向1个文件读/写时，结果是接续读/写
	while (1)
	{
		ret = write(fd1, "ab", 2);
		if (ret < 0)
		{
			perror("write error");
			exit(-1);
		}
		
		sleep(1);
		
		ret = write(fd2, "cd", 2);
		if (ret < 0)
		{
			perror("write error");
			exit(-1);
		}
	}
	
	close(fd1);
	close(fd2);
	exit(0);
}