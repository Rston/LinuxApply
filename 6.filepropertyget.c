/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：文件类型和文件权限管理
 * 功能：通过stat简单读取某个文件属性信息并打印输出；
 *		 通过stat判断某个文件类型；独立判断某个文件的权限。
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PATHNAME "test.txt"

int main(int argc, char **argv)
{
	int ret = -1;
	struct stat buf;
	
	memset(&buf, 0, sizeof(buf));						// 清零buf缓冲区
	ret = stat(PATHNAME, &buf);
	if (ret < 0)
	{
		perror("stat error");
		exit(-1);
	}
	
#if 0
	// 成功获取了stat结构体，从中可以得到各种属性信息了
	printf("inode = %d.\n", buf.st_ino);				// 静态文件Inode编号st_ino
	printf("size = %d bytes.\n", buf.st_size);			// 文件大小st_size	
	printf("st_blksize = %d.\n", buf.st_blksize);		// 操作系统文件读写IO缓冲区大小st_blksize
	printf("st_blocks = %d.\n", buf.st_blocks);			// 占用的块数st_blocks
#endif	
	
#if 0
	// 通过stat判断某个文件的类型
	ret = S_ISREG(buf.st_mode);							
	printf("ret = %d.\n", ret);							// ret = 1.
	ret = S_ISDIR(buf.st_mode);
	printf("ret = %d.\n", ret);							// ret = 0.
#endif
	
#if 1
	// 独立判断某个文件的权限
	// 需在非共享目录下更改文件权限
	// 增加文件属主的可执行权限（chmod u+x test.txt）
	ret =  ((S_IRUSR & buf.st_mode) ? 1 : 0);			// 判断文件的属主是否有可读权限，若有则返回1，若无则返回0
	printf("file owner = %d.\n", ret);
#endif
	
	return 0;
}