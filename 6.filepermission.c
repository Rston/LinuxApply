/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ���ļ����ͺ��ļ�Ȩ�޹���
 * ���ܣ���֤�ļ�����ʱ��Ȩ�޼�����
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int ret = -1;
	
	if (argc != 2)
	{
		printf("usage: %s filename.\n", argv[0]);
		exit(-1);
	}

	// ����linuxԭ��Ŀ¼��Ʃ�硰/home/gec/.���������иó���
	// ������ͨ�û����ֶ��½�ĳ���ļ���Ȼ���ֶ��������û��������л��û����в���
	// �ԡ�./a.out filename����ʽ���г���
	ret = open(argv[1], O_RDONLY);
	if (ret > 0)
	{
		printf("can read.\n");
		close(ret);
	}
	else
	{
		perror("open O_RDONLY error");
	}
	
	ret = open(argv[1], O_WRONLY);
	if (ret > 0)
	{
		printf("can write.\n");
		close(ret);
	}
	else
	{
		perror("open O_WRONLY error");
	}
	
	return 0;
}