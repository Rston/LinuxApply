/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ���������proc��sys�ļ�ϵͳ
 * ���ܣ�����ʱ����������ķ�����	
 */
 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i = 0, val = 0;
	
	// ���RAND_MAX��ֵ
	printf("RAND_MAX = %d.\n", RAND_MAX);		// RAND_MAX = 2147483647.
	
	// �������������ע��ó�����1sʱ��ֻ������1�Σ����򽫵õ�������ͬ���������
	srand(time(NULL));
	for (i=0; i<5; i++)
	{
		val = rand();
		printf("%d ", val);
		printf("%d ", val % 6);
	}
	printf("\n");
	
	return 0;
}