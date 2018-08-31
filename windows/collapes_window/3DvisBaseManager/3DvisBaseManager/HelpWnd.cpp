// HelpWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "3DvisBaseManager.h"
#include "HelpWnd.h"


// CHelpWnd

IMPLEMENT_DYNAMIC(CHelpWnd, CWnd)

CHelpWnd::CHelpWnd()
{

}

CHelpWnd::~CHelpWnd()
{
}


BEGIN_MESSAGE_MAP(CHelpWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_NCDESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CHelpWnd 消息处理程序



void CHelpWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect rect;
	GetClientRect(rect);
	CBaseInner.Paint(dc,rect);
}

void CHelpWnd::OnNcDestroy()
{
	CWnd::OnNcDestroy();
delete this;
	// TODO: 在此处添加消息处理程序代码
}

void CHelpWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::SendMessage(::GetParent(this->m_hWnd),WM_LBUTTONVIEW,(WPARAM)this,0);
	CWnd::OnLButtonDown(nFlags, point);
}

int CHelpWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CBaseInner.SetWndTitle(L"帮助");
	// TODO:  在此添加您专用的创建代码

	return 0;
}
