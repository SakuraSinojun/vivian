

#pragma once

#include <windows.h>


#define BKGNDCOLOR	RGB(255,255,255)
#define WINDOW_WIDTH	320
#define WINDOW_HEIGHT	480

void CreateMyWindow(WNDPROC _lpfnWindowProc, HINSTANCE hInstance);

BOOL PointInRect (POINT point, RECT rect) ;



