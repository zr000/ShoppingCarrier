// History.cpp : 实现文件
//

#include "stdafx.h"
#include "3DvisBaseManager.h"
#include "History.h"


// CHistory

IMPLEMENT_DYNAMIC(CHistory, CWnd)

CHistory::CHistory()
{

}

CHistory::~CHistory()
{
}


BEGIN_MESSAGE_MAP(CHistory, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCDESTROY()
END_MESSAGE_MAP()



// CHistory 消息处理程序



void CHistory::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()

		CRect rect;
	GetClientRect(rect);
	CBaseInner.Paint(dc,rect);
}

int CHistory::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	CBaseInner.SetWndTitle(L"历史查询");
	return 0;
}

void CHistory::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::SendMessage(::GetParent(this->m_hWnd),WM_LBUTTONVIEW,(WPARAM)this,0);
	CWnd::OnLButtonDown(nFlags, point);
}

void CHistory::OnNcDestroy()
{
	
	CWnd::OnNcDestroy();
	delete this;
	// TODO: 在此处添加消息处理程序代码
}
