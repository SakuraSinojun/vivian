// VivianToolset.h : VivianToolset Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CVivianToolsetApp:
// �йش����ʵ�֣������ VivianToolset.cpp
//

class CVivianToolsetApp : public CWinApp
{
public:
	CVivianToolsetApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CVivianToolsetApp theApp;