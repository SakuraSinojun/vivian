// VivianToolsetDoc.h : CVivianToolsetDoc ��Ľӿ�
//


#pragma once


class CVivianToolsetDoc : public CDocument
{
protected: // �������л�����
	CVivianToolsetDoc();
	DECLARE_DYNCREATE(CVivianToolsetDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CVivianToolsetDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


