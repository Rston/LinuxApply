/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��fork�����͸��ӽ��̹����ļ�
 * ���ܣ�ʹ��atexit����ע�������ֹ��������	
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// ������ֹ������1
void exit_func1(void)
{
	printf("Is in exit_func1.\n");
}

// ������ֹ������2
void exit_func2(void)
{
	printf("Is in exit_func2.\n");
}

int main(int argc, char **argv)
{
	int ret = -1;
	
	printf("hello world.\n");
	
	ret = atexit(exit_func1);
	if (ret != 0)
	{
		printf("atexit exit_func1 error.\n");
		exit(-1);
	}
	
	ret = atexit(exit_func2);
	if (ret != 0)
	{
		printf("atexit exit_func2 error.\n");
		exit(-1);
	}
	
	printf("my name is Rston.\n");

#if 1	
	return 0;		// ��ֹ����ʱִ��atexitע��Ľ�����ֹ������
#endif

#if 0
	exit(0);		// ��ֹ����ʱִ��atexitע��Ľ�����ֹ������
#endif

#if 0
	_exit(0);		// ��ֹ����ʱ����ִ��atexitע��Ľ�����ֹ������
#endif
}