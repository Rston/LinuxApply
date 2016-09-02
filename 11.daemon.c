/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：进程关系和进程间通信
 * 功能：创建守护进程。	
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 函数声明
void CreatDaemon(void);

int main(int argc, char **argv)
{
	CreatDaemon();
	
	while (1)
	{
		printf("I am running.\n");
		sleep(1);
	}
	
	return 0;
}

// 把调用该函数的进程变成1个守护进程
void CreatDaemon(void)
{
	pid_t pid = -1;
	
	pid = fork();
	
	if (pid > 0)
	{
		exit(0);		// 父进程直接退出
	}
	else if (0 == pid)
	{
		// setsid将当前进程设置为1个新的会话期session，即将当前进程脱离控制台
		pid = setsid();
		if (pid < 0)
		{
			perror("setsid error");
			exit(-1);
		}

		// 将当前进程工作目录设置为根目录
		chdir("/");
		
		// umask设置为0确保将来进程有最大的文件操作权限
		umask(0);
		
		// 关闭所有文件描述符
		// 获取当前系统中所允许打开的最大文件描述符数目
		int cnt = sysconf(_SC_OPEN_MAX);
		int i = 0;
		for (i=0; i<cnt; i++)
		{
			close(i);
		}
		
		// 将0、1、2定位到/dev/null回收站
		open("/dev/null", O_RDWR);
		open("/dev/null", O_RDWR);
		open("/dev/null", O_RDWR);
	}
	else 	
	{
		perror("fork error");
		exit(-1);
	}
}