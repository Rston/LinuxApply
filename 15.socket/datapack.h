/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：tcp协议和socket编程
 * 功能：封装数据包。
 */
 
#define CMD_REGISTER	1001	// 注册学生信息
#define CMD_CHECK		1002	// 检验学生信息
#define CMD_GETINFO		1003	// 获取学生信息

#define STAT_OK			30		// 回复ok
#define STAT_ERR		31		// 回复出错了

typedef struct commu
{
	char name[20];				// 学生姓名
	int age;					// 学生年龄
	int cmd;					// 命令码
	int stat;					// 状态信息，用来回复
}info;

