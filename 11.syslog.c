/*
 * 公司：XXXX
 * 作者：Rston
 * 项目：进程关系和进程间通信
 * 功能：演示syslog日志服务的使用。	
 */
 
#include <stdio.h>
#include <syslog.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char **argv)
{
	printf("my pid = %d.\n", getpid());

	// 打开和syslogd相连接的通道；程序名标志为a.out；
	// 若信息无法写到log中则将信息直接发送到控制台；
	// 信息中包含进程PID号；信息级别处于普通用户级别
	// 在ubuntu中使用cat /var/log/syslog查看syslog信息
	openlog("a.out", LOG_CONS | LOG_PID, LOG_USER);
	
	// 向log日志写入信息；信息是提示信息
	syslog(LOG_INFO, "My name is Rston, The time of now is %ld.\n", time(NULL));
	
	// 关闭和syslogd连接的通道
	closelog();
	
	return 0;
}