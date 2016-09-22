/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：文件操作的主要接口API
 * 功能：一个简单的文件读写实例。
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int fd = -1;								// fd即file descriptor，文件描述符 	
	int ret = -1;								// 用于接收read返回值，判断是否读文件成功
	char buf[100] = {0};						// 构建缓冲区存放从文件读出的内容
	char bufwrite[20] = "linux is great";		// 构建缓冲区存放要写入文件的内容
	
	fd = open("test.txt", O_RDWR);				// 打开test.txt文件
	if (-1 == fd)								// 判断文件打开是否成功，也可这样写if (fd < 0)
	{
		printf("open file error.\n");
	}
	else
	{
		printf("open file sucess. fd = %d.\n", fd);
	}
	
	ret = write(fd, bufwrite, strlen(bufwrite));	// 写内容到文件中
	if (ret < 0)									// 判断内容是否成功写入文件
	{
		printf("write file errot.\n");
	}
	else
	{
		printf("write %d bytes to file.\n", ret);
		printf("the content of write is [%s].\n", bufwrite);
	}
	
	ret = read(fd, buf, sizeof(buf));	// 读取文件内容
	if (ret < 0)						// 判断读取文件是否成功
	{
		printf("read file error.\n");
	}
	else
	{
		printf("read %d bytes actual from file.\n", ret);
		printf("the content of read is [%s].\n", buf);
	}
	
	close(fd);							// 关闭文件
	
	return 0;
}