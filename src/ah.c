#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "strip.h"

/*
 * 取得原来的命令
 */
char * get_src_exe( char * cmd )
{
	char * src;
	int len;
	len = strlen(cmd);
	src = (char*)malloc(len+12);
	strcpy(src,cmd);
	if(src[len-1]=='e' && src[len-2]=='x' && 
		src[len-3]=='e' && src[len-4]=='.')
	{
		src[len-4]=0;
		strcat(src,"_src.exe");
	}
	else
	{
		strcat(src,"_src");
	}
	return src;
}

/*
 * 程序将替换原来的程序，并传递参数。如果源程序叫ar.exe，将被改名为ar_src.exe。
 * 然后将本程序命名为ar.exe，这样任何对原来ar.exe调用都过一道本程序。
 */
int main(int n,char *args[])
{
	char **arg;
	char * src_cmd;
	int i,ret;

	arg = (char **)malloc((n+1)*sizeof(char*));
	memset(arg,0,sizeof(char*)*(n+1));
	src_cmd = get_src_exe(args[0]);
	printf("------------------------------------\n");
	for(i=0;i<n;i++)
	{
		arg[i] = strip_cygdrive(args[i]);
		printf("[%d] %s -> %s\n",i,args[i],arg[i]);
	}
	ret = execv(src_cmd,arg);
	printf("%s return %d errno=%d\n",src_cmd,ret,errno);
	printf("------------------------------------\n");
	return ret;
}