/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ��Ŀ�����̹�ϵ�ͽ��̼�ͨ��
 * ���ܣ���ʾsyslog��־�����ʹ�á�	
 */
 
#include <stdio.h>
#include <syslog.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{
	printf("my pid = %d.\n", getpid());

	// �򿪺�syslogd�����ӵ�ͨ������������־Ϊa.out��
	// ����Ϣ�޷�д��log������Ϣֱ�ӷ��͵�����̨��
	// ��Ϣ�а�������PID�ţ���Ϣ��������ͨ�û�����
	// ��ubuntu��ʹ��cat /var/log/syslog�鿴syslog��Ϣ
	openlog("a.out", LOG_CONS | LOG_PID, LOG_USER);
	
	// ��log��־д����Ϣ����Ϣ����ʾ��Ϣ
	syslog(LOG_INFO, "My name is Rston, The time of now is %ld.\n", time(NULL));
	
	// �رպ�syslogd���ӵ�ͨ��
	closelog();
	
	return 0;
}