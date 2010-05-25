





#include "message.h"

#include <stdio.h>
#include <vector>




std::vector<QQMESSAGE> 				vMsg;


bool IsSendingTime(const char * str)
{
	int i;
	char c;
	
	//以0D0A换行
	if (*(str+8)!='\n' && *(str+8)!='\r')
	{
		i = (int)*(str+8);
		i = (int)'\n';
		return false;
	}
	
	if (*(str+2) != ':' || *(str+5) != ':')
	{
		return false;
	}
	
	//12:12:12
	for (i=0; i<8; i++)
	{
		c = *(str+i);
		if (!((c>='0' && c<='9') || c==':'))
		{
			return false;
		}
	}
	return true;
	
}



bool parsemessage ( const char * message)
{
	
	int 		i,ii;
	int 		j;
	int 		l , ll;
	int			t;
	char		c;
	int			last_enter;
	QQMESSAGE	msg;
	bool		flag;
	char * p = (char *)message;
	
	memset (&msg, 0, sizeof(msg));
	
	
	l = strlen(message);
	for (i=0; i<l-9; i++)
	{
		if (IsSendingTime(p+i))
		{
			
			j=i-1;
			while (j>=0)
			{
				c = *(p+j);
				if ( c == '\n' )
				{
					break;
				}
				j--;
			}
			
			if (i-j>100)
			{
				continue;
			}
			memset (&msg, 0, sizeof(msg));
			memcpy (msg.Sender, p+j+1, i-j-2);
			memcpy (msg.Time, p+i, 8);
			
			
			//去掉\r
			ll = strlen(msg.Sender);
			for (ii=0; ii<ll; ii++)
			{
				if (*(msg.Sender + ii) == '\r')
				{
					*(msg.Sender + ii) = ' ';
				}
			}
			
			
			//printf ("Sender:\n%s %s", msg.Sender, msg.Time);
			
			//找下一个时间戳
			last_enter = l+1;
			for (j=i+9; j<l-9; j++)
			{
				c = *(p+j);
				if (c=='\n')
				{
					last_enter = j;
				}
				
				if (IsSendingTime(p+j))
				{
					break;
				}		
			}

			if (!IsSendingTime(p+j))
			{
				last_enter = l+1;
			}		
			
			last_enter --;

			//已经找到结尾或下一条消息。
			t = last_enter - i - 9;
			msg.message = new char [t+2];
			memset (msg.message, 0, t+2);
			memcpy (msg.message, p+i+9, t);
			
			
			//判断此条消息是否已经存在
			flag = false;
			for (j=0; j<vMsg.size(); j++)
			{
				if (strcmp(msg.Sender, vMsg[j].Sender)==0 &&
					strcmp(msg.Time, vMsg[j].Time)==0 &&
					strcmp(msg.message, vMsg[j].message)==0)
				{
					flag = true;
					break;
				}
			}
			if (!flag)
			{
				vMsg.push_back(msg);			
			}
		}
	}//end of for
	
	return true;
}



/*

int main()
{

	char * msg ;
	FILE * fp;
	int		l;
	
	fp = fopen("1.txt","r");
	
	msg = new char [1000];
	memset (msg, 0, 1000);

	fread (msg, 1000, 1, fp);
	
	fclose (fp);

	printf(msg);
	
	printf("Start Parsing...\n");
	
	parsemessage(msg);

	int i;
	
	for (i=0; i<vMsg.size(); i++)
	{
		printf("-------------------------------------------\n");
		printf("%s \n%s \n\t%s\n", vMsg[i].Time, vMsg[i].Sender, vMsg[i].message);
	}
	
	
	return 0;
}


*/



