// BaseLine.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DvisBaseManager.h"
#include "BaseLine.h"


// CBaseLine

IMPLEMENT_DYNAMIC(CBaseLine, CWnd)

CBaseLine::CBaseLine()
{

}

CBaseLine::~CBaseLine()
{
}


BEGIN_MESSAGE_MAP(CBaseLine, CWnd)
	ON_WM_NCDESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CBaseLine ��Ϣ�������



void CBaseLine::OnNcDestroy()
{
	CWnd::OnNcDestroy();
delete this;
	// TODO: �ڴ˴������Ϣ����������
}

void CBaseLine::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
::SendMessage(::GetParent(this->m_hWnd),WM_LBUTTONVIEW,(WPARAM)this,0);
	CWnd::OnLButtonDown(nFlags, point);
}

void CBaseLine::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	CRect rect;
	GetClientRect(rect);
	CBaseInner.Paint(dc,rect);
}

int CBaseLine::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CBaseInner.SetWndTitle(L"���߹���");
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}
