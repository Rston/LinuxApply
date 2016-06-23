/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：lseek函数及共享文件
 * 功能：1个进程重复打开同一个文件读取
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int fd1 = -1, fd2 = -1;						// fd即file descriptor，文件描述符 	
	int ret = -1;								// 用于接收read返回值，判断是否读文件成功
	char buf[100] = {0};						// 构建缓冲区存放从文件读出的内容
	
	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test.txt", O_RDONLY);
	if ((-1 == fd1) || (-1 == fd2))				// 判断文件打开是否成功，也可这样写if (fd < 0)
	{
		perror("open file error");				// 通过perror捕捉errno错误信息并打印输出
		exit(-1);
	}

	while (1)
	{
		memset(buf, 0, sizeof(buf));
		ret = read(fd1, buf, 2);				// 读取文件内容
		if (ret < 0)							// 判断读取文件是否成功
		{
			perror("read file error");
			exit(-1);
		}
		else
		{
			printf("the content of read from fd1 is [%s].\n", buf);
		}
		
		sleep(1);
		
		memset(buf, 0, sizeof(buf));
		ret = read(fd2, buf, 2);				// 读取文件内容
		if (ret < 0)							// 判断读取文件是否成功
		{
			perror("read file error");
			exit(-1);
		}
		else
		{
			printf("the content of read from fd2 is [%s].\n", buf);
		}
	}
	
	close(fd1);									// 关闭文件
	close(fd2);

	exit(0);
}