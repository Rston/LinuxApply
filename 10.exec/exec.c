/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ������
 * ���ܣ�ʵ����ʾexec��������÷���	
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	pid_t pid = -1;
	
	pid = fork();
	
	if (pid > 0)
	{	// ���������
		printf("parent ID is %d.\n", getpid());	
	}
	else if (0 == pid)
	{	// �ӽ������
		
#if 0	// ʹ��execl/execv��������ls-la����
		execl("/bin/ls", "ls", "-l", "-a", NULL);	
#elif 0
		char *const arg[] = {"ls", "-l", "-a", NULL};
		execv("/bin/ls", arg);
#endif	
		
#if 0	// ʹ��execl/execv���������Լ�д��app����
		execl("./app", "./app", "argv[1]", "argv[2]", NULL);	
#elif 0
		char *const arg[] = {"./app", "argv[1]", "argv[2]", NULL};
		execv("./app", arg);
#endif

#if 0	// ʹ��execlp/execvp��������ls-la����
		execlp("ls", "ls", "-l", "-a", NULL);	
#elif 0
		char *const arg[] = {"ls", "-l", "-a", NULL};
		execvp("ls", arg);
#endif

#if 0	// ʹ��execlp/execvp���������Լ�д��app����
		execlp("app", "./app", "argv[1]", "argv[2]", NULL);	
#elif 0
		char *const arg[] = {"./app", "argv[1]", "argv[2]", NULL};
		execvp("app", arg);
#endif

#if 0	// ʹ��execle/execve���������Լ�д��app����
		char *const envp[] = {"AA=env[0]", "BB=env[1]", NULL};
		execle("./app", "./app", "argv[1]", "argv[2]", NULL, envp);
#elif 1
		char *const arg[] = {"./app", "argv[1]", "argv[2]", NULL};
		char *const env[] = {"AA=env[0]", "BB=env[1]", NULL};
		execvpe("./app", arg, env);
#endif

		exit(0);
	}
	else if (pid < 0)
	{
		perror("fork error");
		exit(-1);
	}
	
	return 0;
}