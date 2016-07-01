 /*
 * 公司：XXXX
 * 作者：Rston
 * 项目：lseek函数及共享文件
 * 功能：使用lseek函数测试某个文件的大小。
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/* 测试文件的大小，形参为路径名 */
int callen(const char *pathname)
{
	int fd = -1, ret = -1;
	
	fd = open(pathname, O_RDONLY);
	if (-1 == fd)
	{
		perror("open file error");
		exit(-1);
	}
	
	// lseek将文件指针移动到末尾，返回值即文件指针距离文件开头的偏移量，即文件的长度
	ret = lseek(fd, 0, SEEK_END);
	return ret;
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("usage: %s pathname.\n", argv[0]);
		exit(-1);
	}
	
	printf("The size of %s is %d.\n", argv[1], callen(argv[1]));
	
	exit(0);
}