
#include "sign.h"

#include <windows.h>

#include <stdio.h>


char * GetInfo()
{
		return "点名插件";
}

char * GetCommand()
{
	return "点名";
}

int findstr (const char * str1, const char * str2, int nStart =0)
{
	int l1 = lstrlenA(str1);
	int l2 = lstrlenA(str2);
	int i;
	char * temp;
	
	if (l1<l2) return -1;
	
	temp = new char [l2+2];
	
	for (i=nStart; i<=l1-l2; i++)
	{
		memset (temp, 0, l2+2);
		memcpy (temp, str1+i, l2);
		
		if (strcmp(temp, str2)==0)
		{
			delete temp;
			return i;
		}
	
	}
	
	delete temp;
	return -1;
}

char * ExecuteCommand(const char * command)
{
	int i = findstr(command, "点名");
	
	if (i==-1) return NULL;
	
	if ( *(command+i-1) != '\"' )
	{
		return "\"点名\"：\n\n到！\n";
	}
		
	return NULL;
}

void Config()
{

}

char * GetUsage()
{
	return NULL;

}

