
#include "dice.h"

#include <windows.h>
#include "parse.h"
#include "eval_r.h"
#include <stdio.h>


int diceface;

char * GetInfo()
{
	diceface = 20;
	return "������";
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
	//			���ڶӳ�
	////////////////////////////////////////
	if ( findstr(p, "�ӳ�") >=0 )
	{
		if ( MC("����") )
		{
			return "\n��ע�⣺�ӳ����������";
		}
		if ( MC("����") )
		{
			return "\n��ע�⣺�ӳ��������䣡";
		}
		if ( MC("����") )
		{
			return "\n��ע�⣺�ӳ����뵴����";
		}
	}

	////////////////////////////////////////
	//			��������
	////////////////////////////////////////
	if ( MC("����") )
	{
		return "\n /wn ����֪��ѽ����";
	}
	
	if ( MC("��") || MC("��") || MC("����") || MC("daddy") || MC("Daddy") ||
		 MC("DADDY") || MC("father") || MC("Father") || MC("FATHER") )
	{
		return "\n wn ǽ�ˡ�";
	}
	
	if ( MC("����") )
	{
		if ( MC("��") || MC("��") || MC("˯") )
		{
			return "\n ��û�ѡ�";
		}
		if ( MC("������") || MC("ȥ����") || MC("����") )
		{
			return "\n /wn ����֪��ѽ����";
		}
		if ( MC("����") || MC("����") )
		{
			return "\n /baiy ��һ����";
		}
		
	}
	
	if ( findstr(p, "��") >= 0)
	{
		if ( MC("��ʲô��") || MC("��ʲô") || MC("�Ժ�ͽ�") || MC("����") )
		{
			return "\n �ҽС�ռռ����";
		}
		if ( MC("ϲ����") )
		{
			return "\n ϲ����";
		}
		if ( MC("����") )
		{
			return "\n �������ˡ�";
		}
		if ( MC("˵��") )
		{
			return "\n ������";
		}
		if ( MC("Ӣ��") || MC("english") || MC("English") )
		{
			return "\n I don't speak English..";
		}
		return NULL;
	}
	
	if ( MC("ϲ�����ǰ�") )
	{
		return "\n /wsn ��ʲô����ô��";
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
						sprintf (result, "����\"%s\"���������������\n%s=%s=%d", temp, cmd, p, int(f));
					}else{
						sprintf (result, "����\"%s\"���������������\n%s=%s=%f", temp, cmd, p, f);
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
			wsprintf (result, "�ش����⣺��%s�����𰸣�%s", p, ((i==1) ? "�ţ�" : "����"));
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
			wsprintf (result, "Ĭ��������������Ϊ��%d", i);
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

