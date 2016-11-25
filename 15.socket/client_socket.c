/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��tcpЭ���socket���
 * ���ܣ���ʾ�򵥵�socket�ͻ��˳���
 */
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "datapack.h"

#define SERADDR		"192.168.2.51"			// ���������Ÿ����ǵ�IP��ַ
#define SERPORT		9003					// ���������Ÿ����ǵĶ˿ں�

char databuf[100];							// ���ݻ�����
info student;								// ѧ����Ϣ���ݰ�

int main(int argc, char **argv)
{
	int sockfd = -1, ret = -1;
	struct sockaddr_in seraddr = {0};
	struct sockaddr_in cliaddr = {0};
	
	// ����socket���ļ�������
	sockfd = socket(AF_INET, SOCK_STREAM, 0); // ��ַ��ΪIPv4����ʽsocket��ʹ��TCPЭ��
	if (-1 == sockfd)
	{
		perror("sockfd error");
		exit(-1);
	}
	printf("socket success, the sockfd = %d.\n", sockfd);
	
	// ����connect���ӷ�����
	seraddr.sin_family = AF_INET;					// ���õ�ַ��ΪIPv4
	seraddr.sin_port = htons(SERPORT);				// ���õ�ַ�Ķ˿ں���Ϣ
	seraddr.sin_addr.s_addr = inet_addr(SERADDR);	// ����IP��ַ
	ret = connect(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
	if (-1 == ret)
	{
		perror("connect error");
		exit(-1);
	}
	printf("connect success, the fd is = %d.\n", ret);
	
#if 0
	// �ͻ��˷�����������������
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
	// �ͻ��˷������շ���������
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
	// TCP���ӽ�����ͨ��Ӧ�ò�Э����ʵ��ҵ���߼�
	while (1)
	{
		// �ͻ��˷������󵽷�����
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
		
		// �ͻ��˽��շ������Ļظ�
		memset(&student, 0, sizeof(student));
		ret = recv(sockfd, &student, sizeof(student), 0);
		if (-1 == ret)
		{
			perror("recv error");
			exit(-1);
		}
		
		// �ͻ��˽����������Ļظ���������1������
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