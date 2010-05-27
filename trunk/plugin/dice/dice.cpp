
#include "dice.h"

#include <windows.h>
#include "parse.h"
#include "eval_r.h"
#include <stdio.h>


int diceface;

char * GetInfo()
{
	diceface = 20;
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
	char arg;
	static char * result = NULL;
	
	
	i = findstr (command, ".r");
	
	p = (char *)command + i + 2;

	
	arg = *p;
	
	if (arg != ' ')
	{
		p ++;
	}
	
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
		return "Invalid Expression.\nDice Usage:   \".r expression [dice-information]\"";
	}
	
	switch (arg)
	{
		case ' ':
		case 'f':	
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
					
			p = parse(cmd, diceface);
					
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
					if (arg == ' ')
					{
						wsprintf (result, "进行\"%s\"算命，算命结果：\n%s=%s=%d", temp, cmd, p, int(f));
					}else{
						sprintf (result, "进行\"%s\"算命，算命结果：\n%s=%s=%f", temp, cmd, p, f);
					}
					delete cmd;
					return result;
				}
			}
			delete cmd;
			return NULL;
			
			break;
		case 'b':
			i = roll(2) - 1;
			if (result != NULL)
			{
				delete result;
				result = NULL;
			}
			result = new char [strlen(p) + 100];
			wsprintf (result, "回答%s问题：%s", p, ((i==1) ? "当然" : "不"));
			return result;
			break;
		case 'c':
			i = str2int(p);
			if (i<=0 || i>10000)
			{	
				return "Invalid Config Arguments. diceface must be the range [1,10000].";
			}
			diceface = i;
			if (result != NULL)
			{
				delete result;
				result = NULL;
			}
			result = new char [100];
			wsprintf (result, "骰子默认面数设为：%d", i);
			return result;
			break;
		default:
			return GetUsage();
			break;
	}
}

void Config()
{

}

char * GetUsage()
{
	char * usage = "Dice Usage:\n   .r expression [dice-information]";
	return usage;
	
}

