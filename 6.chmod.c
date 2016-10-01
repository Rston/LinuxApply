/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ���ļ����ͺ��ļ�Ȩ�޹���
 * ���ܣ�ʹ��chmod�����޸��ļ�Ȩ�ޡ�
 */

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
#define PATHNAME "test.txt"
 
int main(int argc, char **argv)
{
	int ret = -1;
	
	if (argc != 2)
	{
		printf("usage: %s filename.\n", argv[0]);
		exit(-1);
	}
	
	// -rwx------��û����ָ����Ȩ����Ĭ�ϱ�ȡ����
	ret = chmod(PATHNAME,  S_IRUSR | S_IWUSR |S_IXUSR);
	if (ret < 0)
	{
		perror("chmod error");
		exit(-1);
	}
	
	return 0;
}