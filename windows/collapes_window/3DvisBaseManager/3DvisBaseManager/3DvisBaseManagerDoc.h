// 3DvisBaseManagerDoc.h : CMy3DvisBaseManagerDoc ��Ľӿ�
//


#pragma once


class CMy3DvisBaseManagerDoc : public CDocument
{
protected: // �������л�����
	CMy3DvisBaseManagerDoc();
	DECLARE_DYNCREATE(CMy3DvisBaseManagerDoc)

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
	virtual ~CMy3DvisBaseManagerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


