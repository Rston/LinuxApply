/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：高级IO和多线程和线程同步
 * 功能：演示通过信号量解决主线程和子线程之间的同步问题。
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
	// 分线程阻塞等待信号量
	sem_wait(&sem);
	
	while (0 == flag)
	{
		printf("the cnts of character is %d.\n", strlen(buf));
		memset(buf, 0, sizeof(buf));
		// 分线程阻塞等待信号量
		sem_wait(&sem);
	}
	
	// 退出子线程
	pthread_exit(NULL);	
}

int main(int argc, char **argv)
{
	pid_t ret = -1;
	int value = -1;
	pthread_t th = -1;
	
	// 初始化信号量
	value = sem_init(&sem, 0, 0);	
	if (0 != value)
	{
		perror("sem_init error");
		exit(-1);
	}
	
	// 创建子线程处理打印输出计数功能
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
			// 信号量加1，激活子线程
			sem_post(&sem);
			break;
		}
		// 信号量加1，激活子线程
		sem_post(&sem);
	}
	
	// 主线程回收子线程
	ret = pthread_join(th, NULL);
	if (0 != ret)
	{
		printf("pthread_join error.\n");
		exit(-1);
	}
	printf("pthread_join success.\n");
	
	// 主线程销毁信号量
	value = sem_destroy(&sem);
	if (0 != value)
	{
		perror("sem_destroy error");
		exit(-1);
	}
	printf("sem_destroy success.\n");
	
	return 0;
}