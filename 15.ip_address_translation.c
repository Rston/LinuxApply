/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：待定
 * 功能：演示inet_addr和inet_pton和inet_ntop函数的使用。
 * 0x66		01		a8		c0
 * 0d102	001		168		192
 * 网络字节序即大端模式，网络中只允许有大端模式，不允许有小端模式。
 */
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
 
#define IPADDR "192.168.1.102" 
 
int main(int argc, char **argv)
{
#if 1
	const char *ret = NULL;
	in_addr_t addr = 0x6601a8c0;
	char buf[50] = {0};
	
	ret = inet_ntop(AF_INET, &addr, buf, sizeof(buf));
	if (NULL == ret)
	{
		perror("inet_ntop error");
		exit(-1);
	}
	
	printf("addr = %s.\n", buf);			// addr = 192.168.1.102.
#endif
	
#if 0
	struct in_addr addr = {0};
	int ret = -1;
	
	ret = inet_pton(AF_INET, IPADDR, &addr);
	if (1 != ret)
	{
		printf("inet_pton error.\n");
		exit(-1);
	}
	
	printf("addr = 0x%x.\n", addr.s_addr);	// addr = 0x6601a8c0.
#endif	

#if 0
	in_addr_t addr = 0;
	
	addr = inet_addr(IPADDR);
	
	printf("addr = 0x%x.\n", addr);			// addr = 0x6601a8c0.
#endif
	return 0;
}
