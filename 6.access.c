/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ���ļ����ͺ��ļ�Ȩ�޹���
 * ���ܣ�ʹ��access�����жϵ�ǰ�û��Ƿ�Ը��ļ�����Ӧ�Ĳ���Ȩ�ޡ�
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PATHNAME "test.txt"

int main(int argc, char **argv)
{
	int ret = -1;
	
	ret = access(PATHNAME, F_OK);
	if (ret < 0)
	{
		printf("The file is not exit.\n");
		exit(-1);
	}
	else
	{
		printf("The file is exit.\n");
	}
	
	ret = access(PATHNAME, R_OK);
	if (ret < 0)
	{
		printf("The file can not read.\n");
	}
	else
	{
		printf("The file can read.\n");
	}
	
	return 0;
}