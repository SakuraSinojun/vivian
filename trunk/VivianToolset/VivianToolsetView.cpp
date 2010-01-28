// VivianToolsetView.cpp : CVivianToolsetView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CVivianToolsetView 构造/析构

CVivianToolsetView::CVivianToolsetView()
{
	// TODO: 在此处添加构造代码

}

CVivianToolsetView::~CVivianToolsetView()
{
}

BOOL CVivianToolsetView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CVivianToolsetView 绘制

void CVivianToolsetView::OnDraw(CDC* /*pDC*/)
{
	CVivianToolsetDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CVivianToolsetView 打印

BOOL CVivianToolsetView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CVivianToolsetView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CVivianToolsetView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CVivianToolsetView 诊断

#ifdef _DEBUG
void CVivianToolsetView::AssertValid() const
{
	CView::AssertValid();
}

void CVivianToolsetView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CVivianToolsetDoc* CVivianToolsetView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CVivianToolsetDoc)));
	return (CVivianToolsetDoc*)m_pDocument;
}
#endif //_DEBUG


// CVivianToolsetView 消息处理程序
