/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��wait�庯����exec�庯��
 * ���ܣ���Ϊ�ӽ����д�ִ�еĳ������argc��argv��env�ı�����ֵ��	
 */
 
#include <stdio.h>

// env�����Ǹ�main�������⴫�ݵĻ��������ַ�������
int main(int argc, char **argv, char **env)
{
	int i = 0;
	
	printf("argc = %d.\n", argc);
	
	for (i=0; NULL != argv[i]; i++)
	{
		printf("argv[%d] = %s.\n", i, argv[i]);
	}
	
	for (i=0; NULL != env[i]; i++)
	{
		printf("env[%d] = %s.\n", i, env[i]);
	}
	
	return 0;
}