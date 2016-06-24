/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ��dup��dup2��fcntrl����׼IO
 * ���ܣ�ʹ��dupʵ���ļ�������ļ��ض�λ
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define PATHNAME "./test.txt"
 
int main(int argc, char **argv)
{
	int fd1 = -1, fd2 = -1;
	int ret = -1;
	
	// ���ļ�������ضϣ����������򴴽�
	fd1 = open(PATHNAME, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd1 < 0)
	{
		perror("open error");
		exit(-1);
	}
	printf("fd1 = %d.\n", fd1);
	
	close(1);					// �رձ�׼���1
	fd2 = dup(fd1);				// fd1�ͱ�׼���1����ͬһ���ļ�PATHNAME
	printf("fd2 = %d.\n", fd2);	// ��PATHNAME�ļ��в鿴�������Ϣ
	
	// dup���ص�fd��ԭ����oldfdͬʱ��1���ļ���/дʱ������ǽ�����/д
	while (1)
	{
		ret = write(fd1, "ab.\n", 4);
		if (ret < 0)
		{
			perror("write error");
			exit(-1);
		}
		
		sleep(1);
		
		printf("cd.\n");
	}
	
	close(fd1);
	close(fd2);
	exit(0);
}