/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ�����̹�ϵ�ͽ��̼�ͨ��
 * ���ܣ���ʾsystem�����ļ�ʹ�á�	
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int ret = -1;
	ret = system("ls -la");
	if (ret < 0)
	{
		perror("system error");
		exit(-1);
	}
	
	return 0;
}