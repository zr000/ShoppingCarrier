// 3DvisBaseManagerView.h : CMy3DvisBaseManagerView ��Ľӿ�
//


#pragma once


class CMy3DvisBaseManagerView : public CView
{
protected: // �������л�����
	CMy3DvisBaseManagerView();
	DECLARE_DYNCREATE(CMy3DvisBaseManagerView)

// ����
public:
	CMy3DvisBaseManagerDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMy3DvisBaseManagerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // 3DvisBaseManagerView.cpp �еĵ��԰汾
inline CMy3DvisBaseManagerDoc* CMy3DvisBaseManagerView::GetDocument() const
   { return reinterpret_cast<CMy3DvisBaseManagerDoc*>(m_pDocument); }
#endif

