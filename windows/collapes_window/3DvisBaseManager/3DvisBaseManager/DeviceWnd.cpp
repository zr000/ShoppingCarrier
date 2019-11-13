// DeviceWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DvisBaseManager.h"
#include "DeviceWnd.h"


// CDeviceWnd

IMPLEMENT_DYNAMIC(CDeviceWnd, CWnd)
HANDLE hicon;
CDeviceWnd::CDeviceWnd()
{

}

CDeviceWnd::~CDeviceWnd()
{
}


BEGIN_MESSAGE_MAP(CDeviceWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_NCDESTROY()
	ON_WM_CLOSE()
END_MESSAGE_MAP()



// CDeviceWnd ��Ϣ�������

int CDeviceWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// TODO:  �ڴ������ר�õĴ�������
	
	if(!InitSource())
		return -1;
	
	CBaseInner.SetWndTitle(L"�豸����");

}
BOOL CDeviceWnd::InitSource()
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
void CDeviceWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	CRect rect;
	GetClientRect(rect);
	
	
	//m_listIcon.DrawIcon(memdc.m_hDC);
	
	CBaseInner.Paint(dc,rect);
}

void CDeviceWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	::SendMessage(::GetParent(this->m_hWnd),WM_LBUTTONVIEW,(WPARAM)this,0);
	__super::OnLButtonDown(nFlags, point);
}

void CDeviceWnd::OnNcDestroy()
{
	__super::OnNcDestroy();
	
	delete this;
	// TODO: �ڴ˴������Ϣ����������
}

void CDeviceWnd::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	__super::OnClose();
}
