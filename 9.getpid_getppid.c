/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ��fork�����͸��ӽ��̹����ļ�
 * ���ܣ��ڳ�����ʹ��getpid��getppid��ȡ����ID��	
 */
 
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t id = -1;
	
	id = getpid();						// ��ȡ��ǰ���̵�ID
	printf("getpid id = %d.\n", id);
	
	id = getppid();
	printf("getppid id = %d.\n", id);	// ��ȡ��ǰ���̵ĸ����̵�ID
	
	return 0;
}