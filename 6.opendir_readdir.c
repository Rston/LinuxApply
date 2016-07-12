/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：文件类型和文件权限管理
 * 功能：读取目录文件并打印输出并判断文件类型和统计目录下的文件项数目。	
 */

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	DIR *pDir = NULL;
	struct dirent *pEnt = NULL;
	unsigned int cnt = 0;				// 统计目录文件下的文件项数目
	
	if (argc != 2)
	{
		printf("usage: %s dirname.\n", argv[0]);
		exit(-1);
	}
	
	pDir = opendir(argv[1]);
	if (NULL == pDir)
	{
		perror("opendir error");
		exit(-1);
	}
	
	while (1)
	{
		pEnt = readdir(pDir);
		if (pEnt != NULL)
		{
			// 打印输出该目录下的所有的文件项名字
			printf("name: [%s].\n", pEnt-> d_name);
			// 判断某个文件项是否为普通文件
			if (DT_REG == pEnt->d_type)
			{
				printf("%s is a regular file.\n", pEnt-> d_name);
			}
			else
			{
				printf("%s is not a regular file.\n", pEnt-> d_name);
			}
			// 统计该目录下所有文件项个数
			cnt++;
		}
		else
		{
			break;
		}
	}
	printf("The cnts of fileobject is %d.\n", cnt);
	
	return 0;
}