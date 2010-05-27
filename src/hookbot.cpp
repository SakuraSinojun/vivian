

#include "def.h"

#include <windows.h>
#include <stdio.h>
#include <vector>
#include <iostream>

#include "window.h"

#include "message.h"
#include "analyser.h"


std::vector<QQWND>	vQQWnd;
QQWND				g_qqwnd;
int					lastUnpokeMsg;


extern	std::vector<QQMESSAGE> 				vMsg;


int findStr(const char * str1, const char * str2, int nStart=0)
{
	int i;
	int l;
	int len;
	char * temp;
	
	len = lstrlen(str1);
	l = lstrlen(str2);
		
	temp = new char [l+1];
	
	for (i=nStart; i<len; i++)
	{
		memset(temp, 0, l+1);
		memcpy(temp, str1+i, l);
		
		if (lstrcmp(temp, str2)==0)
		{
			return i;
		}
	}
	return -1;
}

BOOL CALLBACK ChildWindowProcess(HWND hwnd, LPARAM lParam)
{

	int 							l;
	char * 							caption;
	char 							clsName[1024];
	HWND 							hParent;
	std::vector<QQWND>::iterator 	iter;
	QQWND							qw;
	
	
	l = GetWindowTextLength(hwnd);
	caption = new char [l+2];
	GetWindowText (hwnd, caption, l+1);
	GetClassName (hwnd, clsName, sizeof(clsName));
	hParent=::GetParent(hwnd);

	memset(&qw, 0, sizeof(qw));
	
	iter = vQQWnd.end();
	iter --;
	
	if (lstrcmp(caption, "发送(S)")==0)
	{
		//printf ("\tSend Button: %d %s\n", hwnd, caption);
		iter->hSend = hwnd;
	}else if(lstrcmp(clsName, "RichEdit20A")==0 && hParent == (HWND)lParam)
	{
		//printf ("\tChat Widnow: %d %s\n", hwnd, caption);
		iter->hChat = hwnd;
	}else if (lstrcmp(clsName, "RichEdit20A")==0 && hParent != (HWND)lParam)
	{
		//printf( "\tInput Window: %d %s\n", hwnd, caption);
		iter->hInput = hwnd;
	}
	
	return true;
	
}


BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam)
{

	int 							l;
//	int 							i;
	char * 							caption;
	QQWND							qw;
		
	

	l = GetWindowTextLength (hwnd);	
	
	caption = new char[l+2];
	memset(caption, 0, l+2);
	GetWindowText(hwnd, caption, l+1);
	
	//printf("Find window: %d %s\n", hwnd, caption);
	
	
	if (findStr(caption, "群")>=0 || findStr(caption, "交谈")>=0 || findStr(caption, "聊天")>=0)
	{
		memset(&qw, 0, sizeof(qw));
		qw.hWnd = hwnd;
		vQQWnd.push_back(qw);
		
		//printf("Find window: %d %s\n", hwnd, caption);		
		::EnumChildWindows (hwnd,ChildWindowProcess,(LPARAM)hwnd);
	}
	
	delete caption;

	return true;
}

void Initialize()
{

	int 							l;
	char * 							temp;
	int 							i;
	
	
	printf ("正在初始化...\n");
	InitPlugin();
	printf ("初始化完成.\n");
	
	
	EnumWindows(EnumWindowsProc,(LPARAM)NULL);

	printf ("---------------------------------------------\n");
	printf ("                  窗口列表                   \n");
	printf ("---------------------------------------------\n");
	
	
	//for (iter = vQQWnd.begin(); iter != vQQWnd.end(); iter++)
	
	for (i=0; i<vQQWnd.size(); i++)
	{
		l = GetWindowTextLength (vQQWnd[i].hWnd);
		temp = new char [l+2];
		memset (temp, 0, l+2);
		GetWindowText (vQQWnd[i].hWnd, temp, l+1);
		printf("\t%d  --  %s\n", i, temp);
		delete temp;
	}
	
	printf ("---------------------------------------------\n");
	
	i=-1;
	printf ("请选译：\n");
	std::cin>>i;
	
	if (i==-1 || i>=vQQWnd.size())
	{
		exit(0);
	}
	
	memset(&g_qqwnd, 0, sizeof(g_qqwnd));
	g_qqwnd = vQQWnd[i];
	
	lastUnpokeMsg = 0;
	
	
	temp = GetBash();
	
	::SendMessage (g_qqwnd.hInput, EM_SETSEL, 0, -1);
	::SendMessage (g_qqwnd.hInput, EM_REPLACESEL, 1, (LPARAM)temp);

	::Sleep(100);
	::SendMessage (g_qqwnd.hSend, WM_LBUTTONDOWN, 0, 0);
	::SendMessage (g_qqwnd.hSend, WM_LBUTTONUP, 0, 0);
					
	
}



//void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR nEventID, DWORD uElapse)
void OnTimer(UINT nEventID)
{
	int				l;
	char	*		temp;
	char	*		message;
	
	wchar_t * test;
	
	
	switch (nEventID)
	{
	case 1001:
	
		if (!IsWindow(g_qqwnd.hWnd))
		{
			exit(0);
		}
		
		//这地方必须是Unicode编码才能读出来。
		l = SendMessageW (g_qqwnd.hChat, WM_GETTEXTLENGTH, 0, 0);
		test = new wchar_t [l+2];
		memset (test, 0, 2*(l+2));
		SendMessageW (g_qqwnd.hChat, WM_GETTEXT, l, (LPARAM)test);
		l = WideCharToMultiByte (CP_ACP, 0, test, -1, NULL, 0, 0, 0);
		temp = new char [l+10];
		memset (temp, 0, l+10);
		WideCharToMultiByte (CP_ACP, 0, test, -1, temp, l, 0, 0);
	
		delete test;
		
		
		parsemessage (temp);
		
		delete temp;
		
		while (lastUnpokeMsg < vMsg.size())
		{
			printf ("%s %s %s\n", vMsg[lastUnpokeMsg].Time, vMsg[lastUnpokeMsg].Sender, vMsg[lastUnpokeMsg].message);
			
			if ((temp=analyse(vMsg[lastUnpokeMsg].message))!=NULL)
			{
				message = new char [strlen(temp) + 100];
				wsprintf(message, "---------高科技算命，童叟无欺---------\r\n\r\n[[%s(%s)]]\n%s", vMsg[lastUnpokeMsg].Sender, vMsg[lastUnpokeMsg].Time, temp);
				//发送。
				::SendMessage (g_qqwnd.hInput, EM_SETSEL, 0, -1);
				::SendMessage (g_qqwnd.hInput, EM_REPLACESEL, 1, (LPARAM)message);

				::Sleep(100);
				::SendMessage (g_qqwnd.hSend, WM_LBUTTONDOWN, 0, 0);
				::SendMessage (g_qqwnd.hSend, WM_LBUTTONUP, 0, 0);
				
				delete message;
			}
			
			lastUnpokeMsg++;
		}
		
		break;
	case 1002:
		break;
	default:
		break;
	}
}

LRESULT CALLBACK _WndProc(HWND hwnd, UINT uMsg, WPARAM wParam,LPARAM lParam) 
{ 
	switch(uMsg) 
	{
	case WM_CREATE:
		SetTimer (hwnd, 1001, 1000, NULL);
		break;
	case WM_TIMER:
		OnTimer (wParam);
		break;
	default:  
		break;
	} 
	return  DefWindowProc(hwnd,uMsg,wParam,lParam); ; 
}


/*
DWORD WINAPI _threadProc(LPVOID lpParameter)
{
	return 0;
}

void Start()
{
	HANDLE h;

	h = CreateThread ( (LPSECURITY_ATTRIBUTES)NULL, 
						(DWORD)0,
						_threadProc,
						(LPVOID)NULL,
						(DWORD)0,
						(LPDWORD)0);

	WaitForSingleObject (h, -1);

}

*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Initialize();
	
	CreateMyWindow (_WndProc, hInstance);
	//Start();
	
	return 0;
}

int main()
{
	return WinMain(NULL, NULL, NULL, SW_SHOW);
}



 



