// SysWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "3DvisBaseManager.h"
#include "SysWnd.h"


// CSysWnd

IMPLEMENT_DYNAMIC(CSysWnd, CWnd)

CSysWnd::CSysWnd()
{

}

CSysWnd::~CSysWnd()
{
}


BEGIN_MESSAGE_MAP(CSysWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
END_MESSAGE_MAP()

BOOL CSysWnd::InitSource()
{
	int ntop = 40;
	int nxorg = 20;

	int nxspace = 100;
	
	BOOL bret = FALSE;
	bret =  m_listIcon.AddIcon(IDI_ICON8, CRect(nxorg,ntop,nxorg+64,ntop+64), L"用户") 
			&& m_listIcon.AddIcon(IDI_ICON6, CRect(nxorg+90,ntop,nxorg+90+64,ntop+64), L"模型库")
			&& m_listIcon.AddIcon(IDI_ICON3, CRect(nxorg,ntop+nxspace,10+64,ntop+nxspace+64), L"参数")
			&& m_listIcon.AddIcon(IDI_ICON4, CRect(nxorg+90,ntop+nxspace,nxorg+90+64,ntop+nxspace+64), L"查询")
			&& m_listIcon.AddIcon(IDI_ICON2, CRect(nxorg,ntop+2*nxspace,10+64,ntop+2*nxspace+64), L"编辑")
			&& m_listIcon.AddIcon(IDI_ICON5, CRect(nxorg+90,ntop+2*nxspace,nxorg+90+64,ntop+2*nxspace+64), L"管线")
			&& m_listIcon.AddIcon(IDI_ICON1, CRect(nxorg,ntop+3*nxspace,10+64,ntop+3*nxspace+64), L"报警")
			&& m_listIcon.AddIcon(IDI_ICON7, CRect(nxorg+90,ntop+3*nxspace,nxorg+90+64,ntop+3*nxspace+64), L"设备");



	return bret;
}

// CSysWnd 消息处理程序
void CSysWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CWnd::OnPaint()

	CRect rect;
	GetClientRect(rect);
	CBaseInner.Paint(dc,rect,&m_listIcon);
	
//	m_listIcon.DrawIcon(memdc.m_hDC);
	
}

void CSysWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::SendMessage(::GetParent(this->m_hWnd),WM_LBUTTONVIEW,(WPARAM)this,0);
	__super::OnLButtonDown(nFlags, point);
}

void CSysWnd::OnNcDestroy()
{
	__super::OnNcDestroy();
	delete this;
	// TODO: 在此处添加消息处理程序代码
}

int CSysWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	if(!InitSource())
		return -1;
	CBaseInner.SetWndTitle(L"系统管理");
	return 0;
}
