/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：tcp协议和socket编程
 * 功能：演示简单的socket客户端程序。
 */
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "datapack.h"

#define SERADDR		"192.168.2.51"			// 服务器开放给我们的IP地址
#define SERPORT		9003					// 服务器开放给我们的端口号

char databuf[100];							// 数据缓冲区
info student;								// 学生信息数据包

int main(int argc, char **argv)
{
	int sockfd = -1, ret = -1;
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
	
	// 调用connect链接服务器
	seraddr.sin_family = AF_INET;					// 设置地址族为IPv4
	seraddr.sin_port = htons(SERPORT);				// 设置地址的端口号信息
	seraddr.sin_addr.s_addr = inet_addr(SERADDR);	// 设置IP地址
	ret = connect(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
	if (-1 == ret)
	{
		perror("connect error");
		exit(-1);
	}
	printf("connect success, the fd is = %d.\n", ret);
	
#if 0
	// 客户端反复给服务器发数据
	while (1)
	{
		printf("please input the coment of send data.\n");
		gets(databuf);
		
		ret = send(sockfd, &databuf, strlen(databuf), 0);
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
	
#if 0
	// 客户端反复接收服务器数据
	while (1)
	{
		ret = recv(sockfd, &databuf, sizeof(databuf), 0);
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

#if 1
	// TCP连接建立后通过应用层协议来实现业务逻辑
	while (1)
	{
		// 客户端发送请求到服务器
		printf("please input the name.\n");
		scanf("%s", student.name);
		printf("please input the age.\n");
		scanf("%d", &student.age);
		student.cmd = CMD_REGISTER;
		ret = send(sockfd, &student, sizeof(student), 0);
		if (-1 == ret)
		{
			perror("send error");
			exit(-1);
		}
		
		// 客户端接收服务器的回复
		memset(&student, 0, sizeof(student));
		ret = recv(sockfd, &student, sizeof(student), 0);
		if (-1 == ret)
		{
			perror("recv error");
			exit(-1);
		}
		
		// 客户端解析服务器的回复，再做下1步定夺
		if (student.stat == STAT_OK)
		{
			printf("register news success.\n");
		}
		else
		{
			printf("register news error.\n");
		}
	}
#endif
	return 0;
}