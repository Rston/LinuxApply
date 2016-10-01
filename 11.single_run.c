/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：进程关系和进程间通信
 * 功能：演示单例运行程序功能的实现。	
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define PATH "./RstonSingleRun"

// 进程退出函数声明
void delete(void);

int main(int argc, char **argv)
{
	int fd = -1;
	// 若文件不存在，则创建，若文件存在，则报错
	fd = open(PATH, O_RDWR | O_CREAT | O_EXCL, 0664);
	if (fd < 0)
	{
		if (errno == EEXIST)
		{
			printf("The process is now running, plsest not repeat run process.\n");
			return -1;
		}
	}
	
	// 注册进程退出处理函数用于删除特殊文件
	atexit(delete);
	
	int i = 0;
	for (i=0; i<20; i++)
	{
		printf("I am running now.\n");
		sleep(1);
	}
	
	return 0;
}

// 进程退出之前删除特殊文件
void delete(void)
{
	remove(PATH);
}