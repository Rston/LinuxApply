/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ��open������flag���
 * ���ܣ��ļ���дȨ�ޡ������ļ����ݡ��˳����̻���򡢴򿪲����ڵ��ļ�
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int fd = -1;								// fd��file descriptor���ļ������� 	
	int ret = -1;								// ���ڽ���read����ֵ���ж��Ƿ���ļ��ɹ�
	char buf[100] = {0};						// ������������Ŵ��ļ�����������
	char bufwrite[20] = "linux is great";		// �������������Ҫд���ļ�������
	
	// ��test.txt�ļ��������ļ��������򴴽���Ȩ��666���������ļ������򱨴�
	fd = open("test.txt", O_RDWR | O_CREAT | O_EXCL, 0666);				
	if (-1 == fd)								// �ж��ļ����Ƿ�ɹ���Ҳ������дif (fd < 0)
	{
		printf("open file error.\n");
		//return -1;							// ʹ��return��exit�˳����̻����
		exit(-1);
	}
	else
	{
		printf("open file sucess. fd = %d.\n", fd);
	}

#if 1	
	ret = write(fd, bufwrite, strlen(bufwrite));	// д���ݵ��ļ���
	if (ret < 0)									// �ж������Ƿ�ɹ�д���ļ�
	{
		printf("write file errot.\n");
		//return -1;
		exit(-1);
	}
	else
	{
		printf("write %d bytes to file.\n", ret);
		printf("the content of write is [%s].\n", bufwrite);
	}
#endif

#if 1	
	ret = read(fd, buf, sizeof(buf));	// ��ȡ�ļ�����
	if (ret < 0)						// �ж϶�ȡ�ļ��Ƿ�ɹ�
	{
		printf("read file error.\n");
		//return -1;
		exit(-1);
	}
	else
	{
		printf("read %d bytes actual from file.\n", ret);
		printf("the content of read is [%s].\n", buf);
	}
#endif
	
	close(fd);							// �ر��ļ�
	
	//return 0;
	exit(0);
}
