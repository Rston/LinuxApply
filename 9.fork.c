/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：fork函数和父子进程共享文件
 * 功能：使用fork函数创建子进程。	
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t ret = -1;
	
	ret = fork();
	
	if (0 == ret)
	{	// 子进程入口
		printf("my name is child.\n");
		printf("child pid = %d.\n", getpid());
	}
	
	if (ret > 0)
	{	// 父进程入口
		printf("my name is parent.\n");
		printf("parent pid = %d.\n", getpid());
	}
	
	if (ret < 0)
	{	// fork错误
		perror("fork error");
		exit(-1);
	}
	
	return 0;
}