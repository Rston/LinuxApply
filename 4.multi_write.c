/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：lseek函数及共享文件
 * 功能：1个进程重复打开同一个文件写入。
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
	
	// 若文件存在则原来的内容消失，若文件不存在则以权限666创建该文件
#if 0	
	fd1 = open("test.txt", O_RDWR | O_TRUNC | O_CREAT , 0666);				// 分别写
	fd2 = open("test.txt", O_RDWR | O_TRUNC | O_CREAT , 0666);
#else
	fd1 = open("test.txt", O_RDWR | O_TRUNC | O_CREAT | O_APPEND, 0666);	// 接续写
	fd2 = open("test.txt", O_RDWR | O_TRUNC | O_CREAT | O_APPEND, 0666);
#endif
	if ((-1 == fd1) || (-1 == fd2))				// 判断文件打开是否成功，也可这样写if (fd < 0)
	{
		perror("open file error");				// 通过perror捕捉errno错误信息并打印输出
		exit(-1);
	}

	while (1)
	{
		ret = write(fd1, "ab", 2);				// 写内容到文件中
		if (ret < 0)							// 判断内容是否成功写入文件
		{
			perror("write file errot");
			exit(-1);
		}
		else
		{
			printf("the content of write from fd1 is [%s].\n", "ab");
		}
		
		sleep(1);
		
		ret = write(fd2, "cd", 2);				// 写内容到文件中
		if (ret < 0)							// 判断内容是否成功写入文件
		{
			perror("write file errot");
			exit(-1);
		}
		else
		{
			printf("the content of write from fd2 is [%s].\n", "cd");
		}
	}
	
	close(fd1);									// 关闭文件
	close(fd2);

	exit(0);
}