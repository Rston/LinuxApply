/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ���߼�IO�Ͷ��̺߳��߳�ͬ��
 * ���ܣ���ʾͨ���ź���������̺߳����߳�֮���ͬ�����⡣
 */
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

char buf[1024] = {0};
sem_t sem;	
unsigned int flag = 0;		

void *pthread_func(void *arg)
{
	// ���߳������ȴ��ź���
	sem_wait(&sem);
	
	while (0 == flag)
	{
		printf("the cnts of character is %d.\n", strlen(buf));
		memset(buf, 0, sizeof(buf));
		// ���߳������ȴ��ź���
		sem_wait(&sem);
	}
	
	// �˳����߳�
	pthread_exit(NULL);	
}

int main(int argc, char **argv)
{
	pid_t ret = -1;
	int value = -1;
	pthread_t th = -1;
	
	// ��ʼ���ź���
	value = sem_init(&sem, 0, 0);	
	if (0 != value)
	{
		perror("sem_init error");
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
	while (scanf ("%s", buf))
	{
		if (!strncmp(buf, "end", strlen("end")))
		{
			printf("program stop.\n");
			flag = 1;
			// �ź�����1���������߳�
			sem_post(&sem);
			break;
		}
		// �ź�����1���������߳�
		sem_post(&sem);
	}
	
	// ���̻߳������߳�
	ret = pthread_join(th, NULL);
	if (0 != ret)
	{
		printf("pthread_join error.\n");
		exit(-1);
	}
	printf("pthread_join success.\n");
	
	// ���߳������ź���
	value = sem_destroy(&sem);
	if (0 != value)
	{
		perror("sem_destroy error");
		exit(-1);
	}
	printf("sem_destroy success.\n");
	
	return 0;
}