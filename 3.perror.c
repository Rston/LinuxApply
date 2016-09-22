/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：文件读写细节及文件管理
 * 功能：演示perror函数的使用。
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
		//printf("open file error.\n");
		perror("open file error");				// 通过perror捕捉errno错误信息并打印输出
		//return -1;							// 使用return或exit退出进程或程序
		exit(-1);
	}
	else
	{
		printf("open file sucess. fd = %d.\n", fd);
	}

#if 1	
	ret = write(fd, bufwrite, strlen(bufwrite));	// 写内容到文件中
	if (ret < 0)									// 判断内容是否成功写入文件
	{
		//printf("write file errot.\n");
		perror("write file errot");
		//return -1;
		exit(-1);
	}
	else
	{
		printf("write %d bytes to file.\n", ret);
		printf("the content of write is [%s].\n", bufwrite);
	}
#endif

#if 1	
	ret = read(fd, buf, sizeof(buf));	// 读取文件内容
	if (ret < 0)						// 判断读取文件是否成功
	{
		//printf("read file error.\n");
		perror("read file error");
		//return -1;
		exit(-1);
	}
	else
	{
		printf("read %d bytes actual from file.\n", ret);
		printf("the content of read is [%s].\n", buf);
	}
#endif
	
	close(fd);							// 关闭文件
	
	//return 0;
	exit(0);
}
