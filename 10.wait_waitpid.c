/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ��wait�庯����exec�庯��
 * ���ܣ���ʾ�����̵���wait��waitpid���ڻ����ӽ��̡�	
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	pid_t pid = -1, ret = -1;
	int status = -1;
	
	pid = fork();
	if (pid > 0)
	{	// ���������
		printf("parent ID is %d.\n", getpid());
#if 0	
		ret = wait(&status);					// ����wait�����������ڻ����ӽ���
#endif

#if 0
		ret = waitpid(-1, &status, 0);			// ʹ��waitpidʵ��waitЧ��
#endif

#if 0
		ret = waitpid(pid, &status, 0);			// ����waitpid�������ڻ����ض�ID�ӽ���
#endif	

#if 0
		sleep(1);								// ȷ�������������ӽ�����������֤�����ӽ��̳ɹ�
		ret = waitpid(pid, &status,  WNOHANG);	// ������ʽ�����ӽ���
#endif

#if 2
		ret = waitpid(pid, &status,  WNOHANG);	// �����̷�����ʽ�����ӽ��̵��ӽ�����δ�����ķ���ֵ��
#endif		
		printf("The Recover of process ID is %d.\n", ret);
		printf("Whether the child process exits normally %d.\n", WIFEXITED(status));
		printf("Child process is abnormal exit %d.\n", WIFSIGNALED(status));
		printf("Value Normal termination %d.\n", WEXITSTATUS(status));
	}
	else if (0 == pid)
	{	// �ӽ������
#if 2
		sleep(1);								// �����̷�����ʽ�����ӽ��̵��ӽ�����δ�����ķ���ֵ��
#endif
		printf("child ID is %d.\n", getpid());
		printf("Now parent ID is %d.\n", getppid());
		exit(0);								// �����˳��ӽ���
	}
	else
	{
		perror("fork error");
		exit(-1);
	}

	return 0;
}