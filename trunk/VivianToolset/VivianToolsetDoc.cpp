// VivianToolsetDoc.cpp : CVivianToolsetDoc ���ʵ��
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


// CVivianToolsetDoc ����/����

CVivianToolsetDoc::CVivianToolsetDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CVivianToolsetDoc::~CVivianToolsetDoc()
{
}

BOOL CVivianToolsetDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CVivianToolsetDoc ���л�

void CVivianToolsetDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CVivianToolsetDoc ���

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


// CVivianToolsetDoc ����
