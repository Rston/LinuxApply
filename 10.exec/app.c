/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：wait族函数和exec族函数
 * 功能：做为子进程中待执行的程序输出argc和argv和env的变量的值。	
 */
 
#include <stdio.h>

// env即我们给main函数额外传递的环境变量字符串数组
int main(int argc, char **argv, char **env)
{
	int i = 0;
	
	printf("argc = %d.\n", argc);
	
	for (i=0; NULL != argv[i]; i++)
	{
		printf("argv[%d] = %s.\n", i, argv[i]);
	}
	
	for (i=0; NULL != env[i]; i++)
	{
		printf("env[%d] = %s.\n", i, env[i]);
	}
	
	return 0;
}