/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ���ļ���������Ҫ�ӿ�API
 * ���ܣ�һ���򵥵��ļ���дʵ����
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv)
{
	int fd = -1;								// fd��file descriptor���ļ������� 	
	int ret = -1;								// ���ڽ���read����ֵ���ж��Ƿ���ļ��ɹ�
	char buf[100] = {0};						// ������������Ŵ��ļ�����������
	char bufwrite[20] = "linux is great";		// �������������Ҫд���ļ�������
	
	fd = open("test.txt", O_RDWR);				// ��test.txt�ļ�
	if (-1 == fd)								// �ж��ļ����Ƿ�ɹ���Ҳ������дif (fd < 0)
	{
		printf("open file error.\n");
	}
	else
	{
		printf("open file sucess. fd = %d.\n", fd);
	}
	
	ret = write(fd, bufwrite, strlen(bufwrite));	// д���ݵ��ļ���
	if (ret < 0)									// �ж������Ƿ�ɹ�д���ļ�
	{
		printf("write file errot.\n");
	}
	else
	{
		printf("write %d bytes to file.\n", ret);
		printf("the content of write is [%s].\n", bufwrite);
	}
	
	ret = read(fd, buf, sizeof(buf));	// ��ȡ�ļ�����
	if (ret < 0)						// �ж϶�ȡ�ļ��Ƿ�ɹ�
	{
		printf("read file error.\n");
	}
	else
	{
		printf("read %d bytes actual from file.\n", ret);
		printf("the content of read is [%s].\n", buf);
	}
	
	close(fd);							// �ر��ļ�
	
	return 0;
}