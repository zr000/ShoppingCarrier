// History.cpp : ʵ���ļ�
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



// CHistory ��Ϣ�������



void CHistory::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CWnd::OnPaint()

		CRect rect;
	GetClientRect(rect);
	CBaseInner.Paint(dc,rect);
}

int CHistory::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CBaseInner.SetWndTitle(L"��ʷ��ѯ");
	return 0;
}

void CHistory::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	::SendMessage(::GetParent(this->m_hWnd),WM_LBUTTONVIEW,(WPARAM)this,0);
	CWnd::OnLButtonDown(nFlags, point);
}

void CHistory::OnNcDestroy()
{
	
	CWnd::OnNcDestroy();
	delete this;
	// TODO: �ڴ˴������Ϣ����������
}
