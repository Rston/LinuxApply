/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：高级IO和多线程和线程同步
 * 功能：阻塞式IO+非阻塞式IO+多路复用IO+异步IO。
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/select.h>      
#include <sys/time.h>
#include <poll.h>
#include <signal.h>

typedef void (*sighandler_t)(int);
int mousefd = -1;

#if 1
//  SIGIO信号捕获函数
void signal_func(int sig)
{
	char buf[1024] = {0};
	int ret = -1;
	
	if (sig != SIGIO)
		return;
	
	ret = read(mousefd, buf, 8);
	if (ret > 0)
	{
		printf("The coment of read mouse is [%s].\n", buf);
	}
}
#endif

int main(int argc, char **argv)
{
	int fd = -1, ret = -1, flag = -1, i = 0;
	char buf[1024];
	fd_set rfds;
    struct timeval tv;
	struct pollfd pfds[2] = {0};

// 同时读取键盘设备文件和鼠标设备文件演示阻塞式IO的困境
#if 0	
	// 读取鼠标设备文件
	fd = open("/dev/input/mouse0", O_RDONLY);
	if (fd < 0)
	{
		perror("open error");
		exit(-1);
	}
	memset(buf, 0, sizeof(buf));
	printf("before read mouse.\n");
	read(fd, buf, 8);
	printf("The coment of read mouse is [%s].\n", buf);
	
	// 读取键盘设备文件
	memset(buf, 0, sizeof(buf));
	printf("before read keyboard.\n");
	read(0, buf, 8);
	printf("The coment of read keyboard is [%s].\n", buf);
#endif

// 同时读取键盘设备文件和鼠标设备文件演示非阻塞式IO解决方案	
#if 0
	
	// 以非阻塞的方式打开mouse设备文件
	fd = open("/dev/input/mouse0", O_RDONLY | O_NONBLOCK);
	if (fd < 0)
	{
		perror("open error");
		exit(-1);
	}
	
	// 把默认输入stdin变成非阻塞式的
	flag = fcntl(0, F_GETFL);		// 获取原来的Flag
	flag |= O_NONBLOCK;				// 添加非阻塞属性
	fcntl(0, F_SETFL, flag);		// 更新Flag
	
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		ret = read(fd, buf, 8);
		if (ret > 0)
		{
			printf("The coment of read mouse is [%s].\n", buf);
		}
		
		// 读取键盘设备文件
		memset(buf, 0, sizeof(buf));
		ret = read(0, buf, 8);
		if (ret > 0)
		{
			printf("The coment of read keyboard is [%s].\n", buf);
		}
	}
#endif

// 通过select函数实现IO多路复用同时读取键盘设备文件和鼠标设备文件
#if 0
	fd = open("/dev/input/mouse0", O_RDONLY);
	if (fd < 0)
	{
		perror("open error");
		exit(-1);
	}
	
	// 将fd和0两个文件添加到rfds中
	FD_ZERO(&rfds);
    FD_SET(0, &rfds);
	FD_SET(fd, &rfds);
	
	// 设置超时时间为5秒钟
	tv.tv_sec = 5;
    tv.tv_usec = 0;

	ret = select(fd+1, &rfds, NULL, NULL, &tv);
	if (ret < 0)
	{
		perror("select error");
		exit(-1);
	}
	else if (0 == ret)
	{
		printf("Time Out.\n");
	}
	else
	{
		// 检测到键盘输入
		if (FD_ISSET(0, &rfds))
		{
			memset(buf, 0, sizeof(buf));
			read(0, buf, 8);
			printf("The coment of read keyboard is [%s].\n", buf);
		}
		// 检测到鼠标输入
		if (FD_ISSET(fd, &rfds))
		{
			memset(buf, 0, sizeof(buf));
			read(fd, buf, 8);
			printf("The coment of read mouse is [%s].\n", buf);
		}
	}
#endif

// 通过poll函数实现IO多路复用同时读取键盘设备文件和鼠标设备文件
#if 0
	fd = open("/dev/input/mouse0", O_RDONLY);
	if (fd < 0)
	{
		perror("open error");
		exit(-1);
	}
	
	// 初始化pollfd
	pfds[0].fd = 0;				// 键盘
	pfds[0].events = POLLIN;	// 等待读操作
	pfds[1].fd = fd;			// 鼠标
	pfds[1].events = POLLIN;	// 等待读操作
	
	ret = poll(pfds, fd+1, 5000);
	if (ret < 0)
	{
		perror("poll error");
		exit(-1);
	}
	else if (0 == ret)
	{
		printf("Time Out.\n");
	}
	else
	{	
		// 检测到键盘输入或鼠标输入
		for (i=0; i<2; i++)
		{
			if (pfds[i].events == pfds[i].revents)
			{
				memset(buf, 0, sizeof(buf));
				if (0 == i)
				{
					read(0, buf, 8);
				}
				if (1 == i)
				{
					read(fd, buf, 8);
				}
				printf("The coment of read mouse/keyboard is [%s].\n", buf);
			}	
		}
	}
#endif

// 通过异步IO实现同时监测鼠标和键盘的输入
#if 1
	mousefd = open("/dev/input/mouse0", O_RDONLY);
	if (mousefd < 0)
	{
		perror("open error");
		exit(-1);
	}
	
	// 把鼠标的文件描述符设置为可以接受异步IO
	flag = fcntl(mousefd, F_GETFL);
	flag |= O_ASYNC;
	fcntl(mousefd, F_SETFL, flag);
	
	// 把异步IO事件的接收进程设置为当前进程
	fcntl(mousefd, F_SETOWN, getpid());
	
	// 注册当前进程的SIGIO信号捕获函数
	signal(SIGIO, signal_func);
	
	// 读取键盘设备文件
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		ret = read(0, buf, 8);
		if (ret > 0)
		{
			printf("The coment of read keyboard is [%s].\n", buf);
		}
	}
#endif	
	return 0;
}