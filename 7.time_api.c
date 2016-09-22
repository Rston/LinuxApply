/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：各种时间函数的使用
 * 功能：演示各种时间函数的使用。	
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
	time_t tNow = -1;
	struct tm tmNow;
	char buf[100] = {0};
	struct timeval tv = {0};
	struct timezone tz = {0};
	int ret = -1;
	
	// 使用time函数
#if 1
	tNow = time(NULL);
#endif
#if 0
	time(&tNow);
#endif
	printf("time: %ld.\n", tNow);			// time: 1468658754.

#if 0	
	// 使用ctime函数
	printf("ctime: %s", ctime(&tNow));		// ctime: Sat Jul 16 01:45:54 2016
#endif

#if 0
	// 使用gmtime
	memset(&tmNow, 0, sizeof(tmNow));
	gmtime_r(&tNow, &tmNow);				// 年116月6日16时8.
	printf("gmtime: 年%d月%d日%d时%d.\n", tmNow.tm_year, tmNow.tm_mon, tmNow.tm_mday, tmNow.tm_hour);
#endif

#if 0	
	// 使用localtime函数
	memset(&tmNow, 0, sizeof(tmNow));
	localtime_r(&tNow, &tmNow);				// 年116月6日16时1.
	printf("localtime: 年%d月%d日%d时%d.\n", tmNow.tm_year, tmNow.tm_mon, tmNow.tm_mday, tmNow.tm_hour);
#endif

#if 0
	// asctime函数
	memset(&tmNow, 0, sizeof(tmNow));
	localtime_r(&tNow, &tmNow);	
	printf("asctime: %s", asctime(&tmNow));	// asctime: Sat Jul 16 06:43:46 2016
#endif

#if 0	
	//	strftime函数
	memset(&tmNow, 0, sizeof(tmNow));
	localtime_r(&tNow, &tmNow);	
	memset(buf, 0, sizeof(buf));
	strftime(buf, sizeof(buf), "%Y * %m * %d, %H-%M-%S.", &tmNow);
	printf("strftime: [%s]\n", buf);
#endif

#if 0	
	// gettimeofday函数
	ret = gettimeofday(&tv, &tz);
	if (ret < 0)
	{
		perror("gettimeofday error");
		exit(-1);
	}
	// seconds: [1468724768].
    // microseconds: [734027].
	// minutes west of Greenwich : [420].
	// type of DST correction: [0].
	printf("seconds: [%ld].\n", tv.tv_sec);
	printf("microseconds: [%ld].\n", tv.tv_usec);
	printf("minutes west of Greenwich : [%d].\n", tz.tz_minuteswest);
	printf("type of DST correction: [%d].\n", tz.tz_dsttime);
#endif
	
	return 0;
}