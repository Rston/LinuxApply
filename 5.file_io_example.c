/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：dup和dup2和fcntrl及标准IO
 * 功能：实现1个简单的文件IO读写操作
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATHNAME "./test.txt"

int main(int argc, char **argv)
{
	FILE *fp = NULL;
	size_t len = -1;
	char str[] = "Linux Is Great";
	char readbuf[100] = {0};
	
#if 0
	// 以可读写方式打开该文件，若文件存在则截断，若文件不存在则创建
	fp = fopen(PATHNAME, "w+");
	if (NULL == fp)
	{
		perror("fopen error");
		exit(-1);
	}
	
	len = fwrite(str, sizeof(str[0]), sizeof(str)/sizeof(str[0]), fp);
	printf("len of fwrite is %d.\n", len);
	printf("the content of fwrite is [%s].\n", str);
#endif	

#if 1	
	// 以可读写方式打开该文件
	fp = fopen(PATHNAME, "r+");
	if (NULL == fp)
	{
		perror("fopen error");
		exit(-1);
	}
	
	memset(readbuf, 0, sizeof(readbuf));
	len = fread(readbuf, sizeof(char), sizeof(readbuf), fp);
	printf("len of fread is %d.\n", len);
	printf("the content of fread is [%s].\n", readbuf);
#endif
	
	fclose(fp);
	exit(0);
}