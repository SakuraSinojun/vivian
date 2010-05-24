

#include "window.h"

HWND hWnd;


void CreateMyWindow(WNDPROC _lpfnWindowProc, HINSTANCE hInstance)
{
	hInstance = GetModuleHandle(NULL);
	
	WNDCLASS wndclas; 
	wndclas.cbClsExtra 	= 0; 
	wndclas.cbWndExtra 	= 0; 
	wndclas.hbrBackground 	= CreateSolidBrush(BKGNDCOLOR);//(HBRUSH)GetStockObject(BLACK_BRUSH); 
	wndclas.hCursor 		= LoadCursor(NULL,IDC_ARROW); 
	wndclas.hIcon 		= LoadIcon(NULL,IDI_APPLICATION); 
	wndclas.hInstance 	= hInstance; 
	wndclas.lpfnWndProc 	= _lpfnWindowProc; 
	wndclas.lpszClassName	= "SAKURAWINDOW"; 
	wndclas.lpszMenuName	= NULL; 
	wndclas.style		= CS_VREDRAW | CS_HREDRAW; 
	RegisterClass(&wndclas); 
	
	hWnd = CreateWindow("SAKURAWINDOW",
				"SAKURAWINDOW",
				WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_DLGFRAME ,
				CW_USEDEFAULT,
				CW_USEDEFAULT, 
				WINDOW_WIDTH,
				WINDOW_HEIGHT,
				NULL,
				NULL,
				hInstance,
				NULL); 
	
	//ShowWindow (hWnd,SW_SHOWNORMAL); 
	
	MSG msg; 
	while(GetMessage(&msg,NULL,0,0)) 
	{ 
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	} 
	
	return ;
}


BOOL PointInRect (POINT point, RECT rect)
{
	if (rect.right < rect.left)
	{
		rect.left  = rect.left + rect.right ;
		rect.right = rect.left - rect.right ;
		rect.left  = rect.left - rect.right ;
	}
	
	if (rect.bottom < rect.top)
	{
		rect.top  	= rect.top + rect.bottom ;
		rect.bottom = rect.top - rect.bottom ;
		rect.top  	= rect.top - rect.bottom ;
	}
	
	if (point.x >= rect.left && point.x <= rect.right && point.y >= rect.top && point.y <= rect.bottom)
	{
		return TRUE ;
	}
	
	return FALSE ;
	
}








