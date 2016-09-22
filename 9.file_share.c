/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��fork�����͸��ӽ��̹����ļ�
 * ���ܣ���ʾ���ӽ��̹����ļ���	
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PATHNAME "test.txt" 

int main(int argc, char **argv)
{
	int fd = -1;
	pid_t pid = -1;
	
#if 1
	// �ӽ��̼̳и������д򿪵��ļ�
	// ��test.txt�ļ��������ļ��������򴴽���Ȩ��666���������ļ�������ض�
	fd = open(PATHNAME,  O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd < 0)
	{
		perror("open error");
		exit(-1);
	}	
	
	pid = fork();
	if (pid > 0)
	{	// ���������
		printf("parent.\n");
		write(fd, "hello", strlen("hello"));
		sleep(1);	// ����CPU����Ȩ����CPU�����ӽ���
	}
	else if (0 == pid)
	{
		// �ӽ������
		printf("child.\n");
		write(fd, "world", strlen("world"));
		sleep(1);	// ����CPU����Ȩ����CPU���ȸ�����
	}
	else
	{
		perror("fork error");
		exit(-1);
	}
	close(fd);
#endif	
	
#if 0
	// ���ӽ��̸��Զ�������ͬ�ļ�ʵ�ֹ���
	pid = fork();
	if (pid > 0)
	{	// ���������
		#if 1
		fd = open(PATHNAME, O_RDWR);				// �ֱ�д
		#endif
		#if 0
		fd = open(PATHNAME, O_RDWR | O_APPEND);		// ����д
		#endif
		if (fd < 0)
		{
			perror("open error");
			exit(-1);
		}
		
		printf("parent.\n");
		write(fd, "hello", strlen("hello"));
		sleep(1);
	}
	else if (0 == pid)
	{
		// �ӽ������
		#if 1
		fd = open(PATHNAME, O_RDWR);				// �ֱ�д
		#endif
		#if 0
		fd = open(PATHNAME, O_RDWR | O_APPEND);		// ����д
		#endif
		if (fd < 0)
		{
			perror("open error");
			exit(-1);
		}
		
		printf("child.\n");
		write(fd, "world", strlen("world"));
		sleep(1);	// ����CPU����Ȩ����CPU���ȸ�����
	}
	else
	{
		perror("fork error");
		exit(-1);
	}
	close(fd);
#endif

	return 0;
}