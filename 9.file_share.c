/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：fork函数和父子进程共享文件
 * 功能：演示父子进程共享文件。	
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PATHNAME "test.txt" 

int main(int argc, char **argv)
{
	int fd = -1;
	pid_t pid = -1;
	
#if 1
	// 子进程继承父进程中打开的文件
	// 打开test.txt文件，若该文件不存在则创建（权限666），若该文件存在则截断
	fd = open(PATHNAME,  O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror("open error");
		exit(-1);
	}	
	
	pid = fork();
	if (pid > 0)
	{	// 父进程入口
		printf("parent.\n");
		write(fd, "hello", strlen("hello"));
		sleep(1);	// 交出CPU控制权，让CPU调度子进程
	}
	else if (0 == pid)
	{
		// 子进程入口
		printf("child.\n");
		write(fd, "world", strlen("world"));
		sleep(1);	// 交出CPU控制权，让CPU调度父进程
	}
	else
	{
		perror("fork error");
		exit(-1);
	}
	close(fd);
#endif	
	
#if 0
	// 父子进程各自独立打开相同文件实现共享
	pid = fork();
	if (pid > 0)
	{	// 父进程入口
		#if 1
		fd = open(PATHNAME, O_RDWR);				// 分别写
		#endif
		#if 0
		fd = open(PATHNAME, O_RDWR | O_APPEND);		// 接续写
		#endif
		if (fd < 0)
		{
			perror("open error");
			exit(-1);
		}
		
		printf("parent.\n");
		write(fd, "hello", strlen("hello"));
		sleep(1);
	}
	else if (0 == pid)
	{
		// 子进程入口
		#if 1
		fd = open(PATHNAME, O_RDWR);				// 分别写
		#endif
		#if 0
		fd = open(PATHNAME, O_RDWR | O_APPEND);		// 接续写
		#endif
		if (fd < 0)
		{
			perror("open error");
			exit(-1);
		}
		
		printf("child.\n");
		write(fd, "world", strlen("world"));
		sleep(1);	// 交出CPU控制权，让CPU调度父进程
	}
	else
	{
		perror("fork error");
		exit(-1);
	}
	close(fd);
#endif

	return 0;
}