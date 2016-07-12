/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：文件类型和文件权限管理
 * 功能：chown函数修改文件属主和属主所在的组。
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
 
#define PATHNAME "test.txt"
 
int main(int argc, char **argv)
{
	int ret = -1;
	
	if (argc != 2)
	{
		printf("usage: %s filename.\n", argv[0]);
		exit(-1);
	}
	
	// 将test.txt的文件属主和属主所在的组均改为root
	ret = chown(PATHNAME, 0, 0);
	if (ret < 0)
	{
		perror("chown error");
		exit(-1);
	}
	
	return 0;
}