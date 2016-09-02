/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ��linux�е��ź�
 * ���ܣ���ʾsigaction��alarm��pause�����ļ�ʹ�á�
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>	

void mysleep(unsigned int seconds);

#if 1
void signal_func(int sig)
{
	
}
#endif

#if 0
void signal_func(int sig)
{
	printf("alarm happened.\n");
}
#endif

int main(int argc, char **argv)
{
#if 0
	int ret = -1;
	struct sigaction act = {0};
	act.sa_handler = signal_func;
	
	ret = sigaction(SIGALRM, &act, NULL);
	
	ret = alarm(5);
	printf("1st, ret = %d.\n", ret);	// 1st, ret = 0.
	sleep(3);
	
	ret = alarm(5);		
	printf("2st, ret = %d.\n", ret);	// 2st, ret = 2.
	sleep(1);
	
	ret = alarm(5);
	printf("3st, ret = %d.\n", ret);	// 3st, ret = 4.

#if 0
	while (1);
#endif

#if 1
	pause();
#endif
#endif

#if 1
	// ʹ��alarm��pause��ģ��sleep
	printf("before mysleep.\n");
	mysleep(3);
	printf("after mysleep.\n");
#endif
	
	return 0;
}

#if 0
void mysleep(unsigned int seconds)
{
	struct sigaction act = {0};
	
	act.sa_handler = signal_func;
	sigaction(SIGALRM, &act, NULL);
	
	alarm(seconds);
	pause();
}
#endif