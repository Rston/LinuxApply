/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：wait族函数和exec族函数
 * 功能：演示父进程调用wait或waitpid用于回收子进程。	
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	pid_t pid = -1, ret = -1;
	int status = -1;
	
	pid = fork();
	if (pid > 0)
	{	// 父进程入口
		printf("parent ID is %d.\n", getpid());
#if 0	
		ret = wait(&status);					// 调用wait函数阻塞用于回收子进程
#endif

#if 0
		ret = waitpid(-1, &status, 0);			// 使用waitpid实现wait效果
#endif

#if 0
		ret = waitpid(pid, &status, 0);			// 调用waitpid阻塞用于回收特定ID子进程
#endif	

#if 0
		sleep(1);								// 确保父进程慢于子进程消亡，保证回收子进程成功
		ret = waitpid(pid, &status,  WNOHANG);	// 非阻塞式回收子进程
#endif

#if 2
		ret = waitpid(pid, &status,  WNOHANG);	// 父进程非阻塞式回收子进程但子进程尚未消亡的返回值。
#endif		
		printf("The Recover of process ID is %d.\n", ret);
		printf("Whether the child process exits normally %d.\n", WIFEXITED(status));
		printf("Child process is abnormal exit %d.\n", WIFSIGNALED(status));
		printf("Value Normal termination %d.\n", WEXITSTATUS(status));
	}
	else if (0 == pid)
	{	// 子进程入口
#if 2
		sleep(1);								// 父进程非阻塞式回收子进程但子进程尚未消亡的返回值。
#endif
		printf("child ID is %d.\n", getpid());
		printf("Now parent ID is %d.\n", getppid());
		exit(0);								// 正常退出子进程
	}
	else
	{
		perror("fork error");
		exit(-1);
	}

	return 0;
}