// LeftView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "3DvisBaseManager.h"
#include "LeftView.h"


// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CView)

CLeftView::CLeftView():
m_bShow(FALSE)
{

}

CLeftView::~CLeftView()
{
}

BEGIN_MESSAGE_MAP(CLeftView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(WM_LBUTTONVIEW,OnWndLButtonDown)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CLeftView ��ͼ

void CLeftView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
	CRect rect;
	GetClientRect(rect);
	if(!m_bShow)
	{
		m_wndContain.SetCollapesRect(rect);
		m_wndContain.SetActiveWnd(3);
		m_bShow = TRUE;
	}
	
	CBrush brush(RGB(31,31,31));
	pDC->FillRect(&rect, &brush);
}


// CLeftView ���

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CLeftView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CLeftView ��Ϣ�������

int CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	//CDeviceWnd* m_devWnd;
	//CBaseLine*  m_baseLineWnd;
	//CHistory*   m_histortyWnd;
	//CSysWnd*     m_sysWnd;
	//CAlarmWnd*  m_alarmWnd;
	//CHelpWnd*  m_helpWnd;

	m_devWnd = new CDeviceWnd();
	m_baseLineWnd = new CBaseLine();
	m_histortyWnd = new CHistory();
	m_sysWnd = new CSysWnd();
	m_alarmWnd = new CAlarmWnd();
	m_helpWnd = new CHelpWnd();

	CRect rect;
	GetClientRect(rect);

	m_wndContain.AddCollapesWnd(m_devWnd,this);
	m_wndContain.AddCollapesWnd(m_baseLineWnd,this);
	m_wndContain.AddCollapesWnd(m_histortyWnd,this);
	m_wndContain.AddCollapesWnd(m_sysWnd,this);
	m_wndContain.AddCollapesWnd(m_alarmWnd,this);
	m_wndContain.AddCollapesWnd(m_helpWnd,this);

	return 0;
}

void CLeftView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	//SIZE_MAXIMIZED
	// TODO: �ڴ˴������Ϣ����������
	CRect rect;
	GetClientRect(rect);
	
	m_wndContain.SetCollapesRect(rect);
}
LRESULT CLeftView::OnWndLButtonDown(WPARAM pParam,LPARAM)
{
	m_wndContain.OnLButtonDown((CWnd*)pParam);
	return 0;
}
BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ����ר�ô����/����û���
	cs.style |= WS_CLIPCHILDREN;					//��ֹ��˸
	
	return CView::PreCreateWindow(cs);
}
void CLeftView::OnDestroy()
{
	m_devWnd->SendMessage(WM_CLOSE);
	m_sysWnd->SendMessage(WM_CLOSE);
	m_histortyWnd->SendMessage(WM_CLOSE);
	CView::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
}
