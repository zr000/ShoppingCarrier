// RightView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DvisBaseManager.h"
#include "RightView.h"


// CRightView

IMPLEMENT_DYNCREATE(CRightView, CView)

CRightView::CRightView()
{

}

CRightView::~CRightView()
{
}

BEGIN_MESSAGE_MAP(CRightView, CView)
END_MESSAGE_MAP()


// CRightView ��ͼ

void CRightView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���

	CBrush brush(RGB(226,226,226));
	CRect rect;
	GetClientRect(rect);
	pDC->FillRect(&rect, &brush);
}


// CRightView ���

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CRightView ��Ϣ�������
