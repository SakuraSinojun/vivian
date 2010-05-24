
#include "eval_r.h"

#include <stack>
#include <sstream>


bool checkExpr(const char * expr)
{
	int i, j;
	int l = strlen(expr) ;
	char * p = new char[l+1] ;
	bool flag;
	char c;
	int count1,count2;
	
	memset (p, 0, l+1);
	j = 0;
	for (i=0; i<(int)strlen(expr); i++)
	{
		if ( *(expr + i) != ' ' )
		{
			*(p + j) = *(expr + i) ;
			j++ ;
		}
	}
	
	l = strlen(p);
	
	//δ�������
	for (i=0; i<l; i++)
	{
		c = *(p+i);
		
		if (!((c>='0' && c<='9') || c=='.' 
			|| c=='+' || c=='-' || c=='*' || c=='/' 
			|| c=='(' || c==')'))
		{
			delete p ;
			return false;
		}
	}
	
	//����ƥ��
	count1 = 0;
	count2 = 0;
	for (i=0; i<l; i++)
	{	
		c = *(p+i);
		if (c=='(')
		{
			count1++;
		}else if (c==')')
		{
			count2++;
		}
	}
	if (count1 != count2)
	{
		delete p;
		return false;
	}
	
	//��)��ͷ
	if (*p == ')')
	{
		delete p;
		return false ;
	}
	
	//
	if (!((*p >='0' && *p<='9') || *p=='.' || *p =='('))
	{
		delete p;
		return false;
	}
	
	if (!(*(p+l-1)>='0' && *(p+l-1)<='9'  || *(p+l-1)==')'))
	{
		delete p;
		return false;
	}
	
	flag = false ;
	if (!(*(p)>='0' && *p<=9 || *p =='.'))
	{
		flag = true;
	}
	
	//������������
	for(i=0; i<l; i++)
	{
		//printf("%c",*(p+i));
		
		if (!flag)
		{
			if (*(p+i)>='0' && *(p+i)<='9' || *(p+i)=='.')
			{
				//��ǰλ�������֡�
			}else{
				//�Ƿ��š�
				if(*(p+i)!='+' && *(p+i)!='-' && *(p+i)!='*' && *(p+i)!='/'  && *(p+i)!=')')
				{
					delete p;
					return false;
				}
				flag = true;
			}
		}else{
			//�վ�����λ���Ƿ���
			if (*(p+i)>='0' && *(p+i)<='9' || *(p+i)=='.')
			{
				//��ǰλ�������֡�
				flag = false ;
			}else{
				//�Ƿ��š�
				if (! (*(p+i)=='(' || (*(p+i)!='(' && *(p+i-1)==')')))
				{
					delete p;
					return false;
				}
				
			}

		}
	}
	
	//printf("\n");
	
	delete p;
	return true ;
}

float str2float(const char * str)
{
	std::stringstream ss(str);
	float f;
	ss >> f;
 
	return f;
}

int cmpOperator(char op1, char op2)
{
	int o1,o2;
	switch (op1)
	{
	case '+' :
	case '-' :
		o1 = 10 ;
		break ;
	case '*' :
	case '/' :
		o1 = 100 ;
		break ;
	case '$' :
		o1 = 0 ;
		break ;
	default :
		o1 = 1 ;
		break ;
	}
	switch (op2)
	{
	case '+' :
	case '-' :
		o2 = 10 ;
		break ;
	case '*' :
	case '/' :
		o2 = 100 ;
		break ;
	case '(' :
		o2 = 1 ;
		break ;
	default:
		o2 = 0 ;
		break ;
	}
	
	return o1-o2;
}	
	
bool calc(float f1, float f2, char op,float *_out_result)
{
	switch(op)
	{
	case '+':
		f1=f1+f2;
		break;
	case '-':
		f1=f1-f2;
		break;
	case '*':
		f1=f1*f2;
		break;
	case '/':
		if(f2>=-0.00001 && f2<=0.00001)
		{
			*_out_result = 2;
			return false ;
		}
		f1=f1/f2;
		break;
	}

	*_out_result = f1;
	
	return true;
	
}

bool eval_r(const char * expr, float * _out_result)
{
	std::stack<float> sv;
	std::stack<char>  so;
	
	int i, j;
	int l ;
	char * p ;
	char c;
	float f1,f2;
	char o1,o2;
	
	
	//ȥ�ո�
	l = strlen(expr);
	p = new char[l+2];
	memset (p, 0, l+2);
	j = 0;
	for (i=0; i<(int)strlen(expr); i++)
	{
		if ( *(expr + i) != ' ' )
		{
			*(p + j) = *(expr + i) ;
			j++ ;
		}
	}
	l = strlen(p);
	
	//У����ʽ��
	if (!checkExpr(p))
	{
		delete p;
		*_out_result = 1;
		return false;
	}
	
	strcat(p,"$");
	

	/*
	j = 0;
	for (i=0; i<l; i++)
	{
		c = *(p+i);
		if (c=='+' || c=='-' || c=='*' || c=='/')
		{
			j++;
		}
	}
	
	//ֻ��һ�����֡�
	if (j==0)
	{
		for (i=0; i<l; i++)
		{
			c = *(p+i);
			if(c>='0' && c<='9' || c=='.')
			{
				break;
			}
		}
		f1 = str2float(p+i);
		*_out_result = f1 ;
		return true;
	}

	*/
	
	
	i=0;
	while(true)
	{
		c = *(p+i);
		if ((c>='0' && c<='9') || c=='.')
		{
			f1 = str2float(p+i);
			sv.push(f1);
			while ((c>='0' && c<='9') || c=='.')
			{
				i++;
				c = *(p+i);
			}
		}
		o1 = c;
		
		if (c=='$' && so.empty())
		{
			f1 = sv.top();
			*_out_result = f1;
			delete p ;
			return true;
		}

		if (so.empty() || o1=='(')
		{
			so.push(o1);
			i++;
			continue;
		}
		
		o2 = so.top();
		
		if (o1!=')')
		{
			if (cmpOperator(o1,o2)>0)
			{
				so.push(o1);
				i++;
				continue;
			}
			
			f2 = sv.top();
			sv.pop();
			f1 = sv.top();
			sv.pop();
			
			if(!calc(f1,f2,o2,&f1))
			{
				delete p;
				*_out_result = 2;
				return false ;
			}
			sv.push(f1);
			so.pop();

			if (o1 != '$')
			{
				so.push(o1);
				i++;
			}else{
				if (so.empty())
				{
					*_out_result = sv.top();
					delete p;
					return true;
				}
			}
			continue;
		}else{
			while (o2 != '(')
			{
				f2 = sv.top();
				sv.pop();
				f1 = sv.top();
				sv.pop();
				
				so.pop();
				
				if(!calc(f1,f2,o2,&f1))
				{
					delete p;
					*_out_result = 2;
					return false;
				}
				
				sv.push(f1);
				
				o2 =so.top();
			}
			so.pop();
			i++;
			continue;
		}
		
	}
		
	return true;
	
}












