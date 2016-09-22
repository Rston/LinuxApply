/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：文件类型和文件权限管理
 * 功能：验证文件操作时的权限检查规则。
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int ret = -1;
	
	if (argc != 2)
	{
		printf("usage: %s filename.\n", argv[0]);
		exit(-1);
	}

	// 需在linux原生目录（譬如“/home/gec/.”）下运行该程序
	// 需在普通用户下手动新建某个文件，然后手动创建新用户并来回切换用户进行测试
	// 以“./a.out filename”格式运行程序
	ret = open(argv[1], O_RDONLY);
	if (ret > 0)
	{
		printf("can read.\n");
		close(ret);
	}
	else
	{
		perror("open O_RDONLY error");
	}
	
	ret = open(argv[1], O_WRONLY);
	if (ret > 0)
	{
		printf("can write.\n");
		close(ret);
	}
	else
	{
		perror("open O_WRONLY error");
	}
	
	return 0;
}