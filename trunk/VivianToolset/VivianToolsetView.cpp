// VivianToolsetView.cpp : CVivianToolsetView ���ʵ��
//

#include "stdafx.h"
#include "VivianToolset.h"

#include "VivianToolsetDoc.h"
#include "VivianToolsetView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CVivianToolsetView

IMPLEMENT_DYNCREATE(CVivianToolsetView, CView)

BEGIN_MESSAGE_MAP(CVivianToolsetView, CView)
END_MESSAGE_MAP()

// CVivianToolsetView ����/����

CVivianToolsetView::CVivianToolsetView()
{
	// TODO: �ڴ˴���ӹ������

}

CVivianToolsetView::~CVivianToolsetView()
{
}

BOOL CVivianToolsetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CVivianToolsetView ����

void CVivianToolsetView::OnDraw(CDC* /*pDC*/)
{
	CVivianToolsetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CVivianToolsetView ���

#ifdef _DEBUG
void CVivianToolsetView::AssertValid() const
{
	CView::AssertValid();
}

void CVivianToolsetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVivianToolsetDoc* CVivianToolsetView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVivianToolsetDoc)));
	return (CVivianToolsetDoc*)m_pDocument;
}
#endif //_DEBUG


// CVivianToolsetView ��Ϣ�������
