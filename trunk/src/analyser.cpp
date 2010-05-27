


#include "analyser.h"

#include <windows.h>
#include <vector>

typedef char * (WINAPI *LPFNGETINFO)();
typedef char * (WINAPI *LPFNGETCOMMAND)();
typedef char * (WINAPI *LPFNEXECUTECOMMAND)(const char *);
//typedef void   (WINAPI *LPFNCONFIG)();
typedef char * (WINAPI *LPFNGETUSAGE)();


struct PLUGIN
{
	char				dllname[512];
	HINSTANCE			hInstance;
	LPFNGETINFO 		lpfnGetInfo;
	LPFNGETCOMMAND 		lpfnGetCommand;
	LPFNEXECUTECOMMAND	lpfnExecuteCommand;
	//LPFNCONFIG 			lpfnConfig;
	LPFNGETUSAGE 		lpfnGetUsage;
};

std::vector<PLUGIN> vp;


void LoadPlugin (const char * path, const char * dllname)
{
	char * 	temp;
	int		l;
	PLUGIN	plug;
	
	memset (&plug, 0, sizeof(plug));
	
	l = strlen(path) + strlen(dllname) + 2 ;
	temp = new char [l];
	memset (temp, 0, l);
	
	strcpy(temp, path);
	strcat(temp, dllname);
	
	printf ("Loading Plugin : %s\n", dllname);
	
	strcpy (plug.dllname, dllname);
	plug.hInstance = LoadLibrary (temp);
	
	printf ("\tLoading GetInfo()...                           ");
	plug.lpfnGetInfo 		= (LPFNGETINFO)GetProcAddress (plug.hInstance, "GetInfo");
	if (plug.lpfnGetInfo != NULL)
	{
		printf ("[OK]\n");
	}else{
		printf ("[Failed]\n");
	}
	printf ("\tLoading GetCommand()...                        ");	
	plug.lpfnGetCommand 	= (LPFNGETCOMMAND)GetProcAddress (plug.hInstance, "GetCommand");
	if (plug.lpfnGetInfo != NULL)
	{
		printf ("[OK]\n");
	}else{
		printf ("[Failed]\n");
	}
	printf ("\tLoading ExecuteCommand()...                    ");	
	plug.lpfnExecuteCommand	= (LPFNEXECUTECOMMAND)GetProcAddress (plug.hInstance, "ExecuteCommand");
	if (plug.lpfnGetInfo != NULL)
	{
		printf ("[OK]\n");
	}else{
		printf ("[Failed]\n");
	}
	
	/*
	printf ("\tLoading Config()...                            ");	
	plug.lpfnConfig 		= (LPFNCONFIG)GetProcAddress (plug.hInstance, "Config");
	if (plug.lpfnGetInfo != NULL)
	{
		printf ("[OK]\n");
	}else{
		printf ("[Failed]\n");
	}
	*/
	
	
	printf ("\tLoading GetUsage()...                          ");	
	plug.lpfnGetUsage 		= (LPFNGETUSAGE)GetProcAddress (plug.hInstance, "GetUsage");
	if (plug.lpfnGetInfo != NULL)
	{
		printf ("[OK]\n");
	}else{
		printf ("[Failed]\n");
	}
	
	vp.push_back(plug);
	
}

void InitPlugin()
{

	char  				fname[1024];
	WIN32_FIND_DATA 	fd;
	//int 				l;
	HANDLE 				hSearch;
	char  				path[1024];
	
	char * filePathName=new char[MAX_PATH+5];

	memset ( filePathName , 0,  MAX_PATH + 5 );
	
	::GetModuleFileName ( NULL , filePathName , MAX_PATH + 5 );

	for ( int i = MAX_PATH + 4 ; i >= 0 ; i -- )
	{
		if ( *( filePathName + i ) !=  '\\' )
		{
			*( filePathName + i ) = 0;
		}else{
			break;
		}
	}
	
	memset (path, 0, 1024);
	strcpy (path, filePathName);
	strcat (path, "Plugin\\");
	strcat (filePathName, "Plugin\\*.dll");
	
	try{
		

		memset(fname,0, 1024);
		ZeroMemory(&fd, sizeof(WIN32_FIND_DATA));		
		   
		bool bSearchFinished = false;
	    
		hSearch = FindFirstFile(filePathName, &fd);
		//Is directory

		if( (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..") )       
		{

		}else if(strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, ".."))
		{
			LoadPlugin (path, fd.cFileName);
		}
		
		while( !bSearchFinished )
		{
		   if( FindNextFile(hSearch, &fd) )
		   {
		   		if( (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) && strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..") ) 
				{
				   /*
					strcpy(tmpPath, rootDir);
					strcat(tmpPath, fd.cFileName);
					FindFileInDir(tmpPath, strRet);
					*/
				}else if( strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, "..") )
				{
					LoadPlugin (path, fd.cFileName);
				}
		   }else{
			   if( GetLastError() == ERROR_NO_MORE_FILES )          //Normal Finished
			   {
				  bSearchFinished = true;
			   }else{
				  bSearchFinished = true;     //Terminate Search
			   }
		   }  
		}
		FindClose(hSearch);
	}catch(...){
	}
	
}

char * trim(const char * str)
{
	int l = strlen(str) + 2;
	char * temp = new char [l];
	memset (temp, 0, l);
	
	int i,j;
	
	j=0;
	
	for (i=0; i<strlen(str); i++)
	{
		if (*(str+i)=='\n' || *(str+i)=='\r' || *(str+i)=='\t' || *(str+i)==' ')
		{
		}else{
			strcpy (temp, str+i);
			break;
		}
	}
	
	return temp;
}

bool match(const char * message, const char * filter)
{
	int i;
	
	if (strlen(message) < strlen(filter))
	{
		return false;
	}
	
	char * temp = new char [strlen(filter)+2];
	
	for (i=0; i<strlen(message)-strlen(filter)+1; i++)
	{
		memset (temp, 0, strlen(filter)+2);
		memcpy (temp, message+i, strlen(filter));
		if (strcmp(temp, filter)==0 && ((i==0)?true:(*(message+i-1) != '\"' && *(message+i-1)!='\t' )) )
		{
			printf ("匹配%s与%s成功，其前字符为\n%c(%d)\n", temp, filter, *(message+i-1), *(message+i-1));
			delete temp;
			return true;
		}
	}
	
	delete temp;
	return false;
}

char * analyse(const char * message)
{
	int i;
	char * msg = trim(message);
	char * p;
	
	for (i=0; i<vp.size(); i++)
	{
		if (match (msg, vp[i].lpfnGetCommand()))
		{
			printf("与%s(%s)匹配成功。\n", vp[i].dllname, vp[i].lpfnGetCommand());
			p = vp[i].lpfnExecuteCommand(msg);
			//p = "This is a test.";
			delete msg;
			return p;
		}
	}
	
	delete msg;
	return NULL;

}

char * GetBash()
{
	static char * temp = NULL;
	if (temp != NULL)
	{
		delete temp;
	}
	temp = new char [1024];
	strcpy (temp, "----------HookBot Start---------\n");
	strcat (temp, "已加载插件：\n\t");
	for (int i =0; i<vp.size(); i++)
	{
		strcat (temp, vp[i].dllname);
		strcat (temp, "\t");
		strcat (temp, vp[i].lpfnGetInfo());
		strcat (temp, "\t\"");
		strcat (temp, vp[i].lpfnGetCommand());
		strcat (temp, "\"\n\t");
	}
	
	return temp;
	
}





