/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ���߼�IO�Ͷ��̺߳��߳�ͬ��
 * ���ܣ�����ʽIO+������ʽIO+��·����IO+�첽IO��
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
//  SIGIO�źŲ�����
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

// ͬʱ��ȡ�����豸�ļ�������豸�ļ���ʾ����ʽIO������
#if 0	
	// ��ȡ����豸�ļ�
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
	
	// ��ȡ�����豸�ļ�
	memset(buf, 0, sizeof(buf));
	printf("before read keyboard.\n");
	read(0, buf, 8);
	printf("The coment of read keyboard is [%s].\n", buf);
#endif

// ͬʱ��ȡ�����豸�ļ�������豸�ļ���ʾ������ʽIO�������	
#if 0
	
	// �Է������ķ�ʽ��mouse�豸�ļ�
	fd = open("/dev/input/mouse0", O_RDONLY | O_NONBLOCK);
	if (fd < 0)
	{
		perror("open error");
		exit(-1);
	}
	
	// ��Ĭ������stdin��ɷ�����ʽ��
	flag = fcntl(0, F_GETFL);		// ��ȡԭ����Flag
	flag |= O_NONBLOCK;				// ��ӷ���������
	fcntl(0, F_SETFL, flag);		// ����Flag
	
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		ret = read(fd, buf, 8);
		if (ret > 0)
		{
			printf("The coment of read mouse is [%s].\n", buf);
		}
		
		// ��ȡ�����豸�ļ�
		memset(buf, 0, sizeof(buf));
		ret = read(0, buf, 8);
		if (ret > 0)
		{
			printf("The coment of read keyboard is [%s].\n", buf);
		}
	}
#endif

// ͨ��select����ʵ��IO��·����ͬʱ��ȡ�����豸�ļ�������豸�ļ�
#if 0
	fd = open("/dev/input/mouse0", O_RDONLY);
	if (fd < 0)
	{
		perror("open error");
		exit(-1);
	}
	
	// ��fd��0�����ļ���ӵ�rfds��
	FD_ZERO(&rfds);
    FD_SET(0, &rfds);
	FD_SET(fd, &rfds);
	
	// ���ó�ʱʱ��Ϊ5����
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
		// ��⵽��������
		if (FD_ISSET(0, &rfds))
		{
			memset(buf, 0, sizeof(buf));
			read(0, buf, 8);
			printf("The coment of read keyboard is [%s].\n", buf);
		}
		// ��⵽�������
		if (FD_ISSET(fd, &rfds))
		{
			memset(buf, 0, sizeof(buf));
			read(fd, buf, 8);
			printf("The coment of read mouse is [%s].\n", buf);
		}
	}
#endif

// ͨ��poll����ʵ��IO��·����ͬʱ��ȡ�����豸�ļ�������豸�ļ�
#if 0
	fd = open("/dev/input/mouse0", O_RDONLY);
	if (fd < 0)
	{
		perror("open error");
		exit(-1);
	}
	
	// ��ʼ��pollfd
	pfds[0].fd = 0;				// ����
	pfds[0].events = POLLIN;	// �ȴ�������
	pfds[1].fd = fd;			// ���
	pfds[1].events = POLLIN;	// �ȴ�������
	
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
		// ��⵽����������������
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

// ͨ���첽IOʵ��ͬʱ������ͼ��̵�����
#if 1
	mousefd = open("/dev/input/mouse0", O_RDONLY);
	if (mousefd < 0)
	{
		perror("open error");
		exit(-1);
	}
	
	// �������ļ�����������Ϊ���Խ����첽IO
	flag = fcntl(mousefd, F_GETFL);
	flag |= O_ASYNC;
	fcntl(mousefd, F_SETFL, flag);
	
	// ���첽IO�¼��Ľ��ս�������Ϊ��ǰ����
	fcntl(mousefd, F_SETOWN, getpid());
	
	// ע�ᵱǰ���̵�SIGIO�źŲ�����
	signal(SIGIO, signal_func);
	
	// ��ȡ�����豸�ļ�
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