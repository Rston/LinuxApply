/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��fork�����͸��ӽ��̹����ļ�
 * ���ܣ��ڳ�����ʹ��environ�����鿴�����е����л���������	
 */
 
#include <stdio.h>

extern char **environ;				// ����environ����

int main(int argc, char **argv)
{
	int i = 0;
	
	for (i=0; environ[i]!=NULL; i++)
	{
		printf("%s.\n", environ[i]);
	}
	
	return 0;
}