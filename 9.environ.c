/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：fork函数和父子进程共享文件
 * 功能：在程序中使用environ变量查看进程中的所有环境变量。	
 */
 
#include <stdio.h>

extern char **environ;				// 声明environ变量

int main(int argc, char **argv)
{
	int i = 0;
	
	for (i=0; environ[i]!=NULL; i++)
	{
		printf("%s.\n", environ[i]);
	}
	
	return 0;
}