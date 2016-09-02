/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ�����̹�ϵ�ͽ��̼�ͨ��
 * ���ܣ������ػ����̡�	
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// ��������
void CreatDaemon(void);

int main(int argc, char **argv)
{
	CreatDaemon();
	
	while (1)
	{
		printf("I am running.\n");
		sleep(1);
	}
	
	return 0;
}

// �ѵ��øú����Ľ��̱��1���ػ�����
void CreatDaemon(void)
{
	pid_t pid = -1;
	
	pid = fork();
	
	if (pid > 0)
	{
		exit(0);		// ������ֱ���˳�
	}
	else if (0 == pid)
	{
		// setsid����ǰ��������Ϊ1���µĻỰ��session��������ǰ�����������̨
		pid = setsid();
		if (pid < 0)
		{
			perror("setsid error");
			exit(-1);
		}

		// ����ǰ���̹���Ŀ¼����Ϊ��Ŀ¼
		chdir("/");
		
		// umask����Ϊ0ȷ�����������������ļ�����Ȩ��
		umask(0);
		
		// �ر������ļ�������
		// ��ȡ��ǰϵͳ��������򿪵�����ļ���������Ŀ
		int cnt = sysconf(_SC_OPEN_MAX);
		int i = 0;
		for (i=0; i<cnt; i++)
		{
			close(i);
		}
		
		// ��0��1��2��λ��/dev/null����վ
		open("/dev/null", O_RDWR);
		open("/dev/null", O_RDWR);
		open("/dev/null", O_RDWR);
	}
	else 	
	{
		perror("fork error");
		exit(-1);
	}
}