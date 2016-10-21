/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ���߼�IO�Ͷ��̺߳��߳�ͬ��
 * ���ܣ���ʾͨ��������������̺߳����߳�֮���ͬ�����⡣
 */
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

char buf[1024] = {0};
unsigned int flag = 0;	
int value = -1;	
pthread_mutex_t mutex;

void *pthread_func(void *arg)
{
	// ȷ�����̱߳�CPU���ȵ������е�������
	sleep(1);
	while (0 == flag)
	{
		// ����
		value = pthread_mutex_lock(&mutex);
		if (0 != value)
		{
			printf("pthread_mutex_lock error.\n");
			exit(-1);
		}
		printf("the cnts of character is %d.\n", strlen(buf));
		memset(buf, 0, sizeof(buf));
		// ����
		value = pthread_mutex_unlock(&mutex);
		if (0 != value)
		{
			printf("pthread_mutex_unlock error.\n");
			exit(-1);
		}
		// ȷ��CPU�������̼߳������м������
		sleep(1);
	}

	// �˳����߳�
	pthread_exit(NULL);	
}

int main(int argc, char **argv)
{
	pid_t ret = -1;
	pthread_t th = -1;
	
	// ��ʼ������������
	value = pthread_mutex_init(&mutex, NULL);
	if (0 != value)
	{
		printf("pthread_mutex_init error.\n");
		exit(-1);
	}
	
	// �������̴߳����ӡ�����������
	ret = pthread_create(&th, NULL, pthread_func, NULL);
	if (0 != ret)
	{
		printf("pthread_create error.\n");
		return -1;
	}
	
	printf("please input the character, input 'end' stop.\n");
	while (1)
	{
		// ����
		value = pthread_mutex_lock(&mutex);
		if (0 != value)
		{
			printf("pthread_mutex_lock error.\n");
			exit(-1);
		}
		scanf ("%s", buf);
		// ����
		value = pthread_mutex_unlock(&mutex);
		if (0 != value)
		{
			printf("pthread_mutex_unlock error.\n");
			exit(-1);
		}
		
		if (!strncmp(buf, "end", strlen("end")))
		{
			printf("program stop.\n");
			flag = 1;
			break;
		}
		// ��ֹ���̷߳���������ȷ�����߳̾���ǰ��������������������̱߳��ɹ�����
		sleep(1);
	}
	
	// ���̻߳������߳�
	ret = pthread_join(th, NULL);
	if (0 != ret)
	{
		printf("pthread_join error.\n");
		exit(-1);
	}
	printf("pthread_join success.\n");
	
	// ���ٻ�����
	value = pthread_mutex_destroy(&mutex);
	if (0 != value)
	{
		printf("pthread_mutex_destroy error.\n");
		exit(-1);
	}
	printf("pthread_mutex_destroy success.\n");
	
	return 0;
}