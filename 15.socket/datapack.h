/*
 * ��˾��XXXX
 * ���ߣ�Rston
 * ���ͣ�http://blog.csdn.net/rston
 * GitHub��https://github.com/rston
 * ��Ŀ��tcpЭ���socket���
 * ���ܣ���װ���ݰ���
 */
 
#define CMD_REGISTER	1001	// ע��ѧ����Ϣ
#define CMD_CHECK		1002	// ����ѧ����Ϣ
#define CMD_GETINFO		1003	// ��ȡѧ����Ϣ

#define STAT_OK			30		// �ظ�ok
#define STAT_ERR		31		// �ظ�������

typedef struct commu
{
	char name[20];				// ѧ������
	int age;					// ѧ������
	int cmd;					// ������
	int stat;					// ״̬��Ϣ�������ظ�
}info;

