/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ�����̹�ϵ�ͽ��̼�ͨ��
 * ���ܣ���ʾ�������г����ܵ�ʵ�֡�	
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define PATH "./RstonSingleRun"

// �����˳���������
void delete(void);

int main(int argc, char **argv)
{
	int fd = -1;
	// ���ļ������ڣ��򴴽������ļ����ڣ��򱨴�
	fd = open(PATH, O_RDWR | O_CREAT | O_EXCL, 0664);
	if (fd < 0)
	{
		if (errno == EEXIST)
		{
			printf("The process is now running, plsest not repeat run process.\n");
			return -1;
		}
	}
	
	// ע������˳�����������ɾ�������ļ�
	atexit(delete);
	
	int i = 0;
	for (i=0; i<20; i++)
	{
		printf("I am running now.\n");
		sleep(1);
	}
	
	return 0;
}

// �����˳�֮ǰɾ�������ļ�
void delete(void)
{
	remove(PATH);
}