/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：高级IO和多线程和线程同步
 * 功能：多进程+多线程。
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#if 1
void *pthread_func(void *arg)
{
	char buf[1024];
	// 分支任务，读取键盘设备文件
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		printf("before read keyboard.\n");
		read(0, buf, 8);
		printf("The coment of read keyboard is [%s].\n", buf);
	}
}
#endif

int main(int argc, char **argv)
{
	int fd = -1;
	pid_t ret = -1;
	char buf[1024];
	pthread_t th = -1;

// 通过多进程技术同时读取键盘设备文件和鼠标设备文件
#if 0	
	ret = fork();
	if (ret > 0)
	{
		// 父进程，读取键盘设备文件
		while (1)
		{
			memset(buf, 0, sizeof(buf));
			printf("before read keyboard.\n");
			read(0, buf, 8);
			printf("The coment of read keyboard is [%s].\n", buf);
		}
	}
	else if (0 == ret)
	{
		// 子进程，读取鼠标设备文件
		fd = open("/dev/input/mouse0", O_RDONLY);
		if (fd < 0)
		{
			perror("open error");
			exit(-1);
		}
		while (1)
		{
			memset(buf, 0, sizeof(buf));
			printf("before read mouse.\n");
			read(fd, buf, 8);
			printf("The coment of read mouse is [%s].\n", buf);
		}
	}
	else
	{
		perror("fork error");
		exit(-1);
	}
#endif

// 通过多线程技术同时读取键盘设备文件和鼠标设备文件
// gcc 13.keyboard_mouse_thread.c -pthread
#if 1
	// 创建线程读取键盘设备文件
	ret = pthread_create(&th, NULL, pthread_func, NULL);
	if (0 != ret)
	{
		printf("pthread_create error.\n");
		return -1;
	}
	
	// 因为子线程是while(1)死循环，则其可被主线程分离，分离后主线程不必要再去回收子线程
	ret = pthread_detach(th);
	if (0 != ret)
	{
		printf("pthread_detach error.\n");
		return -1;
	}
	
	// 主任务，读取鼠标设备文件
	fd = open("/dev/input/mouse0", O_RDONLY);
	if (fd < 0)
	{
		perror("open error");
		return -1;
	}
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		printf("before read mouse.\n");
		read(fd, buf, 8);
		printf("The coment of read mouse is [%s].\n", buf);
	}
#endif
	return 0;
}