// VivianToolsetView.h : CVivianToolsetView 类的接口
//


#pragma once


class CVivianToolsetView : public CView
{
protected: // 仅从序列化创建
	CVivianToolsetView();
	DECLARE_DYNCREATE(CVivianToolsetView)

// 属性
public:
	CVivianToolsetDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 实现
public:
	virtual ~CVivianToolsetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // VivianToolsetView.cpp 中的调试版本
inline CVivianToolsetDoc* CVivianToolsetView::GetDocument() const
   { return reinterpret_cast<CVivianToolsetDoc*>(m_pDocument); }
#endif

