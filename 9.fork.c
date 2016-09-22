/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��fork�����͸��ӽ��̹����ļ�
 * ���ܣ�ʹ��fork���������ӽ��̡�	
 */

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t ret = -1;
	
	ret = fork();
	
	if (0 == ret)
	{	// �ӽ������
		printf("my name is child.\n");
		printf("child pid = %d.\n", getpid());
	}
	
	if (ret > 0)
	{	// ���������
		printf("my name is parent.\n");
		printf("parent pid = %d.\n", getpid());
	}
	
	if (ret < 0)
	{	// fork����
		perror("fork error");
		exit(-1);
	}
	
	return 0;
}