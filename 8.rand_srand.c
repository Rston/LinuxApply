/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：随机数和proc和sys文件系统
 * 功能：简单延时产生随机数的方法。	
 */
 
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int i = 0, val = 0;
	
	// 输出RAND_MAX的值
	printf("RAND_MAX = %d.\n", RAND_MAX);		// RAND_MAX = 2147483647.
	
	// 产生随机数，需注意该程序在1s时间只能运行1次，否则将得到两组相同的随机数列
	srand(time(NULL));
	for (i=0; i<5; i++)
	{
		val = rand();
		printf("%d ", val);
		printf("%d ", val % 6);
	}
	printf("\n");
	
	return 0;
}