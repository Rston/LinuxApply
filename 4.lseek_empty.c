/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：lseek函数及共享文件
 * 功能：使用lseek构建1个空洞文件。
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int fd = -1;								// fd即file descriptor，文件描述符 	
	int ret = -1;								// 用于接收read返回值，判断是否读文件成功
	char buf[100] = {0};						// 构建缓冲区存放从文件读出的内容
	char bufwrite[20] = "linux is great";		// 构建缓冲区存放要写入文件的内容

	// 打开test.txt文件，若该文件不存在则创建（权限666），若该文件存在则报错
	fd = open("test.txt", O_RDWR | O_CREAT | O_EXCL, 0666);	
	if (-1 == fd)								// 判断文件打开是否成功，也可这样写if (fd < 0)
	{
		perror("open file error");				// 通过perror捕捉errno错误信息并打印输出
		exit(-1);
	}

#if 1	
	ret = lseek(fd, 10, SEEK_SET);				// 使用lseek函数从文件开始位置开始向后移动10个字符位置
	printf("lseek, ret = %d.\n", ret);			// 即构建了1个空洞文件
#endif
	
#if 1	
	ret = write(fd, bufwrite, strlen(bufwrite));// 写内容到文件中
	if (ret < 0)								// 判断内容是否成功写入文件
	{
		perror("write file errot");
		exit(-1);
	}
#endif

	close(fd);									// 关闭文件
	
	exit(0);
}