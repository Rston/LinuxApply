/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：随机数和proc和sys文件系统
 * 功能：通过文件IO使用proc虚拟文件系统。	
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
	{	// 查看当前操作系统版本信息
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
	{	// 查看当前操作系统安装了哪些驱动设备
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