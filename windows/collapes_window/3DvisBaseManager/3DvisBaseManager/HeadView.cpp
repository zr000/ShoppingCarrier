// HeadView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DvisBaseManager.h"
#include "HeadView.h"


// CHeadView

IMPLEMENT_DYNCREATE(CHeadView, CView)

CHeadView::CHeadView()
{

}

CHeadView::~CHeadView()
{
}

BEGIN_MESSAGE_MAP(CHeadView, CView)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CHeadView ��ͼ

void CHeadView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���

	CBrush brush(RGB(204,204,204));
	CRect rect;
	GetClientRect(rect);
	pDC->FillRect(&rect, &brush);
}


// CHeadView ���

#ifdef _DEBUG
void CHeadView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CHeadView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CHeadView ��Ϣ�������

int CHeadView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

