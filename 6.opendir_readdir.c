/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ���ļ����ͺ��ļ�Ȩ�޹���
 * ���ܣ���ȡĿ¼�ļ�����ӡ������ж��ļ����ͺ�ͳ��Ŀ¼�µ��ļ�����Ŀ��	
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	DIR *pDir = NULL;
	struct dirent *pEnt = NULL;
	unsigned int cnt = 0;				// ͳ��Ŀ¼�ļ��µ��ļ�����Ŀ
	
	if (argc != 2)
	{
		printf("usage: %s dirname.\n", argv[0]);
		exit(-1);
	}
	
	pDir = opendir(argv[1]);
	if (NULL == pDir)
	{
		perror("opendir error");
		exit(-1);
	}
	
	while (1)
	{
		pEnt = readdir(pDir);
		if (pEnt != NULL)
		{
			// ��ӡ�����Ŀ¼�µ����е��ļ�������
			printf("name: [%s].\n", pEnt-> d_name);
			// �ж�ĳ���ļ����Ƿ�Ϊ��ͨ�ļ�
			if (DT_REG == pEnt->d_type)
			{
				printf("%s is a regular file.\n", pEnt-> d_name);
			}
			else
			{
				printf("%s is not a regular file.\n", pEnt-> d_name);
			}
			// ͳ�Ƹ�Ŀ¼�������ļ������
			cnt++;
		}
		else
		{
			break;
		}
	}
	printf("The cnts of fileobject is %d.\n", cnt);
	
	return 0;
}