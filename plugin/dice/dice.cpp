
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

char * joke(const char *p)
{

#define MC(x) (findstr(p, x)>=0)

	////////////////////////////////////////
	//			关于队长
	////////////////////////////////////////
	if ( findstr(p, "队长") >=0 )
	{
		if ( MC("风流") )
		{
			return "\n请注意：队长必须风流！";
		}
		if ( MC("威武") )
		{
			return "\n请注意：队长必须威武！";
		}
		if ( MC("荡漾") )
		{
			return "\n请注意：队长必须荡漾！";
		}
	}

	////////////////////////////////////////
	//			关于其它
	////////////////////////////////////////
	if ( MC("人呢") )
	{
		return "\n /wn 我哪知道呀……";
	}
	
	if ( MC("爸") || MC("爹") || MC("父亲") || MC("daddy") || MC("Daddy") ||
		 MC("DADDY") || MC("father") || MC("Father") || MC("FATHER") )
	{
		return "\n wn 墙了。";
	}
	
	if ( MC("胖子") )
	{
		if ( MC("起床") || MC("醒") || MC("睡") )
		{
			return "\n 还没醒。";
		}
		if ( MC("胖子呢") || MC("去哪了") || MC("在哪") )
		{
			return "\n /wn 我哪知道呀……";
		}
		if ( MC("打你") || MC("打人") )
		{
			return "\n /baiy 不一定。";
		}
		
	}
	
	if ( findstr(p, "你") >= 0)
	{
		if ( MC("叫什么名") || MC("叫什么") || MC("以后就叫") || MC("名字") )
		{
			return "\n 我叫「占占」。";
		}
		if ( MC("喜欢我") )
		{
			return "\n 喜欢。";
		}
		if ( MC("爱我") )
		{
			return "\n 爱死你了。";
		}
		if ( MC("说话") )
		{
			return "\n 啊……";
		}
		if ( MC("英语") || MC("english") || MC("English") )
		{
			return "\n I don't speak English..";
		}
		return NULL;
	}
	
	if ( MC("喜欢还是爱") )
	{
		return "\n /wsn 有什么区别么？";
	}
	

	
	return NULL;
	
#undef MC

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
	
	if (joke(p)!=NULL)
	{
		return joke(p);
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
						sprintf (result, "进行\"%s\"算命，算命结果：\n%s=%s=%d", temp, cmd, p, int(f));
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
			wsprintf (result, "回答问题：「%s」，答案：%s", p, ((i==1) ? "嗯！" : "不。"));
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
			wsprintf (result, "默认骰子面数设置为：%d", i);
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
	char * usage = "Dice Usage:\n   \".r expression [dice-information]\"";
	return usage;
	
}

