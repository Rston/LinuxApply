/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：fork函数和父子进程共享文件
 * 功能：在程序中使用getpid和getppid获取进程ID。	
 */
 
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t id = -1;
	
	id = getpid();						// 获取当前进程的ID
	printf("getpid id = %d.\n", id);
	
	id = getppid();
	printf("getppid id = %d.\n", id);	// 获取当前进程的父进程的ID
	
	return 0;
}