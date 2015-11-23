#include <stdio.h>
#include <stdlib.h>
#ifndef WIN32
#include <unistd.h>
#endif

void printenv()
{
	int i = 0;
	char ** envs = environ;
	if(envs)
	{
		while(envs[i]!=NULL)
		{
			printf("%s\n",envs[i]);
			i++;
		}
	}
	else
	{
		printf("environ return NULL\n");
	}
}

int main(int n,char * arg[])
{
	int i;
	printf("test.exe\n");
	printenv();
	for(i=0;i<n;i++)
	{
		printf("%d %s\n",i,arg[i]);
	}
	return 0;
}