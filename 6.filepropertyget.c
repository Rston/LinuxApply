/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ���ļ����ͺ��ļ�Ȩ�޹���
 * ���ܣ�ͨ��stat�򵥶�ȡĳ���ļ�������Ϣ����ӡ�����
 *		 ͨ��stat�ж�ĳ���ļ����ͣ������ж�ĳ���ļ���Ȩ�ޡ�
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
	
	memset(&buf, 0, sizeof(buf));						// ����buf������
	ret = stat(PATHNAME, &buf);
	if (ret < 0)
	{
		perror("stat error");
		exit(-1);
	}
	
#if 0
	// �ɹ���ȡ��stat�ṹ�壬���п��Եõ�����������Ϣ��
	printf("inode = %d.\n", buf.st_ino);				// ��̬�ļ�Inode���st_ino
	printf("size = %d bytes.\n", buf.st_size);			// �ļ���Сst_size	
	printf("st_blksize = %d.\n", buf.st_blksize);		// ����ϵͳ�ļ���дIO��������Сst_blksize
	printf("st_blocks = %d.\n", buf.st_blocks);			// ռ�õĿ���st_blocks
#endif	
	
#if 0
	// ͨ��stat�ж�ĳ���ļ�������
	ret = S_ISREG(buf.st_mode);							
	printf("ret = %d.\n", ret);							// ret = 1.
	ret = S_ISDIR(buf.st_mode);
	printf("ret = %d.\n", ret);							// ret = 0.
#endif
	
#if 1
	// �����ж�ĳ���ļ���Ȩ��
	// ���ڷǹ���Ŀ¼�¸����ļ�Ȩ��
	// �����ļ������Ŀ�ִ��Ȩ�ޣ�chmod u+x test.txt��
	ret =  ((S_IRUSR & buf.st_mode) ? 1 : 0);			// �ж��ļ��������Ƿ��пɶ�Ȩ�ޣ������򷵻�1�������򷵻�0
	printf("file owner = %d.\n", ret);
#endif
	
	return 0;
}