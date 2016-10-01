/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：文件类型和文件权限管理
 * 功能：使用chmod函数修改文件权限。
 */

#include <sys/stat.h>
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
	
	// -rwx------若没特意指明的权限则默认被取消掉
	ret = chmod(PATHNAME,  S_IRUSR | S_IWUSR |S_IXUSR);
	if (ret < 0)
	{
		perror("chmod error");
		exit(-1);
	}
	
	return 0;
}