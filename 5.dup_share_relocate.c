/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：dup和dup2和fcntrl及标准IO
 * 功能：使用dup实现文件共享和文件重定位
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
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
	
	close(1);					// 关闭标准输出1
	fd2 = dup(fd1);				// fd1和标准输出1共享同一个文件PATHNAME
	printf("fd2 = %d.\n", fd2);	// 在PATHNAME文件中查看该输出信息
	
	// dup返回的fd和原来的oldfd同时向1个文件读/写时，结果是接续读/写
	while (1)
	{
		ret = write(fd1, "ab.\n", 4);
		if (ret < 0)
		{
			perror("write error");
			exit(-1);
		}
		
		sleep(1);
		
		printf("cd.\n");
	}
	
	close(fd1);
	close(fd2);
	exit(0);
}