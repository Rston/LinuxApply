/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ���߼�IO�Ͷ��̺߳��߳�ͬ��
 * ���ܣ������+���̡߳�
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
	// ��֧���񣬶�ȡ�����豸�ļ�
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

// ͨ������̼���ͬʱ��ȡ�����豸�ļ�������豸�ļ�
#if 0	
	ret = fork();
	if (ret > 0)
	{
		// �����̣���ȡ�����豸�ļ�
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
		// �ӽ��̣���ȡ����豸�ļ�
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

// ͨ�����̼߳���ͬʱ��ȡ�����豸�ļ�������豸�ļ�
// gcc 13.keyboard_mouse_thread.c -pthread
#if 1
	// �����̶߳�ȡ�����豸�ļ�
	ret = pthread_create(&th, NULL, pthread_func, NULL);
	if (0 != ret)
	{
		printf("pthread_create error.\n");
		return -1;
	}
	
	// ��Ϊ���߳���while(1)��ѭ��������ɱ����̷߳��룬��������̲߳���Ҫ��ȥ�������߳�
	ret = pthread_detach(th);
	if (0 != ret)
	{
		printf("pthread_detach error.\n");
		return -1;
	}
	
	// �����񣬶�ȡ����豸�ļ�
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