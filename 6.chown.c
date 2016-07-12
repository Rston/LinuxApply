/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ���ļ����ͺ��ļ�Ȩ�޹���
 * ���ܣ�chown�����޸��ļ��������������ڵ��顣
 */

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
	
	// ��test.txt���ļ��������������ڵ������Ϊroot
	ret = chown(PATHNAME, 0, 0);
	if (ret < 0)
	{
		perror("chown error");
		exit(-1);
	}
	
	return 0;
}