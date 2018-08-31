// AlarmWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "3DvisBaseManager.h"
#include "AlarmWnd.h"


// CAlarmWnd

IMPLEMENT_DYNAMIC(CAlarmWnd, CWnd)

CAlarmWnd::CAlarmWnd()
{

}

CAlarmWnd::~CAlarmWnd()
{
}


BEGIN_MESSAGE_MAP(CAlarmWnd, CWnd)
	ON_WM_NCDESTROY()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CAlarmWnd 消息处理程序



void CAlarmWnd::OnNcDestroy()
{
	CWnd::OnNcDestroy();
delete this;
	// TODO: 在此处添加消息处理程序代码
}

void CAlarmWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	CBaseInner.Paint(dc,rect);
}

void CAlarmWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::SendMessage(::GetParent(this->m_hWnd),WM_LBUTTONVIEW,(WPARAM)this,0);
	CWnd::OnLButtonDown(nFlags, point);
}

int CAlarmWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CBaseInner.SetWndTitle(L"报警");
	// TODO:  在此添加您专用的创建代码

	return 0;
}
