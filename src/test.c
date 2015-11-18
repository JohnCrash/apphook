#include <stdio.h>

int main(int n,char * arg[])
{
	int i;
	printf("test.exe\n");
	for(i=0;i<n;i++)
	{
		printf("%d %s\n",i,arg[i]);
	}
	return 0;
}