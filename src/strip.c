#include <string.h>

static const char * CYGDRIVE="/cygdrive/";
/*
 * 将cygwin路径转换为windows路径
 * 例如：/cygdrive/c/source 转换为 c:/source
 */
char * strip_cygdrive(char *p)
{
	char * findit;
	char * result;
	int offset;
	if(findit=strstr(p,CYGDRIVE))
	{
		offset = findit-p;
		result = strdup(p);
		strcpy(result+offset+1,result+offset+strlen(CYGDRIVE));
		result[offset]=result[offset+1];
		result[offset+1]=':';
		return result;
	}
	else
		return strdup(p);
}