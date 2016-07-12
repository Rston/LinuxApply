/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：文件类型和文件权限管理
 * 功能：使用access函数判断当前用户是否对该文件有相应的操作权限。
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PATHNAME "test.txt"

int main(int argc, char **argv)
{
	int ret = -1;
	
	ret = access(PATHNAME, F_OK);
	if (ret < 0)
	{
		printf("The file is not exit.\n");
		exit(-1);
	}
	else
	{
		printf("The file is exit.\n");
	}
	
	ret = access(PATHNAME, R_OK);
	if (ret < 0)
	{
		printf("The file can not read.\n");
	}
	else
	{
		printf("The file can read.\n");
	}
	
	return 0;
}