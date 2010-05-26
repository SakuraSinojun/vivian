
#include "dice.h"

#include <windows.h>
#include "parse.h"
#include "eval_r.h"
#include <stdio.h>


char * GetInfo()
{
	return "骰点插件";
}

char * GetCommand()
{
	return ".r";
}

int findstr (const char * str1, const char * str2, int nStart =0)
{
	int l1 = strlen(str1);
	int l2 = strlen(str2);
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
	
	int i,j;
	char * p;
	char * temp;
	char * cmd;
	float f;
	
	static char * result = NULL;
	
	
	i = findstr (command, ".r");
	
	p = (char *)command + i + 2;
	
	if (*p != ' ')
	{
		return NULL;
	}
	
	while (*p == ' ' || *p == '\n' || *p == '\r')
	{
		p++;
	}
	
	if (*p == '\0')
	{
		return "Invalid Expression.";
	}
	
	
	i = findstr (p, "\r");
	j = findstr (p, "\n");
	
	if (j>i) j=i;
	
	
	i = findstr (p, " ");
	if (i==-1) i=j;
	
	if (i>j && j!=-1) i=j;
	
	if (i==-1)
	{
		i=strlen(p);
	}
	
	temp = p + i;
	
	while (*temp == '\n' || *temp == ' ' || *temp == '\r' || *temp =='\t')
	{
		temp ++;
	}
	
	cmd = new char [i+2];
	memset (cmd, 0, i+2);
	memcpy (cmd, p, i);
	
	//printf ("p=%s, cmd=%s\n",p,cmd);
	
	
	p = parse(cmd);
	
	
	if (p == NULL)
	{
		delete cmd;
		return "Invalid Expression...";
	}else{
		if (!eval_r(p, &f))
		{
			if (result != NULL)
			{
				delete result;
				result = NULL;
			}
			result = new char [strlen(p) + 100];
			strcpy (result, "Cannot calculate the the expression: ");
			strcat (result, p);
			delete cmd;
			return result;
		}else{
			if (result != NULL)
			{
				delete result;
				result = NULL;
			}
			result = new char [strlen(p) + 100];
			wsprintf (result, "进行\"%s\"算命，算命结果：\n%s=%s=%d", temp, cmd, p, int(f));
			delete cmd;
			return result;
		}
	}
	
	delete cmd;
	return NULL;
	
}

void Config()
{

}

char * GetUsage()
{
	char * usage = "Dice Usage:\n   .r expression [dice-information]";
	return usage;
	
}

