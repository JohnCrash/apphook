#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "strip.h"

char * get_process_path( )
{
	char arg1[20];
	char exepath[1024 + 1] = {0};

	sprintf( arg1, "/proc/%d/exe", getpid() );
	readlink( arg1, exepath, 1024 );
	return strdup(exepath);
}
/*
 * 取得原来的命令
 */
char * get_src_exe( char * cmd )
{
	char * pp;
	char * abs;
	pp = get_process_path();
	abs = (char *)malloc(strlen(pp)+12);
	strcpy(abs,pp);
	strcat(abs,"_src");
	return abs;
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

	printf("%s\n",get_process_path());
	arg = (char **)malloc((n+1)*sizeof(char*));
	memset(arg,0,sizeof(char*)*(n+1));
	src_cmd = get_src_exe(args[0]);
	printf("------------------------------------\n");
	for(i=0;i<n;i++)
	{
		arg[i] = strip_cygdrive(args[i]);
		printf("[%d] %s -> %s\n",i,args[i],arg[i]);
	}
	printf("execute %s\n",src_cmd);

	ret = execv(src_cmd,arg);
	printf("%s return %d errno=%d\n",src_cmd,ret,errno);
	printf("------------------------------------\n");
	return ret;
}