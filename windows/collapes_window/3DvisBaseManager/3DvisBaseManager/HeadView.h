#pragma once


// CHeadView ��ͼ

class CHeadView : public CView
{
	DECLARE_DYNCREATE(CHeadView)

protected:
	CHeadView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CHeadView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	
};


