/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ���������proc��sys�ļ�ϵͳ
 * ���ܣ�ͨ���ļ�IOʹ��proc�����ļ�ϵͳ��	
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int fd = -1;
	char buf[512] = {0};
	
	if (argc != 2)
	{
		printf("usage: %s -v|-d\n", argv[0]);
		exit(-1);
	}
	
	if (!strcmp(argv[1], "-v"))
	{	// �鿴��ǰ����ϵͳ�汾��Ϣ
		fd = open("/proc/version",  O_RDONLY);
		if (fd < 0)
		{
			perror("open error");
			exit(-1);
		}
		read(fd, buf, sizeof(buf));
		printf("version is %s", buf);
	}	
	else if (!strcmp(argv[1], "-d"))
	{	// �鿴��ǰ����ϵͳ��װ����Щ�����豸
		memset(buf, 0, sizeof(buf));
		fd = open("/proc/devices",  O_RDONLY);
		if (fd < 0)
		{
			perror("open error");
			exit(-1);
		}
		read(fd, buf, sizeof(buf));
		printf("devices is %s", buf);
	}
	
	return 0;
}