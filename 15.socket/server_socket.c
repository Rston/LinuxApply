/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：tcp协议和socket编程
 * 功能：演示简单的socket服务器程序。
 */
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include "datapack.h"

#define SERPORT		9003
#define SERADDR		"192.168.2.51"			// 在linux下通过ifconfig命令查看
#define BACKLOG		100						// 客户端排队数

char databuf[100];							// 数据缓冲区
info student;								// 学生信息数据包

int main(int argc, char **argv)
{
	int sockfd = -1, clifd = -1, ret = -1;
	socklen_t len = 0;
	struct sockaddr_in seraddr = {0};
	struct sockaddr_in cliaddr = {0};
	
	// 调用socket打开文件描述符
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // 地址族为IPv4；流式socket，使用TCP协议
	if (-1 == sockfd)
	{
		perror("sockfd error");
		exit(-1);
	}
	printf("socket success, the sockfd = %d.\n", sockfd);

	// bind绑定sockefd和当前电脑的ip地址&端口号
	seraddr.sin_family = AF_INET;					// 设置地址族为IPv4
	seraddr.sin_port = htons(SERPORT);				// 设置地址的端口号信息
	seraddr.sin_addr.s_addr = inet_addr(SERADDR);	// 设置IP地址
	ret = bind(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
	if (-1 == ret)
	{
		perror("bind error");
		exit(-1);
	}
	printf("bind success.\n");
	
	// listen监听端口
	ret = listen(sockfd, BACKLOG); // 阻塞等待客户端来连接服务器
	if (-1 == ret)
	{
		perror("listen error");
		exit(-1);
	}
	printf("listen success.\n");
	
	// accept阻塞等待客户端接入
	clifd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
	if (-1 == clifd)
	{
		perror("accept error");
		exit(-1);
	}
	printf("connect success, the client fd = %d.\n", clifd);

#if 0
	// 服务器反复接收客户端发过来的数据
	while (1)
	{
		ret = recv(clifd, &databuf, sizeof(databuf), 0);
		if (-1 == ret)
		{
			perror("recv error");
			exit(-1);
		}
		
		printf("The number of bytes recv is %d.\n", ret);
		printf("The monent of recv is %s.\n", databuf);
		
		memset(databuf, 0, sizeof(databuf));
	}
#endif

#if 0
	// 服务器反复给客户端发数据
	while (1)
	{
		printf("please input the coment of send data.\n");
		gets(databuf);
		
		ret = send(clifd, &databuf, strlen(databuf), 0);
		if (-1 == ret)
		{
			perror("send error");
			exit(-1);
		}
		
		printf("The number of bytes send is %d.\n", ret);
		printf("The monent of send is %s.\n", databuf);
		 
		memset(databuf, 0, sizeof(databuf));
	}
#endif

#if 1
	// TCP连接建立后通过应用层协议来实现业务逻辑
	while (1)
	{
		// 服务器接收客户端发送的请求
		ret = recv(clifd, &student, sizeof(info), 0);
		if (-1 == ret)
		{
			perror("recv error");
			exit(-1);
		}
		
		// 服务器解析客户端数据包，然后处理业务
		if (student.cmd == CMD_REGISTER)
		{
			// 服务器要进行真正的注册动作，通常是插入数据库1条信息
			printf("The user will to register the news of student.\n");
			printf("The name of student is %s.\n", student.name);
			printf("The age of student is %d.\n", student.age);
			
			// 服务器回复客户端数据表明请求已经处理OK
			student.stat = STAT_OK;
			ret = send(clifd, &student, sizeof(info), 0);
			if (-1 == ret)
			{
				perror("send error");
				exit(-1);
			}
		}
	}
#endif
	return 0;
}