/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：fork函数和父子进程共享文件
 * 功能：使用atexit函数注册进程终止处理函数。	
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 进程终止处理函数1
void exit_func1(void)
{
	printf("Is in exit_func1.\n");
}

// 进程终止处理函数2
void exit_func2(void)
{
	printf("Is in exit_func2.\n");
}

int main(int argc, char **argv)
{
	int ret = -1;
	
	printf("hello world.\n");
	
	ret = atexit(exit_func1);
	if (ret != 0)
	{
		printf("atexit exit_func1 error.\n");
		exit(-1);
	}
	
	ret = atexit(exit_func2);
	if (ret != 0)
	{
		printf("atexit exit_func2 error.\n");
		exit(-1);
	}
	
	printf("my name is Rston.\n");

#if 1	
	return 0;		// 终止进程时执行atexit注册的进程终止处理函数
#endif

#if 0
	exit(0);		// 终止进程时执行atexit注册的进程终止处理函数
#endif

#if 0
	_exit(0);		// 终止进程时并不执行atexit注册的进程终止处理函数
#endif
}