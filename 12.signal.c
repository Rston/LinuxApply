/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：linux中的信号
 * 功能：演示signal函数的简单使用。
 */
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

typedef void (*sighandler_t)(int);

// ctrl+c信号捕捉函数
void signal_func(int sig)
{
	printf("I catch ctrl + c.\n");
}

int main(int argc, char **argv)
{
#if 1
	// 指定信号SIGINT为具体的signal_func处理函数
	sighandler_t ret = ((sighandler_t) -2);
	ret = signal(SIGINT, signal_func);
	if (SIG_ERR == ret)
	{
		perror("signal error");
		exit(-1);
	}
#endif

#if 0
	// 指定信号SIGINT为默认处理
	signal(SIGINT, SIG_DFL);			
#endif

#if 0	
	// 指定信号SIGINT为忽略处理
	signal(SIGINT, SIG_IGN);		
#endif	
	
	printf("before while(1).\n");
	while(1);
	printf("after while(1).\n");
	
	return 0;
}