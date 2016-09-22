/*
 * 公司：XXXX
 * 作者：Rston
 * 博客：http://blog.csdn.net/rston
 * GitHub：https://github.com/rston
 * 项目：文件类型和文件权限管理
 * 功能：使用umask函数设置新建文件的默认权限。
 * Linux下设置新建文件时的默认权限掩码由umask函数设置 
 * mode_t umask(mode_t umask) 传入四位八进制数，返回系统原先的权限掩码 
 * 0666对应文件权限中的0000 0444对应文件权限中的0222 
 * 	
 * 系统原来的权限掩码是：22.
 * 系统新的权限掩码是：666.
 * 创建了文件test1.txt.
 * -r-xr-xr-x 1 root root 0 Jul 11  2016 test1.txt
 * 系统原来的权限掩码是：666.
 * 系统新的权限掩码是：444.
 * 创建了文件test2.txt.
 * -rwxrwxrwx 1 root root 0 Jul 11  2016 test2.txt
 */ 

#include <stdio.h>  
#include <stdlib.h>  
#include <sys/stat.h>  
#include <sys/types.h> 

int main(int argc, char **argv)
{
	mode_t new_umask, old_umask;  
    
	new_umask = 0666;  
    old_umask = umask(new_umask);  
    printf("系统原来的权限掩码是：%o.\n",old_umask);  
    printf("系统新的权限掩码是：%o.\n",new_umask);  
    system("touch test1.txt");  
    printf("创建了文件test1.txt.\n"); 
	system("ls test1.txt -l");
	
    new_umask = 0444;  
    old_umask = umask(new_umask);  
    printf("系统原来的权限掩码是：%o.\n",old_umask);  
    printf("系统新的权限掩码是：%o.\n",new_umask);  
    system("touch test2.txt");  
    printf("创建了文件test2.txt.\n");  
    system("ls test2.txt -l");  
    
	return 0;  
}