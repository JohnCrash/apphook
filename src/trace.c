#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

char * get_process_path( )
{
	char arg1[20];
	char exepath[1024 + 1] = {0};

	sprintf( arg1, "/proc/%d/exe", getpid() );
	readlink( arg1, exepath, 1024 );
	return strdup(exepath);
}

char * read_cmd(char *abs)
{
	FILE * fp;
	int len;
	char * buf;
	fp=fopen(abs,"r");
	if(fp)
	{
		fseek(fp,0,SEEK_END);
		len = ftell(fp);
		buf = (char*)malloc(len);
		fseek(fp,0,SEEK_SET);
		fread(buf,len,1,fp);
		fclose(fp);
		return buf;
	}
	return NULL;
}
/*
 * 取得原来的命令
 */
char * get_src_exe( char * arg )
{
	char * pp;
	char * abs;
	char * cmd;
	pp = get_process_path();
	abs = (char *)malloc(strlen(pp)+12);
	strcpy(abs,pp);
	strcat(abs,".cmd");
	cmd = read_cmd(abs);
	if(cmd)
	{
		return cmd;
	}
	else
	{
		return abs;
	}
}

char * get_log_file(char *arg)
{
	char * pp;
	char * abs;
	pp = get_process_path();
	abs = (char *)malloc(strlen(pp)+12);
	strcpy(abs,pp);
	strcat(abs,".log");
	return abs;
}
/*
 * 程序运行同目录下同名后缀.cmd中的配置程序
 * 同时将产生的参数写入到同名后缀.log的文件中
 */
int main(int n,char *args[])
{
	char **arg;
	char * src_cmd;
	int i,ret;
	FILE * fp;
	
	printf("%s\n",get_process_path());
	arg = (char **)malloc((n+1)*sizeof(char*));
	memset(arg,0,sizeof(char*)*(n+1));
	src_cmd = get_src_exe(args[0]);
	//args[0] = strdup(src_cmd);
	fp = fopen(get_log_file(args[0]),"a+");
	fprintf(fp,"------------------------------------\n");
	for(i=0;i<n;i++)
	{
		fprintf(fp,"[%d] %s\n",i,args[i]);
	}
	fprintf(fp,"execute %s\n",src_cmd);
	fclose(fp);
	ret = execv(src_cmd,args);
	printf("%s return %d errno=%d\n",src_cmd,ret,errno);
	printf("------------------------------------\n");
	return ret;
}