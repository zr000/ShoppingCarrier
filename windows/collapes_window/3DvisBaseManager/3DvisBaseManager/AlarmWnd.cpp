// AlarmWnd.cpp : ʵ���ļ�
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



// CAlarmWnd ��Ϣ�������



void CAlarmWnd::OnNcDestroy()
{
	CWnd::OnNcDestroy();
delete this;
	// TODO: �ڴ˴������Ϣ����������
}

void CAlarmWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	CBaseInner.Paint(dc,rect);
}

void CAlarmWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	::SendMessage(::GetParent(this->m_hWnd),WM_LBUTTONVIEW,(WPARAM)this,0);
	CWnd::OnLButtonDown(nFlags, point);
}

int CAlarmWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	CBaseInner.SetWndTitle(L"����");
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}
