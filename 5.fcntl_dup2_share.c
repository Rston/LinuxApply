/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��dup��dup2��fcntrl����׼IO
 * ���ܣ�ʹ��fcntlģ��dup2��
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
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
	
	fd2 = fcntl(fd1,  F_DUPFD, 20);		// fd2��fd1ָ��ͬһ���ļ�����Ӧͬһ���ļ�ָ��
	printf("fd2 = %d.\n", fd2);
	
	// fcntl���ص�fd��ԭ����oldfdͬʱ��1���ļ���/дʱ������ǽ�����/д
	while (1)
	{
		ret = write(fd1, "ab", 2);
		if (ret < 0)
		{
			perror("write error");
			exit(-1);
		}
		
		sleep(1);
		
		ret = write(fd2, "cd", 2);
		if (ret < 0)
		{
			perror("write error");
			exit(-1);
		}
	}
	
	close(fd1);
	close(fd2);
	exit(0);
}