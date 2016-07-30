/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：进程关系和进程间通信
 * 功能：演示system函数的简单使用。	
 */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int ret = -1;
	ret = system("ls -la");
	if (ret < 0)
	{
		perror("system error");
		exit(-1);
	}
	
	return 0;
}