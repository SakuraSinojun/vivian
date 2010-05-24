


#include "parse.h"


#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sstream>


char * & CatResult(const char * res)
{
	static char * p = NULL;
	
	int l;
	char * temp ;
	
	if (res==NULL)
	{
		return p;
	}
	
	l = strlen(res) + 1;
	
	if (p!=NULL)
	{
		l += strlen(p) ;
	}
	
	temp = new char[l];
	memset(temp, 0, l);
	
	if (p!=NULL)
	{
		strcpy(temp, p);
		delete p;
	}
	
	strcat(temp, res);
	p = temp;
	
	return p;
	
}

void CleanResult()
{
	char * & p = CatResult(NULL);
	
	if (p!=NULL)
	{
		delete p;
		p = NULL ;
	}
	
}
	


bool IsOp(char c)
{
	if(c=='+' || c=='-' || c=='*' || c=='/' || c=='(' || c==')')
	{
		return true;
	}else{
		return false;
	}
}

bool IsNo(char c)
{
	if(c>='0' && c<='9' || c=='.')
	{
		return true;
	}else{
		return false;
	}
}

bool parseCheckExpr(const char * expr)
{
	int i;
	int l;
	int c;

	l = strlen(expr);

	for (i=0; i<l; i++)
	{
		c = *(expr+i);
		if (!(IsOp(c) || IsNo(c) || c=='d'))
		{
			return false;
		}
	}

	return true;
}

int roll(int dice)
{
	int r;
	
	r = rand() % dice + 1 ;
	
	return r;
	
}

int str2int(const char * str)
{
	std::stringstream ss(str);
	int f;
	ss >> f;
 
	return f;
}

char * parse (const char * expr, int diceface)
{
	
	char * & lastexpr = CatResult(NULL) ;
	
	char * temp;
	
	int i;
	int j;
	int df;
	int po,no;
	int l;
	char c;
	char * p ;
	char * str;
	char * orig_p;
	
	if (!parseCheckExpr(expr))
	{
		return NULL;
	}


	srand(time(NULL));
	
	CleanResult();

	l = strlen(expr);
	i=0;
	j=0;
	p = new char[l+3];
	orig_p = p;
	memset(p, 0, l+3);
	strcpy(p+1, expr);
	p++;
	str = p;
	
	while (true)
	{
		c = *p;
		
		if (c=='\0')
		{
			if (str!=p)
			{
				CatResult(str);
			}
			break;
		}

		if (c!='d')
		{
			p++;
			continue;
		}
		
		no = 1;
		while (!(IsOp(*(p+no)) || *(p+no)=='\0'))
		{
			no++;
		}
		po = 1;
		while (!(IsOp(*(p-po)) || *(p-po)=='\0'))
		{
			po++;
		}
		
		l = p-str-po+1;
		temp = new char [l+1];
		memset(temp, 0, l+1);
		memcpy(temp, str, l);
		CatResult(temp);
		delete temp;
		CatResult("(");

		j = (po==1) ? 1 : str2int(p-po+1) ;
		df = (no==1) ? diceface : str2int(p+1) ;
			
		//骰子数过多……
		if(j>300)
		{
			delete orig_p;
			return NULL;
		}
		
		
		//0面骰子。
		if(df<=0)
		{
			delete orig_p;
			return NULL;
		}
		
		
		temp = new char [100];
		
		for (i=0; i<j; i++)
		{
			memset(temp, 0, 100);
			sprintf(temp, "%d", roll(df));
			CatResult(temp);
			if (i<j-1)
			{
				CatResult("+");
			}
		}
		delete temp ;
		
		CatResult(")");
		p = p + no;
		
		memset (str, 0, p-str);
		str = p;
	}
	
	delete orig_p;
	
	p = CatResult(NULL);
	
	return p ;
	
}


