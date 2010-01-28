// VivianToolsetDoc.cpp : CVivianToolsetDoc 类的实现
//

#include "stdafx.h"
#include "VivianToolset.h"

#include "VivianToolsetDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVivianToolsetDoc

IMPLEMENT_DYNCREATE(CVivianToolsetDoc, CDocument)

BEGIN_MESSAGE_MAP(CVivianToolsetDoc, CDocument)
END_MESSAGE_MAP()


// CVivianToolsetDoc 构造/析构

CVivianToolsetDoc::CVivianToolsetDoc()
{
	// TODO: 在此添加一次性构造代码

}

CVivianToolsetDoc::~CVivianToolsetDoc()
{
}

BOOL CVivianToolsetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CVivianToolsetDoc 序列化

void CVivianToolsetDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CVivianToolsetDoc 诊断

#ifdef _DEBUG
void CVivianToolsetDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CVivianToolsetDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CVivianToolsetDoc 命令
