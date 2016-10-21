/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：高级IO和多线程和线程同步
 * 功能：演示通过互斥锁解决主线程和子线程之间的同步问题。
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
	// 确保主线程被CPU优先调度运行到上锁处
	sleep(1);
	while (0 == flag)
	{
		// 上锁
		value = pthread_mutex_lock(&mutex);
		if (0 != value)
		{
			printf("pthread_mutex_lock error.\n");
			exit(-1);
		}
		printf("the cnts of character is %d.\n", strlen(buf));
		memset(buf, 0, sizeof(buf));
		// 解锁
		value = pthread_mutex_unlock(&mutex);
		if (0 != value)
		{
			printf("pthread_mutex_unlock error.\n");
			exit(-1);
		}
		// 确保CPU调度主线程继续运行监控输入
		sleep(1);
	}

	// 退出子线程
	pthread_exit(NULL);	
}

int main(int argc, char **argv)
{
	pid_t ret = -1;
	pthread_t th = -1;
	
	// 初始化创建互斥锁
	value = pthread_mutex_init(&mutex, NULL);
	if (0 != value)
	{
		printf("pthread_mutex_init error.\n");
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
	while (1)
	{
		// 上锁
		value = pthread_mutex_lock(&mutex);
		if (0 != value)
		{
			printf("pthread_mutex_lock error.\n");
			exit(-1);
		}
		scanf ("%s", buf);
		// 解锁
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
		// 防止主线程反复上锁，确保主线程经过前面的上锁解锁操作后，子线程被成功调度
		sleep(1);
	}
	
	// 主线程回收子线程
	ret = pthread_join(th, NULL);
	if (0 != ret)
	{
		printf("pthread_join error.\n");
		exit(-1);
	}
	printf("pthread_join success.\n");
	
	// 销毁互斥锁
	value = pthread_mutex_destroy(&mutex);
	if (0 != value)
	{
		printf("pthread_mutex_destroy error.\n");
		exit(-1);
	}
	printf("pthread_mutex_destroy success.\n");
	
	return 0;
}