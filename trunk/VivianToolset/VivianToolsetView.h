// VivianToolsetView.h : CVivianToolsetView ��Ľӿ�
//


#pragma once


class CVivianToolsetView : public CView
{
protected: // �������л�����
	CVivianToolsetView();
	DECLARE_DYNCREATE(CVivianToolsetView)

// ����
public:
	CVivianToolsetDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CVivianToolsetView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // VivianToolsetView.cpp �еĵ��԰汾
inline CVivianToolsetDoc* CVivianToolsetView::GetDocument() const
   { return reinterpret_cast<CVivianToolsetDoc*>(m_pDocument); }
#endif

