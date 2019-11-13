// HeadView.cpp : 实现文件
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


// CHeadView 绘图

void CHeadView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码

	CBrush brush(RGB(204,204,204));
	CRect rect;
	GetClientRect(rect);
	pDC->FillRect(&rect, &brush);
}


// CHeadView 诊断

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


// CHeadView 消息处理程序

int CHeadView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

