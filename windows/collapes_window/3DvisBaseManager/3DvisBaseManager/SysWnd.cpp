// SysWnd.cpp : ʵ���ļ�
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
	bret =  m_listIcon.AddIcon(IDI_ICON8, CRect(nxorg,ntop,nxorg+64,ntop+64), L"�û�") 
			&& m_listIcon.AddIcon(IDI_ICON6, CRect(nxorg+90,ntop,nxorg+90+64,ntop+64), L"ģ�Ϳ�")
			&& m_listIcon.AddIcon(IDI_ICON3, CRect(nxorg,ntop+nxspace,10+64,ntop+nxspace+64), L"����")
			&& m_listIcon.AddIcon(IDI_ICON4, CRect(nxorg+90,ntop+nxspace,nxorg+90+64,ntop+nxspace+64), L"��ѯ")
			&& m_listIcon.AddIcon(IDI_ICON2, CRect(nxorg,ntop+2*nxspace,10+64,ntop+2*nxspace+64), L"�༭")
			&& m_listIcon.AddIcon(IDI_ICON5, CRect(nxorg+90,ntop+2*nxspace,nxorg+90+64,ntop+2*nxspace+64), L"����")
			&& m_listIcon.AddIcon(IDI_ICON1, CRect(nxorg,ntop+3*nxspace,10+64,ntop+3*nxspace+64), L"����")
			&& m_listIcon.AddIcon(IDI_ICON7, CRect(nxorg+90,ntop+3*nxspace,nxorg+90+64,ntop+3*nxspace+64), L"�豸");



	return bret;
}

// CSysWnd ��Ϣ�������
void CSysWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()

	CRect rect;
	GetClientRect(rect);
	CBaseInner.Paint(dc,rect,&m_listIcon);
	
//	m_listIcon.DrawIcon(memdc.m_hDC);
	
}

void CSysWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	::SendMessage(::GetParent(this->m_hWnd),WM_LBUTTONVIEW,(WPARAM)this,0);
	__super::OnLButtonDown(nFlags, point);
}

void CSysWnd::OnNcDestroy()
{
	__super::OnNcDestroy();
	delete this;
	// TODO: �ڴ˴������Ϣ����������
}

int CSysWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	if(!InitSource())
		return -1;
	CBaseInner.SetWndTitle(L"ϵͳ����");
	return 0;
}
