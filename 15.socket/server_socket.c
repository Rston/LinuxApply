/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��tcpЭ���socket���
 * ���ܣ���ʾ�򵥵�socket����������
 */
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include "datapack.h"

#define SERPORT		9003
#define SERADDR		"192.168.2.51"			// ��linux��ͨ��ifconfig����鿴
#define BACKLOG		100						// �ͻ����Ŷ���

char databuf[100];							// ���ݻ�����
info student;								// ѧ����Ϣ���ݰ�

int main(int argc, char **argv)
{
	int sockfd = -1, clifd = -1, ret = -1;
	socklen_t len = 0;
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

	// bind��sockefd�͵�ǰ���Ե�ip��ַ&�˿ں�
	seraddr.sin_family = AF_INET;					// ���õ�ַ��ΪIPv4
	seraddr.sin_port = htons(SERPORT);				// ���õ�ַ�Ķ˿ں���Ϣ
	seraddr.sin_addr.s_addr = inet_addr(SERADDR);	// ����IP��ַ
	ret = bind(sockfd, (const struct sockaddr *)&seraddr, sizeof(seraddr));
	if (-1 == ret)
	{
		perror("bind error");
		exit(-1);
	}
	printf("bind success.\n");
	
	// listen�����˿�
	ret = listen(sockfd, BACKLOG); // �����ȴ��ͻ��������ӷ�����
	if (-1 == ret)
	{
		perror("listen error");
		exit(-1);
	}
	printf("listen success.\n");
	
	// accept�����ȴ��ͻ��˽���
	clifd = accept(sockfd, (struct sockaddr *)&cliaddr, &len);
	if (-1 == clifd)
	{
		perror("accept error");
		exit(-1);
	}
	printf("connect success, the client fd = %d.\n", clifd);

#if 0
	// �������������տͻ��˷�����������
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
	// �������������ͻ��˷�����
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
	// TCP���ӽ�����ͨ��Ӧ�ò�Э����ʵ��ҵ���߼�
	while (1)
	{
		// ���������տͻ��˷��͵�����
		ret = recv(clifd, &student, sizeof(info), 0);
		if (-1 == ret)
		{
			perror("recv error");
			exit(-1);
		}
		
		// �����������ͻ������ݰ���Ȼ����ҵ��
		if (student.cmd == CMD_REGISTER)
		{
			// ������Ҫ����������ע�ᶯ����ͨ���ǲ������ݿ�1����Ϣ
			printf("The user will to register the news of student.\n");
			printf("The name of student is %s.\n", student.name);
			printf("The age of student is %d.\n", student.age);
			
			// �������ظ��ͻ������ݱ��������Ѿ�����OK
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