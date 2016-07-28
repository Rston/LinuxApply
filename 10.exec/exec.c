/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：待定
 * 功能：实例演示exec函数族的用法。	
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t pid = -1;
	
	pid = fork();
	
	if (pid > 0)
	{	// 父进程入口
		printf("parent ID is %d.\n", getpid());	
	}
	else if (0 == pid)
	{	// 子进程入口
		
#if 0	// 使用execl/execv函数运行ls-la程序
		execl("/bin/ls", "ls", "-l", "-a", NULL);	
#elif 0
		char *const arg[] = {"ls", "-l", "-a", NULL};
		execv("/bin/ls", arg);
#endif	
		
#if 0	// 使用execl/execv函数运行自己写的app程序
		execl("./app", "./app", "argv[1]", "argv[2]", NULL);	
#elif 0
		char *const arg[] = {"./app", "argv[1]", "argv[2]", NULL};
		execv("./app", arg);
#endif

#if 0	// 使用execlp/execvp函数运行ls-la程序
		execlp("ls", "ls", "-l", "-a", NULL);	
#elif 0
		char *const arg[] = {"ls", "-l", "-a", NULL};
		execvp("ls", arg);
#endif

#if 0	// 使用execlp/execvp函数运行自己写的app程序
		execlp("app", "./app", "argv[1]", "argv[2]", NULL);	
#elif 0
		char *const arg[] = {"./app", "argv[1]", "argv[2]", NULL};
		execvp("app", arg);
#endif

#if 0	// 使用execle/execve函数运行自己写的app程序
		char *const envp[] = {"AA=env[0]", "BB=env[1]", NULL};
		execle("./app", "./app", "argv[1]", "argv[2]", NULL, envp);
#elif 1
		char *const arg[] = {"./app", "argv[1]", "argv[2]", NULL};
		char *const env[] = {"AA=env[0]", "BB=env[1]", NULL};
		execvpe("./app", arg, env);
#endif

		exit(0);
	}
	else if (pid < 0)
	{
		perror("fork error");
		exit(-1);
	}
	
	return 0;
}